//
// Created by agustin on 1/6/20.
//

#include <climits>
#include <string>
#include "common_command_factory.h"
#include "common_command.h"

Command *CommandFactory::get(const std::string &input) {
    if (input == "RENDIRSE"){
        return new Surrender();
    }
    if (input == "AYUDA"){
        return new Help();
    } else {
        const char *p_input = input.c_str();
        char *p_input_end;
        const long number = std::strtol(p_input, &p_input_end, 10);
        uint16_t guest = 0;
        //chequeo si es mas de un parametro buscando un espacio
        if ((input.find(' ', 0)) != std::string::npos){
            std::cout << "Error: argumentos invalidos." << std::endl;
        } else if (number > USHRT_MAX || number <= 0) {
            //debe ser un numero valido, representable en 2 bytes y positivo
            std::cout << "Error: comando inválido. "
                         "Escriba AYUDA para obtener ayuda" << std::endl;
        } else {
            //puedo hacer el casteo de long a uint16 pq es menor a USHRT_MAX
            guest = number;
            return new Number(guest);
        }
    }

    return nullptr;
}
