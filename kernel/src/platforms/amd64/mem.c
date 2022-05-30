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

/*
    Convenient memory functions. GLibC cannot help us, as we're inside our 
    kernel at boot.
 */

unsigned char *memcpy(unsigned char *dest, const unsigned char *src, int count) {
    for (int i = 0; i < count; i++) {
        dest[i] = src[i];
    }

    return dest;
}

unsigned char *memset(unsigned char *dest, unsigned char val, int count) {
    for (int i = 0; i < count; i++) {
        dest[i] = val;
    }

    return dest;
}
