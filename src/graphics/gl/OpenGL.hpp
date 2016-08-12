#ifndef __re_graphics_opengl_hpp_defined
#define __re_graphics_opengl_hpp_defined

#include <gl3/glew.h>
#include <gl3/wglew.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <string>
#include "../../LogFile.hpp"

#define GL_ERROR_CHECK(X) ::re::graphics::gl::error_check(__FILE__, __LINE__, X, __FUNCTION__)
#ifdef RE_DEBUG
#define RE_OGL(X) ((void)(((X), GL_ERROR_CHECK(#X)), 0))
#else
#define RE_OGL(X) ((void)(X))
#endif
#define _RE_OGL(X) X

namespace re
{
	namespace graphics
	{
		namespace gl
		{
			/** Checks for errors that occured in the last OpenGL call.
			@param[in] file: The source file in which the last OpenGL call occured.
			@param[in] line: The line of the last OpenGL call.
			@param[in] exp: The source string of the last OpenGL call.
			@param[in] function: The function in which the last OpenGL call occured. */
			void error_check(const char* file, int line, const char* exp, const char* function);
		}
	}
}

#endif