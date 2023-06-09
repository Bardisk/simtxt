
// static inline hash
#ifndef _BASICS_
#define _BASICS_

#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include <utils.h>
#include <workdir.h>
#include <assert.h>

extern bool is_single_file;
extern bool use_stdin;
extern bool use_stdout;

#ifndef MAXFILESZ
#define MAXFILESZ 134217728
#endif
#ifndef MAXTOKSZ
#define MAXTOKSZ 33554432
#endif

#ifndef MINGRAM
#define MINGRAM 8
#endif

#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define MAX(a, b) ((a) < (b) ? (b) : (a))

#define SHINGLE_LEN(original_len) ((original_len) - MINGRAM + 1)

#ifdef __cplusplus

#endif

#endif