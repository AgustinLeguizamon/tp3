//
// Created by agustin on 22/5/20.
//

#include "server_file_reader.h"
#include "common_oserror_exception.h"
#include <string>

FileReader::FileReader(const std::string &file_name) {
    this->fs.open(file_name);
    if (!fs.is_open()){
        throw OSError("El archivo no se pudo abrir, "
                      "clase FileReader, file_name: %s, "
                      "linea %d", file_name.c_str(), 12);
    }
}

uint16_t FileReader::readNextNumber(){
    std::string s_number;

    if (fs.eof()){
        fs.seekg(0);
    }
    getline(this->fs, s_number);

    uint16_t number = stoi(s_number, nullptr, 10);

    return number;
}


