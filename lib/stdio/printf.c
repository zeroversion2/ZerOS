#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <kernel/asm.h>

static bool print(const char* data, size_t length) {
    const unsigned char* bytes = (const unsigned char*) data;
    for (size_t i = 0; i < length; i++)
        if (putchar(bytes[i]) == EOF)
            return false;
    return true;
}
int printf(const char* restrict format, ...) {
    va_list parameters;
    va_start(parameters, format);

    int written = 0;

    while (*format != '\0') {
        size_t maxrem = INT_MAX - written;

        if (format[0] != '%' || format[1] == '%') {
            if (format[0] == '%')
                format++;
            size_t amount = 1;
            while (format[amount] && format[amount] != '%')
                amount++;
            if (maxrem < amount) {
                //TODO: set errno to EOVERFLOW
                return -1;
            }
            if (!print(format, amount))
                return -1;
            format += amount;
            written += amount;
            continue;
        }

        const char* format_begun_at = format++;

        if (*format == 'c') {
            format++;
            char c = (char) va_arg(parameters, int /*char promotes to int */);
            if (!maxrem) {
                //TODO: set errno to EOVERFLOW
                return -1;
            }
            if (!print(&c, sizeof(c)))
                return -1;
            written++;
        } else if (*format == 's') {
            format++;
            const char* str = va_arg(parameters, const char*);
            size_t len = strlen(str);
            if (maxrem < len) {
                //TODO: set errno to EOVERFLOW
                return -1;
            }
            if (!print(str, len))
                return -1;
            written += len;
        } else if (*format == 'd') {
            format++;
            int num = va_arg(parameters, int);
            int temp = num;
            size_t len = 0;

            //loop to find length
            do {
                len++;
                temp /= 10;
            } while (temp > 0);
            char str[len];
            temp = num;

            //loop to convert to string
            for (size_t i = 0; i < len; i++) {
                char c = (char) ((temp % 10) + '0');
                str[len - i - 1] = c;
                temp /= 10;
            }
            
            if (maxrem < len) {
                //TODO: set errno to EOVERFLOW
                return -1;
            }
            if (!print(str, len)) {
                return -1;
            }
            written += len;
        } else {
            format = format_begun_at;
            size_t len = strlen(format);
            if (maxrem < len) {
                //TODO: set errno to EOVERFLOW
                return -1;
            }
            if (!print(format, len))
                return -1;
            written += len;
            format += len;
        }
    }

    va_end(parameters);
    return written;
}
