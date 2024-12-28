#include "MemoryManager.h"

#include <cstdlib>

#include "Logger.h"

namespace sr {
    void MMInit() {

    }
    void MMClean() {

    }
    void* MMMalloc(size_t size) {
        void* ret = malloc(size);
        if (ret == nullptr) {
            LGDieOnError("memory alloc failed");
        }
        return ret;
    }
    void MMFree(void* memory) {
        free(memory);
    }

}