/*
 * Copyright (c) 1996-2009 Barton P. Miller
 * 
 * We provide the Paradyn Parallel Performance Tools (below
 * described as "Paradyn") on an AS IS basis, and do not warrant its
 * validity or performance.  We reserve the right to update, modify,
 * or discontinue this software at any time.  We shall have no
 * obligation to supply such updates or modifications or any other
 * form of support to you.
 * 
 * By your use of Paradyn, you understand and agree that we (or any
 * other person or entity with proprietary rights in Paradyn) are
 * under no obligation to provide either maintenance services,
 * update services, notices of latent defects, or correction of
 * defects for Paradyn.
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include "debug_parse.h"

using namespace Dyninst::ParseAPI;

int Dyninst::ParseAPI::dyn_debug_parsing = 0;
int Dyninst::ParseAPI::dyn_debug_malware = 0;
int Dyninst::ParseAPI::dyn_debug_initialized = 0;

int Dyninst::ParseAPI::parsing_printf_int(const char *format, ...)
{
    if(!dyn_debug_initialized) {
        if(getenv("DYNINST_DEBUG_PARSING"))
            dyn_debug_parsing = 1;
        if(getenv("DYNINST_DEBUG_MALWARE"))
            dyn_debug_malware = 1;
        dyn_debug_initialized = 1;
    }

    if(!dyn_debug_parsing) return 0;
    if(NULL == format) return -1;

    va_list va;
    va_start(va,format);
    int ret = vfprintf(stderr, format, va);
    va_end(va);

    return ret;
}
        
int Dyninst::ParseAPI::malware_printf_int(const char *format, ...)
{
    if(!dyn_debug_initialized) {
        if(getenv("DYNINST_DEBUG_PARSING"))
            dyn_debug_parsing = 1;
        if(getenv("DYNINST_DEBUG_MALWARE"))
            dyn_debug_malware = 1;
        dyn_debug_initialized = 1;
    }

    if(!dyn_debug_malware) return 0;
    if(NULL == format) return -1;

    va_list va;
    va_start(va,format);
    int ret = vfprintf(stderr, format, va);
    va_end(va);

    return ret;
}
        