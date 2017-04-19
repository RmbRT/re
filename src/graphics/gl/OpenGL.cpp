#include "OpenGL.hpp"
#include "../../types.hpp"
#include <cstdlib>

namespace re
{
	namespace graphics
	{
		namespace gl
		{
			static void gl_error_check(
				const char* file,
				int line,
				const char* exp,
				const char* function)
			{
				while(true)
				{
					GLenum error = glGetError();
					if(error!=GL_NO_ERROR)
					{
						string8_t _error("\n*** OpenGL error ***\nCode: ");
						switch(error)
						{
						case GL_INVALID_ENUM:{_error+="GL_INVALID_ENUM";} break;
						case GL_INVALID_OPERATION:{_error+="GL_INVALID_OPERATION";} break;
						case GL_INVALID_FRAMEBUFFER_OPERATION:{_error+="GL_INVALID_FRAMEBUFFER_OPERATION";} break;
						case GL_INVALID_INDEX:{_error+="GL_INVALID_INDEX";} break;
						case GL_INVALID_VALUE:{_error+="GL_INVALID_VALUE";} break;
						default:
							{
								char buffer[128];
								sprintf(buffer, "#%i (0x%x)", error, error);
								_error += buffer;
							} break;
						}

						_error += " in ::";
						_error += function;
						_error += "\nat ";
						_error += std::to_string(line).c_str();
						_error += " in File ";
						_error += file;
						_error += "\nLine: ";
						_error += exp;
						_error += "\n";

						RE_ASSERTION_FAILURE(_error.c_str());
					}
					else
						break;
				}
			}
		}
	}
}