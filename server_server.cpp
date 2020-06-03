//
// Created by agustin on 22/5/20.
//

#include <iostream>
#include <utility>
#include "server_server.h"
#include "server_th_client.h"

#define CLOSE_SERVER 'q'

Server::Server(FileReader &file_reader, const char* service) :
    file_reader(file_reader),
    acep_socket(),
    keep_running(true){
    acep_socket.bindAndListen(service);
}

void Server::operator()() {
    std::thread acep_th(&Server::acceptClients, this);

    char c = std::cin.get();
    while (c != CLOSE_SERVER){
        c = std::cin.get();
    }
    keep_running = false;
    //cierro el acceptClients asi falla el accept del socket
    acep_socket.shutdown(SHUT_RDWR);
    for (auto & client: clients){
        client->join();
        delete(client);
    }
    this->showResults();

    acep_th.join();
}

uint16_t Server::readNextNumber() {
    return (file_reader.readNextNumber());
}

void Server::showResults() {
    std::cout << "Estadísticas:\n\tGanadores:  "
                << counter.getWinners() << "\n\t"
                "Perdedores: " << counter.getLosers() << "\n";
}

void Server::acceptClients() {
    while (keep_running){
        try {
            Socket server_socket = acep_socket.accept();
            uint16_t guest_number = this->readNextNumber();
            clients.reserve(clients.size() + 1);
            clients.push_back(new ThClient(std::move(server_socket),
                    guest_number, counter));
            /*clients.emplace_back(std::move(server_socket),
                    guest_number, counter);*/
            clients.back()->start();
            for (auto & client: clients){
                if (!client->isRunning()){
                    client->join();
                    delete (client);
                }
            }
        } catch(ClosedSocketException &e) {
            //ocurre si ya cerre el socket aceptador
        }
    }
}
