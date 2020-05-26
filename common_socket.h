//
// Created by agustin on 23/5/20.
//

#ifndef TP3CLION_COMMON_SOCKET_H
#define TP3CLION_COMMON_SOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>


#include <string>

class ClosedSocketException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Socket is Closed";
    }
};

class Socket {
private:
    int sfd;

public:
    Socket();

    Socket(const Socket&) = delete;

    Socket(Socket&& other) noexcept;

    int bindAndListen(const char *service);

    Socket accept() const;

    int connect(const char* host_name, const char* service);

    int send(const void* buffer, ssize_t length) const;

    int recieve(void* buffer, ssize_t length) const;

    int shutdown(int channel);

    int close();

    ~Socket();

private:
    explicit Socket(int file_descriptor);
};

#endif //TP3CLION_COMMON_SOCKET_H
