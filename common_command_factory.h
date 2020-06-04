//
// Created by agustin on 1/6/20.
//

#ifndef TP3CLION_COMMON_COMMAND_FACTORY_H
#define TP3CLION_COMMON_COMMAND_FACTORY_H

#include <string>

class Command;
class CommandFactory {
public:
    CommandFactory() = default;
    Command *get(const std::string &input) const;
};


#endif //TP3CLION_COMMON_COMMAND_FACTORY_H
