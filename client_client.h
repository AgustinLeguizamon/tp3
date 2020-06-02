//
// Created by agustin on 22/5/20.
//

#ifndef TP3CLION_CLIENT_CLIENT_H
#define TP3CLION_CLIENT_CLIENT_H


#include <cstdint>
#include <string>
#include "server_server.h"
#include "common_socket.h"
#include "common_protocol.h"
#include "common_command_factory.h"

class Client {
private:
    Socket client_socket;
    Protocol protocol;
    CommandFactory cmdFactory;

public:
    /*Constructor
     * Se conecta al puerto @param service */
    Client(const char* host_name, const char* service);

    Client(const Client &other) = delete;

    /*Ejecuta el metodo process mientras el socket no este cerrado*/
    void operator()();

private:
    /*Envia por el socket los comandos segun la entrada
     * estandar que sea valida*/
    int process(std::string &input);
};


#endif //TP3CLION_CLIENT_CLIENT_H
