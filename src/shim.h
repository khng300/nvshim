#pragma once

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define __HEAD(head, ...) head
#define __TAIL(head, ...) __VA_ARGS__

#ifdef DEBUG

#include <pthread_np.h>
#include <unistd.h>

#define LOG(...) fprintf(stderr, "[%d:%d] " __HEAD(__VA_ARGS__) "\n", getpid(), pthread_getthreadid_np(), __TAIL(__VA_ARGS__))

#define LOG_ENTRY(fmt, ...) __builtin_choose_expr(__builtin_strcmp("" fmt, "") == 0, LOG("%s()",       __func__), LOG("%s("    fmt ")", __func__, ## __VA_ARGS__))
#define LOG_EXIT( fmt, ...) __builtin_choose_expr(__builtin_strcmp("" fmt, "") == 0, LOG("%s -> void", __func__), LOG("%s -> " fmt,     __func__, ## __VA_ARGS__))

#else

#define LOG(...)
#define LOG_ENTRY(fmt, ...)
#define LOG_EXIT( fmt, ...)

#endif

#define UNIMPLEMENTED()         { fprintf(stderr, "%s is not implemented\n", __func__);                                               assert(0); }
#define UNIMPLEMENTED_ARGS(...) { fprintf(stderr, "%s(" __HEAD(__VA_ARGS__) ") is not implemented\n", __func__, __TAIL(__VA_ARGS__)); assert(0); }

#ifndef SHIM_EXPORT
#define SHIM_EXPORT(sym) SHIM_EXPORT_ ##sym
#endif

#ifndef SHIM_WRAP
#define SHIM_WRAP(fun, ...) SHIM_WRAPPER_ ##fun
#endif

bool str_starts_with(const char* str, const char* substr);

typedef int64_t linux_off64_t;

#ifdef __i386__
typedef int32_t linux_off_t;
#endif

#ifdef __x86_64__
typedef int64_t linux_off_t;
#endif

#include <getopt.h>

typedef struct option linux_option;

#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>

typedef struct rusage linux_rusage;

#include <spawn.h>

typedef struct sched_param linux_sched_param;

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

typedef struct sembuf linux_sembuf;

#include <rpc/rpc.h>

typedef struct pollfd linux_pollfd;

struct linux_rlimit {};

typedef struct linux_rlimit linux_rlimit;
