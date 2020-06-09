//
// Created by agustin on 4/6/20.
//

#ifndef TP3CLION_COMMON_CLOSEDSOCKET_EXCEPTION_H
#define TP3CLION_COMMON_CLOSEDSOCKET_EXCEPTION_H


#include <exception>

class ClosedSocketException : public std::exception {
public:
    /*Al cerrar el server el socket aceptador lanzara 
     * una excepcion de este tipo, se utiliza como parte 
     * de la logica del programa*/
    const char* what() const noexcept override;
};



#endif //TP3CLION_COMMON_CLOSEDSOCKET_EXCEPTION_H
