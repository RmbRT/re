#ifndef __re_exception_hpp_defined
#define __re_exception_hpp_defined

#include <exception>

namespace re
{
	class REException : public std::exception
	{
		int line;
		const char* file;
		const char* msg;
		std::exception* prev;
	public:
		REException(const char* msg, const char* file, int line);
		REException(const char* msg, const char* file, int line, std::exception* prev);

		const char* what() const override;
	};
}

#endif