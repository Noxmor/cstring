#ifndef TEST_H
#define TEST_H

#define CSTRING_IMPLEMENTATION
#include "../include/cstring.h"

#include <stdlib.h>

#define TEST_ASSERT(x) \
    if (!(x)) exit(EXIT_FAILURE)

#endif
