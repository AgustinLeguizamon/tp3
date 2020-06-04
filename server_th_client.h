//
// Created by agustin on 24/5/20.
//

#ifndef TP3CLION_SERVER_TH_CLIENT_H
#define TP3CLION_SERVER_TH_CLIENT_H

#include <thread>
#include <atomic>
#include <string>
#include "common_socket.h"
#include "server_thread.h"
#include "server_protected_counter.h"
#include "common_protocol.h"
#include "server_game.h"

class ThClient : public Thread {
private:
    std::atomic<bool> is_running;
    Protocol protocol;
    ProtectedCounter &counter;
    Socket peer;
    Game game;

public:
    explicit ThClient(Socket&& server_socket, uint16_t number,
            ProtectedCounter &counter);

    ThClient(const ThClient&) = delete;

    //este constructor por movimiento es solo
    //para poder usar el emplace_back/push_back
    ThClient(ThClient&& other) noexcept;

    /*Recibe msg por el socket mientras siga el juego*/
    void run() override;

    bool isRunning() const;

    ~ThClient() override;

private:
    /*Recibe por el socket un caracter, caso que sea 'n' recibe
     * tambien un uint16 y delega a Game*/
    void recieve();
};


#endif //TP3CLION_SERVER_TH_CLIENT_H
