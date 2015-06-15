#ifndef __re_log_file_hpp_defined
#define __re_log_file_hpp_defined

#include "Singleton.hpp"
#include "defines.hpp"
#include "base_types.hpp"

#define RE_LOG(X,...) re::LogFile::GetInst()->writefln(__FUNCTION__": "X, __VA_ARGS__)
#define RE_ASSERTION_FAILURE(X) re::LogFile::GetInst()->assertion_failure(X, __FILE__, __LINE__, __FUNCTION__)
#define RE_ASSERT(X) void((!(X))?(RE_ASSERTION_FAILURE(#X),0):0)
#define RE_TEST(X) re::LogFile::GetInst()->test((X), #X, __FILE__, __LINE__)

namespace re
{
	class LogFile: public Singleton<LogFile>
	{
		std::FILE* logFile;
		const char* name;
		bool use_cout;
	public:
		LogFile();
		LogFile(const char* filename);
		LogFile(const char* filename, const char* console_name);
		~LogFile();

		void mirrorToConsole(bool mirror);

		void write(const char* text);
		void writeln(const char* text);
		void writef(const char* format, ...);
		void writefln(const char* format, ...);

		void flush();
		void close();

		void open(const char* filename);
		void setName(const char* name);

		void test(bool op, const char* expr, const char* file, int line);
		void assertion_failure(const char* expr, const char* file, int line, const char *function);

	private:
		LogFile &operator=(const LogFile &rval);
	};
}

#endif