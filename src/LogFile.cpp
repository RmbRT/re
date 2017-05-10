#include "LogFile.hpp"
#include <cstdlib>
#include <iostream>
#include <cstdarg>
#include <cstring>

namespace re
{
	LogFile::LogFile(const char* filename) : logFile(nullptr), name("unnamed"), use_cout(false)
	{
		if(!(logFile = fopen(filename, "wt")))
		{
			RE_LOG("failed to create logfile %s.\n", filename);
			std::abort();
		}

	}
	LogFile::LogFile(const char *filename, const char *console_name): logFile(nullptr), name(console_name), use_cout(true)
	{
		if(!(logFile = fopen(filename, "wt")))
		{
			RE_LOG("failed to create logfile %s.\n", filename);
			std::abort();
		}
	}
	LogFile::LogFile(): logFile(nullptr), name("unnamed"), use_cout(false)
	{
	}
	LogFile::~LogFile()
	{
		close();
	}
	void LogFile::write(const char* text)
	{
		if(logFile)
		{
			fputs(text, logFile);
		}
		if(use_cout)
			std::cout << text;
	}
	void LogFile::writeln(const char* text)
	{
		if(logFile)
		{
			fputs(text, logFile);
			fputc('\n', logFile);
		}
		if(use_cout)
			std::cout << text << '\n';
	}


	void LogFile::writef(const char* format, ...)
	{
		va_list varargs;
		va_start(varargs, format);
		char buffer[1024] = { 0 };
		vsprintf(buffer, format, varargs);

		if(logFile)
			fwrite(buffer, sizeof(char), std::strlen(buffer), logFile);
		if(use_cout)
			((name)?(std::cout << "[" << name << "] "):std::cout) << buffer;
	}
	void LogFile::writefln(const char* format, ...)
	{
		va_list varargs;
		va_start(varargs, format);
		char buffer[1024] = { 0 };

		int len = vsprintf(buffer, format, varargs);
		buffer[len] = '\n';
		buffer[len+1] = '\0';

		if(logFile)
			fwrite(buffer, sizeof(char), std::strlen(buffer), logFile);
		if(use_cout)
			((name)?(std::cout << "[" << name << "] "):std::cout) << (char*)buffer;
	}

	void LogFile::mirrorToConsole(bool mirror)
	{
		use_cout = mirror;
	}
	void LogFile::open(const char* filename)
	{
		close();
		if(!(logFile = fopen(filename, "wt")))
		{
			RE_LOG("couldn't open log file %s.", filename);
			std::abort();
		}
	}
	void LogFile::close()
	{
		if(logFile)
			fclose(logFile);
		logFile = nullptr;
	}
	void LogFile::flush()
	{
		if(logFile)
			fflush(logFile);

		std::cout.flush();
	}

	void LogFile::setName(const char* name)
	{
		this->name = name;
	}

	void LogFile::assertion_failure(const char* expr, const char* file, int line, const char* function)
	{
		writefln(
			"***ASSERTION FAILURE***\n"
			"Expression:\n"
			"%s\n"
			"In ::%s\n"
			"File: %s\n"
			"Line %i", expr, function, file, line);

		flush();
		std::abort();
	}
}