//
// Created by agustin on 22/5/20.
//

#ifndef TP3CLION_SERVER_MENSSENGER_H
#define TP3CLION_SERVER_MENSSENGER_H


#include <stdint-gcc.h>
#include <string>

class Menssenger {
private:
    int functor;
public:
    Menssenger();

    void send(uint16_t number) const;

    std::string sendResponse(unsigned int good, unsigned int regular,
            unsigned int bad) const;

    std::string sendWinResponse() const;

    std::string sendHelp() const;

    std::string sendYouLose() const;

    std::string getInvalidNumberMsj() const;

    Menssenger (const Menssenger& other) = delete;
};


#endif //TP3CLION_SERVER_MENSSENGER_H
