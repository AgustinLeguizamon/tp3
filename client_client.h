//
// Created by agustin on 22/5/20.
//

#ifndef TP3CLION_CLIENT_CLIENT_H
#define TP3CLION_CLIENT_CLIENT_H


#include <cstdint>
#include <string>
#include "server_server.h"
#include "common_socket.h"

class Client {
private:
    Socket client_socket;
    int socket_state;
    
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

    /*Enviar por el socket @param guest*/
    int sendGuestNumber(uint16_t guest);

    /*Convierte en formato big_endian al @param value */
    uint32_t valueToBigEndian(uint32_t value) const;

    /*Envia por el socket @param command*/
    int sendCommand(const char *command);

    /*Recibe por el socket el largo del string y un string*/
    int recieveResponse();
};


#endif //TP3CLION_CLIENT_CLIENT_H
