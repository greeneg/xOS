/*
 *   Copyright 2022, YggdrasilSoft, LLC
 *   Author: Gary Greene <greeneg@yggdrasilsoft.com>
 *
 *   This file is part of the xOS kernel, the core of the xOS operating system
 *
 *   This Software is free software; you can redistribute it and/or modify it 
 *   under the terms of the GNU Lesser General Public License as published by
 *   the Free Software Foundation.
 *
 *   This Software is distributed in the hope that it will be useful, but
 *   WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 *   or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
 *   License for more details.
 *
 *   You should have received a copy of the GNU Lesser General Public License
 *   along with this Software; if not, write to the Free Software Foundation,
 *   Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "print.h"

const static size_t NUM_COLS = 80;
const static size_t NUM_ROWS = 25;

struct Char {
    uint8_t character;
    uint8_t color;
};

/* the buffer for our screen */
struct Char volatile * buffer = (struct Char*) 0xb8000;
size_t col = 0;
size_t row = 0;

uint8_t color = PRINT_COLOR_WHITE | PRINT_COLOR_BLACK << 4;

void clear_row(size_t row) {
    struct Char empty = (struct Char) {
        character: ' ',
        color: color,
    };

    for (size_t col = 0; col < NUM_COLS; col++) {
        buffer[col + NUM_COLS * row] = empty;
    }
}

void print_clear() {
    for (size_t i = 0; i < NUM_ROWS; i++) {
        clear_row(i);
    }
}

void print_newline() {
    col = 0;

    if (row < NUM_ROWS - 1) {
        row++;
        return;
    } else {
        for (size_t row = 1; row < NUM_ROWS; row++) {
            for (size_t col = 0; col < NUM_COLS; col++) {
                struct Char character = buffer[col + NUM_COLS * row];
                buffer[col + NUM_COLS * (row - 1)] = character;
            }
        }
        clear_row(NUM_ROWS - 1);
    }
}

void print_char(char character) {
    if (character == '\n') {
        print_newline();
        return;
    }

    if (col >= NUM_COLS) {
        print_newline();
    }

    buffer[col + NUM_COLS * row] = (struct Char) {
        character: (uint8_t) character,
        color: color,
    };

    col++;
}

void kprint(char* str) {
    for (size_t i = 0; 1; i++) {
        char character = (uint8_t) str[i];

        if (character == '\0') {
            return;
        }

        print_char(character);
    }
}

// need an int array to string conversion function
void itoa (char *buf, int base, int d) {
    char *p = buf;
    char *p1, *p2;
    unsigned long ud = d;
    int divisor = 10;

    /* If %d is specified and D is minus , put ‘-’ in the head */
    if (base == 'd' && d < 0 ) {
        *p++ = '-';
        buf++;
        ud = -d ;
    } else if (base == 'x') {
        divisor = 16;
    }

    /* Divide UD by DIVISOR until UD == 0 */
    do {
        int remainder = ud % divisor;
        *p++ = (remainder < 10) ? remainder + '0' : remainder + 'a' - 10;
    } while (ud /= divisor);

    /* Terminate BUF */
    *p = 0;

    /* Reverse BUF. */
    p1 = buf;
    p2 = p - 1;
    while (p1 < p2) {
        char tmp = *p1;
        *p1 = *p2;
        *p2 = tmp;
        p1++;
        p2--;
    }
}

// Format a string and print it on the screen , just like the libc
// function printf .
void kprintf (const char *format , ...) {
    char **arg = (char **) &format;
    int c;
    char buf[20];

    arg++;

    while ((c = *format++) != 0 ) {
        if (c != '%') {
            print_char(c);
        } else {
            char *p;
            c = *format++;
            switch (c) {
                case 'd':
                case 'u':
                case 'x':
                    itoa(buf, c, *((int *) arg++));
                    p = buf;
                    goto string;
                    break;
                case 's':
                    p = *arg++;
                    if (p == NULL) {
                        p = "(null)";
                    }
                string :
                    while (*p) {
                        print_char(*p++);
                        break;
                    }
                default :
                    print_char(*((int *) arg++));
                    break;
            }
        }
    }
}

void print_set_color(uint8_t fg, uint8_t bg) {
    color = fg + (bg << 4);
}
