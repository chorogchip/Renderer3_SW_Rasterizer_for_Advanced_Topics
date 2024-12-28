#include <iostream>

#include "Logger.h"
#include "MemoryManager.h"
#include "FileManager.h"
#include "Texture.h"

int main(int argc, char** argv) {
    using namespace sr;
    LGInit();
    MMInit();
    FMInit();

    TextureRGBA image;

    FMClean();
    MMClean();
    LGClean();
    return 0;
}