//
// Created by agustin on 22/5/20.
//

#ifndef TP3CLION_SERVER_SERVER_H
#define TP3CLION_SERVER_SERVER_H


#include <stdint-gcc.h>
#include <vector>
#include <thread>

#include "server_file_reader.h"
#include "server_menssenger.h"
#include "common_socket.h"
#include "server_th_client.h"

class Server {
private:
    FileReader &file_reader;
    Socket acep_socket;
    std::vector<ThClient> clients;
    ProtectedCounter counter;
    bool keep_running;
    
public:
    explicit Server(FileReader &file_reader, const char* service);

    Server(const Server &other) = delete;

    uint16_t readNextNumber();

    void operator()();

    void showResults();

    void acceptClients();
};


#endif //TP3CLION_SERVER_SERVER_H
