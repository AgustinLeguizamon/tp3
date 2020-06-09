//
// Created by agustin on 1/6/20.
//

#ifndef TP3CLION_COMMON_COMMAND_H
#define TP3CLION_COMMON_COMMAND_H

#include <cstdint>

class Socket;
class Protocol;
class Command {
public:
    virtual void operator()(Protocol &protocol,Socket &socket) = 0;
    virtual void free() = 0;
    virtual ~Command() = default;
};

class Surrender: public Command{
public:
    /*Envia el comando 's' por el socket*/
    void operator()(Protocol &protocol,Socket &socket) override;
    void free() override;
};

class Help: public Command{
public:
    /*envia el comando 'h' por el socket*/
    void operator()(Protocol &protocol,Socket &socket) override;
    void free() override;
};

class Number: public Command{
private:
    uint16_t number;
public:
    /*El constructor tiene como atributo el numero que se
     * enviara por el socket*/
    explicit Number(uint16_t number);
    /*Envia primero el comando 'n' y luego el numero en formato bigEndian*/
    void operator()(Protocol &protocol,Socket &socket) override;
    void free() override;
};

#endif //TP3CLION_COMMON_COMMAND_H
