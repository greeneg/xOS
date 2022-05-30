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

uint8_t inbyte(uint16_t port);
void outbyte(uint16_t port, uint8_t data);
