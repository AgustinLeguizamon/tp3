//
// Created by agustin on 23/5/20.
//

#ifndef TP3CLION_COMMON_SOCKET_H
#define TP3CLION_COMMON_SOCKET_H
#define BUF_LEN 256

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <cerrno>
#include <string>
#include <cstdarg>
#include <iostream>
#include <cstring>

class ClosedSocketException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Socket is Closed";
    }
};

class OSError : public std::exception {
private:
    char msg_error[BUF_LEN]="";

public:
    explicit OSError(const char* fmt, ...) noexcept{
        int _errno = errno;

        va_list args;
        va_start(args, fmt);
        int s = vsnprintf(msg_error, BUF_LEN, fmt, args);
        va_end(args);
        strncpy(msg_error+s, strerror(_errno), BUF_LEN+s);
        msg_error[BUF_LEN-1] = 0;
    }
    virtual const char* what() const noexcept {
        return exception::what();
    }

    virtual ~OSError() noexcept = default;
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
