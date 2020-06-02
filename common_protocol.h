//
// Created by agustin on 1/6/20.
//

#ifndef TP3CLION_COMMON_PROTOCOL_H
#define TP3CLION_COMMON_PROTOCOL_H

#include <string>
#include "common_socket.h"

class Protocol {
public:
    int send(Socket &socket, char c);

    int send(Socket &socket, uint16_t number);

    std::string recieve(Socket &socket);

    //server side
    int send(Socket &socket, const std::string &msg);

    uint16_t recieve(Socket &socket, int overload);

private:
    uint16_t valueToBigEndian(uint16_t value) const;

    uint32_t valueToBigEndian(uint32_t value) const;

    uint32_t valueToLocalEndian(uint32_t value) const;

    uint16_t valueToLocalEndian(uint16_t value) const;
};


#endif //TP3CLION_COMMON_PROTOCOL_H
