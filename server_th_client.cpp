//
// Created by agustin on 24/5/20.
//

#include <byteswap.h>
#include "server_th_client.h"
#include <string>

#define HELP_COMMAND 'h'
#define SURRENDER_COMMAND 's'
#define NUMBER_COMMAND 'n'
#define MAX_GUEST_NUMBER 999
#define MIN_GUEST_NUMBER 100
#define CORRECT_GUEST 3
#define ATTEMPTS 10

ThClient::ThClient(Socket&& server_socket, uint16_t number,
        ProtectedCounter &counter) :
    keep_talking(true),
    is_running(true),
    counter(counter),
    peer(std::move(server_socket)),
    number_to_guest(number),
    client_attempts_left(ATTEMPTS),
    client_win(false){
}


//live object
ThClient::ThClient(ThClient &&other) noexcept :
    keep_talking(true),
    is_running(true),
    counter(other.counter),
    peer(std::move(other.peer)),
    number_to_guest(other.number_to_guest),
    client_attempts_left(ATTEMPTS),
    client_win(false)
    {}


void ThClient::run() {
    while ((this->client_attempts_left > 0) && !this->client_win){
        this->recieve();
    }
    counter.increase(client_win);

    peer.shutdown(SHUT_RDWR);
    peer.close();
    is_running = false;
}

//polite, no destruye el socket
//el stop lo llama el hilo principal (el del server)
void ThClient::stop() {
    keep_talking = false;
}

bool ThClient::isRunning(){
    return is_running;
}

void ThClient::recieve() {
    std::string command(sizeof(char), 0);
    char* p_command = (char*) command.c_str();
    peer.recieve(p_command, sizeof(char));

    std::string response;
    if (*p_command == HELP_COMMAND){
        response = menssenger.sendHelp();
    } else if (*p_command == SURRENDER_COMMAND){
        client_attempts_left = 0;
    } else if (*p_command == NUMBER_COMMAND){
        response = this->recieveGuestNumber();
    }

    if (client_attempts_left == 0){
        response = menssenger.sendYouLose();
    }
    this->sendResponse(response);
}


std::string ThClient::recieveGuestNumber() {
    uint16_t guest;
    peer.recieve(&guest, sizeof(uint16_t));
    //paso a endianess local
    guest = proxyToLocalEndian(guest);
    std::string response = this->tryToGuest(guest);

    return response;
}

void ThClient::sendResponse(const std::string& response) const {
    uint32_t size = response.size();
    uint32_t big_endian_size = proxyBigEndian(size);
    peer.send(&big_endian_size, sizeof(uint32_t));
    char* p_response = (char*) response.c_str();
    peer.send(p_response, response.size());
}

std::string ThClient::tryToGuest(uint16_t guest) {
    std::string response;

    if (guest > MAX_GUEST_NUMBER || guest < MIN_GUEST_NUMBER){
        response = menssenger.getInvalidNumberMsj();
        this->client_attempts_left--;
    } else {
        response = this->tryToGuestValidNumber(guest);
    }

    return response;
}

std::string ThClient::tryToGuestValidNumber(uint16_t guest) {
    std::string s_guest = std::to_string(guest);
    std::string s_number_to_guest = std::to_string(number_to_guest);

    std::string visited_number;
    bool repeated_number=false;
    int i=0;
    unsigned int good= 0, bad=0, regular=0;
    size_t pos;
    for (auto & guest_character : s_guest){
        if (visited_number.find(guest_character) != std::string::npos){
            repeated_number = true;
            break;
        }
        visited_number += guest_character;
        pos = s_number_to_guest.find(guest_character);
        if (s_number_to_guest[i] == guest_character){
            good +=1;
        } else if (pos == std::string::npos) {
            bad +=1;
        } else if (pos >= 0){
            regular +=1;
        }
        i++;
    }

    std::string response;
    if (repeated_number){
        response = menssenger.getInvalidNumberMsj();
        client_attempts_left--;
    } else if (good == CORRECT_GUEST){
        client_win = true;
        response = menssenger.sendWinResponse();
    } else {
        client_attempts_left--;
        response = this->menssenger.sendResponse(good, regular, bad);
    }

    return response;
}

/**TODO hacer una clase common_translator*/
uint32_t ThClient::valueToBigEndian(const uint32_t value) const{
    uint32_t little_end = ntohl(value); //pasa a little endian
    uint32_t big_end = bswap_32(little_end); //pasa a big endian

    return big_end;
}

uint16_t ThClient::proxyToLocalEndian(const uint16_t number) const{
    uint16_t local_end = ntohs(number);
    return local_end;
}


uint32_t ThClient::proxyBigEndian(const uint32_t value) const{
    uint32_t big_end = htonl(value);
    return big_end;
}


