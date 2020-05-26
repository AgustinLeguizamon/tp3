//
// Created by agustin on 25/5/20.
//

#ifndef TP3CLION_SERVER_PROTECTED_COUNTER_H
#define TP3CLION_SERVER_PROTECTED_COUNTER_H


#include <mutex>

class ProtectedCounter {
private:
    unsigned int winners;
    unsigned int losers;
    std::mutex mutex;

public:
    ProtectedCounter();

    ProtectedCounter(const ProtectedCounter&) = delete;

    void increaseWinners();

    void increase(bool is_winner);
    
    void increaseLosers();

    unsigned int getWinners();
    
    unsigned int getLosers();
};


#endif //TP3CLION_SERVER_PROTECTED_COUNTER_H
