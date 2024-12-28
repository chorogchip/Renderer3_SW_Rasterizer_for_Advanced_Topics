#pragma once

#include <cstddef>
#include <cstring>
#include <type_traits>

#include "tga/tga.h"
#include "MemoryManager.h"
#include "FileManager.h"
#include "Logger.h"

namespace sr {
    enum class EnumTextureFormat {
        R8G8B8A8,
    };

    template<EnumTextureFormat format> struct GetTypeOfTextureFormat { using T = int; };
    template<> struct GetTypeOfTextureFormat<EnumTextureFormat::R8G8B8A8> { using T = int; };

    template<EnumTextureFormat format>
    class Texture {
    public:
        using T = typename GetTypeOfTextureFormat<format>::T;
    private:
        T* buf_;
        size_t width_, height_;
    public:
        Texture();
        Texture(size_t width, size_t height);
        ~Texture();

        T* GetBuf() const { return buf_; }
        size_t GetWidth() const { return width_; }
        size_t GetHeight() const { return height_; }
        size_t GetBufSize() const { return sizeof(T) * width_ * height_; }

        void Clear();
        void Clear(T value);

        void ReadFromTGAFile(const char* filename);
    private:
        void Clean_();
    };
    
    template<EnumTextureFormat format>
    Texture<format>::Texture(): buf_(nullptr), width_(0), height_(0) {}
    template<EnumTextureFormat format>
    Texture<format>::Texture(size_t width, size_t height): buf_(nullptr), width_(width), height_(height) {
        buf_ = MMMalloc(GetBufSize());
    }
    template<EnumTextureFormat format>
    Texture<format>::~Texture() {
        this->Clean_();
    }

    template<EnumTextureFormat format>
    void Texture<format>::Clean_() {
        width_ = 0;
        height_ = 0;
        if (buf_ != nullptr) {
            MMFree(buf_);
            buf_ = nullptr;
        }
    }

    
    template<EnumTextureFormat format>
    void Texture<format>::Clear() {
        memset(buf_, 1, GetBufSize());
    }
    template<EnumTextureFormat format>
    void Texture<format>::Clear(T value) {
        if constexpr (sizeof(Texture<format>::T) == 1) {
            memset(buf_, 1, GetBufSize());
        } else {
            for (size_t x = 0; x < width_; ++x)
                for (size_t y = 0; y < height_; ++y)
                    buf_[y * width_ + x] = value;
        }
    }


    template<EnumTextureFormat format>
    void Texture<format>::ReadFromTGAFile(const char* filename) {
        this->Clean_();

        FILE* fp = FMOpenFileForRead(filename);
        tga::StdioFileInterface file(fp);
        tga::Decoder decoder(&file);
        tga::Header header;
        if (!decoder.readHeader(header))
            LGDieOnError("error reading header of TGA file ", filename);

        tga::Image image;
        image.bytesPerPixel = header.bytesPerPixel();
        image.rowstride = header.width * header.bytesPerPixel();

        std::vector<uint8_t> buffer(image.rowstride * header.height);
        image.pixels = &buffer[0];

        if (!decoder.readImage(header, image, nullptr))
            LGDieOnError("error reading data of TGA file ", filename);

        decoder.postProcessImage(header, image);

        // TODO
    }

    using TextureRGBA = Texture<EnumTextureFormat::R8G8B8A8>;
}