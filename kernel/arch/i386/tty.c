#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/tty.h>

#include "vga.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint8_t default_color;
uint16_t* terminal_buffer;

void terminal_initialize(void) {
    terminal_row = 0;
    terminal_column = 0;
    default_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    terminal_color = default_color;
    terminal_buffer = VGA_MEMORY;
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    }
}

void terminal_setcolor(enum vga_color fg, enum vga_color bg) {
    terminal_color = vga_entry_color(fg, bg);
}

void terminal_setfg(enum vga_color fg) {
    terminal_color = vga_entry_color(fg, terminal_color >> 4);
}

void terminal_setbg(enum vga_color bg) {
    terminal_color = vga_entry_color((terminal_color << 4) >> 4, bg);
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c) {
    unsigned char uc = c;
    terminal_putentryat(uc, terminal_color, terminal_column, terminal_row);
    if (++terminal_column == VGA_WIDTH) {
        terminal_column = 0;
        if (++terminal_row == VGA_HEIGHT)
            terminal_row = 0;
    }
}

void terminal_scroll(uint8_t amount) {
    for (size_t y = 1; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index - VGA_WIDTH] = terminal_buffer[index];
        }
    }
    for (size_t y = VGA_HEIGHT - amount; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            terminal_buffer[y * VGA_WIDTH + x] = vga_entry(' ', default_color);
        }
    }
    terminal_row -= amount;
}

void read_escape_code(uint16_t escape_code) {
    switch (escape_code) {
        case 0:
            terminal_color = default_color;
            break;
        case 31:
            terminal_setfg(VGA_COLOR_RED);
            break;
        case 32:
            terminal_setfg(VGA_COLOR_GREEN);
            break;
    }
}

void terminal_write(const char* data, size_t size) {
    static bool escape = false;
    static uint8_t escape_index = 0;
    static uint16_t escape_code = 0;
    for (size_t i = 0; i < size; i++) {
        if (data[i] == '\n') {
            terminal_column = 0;
            if (terminal_row >= VGA_HEIGHT - 1)
                terminal_scroll(1);
            terminal_row++;
        } else if (data[i] == '\033') {
            escape = true;
            escape_index = 1;
            escape_code = 0;
        } else if (escape) {
            if (data[i] == '[' && escape_index==1)
                escape_index++;
            else if ('9'>=data[i] && data[i]>='0' && escape_index>1) {
                escape_code *= 10;
                escape_code += (int)(data[i]-'0');
                escape_index++;
            }
            else if (data[i] == 'm') {
                read_escape_code(escape_code);
                escape = false;
            } else {
                escape = false;
            }
        } else
            terminal_putchar(data[i]);
    }
}

void terminal_writestring(const char* data) {
    terminal_write(data, strlen(data));
}
