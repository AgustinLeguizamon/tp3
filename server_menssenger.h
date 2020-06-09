//
// Created by agustin on 22/5/20.
//

#ifndef TP3CLION_SERVER_MENSSENGER_H
#define TP3CLION_SERVER_MENSSENGER_H

#include <stdint-gcc.h>
#include <string>

class Menssenger {
public:
    Menssenger() = default;

    Menssenger (const Menssenger& other) = delete;

    /*Devuelve un string con la cantidad de aciertos dados por 
     * @param good, regular, bad*/
    std::string writeResponse(unsigned int good, unsigned int regular,
                              unsigned int bad) const;

    /*Devuelve un string con mensaje de victoria*/
    std::string writeYouWinMsg() const;

    /*Devuelve un string con informacion sobre como funciona el juego*/
    std::string writeHelpMsg() const;

    /*Devuelve un string con msg de derrota*/
    std::string writeYouLoseMsg() const;

    /*Devuelve un string de error*/
    std::string writeInvalidNumberMsg() const;
};


#endif //TP3CLION_SERVER_MENSSENGER_H
