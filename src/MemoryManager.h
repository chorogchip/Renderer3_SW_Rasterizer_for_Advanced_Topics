#pragma once

#include <cstddef>

namespace sr {
    extern void MMInit();
    extern void MMClean();
    extern void* MMMalloc(size_t size);
    extern void MMFree(void* memory);
}