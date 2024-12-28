#include "FileManager.h"

#include <sys/stat.h>
#include <cstdio>
#include <cstring>

#include "Logger.h"

namespace sr {
    static bool FMIsFileExists(const char* filename) {
        struct stat buf;
        return stat(filename, &buf) == 0;
    }
    
    void FMInit() {

    }

    void FMClean() {

    }
    
    void FMWriteToFile(const char* filename, const void* buf, size_t size) {
        FILE* fp = std::fopen(filename, "wb");
        if (fp == nullptr) {
            LGDieOnError("cannot open file ", filename);
        }
        const size_t written_bytes = std::fwrite(buf, 1, size, fp);
        std::fclose(fp);
        LOGGER() << "wrote " << written_bytes << " bytes to file [" << filename << "]\n";
    }

    std::string FMWriteToFileDontOverWrite(const char* filename_prefix, const char* filename_suffix, const void* buf, size_t size) {
        std::string filename_final = std::string(filename_prefix) + filename_suffix;
        for (int id = 1; FMIsFileExists(filename_final.c_str()); ++id) {
            filename_final = std::string(filename_prefix) + std::to_string(id) + filename_suffix;
        }
        FILE* fp = std::fopen(filename_final.c_str(), "wb");
        if (fp == nullptr) {
            LGDieOnError("cannot open file ", filename_final.c_str());
        }
        const size_t written_bytes = std::fwrite(buf, 1, size, fp);
        std::fclose(fp);
        LOGGER() << "wrote " << written_bytes << " bytes to file [" << filename_final << "]\n";
        return filename_final;
    }

    void FMReadFromFile(void* buf, const char* filename, size_t max_size) {
        FILE* fp = std::fopen(filename, "rb");
        if (fp == nullptr) {
            LGDieOnError("cannot open file ", filename);
        }
        const size_t read_bytes = std::fread(buf, 1, max_size, fp);
        std::fclose(fp);
        LOGGER() << "read " << read_bytes << " bytes from file [" << filename << "]\n";
    }

    extern FILE* FMOpenFileForRead(const char* filename) {
        FILE* fp = std::fopen(filename, "rb");
        if (fp == nullptr) {
            LGDieOnError("cannot open file ", filename);
        }
        LOGGER() << "opened file descriptor [" << (size_t)fp << "]\n";
        return fp;
    }
    
    extern void FMCloseFileForRead(FILE* fp) {
        std::fclose(fp);
        LOGGER() << "closed file descriptor [" << (size_t)fp << "]\n";
    }
}