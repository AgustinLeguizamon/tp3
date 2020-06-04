//
// Created by agustin on 4/6/20.
//

#ifndef TP3CLION_COMMON_OSERROR_EXCEPTION_H
#define TP3CLION_COMMON_OSERROR_EXCEPTION_H


#include <exception>
#include <cerrno>
#include <cstring>
#include <cstdarg>
#include <cstdio>

#define BUF_LEN 256

class OSError : public std::exception {
private:
    char msg_error[BUF_LEN]="";

public:
    explicit OSError(const char* fmt, ...) noexcept;

    const char* what() const noexcept override;

    ~OSError() noexcept override = default;
};



#endif //TP3CLION_COMMON_OSERROR_EXCEPTION_H
