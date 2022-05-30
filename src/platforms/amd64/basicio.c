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
    We use inbyte for reading from the I/O ports to get data from devices such
    as the keyboard. To do so, we need the 'inb' instruction, which is only
    accessible from assemby. So the C function is simply an extern asm wrapper
    around that single assembly instruction.
*/
#include <stdint.h>
#include <stddef.h>

uint8_t inbyte(uint16_t port) {
    uint8_t ret;

    /* inline assembly */
    __asm__ __volatile__ ("inb %1, %0" : "=a" (ret) : "d" (port));

    return ret;
}

/*
    We use outbyte to write to I/O ports, e.g. to send bytes to devices. Again
    we need to use inline asm to wrap the call, as it is only available as a
    direct register call in the CPU
 */
void outbyte(uint16_t port, uint8_t data) {
    __asm__ __volatile__ ("outb %1, %0" : : "d" (port), "a" (data));
}
