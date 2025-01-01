#include "Bresenham.h"

#include <cstdlib>
#include <algorithm>
#include <functional>

#include "Logger.h"

namespace sr::bresenham {
    void DrawLine(int x1, int y1, int x2, int y2, std::function<void(int,int)> draw_func) {
        const int dx = x2 - x1;
        const int dy = y2 - y1;
        const int adx = std::abs(dx);
        const int ady = std::abs(dy);
        const int incr = 1 - ((static_cast<unsigned>(dx ^ dy) >> 30U) & 2);
        if (adx > ady) {
            // x incrementing
            if (x2 < x1) { std::swap(x1, x2); std::swap(y1, y2); }
            int x = x1;
            int y = y1;
            const int det_add1 = 2 * ady;
            const int det_add2 = 2 * (ady - adx);
            int det = 2 * ady - adx;
            for (; x <= x2; ++x) {
                draw_func(x, y);
                if (det < 0) det += det_add1;
                else { det += det_add2; y += incr; }
            }
        } else {
            // y incrementing
            if (y2 < y1) { std::swap(x1, x2); std::swap(y1, y2); }
            int x = x1;
            int y = y1;
            const int det_add1 = 2 * adx;
            const int det_add2 = 2 * (adx - ady);
            int det = 2 * adx - ady;
            for (; y <= y2; ++y) {
                draw_func(x, y);
                if (det < 0) det += det_add1;
                else { det += det_add2; x += incr; }
            }
        }
    }
}