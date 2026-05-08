#ifndef TEST_H
#define TEST_H

#define CSTRING_IMPLEMENTATION
#include "../include/cstring.h"

#include <stdlib.h>

#define TEST_INIT_STRING(str, capacity) \
    do \
    { \
        for (size_t _i = 0; _i < capacity; ++_i) str[_i] = '#'; \
        str[capacity - 1] = '\0'; \
    } while (0)

#define TEST_MAKE_STRING(name, capacity) \
    char name[capacity]; \
    TEST_INIT_STRING(name, capacity)

#define TEST_MAKE_SSO_STRING(name) \
    TEST_MAKE_STRING(name, CSTRING_SSO_CAPACITY - 1)

#define TEST_MAKE_HEAP_STRING(name) \
    TEST_MAKE_STRING(name, CSTRING_SSO_CAPACITY + 1)

#define TEST_ASSERT(x) \
    if (!(x)) exit(EXIT_FAILURE)

#endif
