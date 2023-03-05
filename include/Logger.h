#pragma once

#include <iostream>

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
		void Log()
		{
			std::cout << std::endl;
		}

		template<typename First, typename ... Strings>
		void Log(First arg, const Strings&... rest)
		{
			std::cout << arg;
			Log(rest...);
		}
	}

	template<typename First, typename ... Strings>
	void Debug(First arg, const Strings&... rest)
	{
		Log(COLOR_BOLD_WHITE, "[Debug]   ", COLOR_WHITE, arg, rest...);
	}

	template<typename First, typename ... Strings>
	void Error(First arg, const Strings&... rest)
	{
		Log(COLOR_BOLD_WHITE, "[Error]   ", COLOR_RED, arg, rest...);
	}

	template<typename First, typename ... Strings>
	void Info(First arg, const Strings&... rest)
	{
		Log(COLOR_BOLD_WHITE, "[Info]   ", COLOR_BLUE, arg, rest...);
	}

	template<typename First, typename ... Strings>
	void Warn(First arg, const Strings&... rest)
	{
		Log(COLOR_BOLD_WHITE, "[Warn]   ", COLOR_YELLOW, arg, rest...);
	}
};
