//
// Created by agustin on 22/5/20.
//

#include <iostream>
#include "server_server.h"
#include "server_th_client.h"

//para el reserve del vector clients, si no el programa falla
#define MAX_CLIENTS 4

Server::Server(FileReader &file_reader, const char* service) :
    file_reader(file_reader),
    acep_socket(),
    keep_running(true){
    acep_socket.bindAndListen(service);
}

void Server::operator()() {
    std::thread acep_th(&Server::aceptador, this);

    char c = std::cin.get();
    while (c != 'q'){
        c = std::cin.get();
    }
    keep_running = false;
    //cierro el aceptador asi falla el acept
    acep_socket.shutdown(SHUT_RDWR);
    for (auto & client: clients){
        //client.stop()
        client.join();
    }
    this->showResults();

    acep_th.join();
}

uint16_t Server::readNextNumber() {
    return (file_reader.readNextNumber());
}

void Server::showResults() {
    std::cout << "Estadísticas:\n\tGanadores:" << counter.getWinners() << "\n\t"
                "Perdedores:" << counter.getLosers() << "\n";
}

void Server::aceptador() {
    while (keep_running){
        try {
            Socket server_socket = acep_socket.accept();
            uint16_t guest_number = this->readNextNumber();
            clients.reserve(MAX_CLIENTS);
            clients.emplace_back(std::move(server_socket),
                    guest_number, counter);
            clients.back().start();
            for (auto & client: clients){
                if (!client.isRunning()){
                    client.join();
                }
            }
        } catch(ClosedSocketException &e) {
        }
    }
}
