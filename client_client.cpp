//
// Created by agustin on 22/5/20.
//

#include <iostream>
#include <byteswap.h>
#include <climits>
#include <string>
#include "client_client.h"

#define SURRENDER_COMMAND 's'
#define HELP_COMMAND 'h'
#define NUMBER_COMMAND 'n'

Client::Client(const char* host_name, const char* service) :
    client_socket(), socket_state(1){
    client_socket.connect(host_name, service);
}

int Client::process(std::string &input) {
    int still_playing = 1;
    if (input == "AYUDA") {
        const char command = HELP_COMMAND;
        still_playing = this->sendCommand(&command);
    } else if (input == "RENDIRSE") {
        const char command = SURRENDER_COMMAND;
        still_playing = this->sendCommand(&command);
    } else {
        const char *p_input = input.c_str();
        char *p_input_end;
        const long number = std::strtol(p_input, &p_input_end, 10);

        //chequeo si es mas de un parametro buscando un espacio
        if ((input.find(' ', 0)) != std::string::npos) {
            std::cout << "Error: argumentos invalidos." << std::endl;
        } else if (number > USHRT_MAX || number <= 0) {
            //debe ser un numero valido, representable en 2 bytes y positivo
            std::cout << "Error: comando inválido. "
                         "Escriba AYUDA para obtener ayuda" << std::endl;
        } else {
            //puedo hacer el casteo de long a uint16 pq es menor a USHRT_MAX
            uint16_t guest = number;
            still_playing = this->sendGuestNumber(guest);
        }
    }

    return still_playing;
}

//hacer clase protocolo que haga esto
int Client::sendGuestNumber(uint16_t guest)  {
    const char command = NUMBER_COMMAND;
    this->client_socket.send(&command, sizeof(char));
    uint16_t big_end_guest = valueToBigEndian(guest);
    this->client_socket.send(&big_end_guest, sizeof(uint16_t));
    int still_playing = this->recieveResponse();
    return still_playing;
}

//clase protoclo, como el socket compartido entre server y cliente
uint32_t Client::valueToBigEndian(const uint32_t value) const{
    uint32_t little_end = ntohl(value); //pasa a little endian
    uint32_t big_end = bswap_32(little_end); //

    return big_end;
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
