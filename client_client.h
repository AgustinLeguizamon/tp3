//
// Created by agustin on 22/5/20.
//

#ifndef TP3CLION_CLIENT_CLIENT_H
#define TP3CLION_CLIENT_CLIENT_H


#include <cstdint>
#include "server_server.h"
#include "common_socket.h"

class Client {
private:
    Socket client_socket;
    int socket_state;
    
public:
    Client(const char* host_name, const char* service);

    Client(const Client &other) = delete;

    void write();

    void operator()();

private:
    void sendGuestNumber(uint16_t guest);

    uint32_t valueToBigEndian(uint32_t value) const;

    void sendCommand(const char *command);

    void recieveResponse();
};


#endif //TP3CLION_CLIENT_CLIENT_H
