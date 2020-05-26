//
// Created by agustin on 22/5/20.
//

#ifndef TP3CLION_SERVER_FILE_READER_H
#define TP3CLION_SERVER_FILE_READER_H

#include <fstream>
#include <string>

class FileReader {
private:
    std::ifstream fs;

public:
    explicit FileReader(const std::string &file_name);

    uint16_t readNextNumber();
};


#endif //TP3CLION_SERVER_FILE_READER_H
