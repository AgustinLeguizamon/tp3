//
// Created by agustin on 3/6/20.
//

#ifndef TP3CLION_SERVER_GAME_H
#define TP3CLION_SERVER_GAME_H


#include <cstdint>
#include <string>
#include "server_menssenger.h"

class Game {
private:
    Menssenger menssenger;
    uint16_t number_to_guest;
    unsigned int client_attempts_left;
    bool still_playing;
    bool is_client_winner;

public:
    /*Ctor, con el numero @param a adivinar*/
    explicit Game(uint16_t number);

    Game(Game &&other) noexcept;

    /*Devuelve un string segun el tipo de comando @param c*/
    std::string process(const char &c);

    /*Devuelve un string con la cantidad de numeros acertados o
     * si el jugador gano o perdio*/
    std::string process(uint16_t guest);

    bool isStillPlaying() const;

    bool isWinner() const;

private:
    /*Verifica que el numero sea valido, caso contrario devuelve
     * un string con el msg de error*/
    std::string tryToGuest(uint16_t guest);

    /*Verifica si los 3 numeros son correctos, caso contrario
     * devuelve un string con la cantidad de aciertos*/
    std::string tryToGuestValidNumber(uint16_t guest);
};


#endif //TP3CLION_SERVER_GAME_H
