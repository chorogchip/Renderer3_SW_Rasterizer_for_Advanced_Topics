#pragma once

#include <cstddef>
#include <cstring>
#include <type_traits>

#include "tga/tga.h"
#include "MemoryManager.h"
#include "FileManager.h"
#include "Logger.h"
#include "Color.h"

namespace sr {
    enum class EnumTextureFormat {
        R8G8B8A8,
        G8,
    };

    template<EnumTextureFormat format> struct GetTypeOfTextureFormat { using Texel = uint32_t; };
    template<> struct GetTypeOfTextureFormat<EnumTextureFormat::R8G8B8A8> { using Texel = Color::RGBA8; };

    template<EnumTextureFormat format>
    class Texture {
    public:
        using Texel = typename GetTypeOfTextureFormat<format>::Texel;
    private:
        Texel* buf_;
        size_t width_, height_;
    public:
        Texture();
        Texture(size_t width, size_t height);
        Texture(const Texture&);
        Texture(Texture &&);
        ~Texture();

        Texel* GetBuf() const { return buf_; }
        size_t GetWidth() const { return width_; }
        size_t GetHeight() const { return height_; }
        size_t GetBufSize() const { return sizeof(Texel) * width_ * height_; }
        Texel& At(int x, int y) { return buf_[x + y * width_]; }
        const Texel& At(int x, int y) const { return buf_[x + y * width_]; }

        void Clear();
        void Clear(Texel value);

        // only can be used for EnumTextureFormat::R8G8B8A8 or EnumTextureFormat::G8.
        void ReadFromTGAFile(const char* filename_without_extension);
        // only can be used for EnumTextureFormat::R8G8B8A8 or EnumTextureFormat::G8.
        void WriteToTGAFile(const char* filename_without_extension, bool change_name_if_name_collides = false);

    private:
        void Clean_();

    public:
    };
    
    template<EnumTextureFormat format>
    Texture<format>::Texture(): buf_(nullptr), width_(0), height_(0) {}
    template<EnumTextureFormat format>
    Texture<format>::Texture(size_t width, size_t height): buf_(nullptr), width_(width), height_(height) {
        buf_ = static_cast<Texel*>(MMMalloc(GetBufSize()));
        this->Clear();
    }

    template<EnumTextureFormat format>
    Texture<format>::Texture(const Texture& other): buf_(nullptr), width_(other.width_), height_(other.height_) {
        const size_t size = GetBufSize();
        buf_ = static_cast<Texel*>(MMMalloc(size));
        memcpy(buf_, other.buf_, size);
    }

    template<EnumTextureFormat format>
    Texture<format>::Texture(Texture && other): buf_(other.buf_), width_(other.width_), height_(other.height_) {
        other.buf_ = nullptr;
        other.width_ = 0;
        other.height_ = 0;
    }

    template<EnumTextureFormat format>
    Texture<format>::~Texture() {
        this->Clean_();
    }

    template<EnumTextureFormat format>
    void Texture<format>::Clean_() {
        if (buf_ != nullptr) {
            MMFree(buf_);
            buf_ = nullptr;
        }
        width_ = 0;
        height_ = 0;
    }

    
    template<EnumTextureFormat format>
    void Texture<format>::Clear() {
        memset(static_cast<void*>(buf_), 0, GetBufSize());
    }
    template<EnumTextureFormat format>
    void Texture<format>::Clear(Texel value) {
        if constexpr (sizeof(Texture<format>::Texel) == 1) {
            memset(buf_, 0, GetBufSize());
        } else {
            for (size_t y = 0; y < height_; ++y)
                for (size_t x = 0; x < width_; ++x)
                    buf_[y * width_ + x] = value;
        }
    }

    template<EnumTextureFormat format>
    void Texture<format>::ReadFromTGAFile(const char* filename_without_extension) {
        static_assert(format == EnumTextureFormat::R8G8B8A8 || format == EnumTextureFormat::G8);

        this->Clean_();

        std::string filename = std::string(filename_without_extension) + ".tga";
        FILE* fp = FMOpenFileForRead(filename.c_str());
        tga::StdioFileInterface file(fp);
        tga::Decoder decoder(&file);
        tga::Header header;
        if (!decoder.readHeader(header))
            LGDieOnError("error reading header of TGA file ", filename);

        tga::Image image;
        image.bytesPerPixel = header.bytesPerPixel();
        LGAssert(header.bytesPerPixel() == sizeof(Texel), "TGA image format in code is not compatible with file ", filename);
        image.rowstride = header.width * header.bytesPerPixel();

        width_ = header.width;
        height_ = header.height;
        buf_ = MMMalloc(GetBufSize());
        std::vector<uint8_t> buffer(image.rowstride * header.height);
        image.pixels = static_cast<uint8_t*>(buf_);

        if (!decoder.readImage(header, image, nullptr))
            LGDieOnError("error reading data of TGA file ", filename);

        decoder.postProcessImage(header, image);

        FMCloseFileForRead(fp);

        LOGGER() << "initialized texture from TGA file " << filename << '\n';
    }

    template<EnumTextureFormat format>
    void Texture<format>::WriteToTGAFile(const char* filename_without_extension, bool change_name_if_name_collides) {
        static_assert(format == EnumTextureFormat::R8G8B8A8 || format == EnumTextureFormat::G8);

        FILE* fp;
        std::string filename = std::string(filename_without_extension);
        if (!change_name_if_name_collides) {
            filename += ".tga";
            fp = FMOpenFileForWrite(filename.c_str());
        } else {
            auto [fp_new, res_str] = FMOpenFileForWriteDontOverWrite(filename_without_extension, ".tga");
            fp = fp_new;
            filename = res_str;
        }
        tga::StdioFileInterface file(fp);
        tga::Encoder encoder(&file);
        tga::Header header{};
        header.idLength = 0;
        header.colormapType = 0;
        header.imageType = format == EnumTextureFormat::R8G8B8A8 ? 2 : 3;
        header.xOrigin = 0;
        header.yOrigin = 0;
        header.width = width_;
        header.height = height_;
        header.bitsPerPixel = format == EnumTextureFormat::R8G8B8A8 ? 32 : 8;
        header.imageId = format == EnumTextureFormat::R8G8B8A8 ? 8 : 1;

        encoder.writeHeader(header);

        tga::Image image;
        image.bytesPerPixel = header.bytesPerPixel();
        image.rowstride = header.width * image.bytesPerPixel;
        image.pixels = static_cast<uint8_t*>(static_cast<void*>(buf_));

        encoder.writeImage(header, image, nullptr);
        encoder.writeFooter();

        FMCloseFileForWrite(fp);

        LOGGER() << "wrote TGA file " << filename << " from texture\n";
    }

    using TextureRGBA = Texture<EnumTextureFormat::R8G8B8A8>;
    using TextureGrayscale = Texture<EnumTextureFormat::G8>;
    
}