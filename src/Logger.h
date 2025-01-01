#pragma once

#include <fstream>

namespace sr {
    
    [[maybe_unused]]  // this function is used, but for turn off wrong compiler warning
    static void _PrintMessages() {}

    template<typename... MSGs>
    static void _PrintMessages(const char* msg, MSGs... messages) {
        fputs(msg, stdout);
        _PrintMessages(messages...);
    }

    template<typename... MSGs>
    void LGDieOnError(const char* msg, MSGs... messages) {
        fputs("Error: ", stdout);
        _PrintMessages(msg, messages...);
        fputs("\nApp Terminating.\n", stdout);
        fflush(nullptr);
        exit(0);
    }

    template<typename... MSGs>
    void LGAssert(bool condition, const char* error_msg, MSGs... error_messages) {
        if (!condition) {
            fputs("Error (assertion failed) : ", stdout);
            _PrintMessages(error_msg, error_messages...);
            fputs("\nApp Terminating.\n", stdout);
            fflush(nullptr);
            exit(0);
        }
    }

    extern void LGInit();
    extern void LGClean();
    extern std::ofstream& LOGGER();
}