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

#pragma once

#include <stdint.h>
#include <stddef.h>

enum {
    PRINT_COLOR_BLACK       = 0,
    PRINT_COLOR_BLUE        = 1,
    PRINT_COLOR_GREEN       = 2,
    PRINT_COLOR_CYAN        = 3,
    PRINT_COLOR_RED         = 4,
    PRINT_COLOR_MAGENTA     = 5,
    PRINT_COLOR_BROWN       = 6,
    PRINT_COLOR_LIGHT_GREY  = 7,
    PRINT_COLOR_DARK_GREY   = 8,
    PRINT_COLOR_LIGHT_BLUE  = 9,
    PRINT_COLOR_LIGHT_GREEN = 10,
    PRINT_COLOR_LIGHT_CYAN  = 11,
    PRINT_COLOR_LIGHT_RED   = 12,
    PRINT_COLOR_PINK        = 13,
    PRINT_COLOR_YELLOW      = 14,
    PRINT_COLOR_WHITE       = 15
};

void print_clear();
void print_char(char c);
void kprint(char* string);
void print_set_color(uint8_t fg, uint8_t bg);
