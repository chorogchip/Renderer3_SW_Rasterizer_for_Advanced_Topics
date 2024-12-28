#pragma once

#include <cstddef>
#include <string>
#include <cstdio>

namespace sr {

    // Init FileManager. Call it after call LGInit().
    extern void FMInit();

    // Clear FileManager. Call it before call LGClean().
    extern void FMClean();



    // writes data to a file. this can overwrite data. if failed, it terminates program with log.
    extern void FMWriteToFile(const char* filename, const void* buf, size_t size);

    // writes data to a file. if a file with same name already exists, then it try to put ascending number after suffix and store iteratively.
    // if failed to store, it terminates program with log.
    // returns name of the stored file.
    extern std::string FMWriteToFileDontOverWrite(const char* filename_prefix, const char* filename_suffix, const void* buf, size_t size);

    // reads data from file to memory.
    // if failed to read, it terminates program with log.
    extern void FMReadFromFile(void* buf, const char* filename, size_t max_size);

    // get opened FILE* to read data from file.
    // if failed to read, it terminates program with log.
    extern FILE* FMOpenFileForRead(const char* filename);
    
    // close FILE* to read data from file.
    extern void FMCloseFileForRead(FILE* fp);
    
}