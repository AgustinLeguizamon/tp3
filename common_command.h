//
// Created by agustin on 1/6/20.
//

#ifndef TP3CLION_COMMON_COMMAND_H
#define TP3CLION_COMMON_COMMAND_H

#include "common_protocol.h"

class Command {
public:
    virtual void operator()(Protocol &protocol,Socket &socket) = 0;
    virtual void free() = 0;
    virtual ~Command();
};

class Surrender: public Command{
public:
    void operator()(Protocol &protocol,Socket &socket) override;
    void free() override;
};

class Help: public Command{
public:
    void operator()(Protocol &protocol,Socket &socket) override;
    void free() override;
};

class Number: public Command{
private:
    uint16_t number;
public:
    explicit Number(uint16_t number);
    void operator()(Protocol &protocol,Socket &socket) override;
    void free() override;
};

#endif //TP3CLION_COMMON_COMMAND_H
