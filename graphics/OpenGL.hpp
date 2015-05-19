#ifndef __re_graphics_opengl_hpp_defined
#define __re_graphics_opengl_hpp_defined

#include <gl3\glew.h>
#include <gl3\wglew.h>
#define GLFW_INCLUDE_NONE
#include <glfw\glfw3.h>
#include <string>
#include "../LogFile.hpp"

#define GL_ERROR_CHECK(X) gl_error_check(__FILE__, __LINE__, X, __FUNCTION__)
#ifdef RE_DEBUG
#define RE_OGL(X) ((void)(((X), GL_ERROR_CHECK(#X)), 0))
#else
#define RE_OGL(X) ((void)(X))
#endif
#define _RE_OGL(X) X

static void gl_error_check(const char* file, int line, const char* exp, const char* function)
{
	while(true)
	{
		GLenum error = glGetError();
		if(error!=GL_NO_ERROR)
		{
			std::string _error("\n*** OpenGL error ***\nCode: ");
			switch(error)
			{
			case GL_INVALID_ENUM:{_error+="GL_INVALID_ENUM";} break;
			case GL_INVALID_OPERATION:{_error+="GL_INVALID_OPERATION";} break;
			case GL_INVALID_FRAMEBUFFER_OPERATION:{_error+="GL_INVALID_FRAMEBUFFER_OPERATION";} break;
			case GL_INVALID_INDEX:{_error+="GL_INVALID_INDEX";} break;
			case GL_INVALID_VALUE:{_error+="GL_INVALID_VALUE";} break;
			default:{_error+="#";_error+=std::to_string(error);} break;
			}
			_error += " in ::";
			_error += function;
			_error += "\nat ";
			_error += std::to_string(line);
			_error += " in File ";
			_error += file;
			_error += "\nLine: ";
			_error += exp;
			_error+="\n";
			RE_ASSERTION_FAILURE(_error.c_str());
		}
		else
			break;
	}
}


#endif