#pragma once

#include <cstdint>
#include <array>

namespace sr {
    
    namespace Color {
        struct RGBA8 {
            uint8_t r, g, b, a;
            constexpr RGBA8(): r(0), g(0), b(0), a(0) {}
            constexpr explicit RGBA8(uint32_t val): r(val>>24), g(val>>16), b(val>>8), a(val) {}
            constexpr explicit RGBA8(uint8_t red, uint8_t green, uint8_t blue): r(red), g(green), b(blue), a(0xff) {}
            constexpr explicit RGBA8(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha): r(red), g(green), b(blue), a(alpha) {}
        };
        
        inline constexpr RGBA8 BLACK{0, 0, 0};
        inline constexpr RGBA8 DARK_GREY{64, 64, 64};
        inline constexpr RGBA8 GREY{128, 128, 128};
        inline constexpr RGBA8 LIGHT_GREY{192, 192, 192};
        inline constexpr RGBA8 WHITE{255, 255, 255};
        inline constexpr RGBA8 RED{255, 0, 0};
        inline constexpr RGBA8 ORANGE{255, 128, 0};
        inline constexpr RGBA8 YELLOW{255, 255, 0};
        inline constexpr RGBA8 NEON{128, 255, 0};
        inline constexpr RGBA8 GREEN{0, 255, 0};
        inline constexpr RGBA8 MINT{0, 255, 128};
        inline constexpr RGBA8 SKYBLUE{0, 255, 255};
        inline constexpr RGBA8 CYAN{0, 128, 255};
        inline constexpr RGBA8 BLUE{0, 0, 255};
        inline constexpr RGBA8 VIOLET{128, 0, 255};
        inline constexpr RGBA8 PINK{255, 0, 255};
        inline constexpr RGBA8 MAGENTA{255, 0, 128};
    };

}