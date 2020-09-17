// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#ifndef _LIBOS_TCALL_H
#define _LIBOS_TCALL_H

#include <libos/defs.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>

typedef enum libos_tcall_number
{
    LIBOS_TCALL_RANDOM = 2048,
    LIBOS_TCALL_ALLOCATE = 2049,
    LIBOS_TCALL_DEALLOCATE = 2050,
    LIBOS_TCALL_VSNPRINTF = 2051,
    LIBOS_TCALL_WRITE_CONSOLE = 2052,
    LIBOS_TCALL_GEN_CREDS = 2053,
    LIBOS_TCALL_FREE_CREDS = 2054,
    LIBOS_TCALL_VERIFY_CERT = 2055,
    LIBOS_TCALL_CLOCK_GETTIME = 2056,
    LIBOS_TCALL_ISATTY = 2057,
    LIBOS_TCALL_ADD_SYMBOL_FILE = 2058,
    LIBOS_TCALL_LOAD_SYMBOLS = 2059,
    LIBOS_TCALL_UNLOAD_SYMBOLS = 2060,
    LIBOS_TCALL_CREATE_THREAD = 2061,
    LIBOS_TCALL_WAIT = 2062,
    LIBOS_TCALL_WAKE = 2063,
    LIBOS_TCALL_WAKE_WAIT = 2064,
    LIBOS_TCALL_EXPORT_FILE = 2065,
    LIBOS_TCALL_SET_RUN_THREAD_FUNCTION = 2066,
} libos_tcall_number_t;

long libos_tcall(long n, long params[6]);

typedef long (*libos_tcall_t)(long n, long params[6]);

long libos_tcall_random(void* data, size_t size);

long libos_tcall_thread_self(void);

long libos_tcall_vsnprintf(
    char* str,
    size_t size,
    const char* format,
    va_list ap);

long libos_tcall_write_console(int fd, const void* buf, size_t count);

long libos_tcall_create_thread(uint64_t cookie);

long libos_tcall_wait(uint64_t event, const struct timespec* timeout);

long libos_tcall_wake(uint64_t event);

long libos_tcall_wake_wait(
    uint64_t waiter_event,
    uint64_t self_event,
    const struct timespec* timeout);

long libos_tcall_export_file(const char* path, const void* data, size_t size);

long libos_tcall_add_symbol_file(
    const void* file_data,
    size_t file_size,
    const void* text_data,
    size_t text_size);

long libos_tcall_load_symbols(void);

long libos_tcall_unload_symbols(void);

typedef long (*libos_run_thread_t)(uint64_t cookie, uint64_t event);

long libos_tcall_set_run_thread_function(libos_run_thread_t function);

#endif /* _LIBOS_TCALL_H */
