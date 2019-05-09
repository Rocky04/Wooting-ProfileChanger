#ifndef DEBUG_H
#define DEBUG_H

#ifdef _MSC_VER
#	pragma once
#endif

#include <stdio.h>
#include <time.h>

#ifdef DEBUG
#	define DEBUG_PRINT(...) fprintf(stderr, "DEBUG (Time=%ld): ", clock()); fprintf(stderr, __VA_ARGS__)
#else
#	define DEBUG_PRINT(...)
#endif

#endif
