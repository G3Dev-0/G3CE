/*
CONSOLE:
Output handling (info, warning, error, debug)
*/

#include <stdbool.h>

#include "engine/utils/console.h"

#define LOAD_FUNCTION_ARGS va_list args; va_start(args, format);

// generic output function
void console_generic_output(FILE* stream, const char* logLevel, const char* format, va_list* args, bool endWithNewLine) {
    // print prefix
    fprintf(stream, "%s", logLevel);

    // Use vprintf (or vfprintf) to print the formatted message.
    // vprintf takes the format string and the va_list.
    vfprintf(stream, format, *args);

    // Add a newline if the format string doesn't end with one.
    // This makes sure each log message appears on a new line.
    if (endWithNewLine && format != NULL && strlen(format) > 0 && format[strlen(format) - 1] != '\n') {
        printf(COLOR_RESET "\n"); // also reset the color when ending the line
    }

    // Clean up the va_list object. This is crucial!
    va_end(*args);
}

// literally a printf
void console_printf(const char* format, ...) {
    LOAD_FUNCTION_ARGS
    console_generic_output(stdout, "", format, &args, false);
}

// generic output (just like a printf but with also a new line character at the end)
void console_output(const char* format, ...) {
    LOAD_FUNCTION_ARGS
    console_generic_output(stdout, "", format, &args, true);
}

// info log level
void console_info(const char* format, ...) {
    LOAD_FUNCTION_ARGS
    console_generic_output(stdout, "[INFO]: ", format, &args, true);
}

// log log level
void console_log(const char* format, ...) {
    LOAD_FUNCTION_ARGS
    console_generic_output(stdout, COLOR_GREEN "[LOG]: ", format, &args, true);
}

// warning log level
void console_warning(const char* format, ...) {
    LOAD_FUNCTION_ARGS
    console_generic_output(stdout, COLOR_ORANGE "[WARNING]: ", format, &args, true);
}

// error log level
void console_error(const char* format, ...) {
    LOAD_FUNCTION_ARGS
    console_generic_output(stderr, COLOR_RED "[ERROR]: ", format, &args, true);
}

// debug log level
void console_debug(const char* format, ...) {
    LOAD_FUNCTION_ARGS
    console_generic_output(stdout, COLOR_BLUE "[DEBUG]: ", format, &args, true);
}