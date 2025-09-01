/*
CONSOLE:
Output handling (info, warning, error, debug)
*/

#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdio.h>    // For printf, vprintf
#include <stdarg.h>   // For va_list, va_start, va_end
#include <string.h>   // For strlen (optional, for safety check)

// COLORS
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_ORANGE  "\x1b[38;5;208m"
#define COLOR_RESET   "\x1b[0m"

// generic output function
void console_generic_output(FILE* stream, const char* logLevel, const char* format, va_list* args);

// generic output (just like a printf)
void console_output(const char* format, ...);
// info log level
void console_info(const char* format, ...);
// log log level
void console_log(const char* format, ...);
// warning log level
void console_warning(const char* format, ...);
// error log level
void console_error(const char* format, ...);
// debug log level
void console_debug(const char* format, ...);

#endif