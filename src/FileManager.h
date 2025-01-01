#pragma once

#include <utility>
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
    extern void FMReadFromFile(void* buf, const char* filename, size_t max_size);

    // get opened FILE* to read data from file.
    extern FILE* FMOpenFileForRead(const char* filename);
    
    // close FILE* to read data from file.
    extern void FMCloseFileForRead(FILE* fp);

    // get opened FILE* to write data from file.
    extern FILE* FMOpenFileForWrite(const char* filename);
    
    // get opened FILE* to write data from file.
    // if a file with same name already exists, then it try to put ascending number after suffix and store iteratively.
    // returns name of the opened file.
    extern std::pair<FILE*, std::string> FMOpenFileForWriteDontOverWrite(const char* filename_prefix, const char* filename_suffix);
    
    // close FILE* to write data from file.
    extern void FMCloseFileForWrite(FILE* fp);
    
}