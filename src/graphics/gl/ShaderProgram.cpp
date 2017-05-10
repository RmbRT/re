#include "ShaderProgram.hpp"
#include "VertexArray.hpp"
#include "OpenGL.hpp"

#include <fstream>
#include <streambuf>
#include <vector>

#include <cstring>

#define RE_MAT_TRANSPOSE false

re::graphics::gl::Binding re::graphics::gl::ShaderProgram::s_bound;

static re::graphics::gl::ShaderProgram::uniform_t const kInvalid = -1;

namespace re
{
	namespace graphics
	{
		namespace gl
		{
			void ShaderProgram::use()
			{
				if(!s_bound.bound(handle()))
				{
					RE_OGL("Previous Error.");
					RE_OGL(glUseProgram(handle()));
					s_bound.bind(handle());
				}
			}

			void ShaderProgram::unuse()
			{
				if(!s_bound.empty())
				{
					RE_OGL(glUseProgram(0));
					s_bound.unbind();
				}
			}

			void ShaderProgram::create()
			{
				destroy();
				RE_OGL(set_handle(glCreateProgram()));
			}

			void ShaderProgram::destroy()
			{
				delete_shaders();
				RE_OGL(glDeleteProgram(handle()));
				null_handle();
			}

			bool ShaderProgram::load_from_string(
				char const * code,
				ShaderType shader)
			{
				if(!m_shaders[shader].exists())
				{
					static util::Lookup<ShaderType, GLenum> const k_lookup = {
						{ ShaderType::kVertex,  GL_VERTEX_SHADER },
						{ ShaderType::kFragment, GL_FRAGMENT_SHADER },
						{ ShaderType::kGeometry, GL_GEOMETRY_SHADER },
						{ ShaderType::kTesselationControl, GL_TESS_CONTROL_SHADER },
						{ ShaderType::kTesselationEvaluation, GL_TESS_EVALUATION_SHADER }
					};
					RE_OGL(m_shaders[shader].set_handle(glCreateShader(k_lookup[shader])));
				}

				GLint len = std::strlen(code);
				RE_OGL(glShaderSource(m_shaders[shader].handle(), 1, &code, &len));

				return true;
			}

			bool ShaderProgram::load_from_file(
				char const * filename,
				ShaderType shader)
			{
				std::ifstream t(filename);
				if(!t.is_open())
					return false;

				std::string str;

				t.seekg(0, std::ios::end);
				str.reserve(t.tellg());
				t.seekg(0, std::ios::beg);

				str.assign(std::istreambuf_iterator<char>(t),
					std::istreambuf_iterator<char>());

				return load_from_string(str.c_str(), shader);
			}

			bool ShaderProgram::compile_shaders(
				ProgramCompilationResult * result)
			{
				bool anyFail = false;

				for(int i = 0; i<RE_COUNT(ShaderType); i++)
				{
					if(result)
					{
						result->results[i].exists = m_shaders[i].exists();
						result->results[i].log.clear();
						result->results[i].success = false;
					}
					if(!m_shaders[i].exists())
						continue;
					RE_OGL(glCompileShader(m_shaders[i].handle()));
				}

				for(int i = 0; i<RE_COUNT(ShaderType); i++)
				{
					if(!m_shaders[i].exists())
						continue;
					GLint success = 0;
					RE_OGL(glGetShaderiv(m_shaders[i].handle(), GL_COMPILE_STATUS, &success));
					RE_LOG("CompileStatus %i: %i", i, success);
					if(!success)
						anyFail = true;
					if(result)
					{
						GLint logSize = 0;
						RE_OGL(glGetShaderiv(m_shaders[i].handle(), GL_INFO_LOG_LENGTH, &logSize));
						result->results[i].log.resize(logSize);
						RE_OGL(glGetShaderInfoLog(m_shaders[i].handle(), logSize, nullptr, result->results[i].log.c_data()));

						result->results[i].success = success == GL_TRUE;
					}
					if(success)
						RE_OGL(glAttachShader(handle(), m_shaders[i].handle()));
				}
				return !anyFail;
			}

			bool ShaderProgram::link_program(
				ProgramLinkResult* result,
				VertexElement const * elements,
				size_t element_count)
			{
				RE_DBG_ASSERT(exists());

				for(size_t i = 0; i < element_count; i++)
				{
					RE_OGL(glBindAttribLocation(handle(), i, elements[i].name));
				}

				/*for(auto shader: shaders)
				{
					if(shader)
					{
						RE_OGL(glAttachShader(id, shader));
					}
				}*/

				RE_OGL(glLinkProgram(handle()));
				GLint isLinked = 0;
				RE_OGL(glGetProgramiv(handle(), GL_LINK_STATUS, &isLinked));

				GLenum error = glGetError();
				RE_LOG("LinkStatus: %i (%i, %s)", isLinked, error, glewGetErrorString(error));

				if(result)
				{
					GLint logSize = 0;
					RE_OGL(glGetProgramiv(handle(), GL_INFO_LOG_LENGTH, &logSize));
					if(logSize)
					{
						result->log.resize(logSize);
						RE_OGL(glGetProgramInfoLog(handle(), logSize, nullptr, result->log.c_data()));
					}
					else
						result->log.clear();
					result->success = isLinked == GL_TRUE;
				}

				for(int i = 0; i<RE_COUNT(ShaderType); i++)
				{
					if(!m_shaders[i].exists())
						continue;

					RE_OGL(glDetachShader(handle(), m_shaders[i].handle()));
				}

				delete_shaders();

				return isLinked == GL_TRUE;
			}

			bool ShaderProgram::validate(
				string8_t *result)
			{
				RE_DBG_ASSERT(exists());
				RE_OGL(glValidateProgram(handle()));
				GLint success;
				RE_OGL(glGetProgramiv(handle(), GL_VALIDATE_STATUS, &success));
				if(result)
				{
					GLint logSize = 0;
					RE_OGL(glGetProgramiv(handle(), GL_INFO_LOG_LENGTH, &logSize));
					if(logSize)
					{
						result->resize(logSize);
						RE_OGL(glGetProgramInfoLog(handle(), logSize, nullptr, result->c_data()));
					}
					else
						result->clear();
				}
				return success == GL_TRUE;
			}

			void ShaderProgram::delete_shaders()
			{
				for(int i = 0; i<RE_COUNT(ShaderType); i++)
				{
					if(!m_shaders[i].exists())
						continue;
					RE_OGL(glDeleteShader(m_shaders[i].handle()));
					m_shaders[i].null_handle();
				}
			}

			bool ShaderProgram::used() const
			{
				RE_DBG_ASSERT(exists());
				return s_bound.bound(handle());
			}

			ShaderProgram::uniform_t ShaderProgram::get_uniform(
				char const * uniform)
			{
				GLint temp;
				RE_OGL(temp = glGetUniformLocation(handle(), uniform));
				return temp;
			}

			/*Int32*/
			bool ShaderProgram::set_uniform(
				char const * uniform,
				int32_t val)
			{
				RE_DBG_ASSERT(exists());
				RE_DBG_ASSERT(used());

				uniform_t _uniform = get_uniform(uniform);
				if(kInvalid == _uniform)
					return false;
				RE_OGL(glUniform1i(_uniform, val));
				return true;
			}

			bool ShaderProgram::set_uniform(
				ShaderProgram::uniform_t uniform,
				int32_t val)
			{
				RE_DBG_ASSERT(exists());
				RE_DBG_ASSERT(used());

				if(kInvalid == uniform)
					return false;

				RE_OGL(glUniform1i(uniform, val));
				return true;
			}

			/*float*/
			bool ShaderProgram::set_uniform(
				char const * uniform,
				float val)
			{
				RE_DBG_ASSERT(exists());
				RE_DBG_ASSERT(used());

				uniform_t _uniform = get_uniform(uniform);
				if(kInvalid == _uniform)
					return false;
				RE_OGL(glUniform1f(_uniform, val));
				return true;
			}

			bool ShaderProgram::set_uniform(
				ShaderProgram::uniform_t uniform,
				float val)
			{
				RE_DBG_ASSERT(exists());
				RE_DBG_ASSERT(used());

				if(kInvalid == uniform)
					return false;

				RE_OGL(glUniform1f(uniform, val));
				return true;
			}

			/*fvec2*/
			bool ShaderProgram::set_uniform(
				char const * uniform,
				math::fvec2_t const& val)
			{
				RE_DBG_ASSERT(exists());
				RE_DBG_ASSERT(used());

				uniform_t _uniform = get_uniform(uniform);
				if(kInvalid == _uniform)
					return false;
				/*Vector to float[] operator!*/
				RE_OGL(glUniform2fv(_uniform, 1, val));
				return true;
			}

			bool ShaderProgram::set_uniform(
				ShaderProgram::uniform_t uniform,
				math::fvec2_t const& val)
			{
				RE_DBG_ASSERT(exists());
				RE_DBG_ASSERT(used());

				if(kInvalid == uniform)
					return false;

				/*Vector to float[] operator!*/
				RE_OGL(glUniform2fv(uniform, 1, val));
				return true;
			}

			/*fvec3*/
			bool ShaderProgram::set_uniform(
				char const * uniform,
				math::fvec3_t const& val)
			{
				RE_DBG_ASSERT(exists());
				RE_DBG_ASSERT(used());

				uniform_t _uniform = get_uniform(uniform);
				if(kInvalid == _uniform)
					return false;
				/*Vector to float[] operator!*/
				RE_OGL(glUniform3fv(_uniform, 1, val));
				return true;
			}

			bool ShaderProgram::set_uniform(
				ShaderProgram::uniform_t uniform,
				math::fvec3_t const& val)
			{
				RE_DBG_ASSERT(exists());
				RE_DBG_ASSERT(used());

				if(kInvalid == uniform)
					return false;

				/*Vector to float[] operator!*/
				RE_OGL(glUniform3fv(uniform, 1, val));
				return true;
			}

			/*fvec4*/
			bool ShaderProgram::set_uniform(
				char const * uniform,
				math::fvec4_t const& val)
			{
				RE_DBG_ASSERT(exists());
				RE_DBG_ASSERT(used());

				uniform_t _uniform = get_uniform(uniform);
				if(kInvalid == _uniform)
					return false;
				/*Vector to float[] operator!*/
				RE_OGL(glUniform4fv(_uniform, 1, val));
				return true;
			}

			bool ShaderProgram::set_uniform(
				ShaderProgram::uniform_t uniform,
				math::fvec4_t const& val)
			{
				RE_DBG_ASSERT(exists());
				RE_DBG_ASSERT(used());

				if(kInvalid == uniform)
					return false;

				/*Vector to float[] operator!*/
				RE_OGL(glUniform4fv(uniform, 1, val));
				return true;
			}

			/*fmat3x3*/
			bool ShaderProgram::set_uniform(
				char const * uniform,
				math::fmat3x3_t const& val)
			{
				RE_DBG_ASSERT(exists());
				RE_DBG_ASSERT(used());

				uniform_t _uniform = get_uniform(uniform);
				if(kInvalid == _uniform)
					return false;
				/*Vector to float[] operator!*/
				RE_OGL(glUniformMatrix3fv(_uniform, 1, RE_MAT_TRANSPOSE, val.v0));
				return true;
			}

			bool ShaderProgram::set_uniform(
				ShaderProgram::uniform_t uniform,
				math::fmat3x3_t const& val)
			{
				RE_DBG_ASSERT(exists());
				RE_DBG_ASSERT(used());

				if(kInvalid == uniform)
					return false;

				/*Vector to float[] operator!*/
				RE_OGL(glUniformMatrix3fv(uniform, 1, RE_MAT_TRANSPOSE, val.v0));
				return true;
			}

			/*fmat4x4*/
			bool ShaderProgram::set_uniform(
				char const * uniform,
				math::fmat4x4_t const& val)
			{
				RE_DBG_ASSERT(exists());
				RE_DBG_ASSERT(used());

				uniform_t _uniform = get_uniform(uniform);
				if(kInvalid == _uniform)
					return false;
				/*Vector to float[] operator!*/
				RE_OGL(glUniformMatrix4fv(_uniform, 1, RE_MAT_TRANSPOSE, val.v0));
				return true;
			}

			bool ShaderProgram::set_uniform(
				ShaderProgram::uniform_t uniform,
				math::fmat4x4_t const& val)
			{
				RE_DBG_ASSERT(exists());
				RE_DBG_ASSERT(used());

				if(kInvalid == uniform)
					return false;

				/*Vector to float[] operator!*/
				RE_OGL(glUniformMatrix4fv(uniform, 1, RE_MAT_TRANSPOSE, val.v0));
				return true;
			}
		}
	}
}