#pragma once

#include <cstddef>

#include "MemoryManager.h"

namespace sr {
    template<typename T>
    class UniqueMemPTR {
    public:
        T* buf_;
        explicit UniqueMemPTR(size_t size) {
            buf_ = MMMalloc(sizeof(T) * size);
        }
        UniqueMemPTR(T* ptr): buf_(ptr) {}
        UniqueMemPTR(const UniqueMemPTR&) = delete;
        UniqueMemPTR(UniqueMemPTR&& other): buf_(other.buf_) {
            other.buf_ = nullptr;
        }
        ~UniqueMemPTR() {
            if (buf_ != nullptr) {
                MMFree(buf_);
                buf_ = nullptr;
            }
        }
    };
    typedef UniqueMemPTR<unsigned char> UniqueBuf;
}