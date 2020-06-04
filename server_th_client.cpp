//
// Created by agustin on 24/5/20.
//

#include "server_th_client.h"
#include <string>
#include <utility>

#define HELP_COMMAND 'h'
#define SURRENDER_COMMAND 's'
#define NUMBER_COMMAND 'n'

ThClient::ThClient(Socket&& server_socket, uint16_t number,
        ProtectedCounter &counter) :
    is_running(true),
    protocol(),
    counter(counter),
    peer(std::move(server_socket)),
    game(number)
    {}


//live object
ThClient::ThClient(ThClient &&other) noexcept :
    is_running(true),
    protocol(),
    counter(other.counter),
    peer(std::move(other.peer)),
    game(std::move(other.game))
    {}


void ThClient::run() {
    while (game.isStillPlaying()){
        this->recieve();
    }
    counter.increase(game.isWinner());
}

bool ThClient::isRunning() const{
    return is_running;
}

void ThClient::recieve() {
    char c_cmd;
    peer.recieve(&c_cmd, sizeof(char));
    std::string response;
    if (c_cmd == HELP_COMMAND || c_cmd == SURRENDER_COMMAND){
        response = game.process(c_cmd);
    } else if (c_cmd == NUMBER_COMMAND){
        uint16_t guest = protocol.recieve(this->peer,0);
        response = game.process(guest);
    }
    protocol.send(this->peer, response);
}

ThClient::~ThClient() {
    is_running = false;
}

