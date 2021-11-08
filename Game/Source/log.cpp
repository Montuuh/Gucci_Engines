#pragma once
#include "Globals.h"

std::vector<std::string> consoleLog;

std::string GetConsoleText(int i)
{
	return consoleLog[i];
}

int GetConsoleSize()
{
	return consoleLog.size();
}

void log(const char file[], int line, const char* format, ...)
{
	static char tmp_string[4096];
	static char tmp_string2[4096];
	static va_list  ap;

	// Construct the string from variable arguments
	va_start(ap, format);
	vsprintf_s(tmp_string, 4096, format, ap);
	va_end(ap);
	sprintf_s(tmp_string2, 4096, "\n%s(%d) : %s", file, line, tmp_string);
	OutputDebugString(tmp_string2);
	
	consoleLog.push_back(tmp_string2);
	consoleLog.back().erase(consoleLog.back().begin());
	if (consoleLog.size() > CONSOLE_LOG_LIMIT)
	{
		consoleLog.erase(consoleLog.begin());
	}
}