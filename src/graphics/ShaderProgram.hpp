#ifndef __re_shader_hpp_defined
#define __re_shader_hpp_defined

#include "../types.hpp"
#include "../math/Vector.hpp"
#include "../math/Matrix.hpp"
#include "ShaderType.hpp"

namespace re
{
	namespace graphics
	{
		struct ShaderCompilationResult
		{
			/*The log message from compiling.*/
			string log[ST_COUNT];
			/*Indicates the result of compiling.*/
			bool success[ST_COUNT];
			/*Indicates whether the shader actually exists.*/
			bool exists[ST_COUNT];
		};
		struct ProgramLinkResult
		{
			string log;
			bool success;
		};

		/*Represents a shader program that processes rendering calls.
		Use alloc() to allocate the shader on the GPU.
		To prevent memory leaks, call destroy() when you do not need the ShaderProgram anymore. It will not be called by the destructor!*/
		class ShaderProgram
		{
			/*The handle of the shader program.*/
			uint32 id;
			/*The handles of the shaders used by the program.*/
			uint32 shaders[ST_COUNT];
		public:
			/*The type representing the offset of the uniform variable in the shader program.*/
			typedef int32 uniform_t;

			/*Constructs a shader program and sets its handle and shaders to none.*/
			ShaderProgram();
			/*Moves a shader program from one instance to another, invalidating the source instance.*/
			ShaderProgram(ShaderProgram &&move);
			/*Destroys a shader program and deallocates the memory used by it and the shaders on the GPU.*/
			~ShaderProgram();

			/*Binds the shader program to the graphics pipeline.
			All render calls will be processed by the shader program until another one is used or it is destroyed.*/
			void use();

			/*Returns whether the shader is currently used.*/
			bool isUsed();

			/*Unbinds the shader program from the graphics pipeline.
			The default OpenGL shader program will be used until another one is used.*/
			static void unuse();

			/*Allocates a handle for the shader program. Does not allocate the shaders.*/
			void create();
			/*Deletes the handle and sets it to none, if exists. Does not delete the shaders.*/
			void destroy();

			/*Loads the given string onto the GPU as the source code of the given shader.
			This method allocates the shader if it didnt exist before on the GPU.
			@param[in] code: The source code of the shader.
			@param[in] shader: The @{re::graphics::ShaderType} value indicating the shader.
			@return: true on success, false on error.*/
			bool loadFromString(const char* code, ShaderType shader);
			
			/*Loads the given file contents onto the GPU as the source code of the given shader.
			This method allocates the shader if it didnt exist before on the GPU.
			This method calls loadFromString() with the file contents of the given file.
			@param[in] filename: The file containing the source code of the shader.
			@param[in] shader: The @{re::graphics::ShaderType} value indicating the shader.
			@return: true on success, false on error.*/
			bool loadFromFile(const char* filename, ShaderType shader);

			/*Compiles all shaders.
			@param[out] result: The CompilationResult. Pass nullptr if you do not want to get the results.
			@return: true on success, false on error.*/
			bool compileShaders(ShaderCompilationResult* result);
			/*Deletes all shader handles and sets them to none, if they exist.
			Call this to prevent memory leaks!*/
			void deleteShaders();
			/*Links the program. This must be called after all shaders are compiled.
			@return: true on success, false on error.*/
			bool linkProgram(ProgramLinkResult* result);

			/*Validates the ShaderProgram.*/
			bool validate(string *result);
			/*Returns the offset of the uniform with the given name within the program.
			@return: -1 if not found, the offset of the uniform if found.*/
			uniform_t getUniform(const char* uniform);

			/*Finds the uniform with the given name and sets it to the given value.
			If it does not exist, this will do nothing.*/
			bool setUniform(const char* uniform, int32 val);
			/*Sets the given uniform to the given value.*/
			bool setUniform(uniform_t uniform, int32 val);

			/*Finds the uniform with the given name and sets it to the given value.
			If it does not exist, this will do nothing.*/
			bool setUniform(const char* uniform, float val);
			/*Sets the given uniform to the given value.*/
			bool setUniform(uniform_t uniform, float val);

			/*Finds the uniform with the given name and sets it to the given value.
			If it does not exist, this will do nothing.*/
			bool setUniform(const char* uniform, const math::fvec2 &val);
			/*Sets the given uniform to the given value.*/
			bool setUniform(uniform_t uniform, const math::fvec2 &val);

			/*Finds the uniform with the given name and sets it to the given value.
			If it does not exist, this will do nothing.*/
			bool setUniform(const char* uniform, const math::fvec3 &val);
			/*Sets the given uniform to the given value.*/
			bool setUniform(uniform_t uniform, const math::fvec3 &val);

			/*Finds the uniform with the given name and sets it to the given value.
			If it does not exist, this will do nothing.*/
			bool setUniform(const char* uniform, const math::fvec4 &val);
			/*Sets the given uniform to the given value.*/
			bool setUniform(uniform_t uniform, const math::fvec4 &val);

			/*Finds the uniform with the given name and sets it to the given value.
			If it does not exist, this will do nothing.*/
			bool setUniform(const char* uniform, const math::fmat3x3 &val);
			/*Sets the given uniform to the given value.*/
			bool setUniform(uniform_t uniform, const math::fmat3x3 &val);

			/*Finds the uniform with the given name and sets it to the given value.
			If it does not exist, this will do nothing.*/
			bool setUniform(const char* uniform, const math::fmat4x4 &val);
			/*Sets the given uniform to the given value.*/
			bool setUniform(uniform_t uniform, const math::fmat4x4 &rval);

		private:
			/*Invalidates the program and shader handles. This function does not release any memory!*/
			void invalidate();

			/*The currently used shader program. This is used to prevent */
			static uint32 used;
		};
	}
}


#endif