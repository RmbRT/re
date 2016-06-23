namespace re
{
	namespace graphics
	{
		namespace gl
		{
			static void gl_error_check
			{
				while(true)
				{
					GLenum error = glGetError();
					if(error!=GL_NO_ERROR)
					{
						string _error("\n*** OpenGL error ***\nCode: ");
						switch(error)
						{
						case GL_INVALID_ENUM:{_error+="GL_INVALID_ENUM";} break;
						case GL_INVALID_OPERATION:{_error+="GL_INVALID_OPERATION";} break;
						case GL_INVALID_FRAMEBUFFER_OPERATION:{_error+="GL_INVALID_FRAMEBUFFER_OPERATION";} break;
						case GL_INVALID_INDEX:{_error+="GL_INVALID_INDEX";} break;
						case GL_INVALID_VALUE:{_error+="GL_INVALID_VALUE";} break;
						default:{_error+=string("#%i (0x%x)", error);} break;
						}

						_error += string(" in ::%s\nat %u in File %s\nLine: %s\n", function, line, file, exp);

						RE_ASSERTION_FAILURE(_error.c_str());
					}
					else
						break;
				}
			}
		}
	}
}