#include "Exception.hpp"
#include "types.hpp"

namespace re
{
	REException::REException(const char* msg, const char* file, int line):
		msg(msg), file(file), line(line), prev(nullptr)	{	}
	REException::REException(const char* msg, const char* file, int line, std::exception* prev):
		msg(msg), file(file), line(line), prev(prev)	{	}

	const char* REException::what() const
	{
		string temp("REException '");
		temp.append(msg);
		temp.append("' in ");
		temp.append(file);
		temp.push_back('@');
		char buf[32] = { 0 };
		itoa(line, buf, 10);
		temp.append(buf);
		if(prev)
		{
			temp.append(" derived from ");
			temp.append(prev->what());
		}
		return temp.c_str();
	}
}