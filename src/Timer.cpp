#include "Timer.h"

// Démarre le timer
void Timer::start() {
    start_time = std::chrono::high_resolution_clock::now();
}

// Arrête le timer
void Timer::stop() {
    end_time = std::chrono::high_resolution_clock::now();
}

// Affiche le temps écoulé
void Timer::print(const std::string& label) const {
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    std::cout << label << ": " << duration << " ms" << std::endl;
}
