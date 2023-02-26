#pragma once

#include <cstdio>

// Color Codes
// https://gist.github.com/iamnewton/8754917
#define COLOR_RESET       "\e[0m"
#define COLOR_RED         "\e[0;31m"
#define COLOR_GREEN       "\e[0;32m"
#define COLOR_YELLOW      "\e[0;33m"
#define COLOR_BLUE        "\e[0;34m"
#define COLOR_WHITE       "\e[0;37m"
#define COLOR_BOLD_RED    "\e[1;31m"
#define COLOR_BOLD_GREEN  "\e[1;32m"
#define COLOR_BOLD_YELLOW "\e[1;33m"
#define COLOR_BOLD_BLUE   "\e[1;34m"
#define COLOR_BOLD_WHITE  "\e[1;37m"


namespace Logger
{
	namespace
	{
		template<typename... Args>
		void Log(const char* msg, Args... args)
		{
			printf(msg, args...);
			printf(COLOR_RESET);
			printf("\n");
		}

		template<typename... Args>
		void Log(const char* color, const char* prefix, const char* msg, Args... args)
		{
			printf(COLOR_BOLD_WHITE);
			printf("[%s]   ", prefix);
			printf(color);
			Log(msg, args...);
		}
	}

	template<typename... Args>
	void Debug(const char* msg, Args... args)
	{
		Log(COLOR_WHITE, "Debug", msg, args...);
	}

	template<typename... Args>
	void Info(const char* msg, Args... args)
	{
		Log(COLOR_BLUE, "Info", msg, args...);
	}

	template<typename... Args>
	void Error(const char* msg, Args... args)
	{
		Log(COLOR_RED, "Error", msg, args...);
	}

	template<typename... Args>
	void Warn(const char* msg, Args... args)
	{
		Log(COLOR_YELLOW, "Warning", msg, args...);
	}
};
