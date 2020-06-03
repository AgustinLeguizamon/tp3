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
    explicit Game(uint16_t number);

    Game(Game &&other) noexcept;

    std::string process(const char &c);

    std::string process(uint16_t guest);

    bool isStillPlaying();

    bool isWinner();

private:
    std::string tryToGuest(uint16_t guest);

    std::string tryToGuestValidNumber(uint16_t guest);
};


#endif //TP3CLION_SERVER_GAME_H
