// sТrings.h
#pragma once


#include <acx/base.h>
#include <acx/aliases.h>

#include <algorithm>
#include <cctype>
#include <iomanip>
#include <iostream>
#include <sstream>


namespace acx {


#ifdef ACX_CLI

	SCSTR NL = "\n";

	SCSTR MSG_CONTINUE = "Press ENTER to continue...";
	SCSTR MSG_RETURN = "Press ENTER to return...";
	SCSTR MSG_WELCOME = "Welcome! ";
	SCSTR MSG_BYE = "Goodbye!";
	SCSTR MSG_OPTION = "Option: ";
	SCSTR MSG_INPUT_ROW = "Row: ";
	SCSTR MSG_INPUT_COL = "Column: ";
	SCSTR MSG_INPUT_ID = "ID: ";
	SCSTR MSG_INPUT_NAME = "Name: ";
	SCSTR MSG_INPUT_DESC = "Description: ";
	SCSTR MSG_INPUT_QTY = "Quantity: ";
	SCSTR MSG_SAVED = "Saved successfully.";
	SCSTR MSG_LOADED = "Loaded successfully.";
	SCSTR MSG_DONE = "Done.";
	SCSTR MSG_ERROR_PREFIX = "[!] ";
	SCSTR MSG_INVALID_OPTION = "[!] Invalid option. Please choose among the options listed above.";

	SCSTR MSG_MAIN_MENU_FIRST_RUN_INTRO = "You are in the main menu. Choose an option and press ENTER to interact with the program.";
	SCSTR MSG_MAIN_MENU_INTRO = "Main Menu";
	SCSTR MSG_MAIN_MENU_OPTION_0 = "0.Exit";

#endif


	// =====Generic text

#ifdef ACX_TXT

	SCSTR TXT_EMPTY = "";
	SCSTR TXT_SPACE = " ";
	SCSTR TXT_COMMA = ",";
	SCSTR TXT_LEFT_BRACKET = "[";
	SCSTR TXT_RIGHT_BRACKET_SPACE = "] ";
	SCSTR TXT_ARROW = " -> ";
	SCSTR TXT_TRUE = "true";
	SCSTR TXT_FALSE = "false";

#endif


	// =====Text files

#ifdef ACX_TXT_FILES

	SCSTR JSON_OPEN = "{\n";
	SCSTR JSON_ARRAY_CLOSE_COMMA = "  ],\n";
	SCSTR JSON_ARRAY_CLOSE = "  ]\n";
	SCSTR JSON_CLOSE = "}\n";

	SCSTR JSON_ROW_PREFIX = "    \"";
	SCSTR JSON_ROW_SUFFIX = "\"";

#endif


	// =====Time

#ifdef ACX_TIME

	SCSTR ERR_TIME_MONTH_RANGE = "Month must be in range [1, 12]";
	SCSTR ERR_TIME_DAY_RANGE = "Day must be in range [1, 31]";
	SCSTR ERR_TIME_HOUR_RANGE = "Hours must be in range [0, 23]";
	SCSTR ERR_TIME_MINUTE_RANGE = "Minutes must be in range [0, 59]";
	SCSTR ERR_TIME_SECOND_RANGE = "Seconds must be in range [0, 59]";
	SCSTR ERR_TIME_MILLISECOND_RANGE = "Milliseconds must be in range [0, 999]";
	SCSTR ERR_TIME_MIDNIGHT_RANGE = "Milliseconds from midnight exceeds maximum for the day";
	SCSTR ERR_TIME_TZ_RANGE = "Timezone offset must be in range [-720, 840] minutes";
	SCSTR ERR_TIME_MICROSECOND_RANGE = "Microseconds must be in range [0, 999]";
	SCSTR ERR_TIME_INVALID_MONTH = "Invalid month: must be 1-12";
	SCSTR ERR_TIME_INVALID_DAY = "Invalid day: must be 1-31";
	SCSTR ERR_TIME_INVALID_MILLISECONDS = "Invalid milliseconds";
	SCSTR ERR_TIME_INVALID_TZ = "Invalid timezone offset";
	SCSTR ERR_TIME_INVALID_MICROSECONDS = "Invalid microseconds: must be 0-999";
	SCSTR ERR_TIME_TARGET_TZ = "Target timezone offset is invalid";
	SCSTR ERR_TIME_TIME_T = "Invalid time_t value";
	SCSTR ERR_TIME_TO_TIME_T = "Failed to convert to time_t";
	SCSTR ERR_TIME_BUFFER_NULL = "Buffer pointer is null";
	SCSTR ERR_TIME_PARSE = "Invalid time string";
	SCSTR FMT_TIME_STRING = "%04u-%02u-%02u %02u:%02u:%02u.%03u.%03u%s (UTC%+03d:%02u)%s";
	SCSTR FMT_TIME_ISO8601 = "%04u-%02u-%02uT%02u:%02u:%02u.%03u%+03d:%02u";
	SCSTR TXT_LEAP_SECOND = "+leap";
	SCSTR TXT_DST = " DST";

#endif


	// =====Errors
#ifdef ACX_ERR_HANDLING

	SCSTR ERR_GENERAL = "Error occured: ";
	SCSTR ERR_TERMINATED = "Program was terminated by user.";
	SCSTR ERR_NOT_IMPLEMENTED = "This method or class is yet to be implemented.";
	SCSTR ERR_INVALID_ARGUMENT = "Invalid method/function argument.";
	SCSTR ERR_NOT_NUMBER = "Not a number.";

	SCSTR ERR_TRIM_ERROR = "trim() finished with an error.";
	SCSTR ERR_MENU_OPT_BELOW_ZERO = "Menu option number was less than zero.";

	SCSTR ERR_CANT_OPEN_FILE = "Cannot open file: ";
	SCSTR ERR_FILE_EMPTY = "File is empty: ";
	SCSTR ERR_FILE_NO_RECORDS = "No valid records found in file: ";

	SCSTR ERR_LINE = "Line ";

#endif


	// =====Helpers

	inline string trim(const std::string& s) {
		auto start = std::find_if_not(
			s.begin(), s.end(),
			[](unsigned char c) {
				return isspace(static_cast<int>(c));
			}
		);
		auto end = std::find_if_not(
			s.rbegin(), s.rend(),
			[](unsigned char c) {
				return isspace(static_cast<int>(c));
			}
		).base();
		return (start < end) ? std::string(start, end) : "";
	}

	inline string pad_right(const string& s, const int width) {
		int size = static_cast<int>(s.size());
		if (size >= width) {
			return s.substr(0, width);
		}
		return s + string(width - size, ' ');
	}

	inline string pad_left(const string& s, const int width) {
		int size = static_cast<int>(s.size());
		if (size >= width) {
			return s.substr(0, width);
		}
		return string(width - size, ' ') + s;
	}

	inline string format_float(const float value, const int precision) {
		std::ostringstream oss;
		oss << std::fixed << std::setprecision(precision) << value;
		return oss.str();
	}

	inline void print_separator(std::ostream& os, const char c, const int width) {
		os << string(width, c) << '\n';
	}


}
