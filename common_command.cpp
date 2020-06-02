//
// Created by agustin on 1/6/20.
//

#include "common_command.h"
#define SURRENDER_COMMAND 's'
#define HELP_COMMAND 'h'
#define NUMBER_COMMAND 'n'

void Surrender::operator()(Protocol &protocol, Socket &socket) {
    protocol.send(socket, SURRENDER_COMMAND);
}

void Surrender::free() {
    delete this;
}

void Help::operator()(Protocol &protocol, Socket &socket) {
    protocol.send(socket, HELP_COMMAND);
}

void Help::free() {
    delete this;
}

void Number::operator()(Protocol &protocol, Socket &socket) {
    protocol.send(socket, NUMBER_COMMAND);
    protocol.send(socket, number);
}

Number::Number(uint16_t number) : number(number) {}

void Number::free() {
    delete this;
}

