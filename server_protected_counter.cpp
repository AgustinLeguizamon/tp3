//
// Created by agustin on 25/5/20.
//

#include "server_protected_counter.h"


ProtectedCounter::ProtectedCounter() :
    winners(0),
    losers(0)
    {}

void ProtectedCounter::increaseWinners() {
    std::unique_lock<std::mutex> lock(mutex);
    winners++;
}

void ProtectedCounter::increaseLosers() {
    std::unique_lock<std::mutex> lock(mutex);
    losers++;
}

void ProtectedCounter::increase(bool is_winner) {
    std::unique_lock<std::mutex> lock(mutex);
    if (is_winner){
        winners++;
    } else {
        losers++;
    }
}

unsigned int ProtectedCounter::getWinners() {
    return winners;
}

unsigned int ProtectedCounter::getLosers() {
    return losers;
}

