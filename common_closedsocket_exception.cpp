//
// Created by agustin on 4/6/20.
//

#include "common_closedsocket_exception.h"

const char *ClosedSocketException::what() const noexcept {
    return "Socket is Closed";
}
