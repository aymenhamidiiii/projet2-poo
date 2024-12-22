#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <string>
#include <iostream>

class Timer {
public:
    // Commence le chronométrage
    void start();

    // Arrête le chronométrage
    void stop();

    // Affiche le temps écoulé avec un label
    void print(const std::string& label) const;

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time, end_time;
};

#endif // TIMER_H
