//
// Created by agustin on 22/5/20.
//

#include <iostream>
#include <string>
#include "client_client.h"
#include "common_command.h"

#define SURRENDER_COMMAND 's'
#define HELP_COMMAND 'h'
#define NUMBER_COMMAND 'n'
#define YOU_WON_MSG "Ganaste"
#define YOU_LOSE_MSG "Perdiste"

Client::Client(const char* host_name, const char* service) :
    client_socket(),
    protocol(){
    client_socket.connect(host_name, service);
}

int Client::process(std::string &input) {
    int still_playing = 1;
    // issue #3
    Command *cmd = this->cmdFactory.get(input);
    if (cmd){
        (*cmd) (this->protocol, this->client_socket);
        std::string response = this->protocol.recieve(this->client_socket);
        std::cout << response << std::endl;
        if (response == YOU_WON_MSG || response == YOU_LOSE_MSG){
            still_playing = 0;
        }
        cmd->free();
    }
    return still_playing;
}


void Client::operator()() {
    std::string input;
    while (std::getline(std::cin,input) && this->process(input)){}
 }

