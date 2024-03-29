//
// Created by agustin on 25/5/20.
//

#include "server_protected_counter.h"


ProtectedCounter::ProtectedCounter() :
    winners(0),
    losers(0)
    {}

void ProtectedCounter::increase(const bool is_winner) {
    std::unique_lock<std::mutex> lock(mutex);
    if (is_winner){
        winners++;
    } else {
        losers++;
    }
}

unsigned int ProtectedCounter::getWinners() {
    std::unique_lock<std::mutex> lock(mutex);
    return winners;
}

unsigned int ProtectedCounter::getLosers() {
    std::unique_lock<std::mutex> lock(mutex);
    return losers;
}

