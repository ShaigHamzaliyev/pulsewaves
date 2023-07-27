#include <iostream>
#ifndef PULSEWAVE_HPP
#define PULSEWAVE_HPP

#include <string>
#include <vector>

class VLR {
    public:
        VLR(std::ifstream& file);
    private:
        std::string user_id; // Declare the member variables here
        uint32_t record_id;
        uint32_t reserved;
        int64_t record_length;
        std::string description;
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
    // std::vector<std::vector<std::pair<double, double>>> pulseWave();

// private:
    // Define PulseWaves class members here
};

#endif // PULSEWAVES_HPP