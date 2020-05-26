//
// Created by agustin on 23/5/20.
//

#include <netdb.h>
#include <cstring>
#include <unistd.h>
#include "common_socket.h"

#define BACKLOG 10; //cantidad maxima de solicitudes en espera

Socket::Socket() :
    sfd(-1)
    {}

Socket::Socket(int file_descriptor) :
        sfd(file_descriptor)
    {}

Socket::Socket(Socket &&other) noexcept {
    this->sfd = other.sfd;
    other.sfd = -1;
}



int Socket::bindAndListen(const char* service) {
    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM; //TCP
    hints.ai_flags = AI_PASSIVE;
    hints.ai_protocol = 0;
    hints.ai_canonname = nullptr;
    hints.ai_addr = nullptr;
    hints.ai_next = nullptr;

    struct addrinfo *result;
    getaddrinfo(nullptr, service, &hints, &result);

    struct addrinfo *rp = result;

    bool success = false;
    while (!success && rp != nullptr){
        int socket_file_descriptor = socket(rp->ai_family, rp->ai_socktype,
                                            rp->ai_protocol);

        if (bind(socket_file_descriptor, rp->ai_addr, rp->ai_addrlen) == 0){
            success = true;
            int backlog = BACKLOG;
            listen(socket_file_descriptor, backlog);
            this->sfd = socket_file_descriptor;
        } else {
            rp = rp->ai_next;
            ::close(socket_file_descriptor);
        }
    }
    freeaddrinfo(result);
/*
    if(!success){
        throw OSError("El socket no pudo bindearse al puerto %s", service);
    }
*/
    return 0;
}


Socket Socket::accept() const {
    int acep_file_descriptor = this->sfd;
    socklen_t peer_addr_size = sizeof(struct sockaddr_in);

    struct sockaddr_in peer_addr;
    int file_descriptor = ::accept(acep_file_descriptor,
                                   (struct sockaddr *) &peer_addr,
                                           &peer_addr_size);

    if (file_descriptor == -1){
        throw ClosedSocketException();
    }

    return std::move(Socket(file_descriptor));
}


int Socket::connect(const char *host_name, const char *service) {
    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM; //TCP
    hints.ai_flags = 0;
    hints.ai_protocol = 0;

    struct addrinfo *result;
    getaddrinfo(host_name, service, &hints, &result);

    struct addrinfo *rp = result;

    bool success = false;
    while (!success && rp != nullptr){
        int socket_file_descriptor = socket(rp->ai_family, rp->ai_socktype,
                                            rp->ai_protocol);

        if (::connect(socket_file_descriptor,
                rp->ai_addr, rp->ai_addrlen) != -1){
            success = true;
            this->sfd = socket_file_descriptor;
        } else {
            rp = rp->ai_next;
            ::close(socket_file_descriptor);
        }
    }

    freeaddrinfo(result);
/*
    if(!success){
        throw OSError("El socket no pudo conectarse al host %s, puerto %s", host_name, service);
    }
*/
    return 0;
}

int Socket::send(const void *buffer, ssize_t length) const {
    ssize_t n_send = 1;
    int bytes_sent = 0;

    while (bytes_sent < length && n_send > 0){
        n_send = ::send(this->sfd, buffer, length, MSG_NOSIGNAL);
        bytes_sent += n_send;
    }

    if (n_send == 0){
        /*Cerraron el socket*/
        return 0;
    }
    if (n_send == -1){
       /**Error tirar excepcion */
    }

    return n_send;
}

int Socket::recieve(void* buffer, ssize_t length) const {
    ssize_t n_recv = 1;
    int bytes_recv = 0;

    while (bytes_recv < length && n_recv > 0){
        n_recv = recv(this->sfd, buffer, length, 0);
        bytes_recv += n_recv;
    }
    if (n_recv == 0){
        /*Cerraron el socket*/
        return 0;
    }
    if (n_recv == -1){
        /**Error tirar excepcion */
    }


    return n_recv;
}

Socket::~Socket() {
    ::shutdown(this->sfd, SHUT_RDWR);
    ::close(this->sfd);
}

int Socket::shutdown(int channel) {
    ::shutdown(this->sfd, SHUT_RDWR);
    return  0;
}

int Socket::close(){
    ::close((this->sfd));
    return 0;
}
