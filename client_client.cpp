//
// Created by agustin on 22/5/20.
//

#include <iostream>
#include <byteswap.h>
#include <climits>
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
    /*std::string s_response;
    if (input == "AYUDA") {
        this->protocol.send(this->client_socket, HELP_COMMAND);
        s_response = this->protocol.recieve(this->client_socket);
        //still_playing = this->sendCommand(&command);
    } else if (input == "RENDIRSE") {
        this->protocol.send(this->client_socket, SURRENDER_COMMAND);
        s_response = this->protocol.recieve(this->client_socket);
        //falta que stillplaying pase a ser 0 para terminar
        //still_playing = this->sendCommand(&command);
    } else {
        //envio el comando como siempre
        //por overload al recibir un number protocol.send le aplica el endianess
        uint16_t guest = this->isValid(input);
        if(guest){
            protocol.send(this->client_socket, NUMBER_COMMAND);
            protocol.send(this->client_socket, guest);
            s_response = this->protocol.recieve(this->client_socket);
            //still_playing = this->sendGuestNumber(guest);
        }
    }

    std::cout << s_response << std::endl;
    if (s_response == "Ganaste" || s_response == "Perdiste"){
        still_playing = 0;
    }
    */
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

//hacer clase protocolo que haga esto
int Client::sendGuestNumber(uint16_t guest)  {
    const char command = NUMBER_COMMAND;
    this->client_socket.send(&command, sizeof(char));
    uint16_t big_end_guest = proxyBigEndian(guest);
    this->client_socket.send(&big_end_guest, sizeof(uint16_t));
    int still_playing = this->recieveResponse();
    return still_playing;
}

//clase protocolo, como el socket compartido entre server y cliente
uint32_t Client::valueToBigEndian(const uint32_t value) const{
    uint32_t little_end = ntohl(value); //pasa a little endian
    uint32_t big_end = bswap_32(little_end); //

    return big_end;
}

uint16_t Client::proxyBigEndian(const uint16_t value) const{
    uint16_t big_end = htons(value);
    return big_end;
}

uint32_t Client::proxyToLocalEndian(const uint32_t size) const{
    uint32_t local_end = ntohl(size);
    return local_end;
}

//clase protocolo
int Client::sendCommand(const char *command) {
    this->client_socket.send(command, sizeof(char));
    int still_playing = this->recieveResponse();

    return still_playing;
}

int Client::recieveResponse(){
    uint32_t size;
    this->client_socket.recieve(&size, sizeof(uint32_t));
    size = proxyToLocalEndian(size);
    std::string response(size,0);
    char* p_response = (char*) response.c_str();
    int still_playing = this->client_socket.recieve(p_response, size);
    //
    std::string s_response(p_response);
    if (s_response == "Ganaste" || s_response == "Perdiste"){
        still_playing = 0;
    }

    std::cout << s_response << std::endl;

    return still_playing;
}

void Client::operator()() {
    //tengo que ingresar un numero mas antes de que socket_state 
    // sea 0 pq el server cerro el socket server_socket
    std::string input;
    while (std::getline(std::cin,input) && this->process(input)){}
 }

uint16_t Client::isValid(std::string &input) {
    const char *p_input = input.c_str();
    char *p_input_end;
    const long number = std::strtol(p_input, &p_input_end, 10);
    uint16_t guest = 0;
    //chequeo si es mas de un parametro buscando un espacio
    if ((input.find(' ', 0)) != std::string::npos) {
        std::cout << "Error: argumentos invalidos." << std::endl;
    } else if (number > USHRT_MAX || number <= 0) {
        //debe ser un numero valido, representable en 2 bytes y positivo
        std::cout << "Error: comando inválido. "
                     "Escriba AYUDA para obtener ayuda" << std::endl;
    } else {
        //puedo hacer el casteo de long a uint16 pq es menor a USHRT_MAX
        guest = number;
    }

    return guest;
}
