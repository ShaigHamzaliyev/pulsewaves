#include <iostream>
#ifndef PULSEWAVE_HPP
#define PULSEWAVE_HPP

#include <string>
#include <vector>
#include <map> 
#include <memory>
#include <variant>
#include <any>

class VLR {
    public:
    VLR(std::ifstream& file);

    std::string userID;
    uint32_t recordID;
    uint32_t reserved;
    int64_t recordLength;
    std::string description;
    std::map<std::string, SamplingRecord> samplingRecords;

    //using RecordVariant = std::variant<PulseDecriptor, Scanner>; // Use std::variant to store either PulseDecriptor or Scanner
    //RecordVariant record;

    std::any record; // not sure about the types of the key and value yet!!!
};

class PulseRecord {
    // Declare PulseRecord class members and methods here
};

class Waves {
    // Declare Waves class members and methods here
};

class Scanner{
    public:
    Scanner(std::ifstream& file);

    uint32_t size;
    uint32_t reserved;
    std::string instrument;
    std::string serial;
    float wavelength;
    float out_pulse_width;
    uint32_t scan_pattern;
    uint32_t num_facets;
    float scan_frequency;
    float scan_angle_min;
    float scan_angle_max;
    float pulse_frequency;
    float beam_diam;
    float beam_diverge;
    float min_range;
    float max_range;
    std::string description;
};

class PulseWaves {
public:
    PulseWaves(const std::string& pls_file);
    std::map<int, VLR> vlrs;

    // Define PulseWaves class methods here
// PulseWaves(const std::string& pls_file);
    // std::vector<std::vector<std::pair<double, double>>> pulseWave();

// private:
    // Define PulseWaves class members here
};

class PulseDecriptor{
    public:
    PulseDecriptor(std::ifstream& f);

    // Public member variables
    uint32_t size;
    uint32_t reserved;
    int32_t optical_center;
    uint16_t num_extra_wave_bytes;
    uint16_t num_samplings;
    float sample_units;
    uint32_t compression;
    uint32_t scanner_index;
    std::string description;
};

class SamplingRecord{
    public:
        SamplingRecord(std::ifstream& f);
        std::string description;
};


#endif // PULSEWAVES_HPP