#ifndef __re_shader_hpp_defined
#define __re_shader_hpp_defined

#include "ShaderType.hpp"
#include "Handle.hpp"
#include "Binding.hpp"
#include "../../types.hpp"
#include "../../math/Vector.hpp"
#include "../../math/Matrix.hpp"
#include "../../util/Lookup.hpp"

namespace re
{
	namespace graphics
	{
		namespace gl
		{
			// no need to include the VertexArray header just for this.
			struct VertexElement;

			/** Compilation result of a shader. */
			struct ShaderCompilationResult
			{
				/** The log message from compiling. */
				string8_t log;
				/** Indicates the result of compiling. */
				bool success;
				/** Indicates whether the shader actually exists. */
				bool exists;
			};

			/** Compilation result of a program. */
			struct ProgramCompilationResult
			{
				/** The shaders' results. */
				util::Lookup<ShaderType, ShaderCompilationResult> results;
			};

			/** Program linkage result. */
			struct ProgramLinkResult
			{
				/** Log message. */
				string8_t log;
				/** Whether linking was succeeded. */
				bool success;
			};

			/** Represents a shader program that processes rendering calls.
				Use alloc() to allocate the shader on the GPU. To prevent memory leaks, call destroy() when you do not need the ShaderProgram anymore. It will not be called by the destructor. */
			class ShaderProgram : protected Handle
			{
				/** The currently active shader program.
					This is used to prevent redundant calls to activate shader programs. */
				static Binding s_bound;

				/** The handles of the shaders used by the program. */
				util::Lookup<ShaderType, Handle> m_shaders;
			public:
				/** The type representing the offset of the uniform variable in the shader program. */
				typedef int32_t uniform_t;

				/** Constructs a shader program and sets its handle and shaders to none. */
				ShaderProgram() = default;
				/** Moves a shader program from one instance to another, invalidating the source instance. */
				ShaderProgram(ShaderProgram &&move) = default;
				ShaderProgram &operator=(ShaderProgram &&) = default;

				/** Binds the shader program to the graphics pipeline.
					All render calls will be processed by the shader program until another one is used or it is destroyed. */
				void use();

				/** Returns whether the shader is currently used. */
				bool used() const;

				/** Unbinds the shader program from the graphics pipeline.
					The default OpenGL shader program will be used until another one is used. */
				static void unuse();

				/** Allocates a handle for the shader program. Does not allocate the shaders. */
				void create();
				/** Deletes the handle and sets it to none, if exists. Does not delete the shaders. */
				void destroy();

				/** Loads the given string onto the GPU as the source code of the given shader.
					This method allocates the shader if it didnt exist before on the GPU.
				@param[in] code:
					The source code of the shader.
				@param[in] shader:
					The ShaderType value indicating the shader.
				@return
					true on success, false on error. */
				bool load_from_string(char const * code, ShaderType shader);

				/** Loads the given file contents onto the GPU as the source code of the given shader.
					This method allocates the shader if it didnt exist before on the GPU.
					This method calls loadFromString() with the file contents of the given file.
				@param[in] filename:
					The file containing the source code of the shader.
				@param[in] shader:
					The ShaderType value indicating the shader.
				@return
					true on success, false on error. */
				bool load_from_file(char const * filename, ShaderType shader);

				/** Compiles all shaders.
				@param[out] result:
					The detailed compilation result. Pass `nullptr` if you do not want to get the results.
				@return
					true on success, false on error. */
				bool compile_shaders(ProgramCompilationResult* result);
				/** Deletes all shader handles and sets them to none, if they exist.
				Call this to prevent memory leaks. */
				void delete_shaders();

				/** Links the program.
					This must be called after all shaders are compiled.
				@tparam Vertex:
					The vertex type that is used for the 
				@param[out] result:
					The detailed linking result, or `nullptr`.
				@return
					`true` on success, `false` on error. */
				template<class Vertex>
				bool link_program(
					ProgramLinkResult* result);
				/** Links the program.
					This must be called after all shaders are compiled.
				@param[out] result:
					The detailed linking result, or `nullptr`.
				@return
					`true` on success, `false` on error. */
				bool link_program(
					ProgramLinkResult* result,
					VertexElement const * elements,
					size_t element_count);

				/** Validates the ShaderProgram.
				@param[out] result:
					The status message, or nullptr.
				@return
					true on success, false on error. */
				bool validate(string8_t *result);

				/** Returns the offset of the uniform with the given name within the program.
				@return
					-1 if not found, the offset of the uniform if found. */
				uniform_t get_uniform(char const * uniform);

				/** Finds the uniform with the given name and sets it to the given value.
					If it does not exist, this will do nothing. */
				bool set_uniform(char const * uniform, int32_t val);
				/** Sets the given uniform to the given value. */
				bool set_uniform(uniform_t uniform, int32_t val);

				/** Finds the uniform with the given name and sets it to the given value.
					If it does not exist, this will do nothing. */
				bool set_uniform(char const * uniform, float val);
				/** Sets the given uniform to the given value. */
				bool set_uniform(uniform_t uniform, float val);

				/** Finds the uniform with the given name and sets it to the given value.
					If it does not exist, this will do nothing. */
                bool set_uniform(char const * uniform, math::fvec2_t const& val);
				/** Sets the given uniform to the given value. */
                bool set_uniform(uniform_t uniform, math::fvec2_t const& val);

				/** Finds the uniform with the given name and sets it to the given value.
					If it does not exist, this will do nothing. */
                bool set_uniform(char const * uniform, math::fvec3_t const& val);
				/** Sets the given uniform to the given value. */
                bool set_uniform(uniform_t uniform, math::fvec3_t const& val);

				/** Finds the uniform with the given name and sets it to the given value.
					If it does not exist, this will do nothing. */
                bool set_uniform(char const * uniform, math::fvec4_t const& val);
				/** Sets the given uniform to the given value. */
                bool set_uniform(uniform_t uniform, math::fvec4_t const& val);

				/** Finds the uniform with the given name and sets it to the given value.
					If it does not exist, this will do nothing. */
                bool set_uniform(char const * uniform, math::fmat3x3_t const& val);
				/** Sets the given uniform to the given value. */
                bool set_uniform(uniform_t uniform, math::fmat3x3_t const& val);

				/** Finds the uniform with the given name and sets it to the given value.
					If it does not exist, this will do nothing. */
                bool set_uniform(char const * uniform, math::fmat4x4_t const& val);
				/** Sets the given uniform to the given value. */
                bool set_uniform(uniform_t uniform, math::fmat4x4_t const& rval);
			};
		}
	}
}


#endif
