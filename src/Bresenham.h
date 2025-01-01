#pragma once

#include <functional>

namespace sr::bresenham {
    extern void DrawLine(int x1, int y1, int x2, int y2, std::function<void(int,int)> draw_func);
}