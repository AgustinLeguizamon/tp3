//
// Created by agustin on 22/5/20.
//

#include "server_menssenger.h"
#include <string>

#define MAX_NUMBERS 3

std::string Menssenger::writeResponse(unsigned int good,
        unsigned int regular, unsigned int bad) const {
    std::string response;

    std::string s_good;
    std::string s_regular;
    std::string s_bad;

    std::string separator = "";
    if (good < MAX_NUMBERS && regular < MAX_NUMBERS && bad < MAX_NUMBERS){
       separator = ", ";
    }
    if (good > 0){
        s_good = std::to_string(good) + " bien" + separator;
    }
    if (regular > 0){
        s_regular = std::to_string(regular) + " regular" + separator;
    }
    
    response = s_good + s_regular;

    if (bad == MAX_NUMBERS){
        response = std::to_string(bad) + " mal";
    }

    size_t pos = response.find_last_of(',');
    if (pos != std::string::npos){
        response = response.substr(0, pos);
    }

    return response;
}

std::string Menssenger::writeYouWinMsg() const {
    return "Ganaste";
}

std::string Menssenger::writeHelpMsg() const {
    std::string help_message = "Comandos válidos:\n\t"
                               "AYUDA: despliega la lista de comandos "
                               "válidos\n\t"
                               "RENDIRSE: pierde el juego automáticamente\n\t"
                               "XXX: Número de 3 cifras a ser "
                               "enviado al servidor "
                               "para adivinar el número secreto";

    return help_message;
}

std::string Menssenger::writeYouLoseMsg() const {
    return "Perdiste";
}

std::string Menssenger::writeInvalidNumberMsg() const {
    return "Número inválido. Debe ser de 3 cifras no repetidas";
}

Menssenger::Menssenger() : functor(0){}
