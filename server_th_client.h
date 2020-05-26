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
#include "server_menssenger.h"
#include "server_protected_counter.h"

class ThClient : public Thread {
private:
    std::atomic<bool> keep_talking;
    std::atomic<bool> is_running;
    Menssenger menssenger;
    ProtectedCounter &counter;
    Socket peer;
    uint16_t number_to_guest;
    unsigned int client_attempts_left;
    std::atomic<bool> client_win;

public:
    explicit ThClient(Socket&& server_socket, uint16_t number,
            ProtectedCounter &counter);

    ThClient(const ThClient&) = delete;

    //este constructor por movimiento es solo
    // para poder usar el emplace_back/push_back
    ThClient(ThClient&& other) noexcept;

    void stop();

    void run() override;

    bool isRunning();

private:
    void recieve();

    std::string recieveGuestNumber();

    void sendResponse(const std::string &response) const;

    std::string tryToGuest(uint16_t guest);

    std::string tryToGuestValidNumber(uint16_t guest);

    uint32_t valueToBigEndian(uint32_t value) const;
};


#endif //TP3CLION_SERVER_TH_CLIENT_H
