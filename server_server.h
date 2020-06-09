//
// Created by agustin on 22/5/20.
//

#ifndef TP3CLION_SERVER_SERVER_H
#define TP3CLION_SERVER_SERVER_H


#include <stdint-gcc.h>
#include <vector>
#include <thread>

#include "server_file_reader.h"
#include "common_socket.h"
#include "server_th_client.h"

class Server {
private:
    FileReader &file_reader;
    Socket acep_socket;
    std::vector<ThClient*> clients;
    ProtectedCounter counter;
    std::atomic <bool> keep_running;
    
public:
    explicit Server(FileReader &file_reader, const char* service);

    Server(const Server &other) = delete;

    /* Levanta el servidor, acepta nuevos clientes lanzando threads 
     * por cada uno y eliminando aquellos que dejaron de jugar
     * espera una 'q' por la entrada estandar para cerrar el servidor*/
    void operator()();

private:
    /*Obtiene el siguiente numero para que el cliente adivine*/
    uint16_t readNextNumber();

    /*Muestra la cantidad de ganadores y perdedores mientras
     * estuvo levantado el server*/
    void showResults();

    /*Thread, encargado de aceptar nuevos clientes*/
    void acceptClients();
};


#endif //TP3CLION_SERVER_SERVER_H
