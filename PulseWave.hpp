#include <iostream>
#ifndef PULSEWAVES_HPP
#define PULSEWAVES_HPP

#include <string>
#include <vector>

class VLR {
    // std::string pls
};

class PulseRecord {
    // Declare PulseRecord class members and methods here
};

class Waves {
    // Declare Waves class members and methods here
};

class PulseWaves {
public:
    PulseWaves(const std::string& pls_file);

    // Define PulseWaves class methods here
// PulseWaves(const std::string& pls_file);
    std::vector<std::vector<std::pair<double, double>>> pulseWave();

// private:
    // Define PulseWaves class members here
};

#endif // PULSEWAVES_HPP