#include <iostream>

#include "Logger.h"
#include "MemoryManager.h"
#include "FileManager.h"
#include "Texture.h"
#include "Bresenham.h"
#include "Vector.h"

int main(int argc, char** argv) {
    using namespace sr;
    LGInit();
    MMInit();
    FMInit();
    LOGGER() << "program started to run successfully\n";

    /*
    TextureRGBA image(100, 100);
    image.Clear(Color::NEON);

    std::tuple<int,int,int,int> indices[3] { {10, 10, 90, 20}, {90, 20, 50, 90}, {60, 90, 10, 20} };

    for(auto [x1, y1, x2, y2] : indices)
        bresenham::DrawLine(x1, y1, x2, y2, [&](int x, int y){
            image.At(x, y) = Color::RED;
        });

    image.WriteToTGAFile("output_images/test1_file", true);*/
    Vector2<float> v1, v2(1, 2);
    v1 = v1 + v2;
    v1 *= 4;
    float a = v1.dot(v2);

    LOGGER() << "program started to close\n";
    FMClean();
    MMClean();
    LGClean();
    return 0;
}