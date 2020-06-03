//
// Created by agustin on 3/6/20.
//

#include <string>
#include "server_game.h"
#define ATTEMPTS 10
#define MAX_GUEST_NUMBER 999
#define MIN_GUEST_NUMBER 100
#define CORRECT_GUEST 3
#define HELP_COMMAND 'h'
#define SURRENDER_COMMAND 's'
#define NUMBER_COMMAND 'n'

Game::Game(uint16_t number) :
    number_to_guest(number),
    client_attempts_left(ATTEMPTS),
    still_playing(true),
    is_client_winner(false)
    {}

Game::Game(Game &&other) noexcept :
    number_to_guest(other.number_to_guest),
    client_attempts_left(ATTEMPTS),
    still_playing(true),
    is_client_winner(false)
    {}

std::string Game::process(const char &c) {
    std::string response;
    if (c == HELP_COMMAND){
        response = menssenger.sendHelp();
    } else if (c == SURRENDER_COMMAND) {
        client_attempts_left = 0;
        still_playing = false;
        response = menssenger.sendYouLose();
    }
    return response;
}

std::string Game::process(uint16_t guest) {
    std::string response = tryToGuest(guest);
    if (client_attempts_left <= 0){
        still_playing = false;
        response = menssenger.sendYouLose();
    }
    return response;
}

std::string Game::tryToGuest(uint16_t guest) {
    std::string response;

    if (guest > MAX_GUEST_NUMBER || guest < MIN_GUEST_NUMBER){
        response = menssenger.getInvalidNumberMsj();
        this->client_attempts_left--;
    } else {
        response = this->tryToGuestValidNumber(guest);
    }

    return response;
}

std::string Game::tryToGuestValidNumber(uint16_t guest) {
    std::string s_guest = std::to_string(guest);
    std::string s_number_to_guest = std::to_string(number_to_guest);

    std::string visited_number;
    bool repeated_number=false;
    int i=0;
    unsigned int good= 0, bad=0, regular=0;
    size_t pos;
    for (auto & guest_character : s_guest){
        if (visited_number.find(guest_character) != std::string::npos){
            repeated_number = true;
            break;
        }
        visited_number += guest_character;
        pos = s_number_to_guest.find(guest_character);
        if (s_number_to_guest[i] == guest_character){
            good +=1;
        } else if (pos == std::string::npos) {
            bad +=1;
        } else if (pos >= 0){
            regular +=1;
        }
        i++;
    }

    std::string response;
    if (repeated_number){
        response = menssenger.getInvalidNumberMsj();
        client_attempts_left--;
    } else if (good == CORRECT_GUEST){
        still_playing = false;
        is_client_winner = true;
        response = menssenger.sendWinResponse();
    } else {
        client_attempts_left--;
        response = this->menssenger.sendResponse(good, regular, bad);
    }

    return response;
}

bool Game::isStillPlaying(){
    return still_playing;
}

bool Game::isWinner(){
    return is_client_winner;
}
