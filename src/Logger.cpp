#include "Logger.h"
#include <cstdarg>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fstream>


namespace sr {
    

    static std::ofstream log_stream;

    void LGInit() {
        const auto now = std::chrono::system_clock::now();
        const time_t tt = std::chrono::system_clock::to_time_t(now);
        tm loc_time{};
        localtime_r(&tt, &loc_time);
        const char* log_dir = "logs";
        char buf[256];
        snprintf(buf, sizeof(buf),
            "%s/Log-%d-%02d-%02d-%02d:%02d:%02d.txt",
            log_dir,
            loc_time.tm_year+1900,
            loc_time.tm_mon+1,
            loc_time.tm_mday,
            loc_time.tm_hour,
            loc_time.tm_min,
            loc_time.tm_sec);
        log_stream = std::ofstream(buf);
        if (!log_stream.is_open()) {
            LGDieOnError("Failed to open log file");
        }

    }
    void LGClean() {
        log_stream.close();
    }
    
    std::ofstream& LOGGER() {
        return log_stream;
    }
}