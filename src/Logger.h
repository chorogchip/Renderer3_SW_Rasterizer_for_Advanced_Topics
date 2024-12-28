#pragma once

#include <fstream>

namespace sr {

    static void _LGDieOnError() {}

    template<typename... MSGs>
    static void _LGDieOnError(const char* msg, MSGs... messages) {
        fputs(msg, stdout);
        _LGDieOnError(messages...);
    }

    template<typename... MSGs>
    void LGDieOnError(const char* msg, MSGs... messages) {
        fputs("Error: ", stdout);
        _LGDieOnError(msg, messages...);
        fputs("\nApp Terminating.\n", stdout);
        fflush(nullptr);
        exit(0);
    }

    extern void LGInit();
    extern void LGClean();
    extern std::ofstream& LOGGER();
}