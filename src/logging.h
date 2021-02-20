#include "parser_constants.h"

// Allow logging functionality to be excluded,
// because devices with memory limitations may not
// have the capacity to include stdarg.h
#ifndef LOGGING_DISABLED
    #include <stdarg.h>
    #include <stdio.h>
#endif

#ifndef LOGGING_DISABLED

/**
 * Function for logging.
 *
 * :param format: Message to log. (**Input only**)
 *
 * :since: v0.1
 */
typedef void (*logging_function_t) (const char *message);

#endif // LOGGING_DISABLED

#ifndef MIDI_PARSER_LOGGING_
#define MIDI_PARSER_LOGGING_

static logging_function_t m_logging_function = NULL;

#ifndef LOGGING_DISABLED
/**
 * Allows the user to register a logging function to enable logging.
 *
 * :param logging_function: (**Input only**)
 *
 * :since: v0.1
 */
void midi_register_logging_function(logging_function_t logging_function)
{
    m_logging_function = logging_function;
}
#endif // LOGGING_DISABLED

/**
 * A printf-like function that logs a given message.
 *
 * :param message: Format string (**Input only**)
 * :param ...:     Variable number of arguments for format specifiers. (**Input only**)
 *
 * :since: v0.1
 */
void midi_log_info(const char *message, ...)
{
    if (m_logging_function == NULL)
    {
        return;
    }

    #ifndef LOGGING_DISABLED
        va_list args;
        va_start(args, message);
        char formatted_message[MAXIMUM_LOG_MESSAGE_SIZE];
        vsnprintf(formatted_message, MAXIMUM_LOG_MESSAGE_SIZE, message, args);
        m_logging_function(formatted_message);
        va_end(args);
    #endif
}

/**
 * Logs the given bytes.
 *
 * :param bytes: (**Input only**)
 * :param length: The number of bytes. (**Input only**)
 *
 * :since: v0.1
 */
void midi_log_bytes(uint8_t *bytes, uint16_t length)
{
    if (length == 0) {
        midi_log_info("(no bytes to log)");
        return;
    }

    midi_log_info("logging %d bytes:", length);

    for (uint8_t i = 0; i < length; i++)
    {
        midi_log_info("\tbyte %d: %x", i, bytes[i]);
    }
}
#endif
