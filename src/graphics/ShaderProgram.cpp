#include "ShaderProgram.hpp"
#include "OpenGL.hpp"
#include "AttribLocation.hpp"
#include "../modules/GLObjectManager.hpp"

#include <fstream>
#include <streambuf>
#include <vector>

#define RE_MAT_TRANSPOSE false

re::uint32_t re::graphics::ShaderProgram::used = 0;

namespace re
{
	namespace graphics
	{
		ShaderProgram::ShaderProgram(): id(0)
		{
			invalidate();
		}
		ShaderProgram::ShaderProgram(ShaderProgram &&move) : id(move.id) {
			for(unsigned i = 0; i<ST_COUNT; i++)
				shaders[i] = move.shaders[i];
			move.invalidate();
		}
		ShaderProgram::~ShaderProgram()
		{
			destroy();
		}
		void ShaderProgram::invalidate()
		{
			id = 0;
			for(auto &i: shaders) i = 0;
		}
		void ShaderProgram::use()
		{
			if(used != id)
			{
				RE_OGL("Previous Error.");
				RE_OGL(glUseProgram(id));
				used = id;
			}
		}

		void ShaderProgram::unuse()
		{
			if(used)
			{
				RE_OGL(glUseProgram(0));
				used = 0;
			}
		}

		void ShaderProgram::create()
		{
			destroy();
			RE_OGL(id = glCreateProgram());
		}

		void ShaderProgram::destroy()
		{
			deleteShaders();
			RE_OGL(glDeleteProgram(id));
			id = 0;
		}

		bool ShaderProgram::loadFromString(const char* code, ShaderType shader)
		{
			if(!shaders[int(shader)])
			{
				GLenum shader_type = GL_INVALID_ENUM;
				switch(shader)
				{
				case ShaderType::ST_VERTEX:
					{
						shader_type = GL_VERTEX_SHADER;
					} break;
				case ShaderType::ST_FRAGMENT:
					{
						shader_type = GL_FRAGMENT_SHADER;
					} break;
				case ShaderType::ST_GEOMETRY:
					{
						shader_type = GL_GEOMETRY_SHADER;
					} break;
				case ShaderType::ST_TESS_CONTROL:
					{
						shader_type = GL_TESS_CONTROL_SHADER;
					} break;
				case ShaderType::ST_TESS_EVALUATION:
					{
						shader_type = GL_TESS_EVALUATION_SHADER;
					} break;
				default:
					{
						RE_ASSERTION_FAILURE("Unknown ShaderType!");
					} break;
				}
				shaders[int(shader)] = glCreateShader(shader_type);
			}
			
			GLint len = strlen(code);
			RE_OGL(glShaderSource(shaders[int(shader)], 1, &code, &len));

			return true;
		}

		bool ShaderProgram::loadFromFile(const char* filename, ShaderType shader)
		{
			std::ifstream t(filename);
			if(!t.is_open())
				return false;

			std::string str;

			t.seekg(0, std::ios::end);   
			str.reserve(t.tellg());
			t.seekg(0, std::ios::beg);

			str.assign((std::istreambuf_iterator<char>(t)),
            std::istreambuf_iterator<char>());

			return loadFromString(str.c_str(), shader);
		}

		bool ShaderProgram::compileShaders(ShaderCompilationResult* result)
		{
			bool anyFail = false;

			for(int i = 0; i<ST_COUNT; i++)
			{
				if(result)
				{
					result->exists[i] = shaders[i] != 0;
					result->log[i].clear();
					result->success[i] = false;
				}
				if(!shaders[i])
					continue;
				RE_OGL(glCompileShader(shaders[i]));
			}
			for(int i = 0; i<ST_COUNT; i++)
			{
				if(!shaders[i])
					continue;
				GLint success = 0;
				RE_OGL(glGetShaderiv(shaders[i], GL_COMPILE_STATUS, &success));
				LogFile::GetInst()->writefln("CompileStatus %i: %i", i, success);
				if(!success)
					anyFail = true;
				if(result)
				{
					GLint logSize = 0;
					RE_OGL(glGetShaderiv(shaders[i], GL_INFO_LOG_LENGTH, &logSize));
					std::vector<GLchar> _log(logSize);
					RE_OGL(glGetShaderInfoLog(shaders[i], logSize, nullptr, &_log[0]));
				
					result->log[i].assign(_log.data());
					result->success[i] = success == GL_TRUE;
				}
				if(success)
					RE_OGL(glAttachShader(id, shaders[i]));
			}
			return !anyFail;
		}

		bool ShaderProgram::linkProgram(ProgramLinkResult* result)
		{
			RE_OGL(glBindAttribLocation(id, (int)AttribLocation::AL_POSITION, AttributeNames[(int)AttribLocation::AL_POSITION].c_str()));
			RE_OGL(glBindAttribLocation(id, (int)AttribLocation::AL_NORMAL, AttributeNames[(int)AttribLocation::AL_NORMAL].c_str()));
			RE_OGL(glBindAttribLocation(id, (int)AttribLocation::AL_COLOR, AttributeNames[(int)AttribLocation::AL_COLOR].c_str()));
			RE_OGL(glBindAttribLocation(id, (int)AttribLocation::AL_TEXCOORD, AttributeNames[(int)AttribLocation::AL_TEXCOORD].c_str()));

			RE_ASSERT(id);

			/*for(auto shader: shaders)
			{
				if(shader)
				{
					RE_OGL(glAttachShader(id, shader));
				}
			}*/

			RE_OGL(glLinkProgram(id));
			GLint isLinked = 0;
			RE_OGL(glGetProgramiv(id, GL_LINK_STATUS, &isLinked));
			
			LogFile::GetInst()->writefln("LinkStatus: %i (%i, %s)", isLinked, glGetError(), glewGetErrorString(glGetError()));

			if(result)
			{
				GLint logSize = 0;
				RE_OGL(glGetProgramiv(id, GL_INFO_LOG_LENGTH, &logSize));
				if(logSize)
				{
					std::vector<GLchar> _log(logSize);
					RE_OGL(glGetProgramInfoLog(id, logSize, nullptr, &_log[0]));
					_log.push_back(0);
					result->log.assign(&_log[0]);
				}
				else
					result->log.assign("");
				result->success = isLinked == GL_TRUE;
			}

			for(int i = 0; i<ST_COUNT; i++)
			{
				if(!shaders[i])
					continue;

				RE_OGL(glDetachShader(id, shaders[i]));
			}
			deleteShaders();
			return isLinked == GL_TRUE;
		}

		bool ShaderProgram::validate(string *result)
		{
			RE_ASSERT(id);
			RE_OGL(glValidateProgram(id));
			GLint success;
			RE_OGL(glGetProgramiv(id, GL_VALIDATE_STATUS, &success));
			if(result)
			{
				GLint logSize = 0;
				RE_OGL(glGetProgramiv(id, GL_INFO_LOG_LENGTH, &logSize));
				if(logSize)
				{
					std::vector<GLchar> _log(logSize);
					RE_OGL(glGetProgramInfoLog(id, logSize, nullptr, &_log[0]));
					result->assign(&_log[0]);
				}
				else
					result->assign("");
			}
			return success == GL_TRUE;
		}

		void ShaderProgram::deleteShaders()
		{
			for(int i = 0; i<ST_COUNT; i++)
			{
				if(!shaders[i])
					continue;
				RE_OGL(glDeleteShader(shaders[i]));
				shaders[i] = 0;
			}
		}

		bool ShaderProgram::isUsed()
		{
			return (used == id) && id;
		}

		ShaderProgram::uniform_t ShaderProgram::getUniform(const char* uniform)
		{
			GLint temp;
			RE_OGL(temp = glGetUniformLocation(id, uniform));
			return temp;
		}

		/*Int32*/
		bool ShaderProgram::setUniform(const char* uniform, int32_t val)
		{
			if(!isUsed())
				return false;
			uniform_t _uniform = getUniform(uniform);
			if(-1 == _uniform)
				return false;
			RE_OGL(glUniform1i(_uniform, val));
			return true;
		}

		bool ShaderProgram::setUniform(ShaderProgram::uniform_t uniform, int32_t val)
		{
			if(!isUsed() || (-1 == uniform))
				return false;

			RE_OGL(glUniform1i(uniform, val));
			return true;
		}
		
		/*float*/
		bool ShaderProgram::setUniform(const char* uniform, float val)
		{
			if(!isUsed())
				return false;
			uniform_t _uniform = getUniform(uniform);
			if(-1 == _uniform)
				return false;
			RE_OGL(glUniform1f(_uniform, val));
			return true;
		}

		bool ShaderProgram::setUniform(ShaderProgram::uniform_t uniform, float val)
		{
			if(!isUsed() || (-1 == uniform))
				return false;

			RE_OGL(glUniform1f(uniform, val));
			return true;
		}

		/*fvec2*/
		bool ShaderProgram::setUniform(const char* uniform, const math::fvec2 &val)
		{
			if(!isUsed())
				return false;
			uniform_t _uniform = getUniform(uniform);
			if(-1 == _uniform)
				return false;
			/*Vector to float[] operator!*/
			RE_OGL(glUniform2fv(_uniform, 1, val));
			return true;
		}

		bool ShaderProgram::setUniform(ShaderProgram::uniform_t uniform, const math::fvec2 &val)
		{
			if(!isUsed() || (-1 == uniform))
				return false;

			/*Vector to float[] operator!*/
			RE_OGL(glUniform2fv(uniform, 1, val));
			return true;
		}

		/*fvec3*/
		bool ShaderProgram::setUniform(const char* uniform, const math::fvec3 &val)
		{
			if(!isUsed())
				return false;
			uniform_t _uniform = getUniform(uniform);
			if(-1 == _uniform)
				return false;
			/*Vector to float[] operator!*/
			RE_OGL(glUniform3fv(_uniform, 1, val));
			return true;
		}

		bool ShaderProgram::setUniform(ShaderProgram::uniform_t uniform, const math::fvec3 &val)
		{
			if(!isUsed() || (-1 == uniform))
				return false;

			/*Vector to float[] operator!*/
			RE_OGL(glUniform3fv(uniform, 1, val));
			return true;
		}

		/*fvec4*/
		bool ShaderProgram::setUniform(const char* uniform, const math::fvec4 &val)
		{
			if(!isUsed())
				return false;
			uniform_t _uniform = getUniform(uniform);
			if(-1 == _uniform)
				return false;
			/*Vector to float[] operator!*/
			RE_OGL(glUniform4fv(_uniform, 1, val));
			return true;
		}

		bool ShaderProgram::setUniform(ShaderProgram::uniform_t uniform, const math::fvec4 &val)
		{
			if(!isUsed() || (-1 == uniform))
				return false;

			/*Vector to float[] operator!*/
			RE_OGL(glUniform4fv(uniform, 1, val));
			return true;
		}

		/*fmat3x3*/
		bool ShaderProgram::setUniform(const char* uniform, const math::fmat3x3 &val)
		{
			if(!isUsed())
				return false;
			uniform_t _uniform = getUniform(uniform);
			if(-1 == _uniform)
				return false;
			/*Vector to float[] operator!*/
			RE_OGL(glUniformMatrix3fv(_uniform, 1, RE_MAT_TRANSPOSE, val.v0));
			return true;
		}

		bool ShaderProgram::setUniform(ShaderProgram::uniform_t uniform, const math::fmat3x3 &val)
		{
			if(!isUsed() || (-1 == uniform))
				return false;

			/*Vector to float[] operator!*/
			RE_OGL(glUniformMatrix3fv(uniform, 1, RE_MAT_TRANSPOSE, val.v0));
			return true;
		}

		/*fmat4x4*/
		bool ShaderProgram::setUniform(const char* uniform, const math::fmat4x4 &val)
		{
			if(!isUsed())
				return false;
			uniform_t _uniform = getUniform(uniform);
			if(-1 == _uniform)
				return false;
			/*Vector to float[] operator!*/
			RE_OGL(glUniformMatrix4fv(_uniform, 1, RE_MAT_TRANSPOSE, val.v0));
			return true;
		}

		bool ShaderProgram::setUniform(ShaderProgram::uniform_t uniform, const math::fmat4x4 &val)
		{
			if(!isUsed() || (-1 == uniform))
				return false;

			/*Vector to float[] operator!*/
			RE_OGL(glUniformMatrix4fv(uniform, 1, RE_MAT_TRANSPOSE, val.v0));
			return true;
		}

	}
}