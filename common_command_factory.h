//
// Created by agustin on 1/6/20.
//

#ifndef TP3CLION_COMMON_COMMAND_FACTORY_H
#define TP3CLION_COMMON_COMMAND_FACTORY_H

#include <string>

class Command;
class CommandFactory {
private:
    /*TODO: ver si hago singleton o los dejo publicos, Singleton tiene los constructos privados para
     * evitar que se instancien mas de una vez*/
    CommandFactory(const CommandFactory&)= default;
    CommandFactory& operator=(const CommandFactory &) = default;
public:
    CommandFactory() = default;
    Command *get(const std::string &input);
};


#endif //TP3CLION_COMMON_COMMAND_FACTORY_H
