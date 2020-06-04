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
    /*Abre el archivo de nombre @param file_name*/
    explicit FileReader(const std::string &file_name);

    /*Lee una linea completa del archivo, y lo convierte a uint16*/
    uint16_t readNextNumber();
};


#endif //TP3CLION_SERVER_FILE_READER_H
