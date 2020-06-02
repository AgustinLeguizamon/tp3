//
// Created by agustin on 24/5/20.
//

#include "server_th_client.h"
#include "common_command.h"
#include <string>

#define HELP_COMMAND 'h'
#define SURRENDER_COMMAND 's'
#define NUMBER_COMMAND 'n'
#define MAX_GUEST_NUMBER 999
#define MIN_GUEST_NUMBER 100
#define CORRECT_GUEST 3
#define ATTEMPTS 10

ThClient::ThClient(Socket&& server_socket, uint16_t number,
        ProtectedCounter &counter) :
    is_running(true),
    protocol(),
    counter(counter),
    peer(std::move(server_socket)),
    number_to_guest(number),
    client_attempts_left(ATTEMPTS),
    client_win(false){
}


//live object
ThClient::ThClient(ThClient &&other) noexcept :
    is_running(true),
    protocol(),
    counter(other.counter),
    peer(std::move(other.peer)),
    number_to_guest(other.number_to_guest),
    client_attempts_left(ATTEMPTS),
    client_win(false)
    {}


void ThClient::run() {
    while ((this->client_attempts_left > 0) && !this->client_win){
        this->recieve();
    }
    counter.increase(client_win);
    peer.shutdown(SHUT_RDWR);
    peer.close();
}

bool ThClient::isRunning(){
    return is_running;
}

void ThClient::recieve() {
    char c_cmd;
    peer.recieve(&c_cmd, sizeof(char));
    //Command *cmd = this->cmdFactory.get(c_cmd);
    std::string response;
    if (c_cmd == HELP_COMMAND){
        //command help (server)
        response = menssenger.sendHelp();
    } else if (c_cmd == SURRENDER_COMMAND){
        //command surrender
        client_attempts_left = 0;
    } else if (c_cmd == NUMBER_COMMAND){
        //command number
        uint16_t guest = protocol.recieve(this->peer,0);
        response = this->tryToGuest(guest);
    }
    if (client_attempts_left == 0){
        response = menssenger.sendYouLose();
    }
    protocol.send(this->peer, response);
}

/**HAcer una clase Game o resolverlo dentro del Command
 * Number con command factory*/
std::string ThClient::tryToGuest(uint16_t guest) {
    std::string response;

    if (guest > MAX_GUEST_NUMBER || guest < MIN_GUEST_NUMBER){
        response = menssenger.getInvalidNumberMsj();
        this->client_attempts_left--;
    } else {
        response = this->tryToGuestValidNumber(guest);
    }

    return response;
}

std::string ThClient::tryToGuestValidNumber(uint16_t guest) {
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
        client_win = true;
        response = menssenger.sendWinResponse();
    } else {
        client_attempts_left--;
        response = this->menssenger.sendResponse(good, regular, bad);
    }

    return response;
}

ThClient::~ThClient() {
    is_running = false;
}


