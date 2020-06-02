//
// Created by agustin on 1/6/20.
//

#include <string>
#include "common_protocol.h"

int Protocol::send(Socket &socket,const char c){
    socket.send(&c, sizeof(char));
    return 0;
}

int Protocol::send(Socket &socket,uint16_t number){
    uint16_t big_end_guest = valueToBigEndian(number);
    socket.send(&big_end_guest, sizeof(uint16_t));
    return 0;
}

std::string Protocol::recieve(Socket &socket){
    uint32_t size;
    socket.recieve(&size, sizeof(uint32_t));
    size = valueToLocalEndian(size);
    std::string response(size,0);
    char* p_response = (char*) response.c_str();
    socket.recieve(p_response, size);
    std::string s_response(p_response);

    return s_response;
}

uint16_t Protocol::valueToBigEndian(const uint16_t value) const{
    uint16_t big_end = htons(value);
    return big_end;
}

//server side
uint32_t Protocol::valueToBigEndian(const uint32_t value) const{
    uint32_t big_end = htons(value);
    return big_end;
}

uint32_t Protocol::valueToLocalEndian(const uint32_t value) const{
    uint32_t local_end = ntohl(value);
    return local_end;
}

//server side
uint16_t Protocol::valueToLocalEndian(const uint16_t value) const{
    uint16_t local_end = ntohl(value);
    return local_end;
}

