//
// Created by agustin on 4/6/20.
//

#ifndef TP3CLION_COMMON_CLOSEDSOCKET_EXCEPTION_H
#define TP3CLION_COMMON_CLOSEDSOCKET_EXCEPTION_H


#include <exception>

class ClosedSocketException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Socket is Closed";
    }
};



#endif //TP3CLION_COMMON_CLOSEDSOCKET_EXCEPTION_H
