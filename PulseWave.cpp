#include "PulseWave.hpp"
#include <iostream>
#include <fstream>
#include <string>

// Define methods of VLR class here
// ...

VLR::VLR(std::ifstream& f){
    char user_id_data[16];
    f.read(user_id_data, sizeof(user_id_data));
    userID = std::string(user_id_data).substr(0, 16);

    uint32_t temp;
    f.read(reinterpret_cast<char*>(&temp), sizeof(temp));
    recordID = temp;

    f.read(reinterpret_cast<char*>(&temp), sizeof(temp));
    reserved = temp;

    int64_t temp_record_length;
    f.read(reinterpret_cast<char*>(&temp_record_length), sizeof(temp_record_length));
    recordLength = temp_record_length;

    char description_data[64];
    f.read(description_data, sizeof(description_data));
    description = std::string(description_data).substr(0, 64);
    
}

Scanner::Scanner(std::ifstream& f) {
    f.read(reinterpret_cast<char*>(&size), sizeof(size));
    f.read(reinterpret_cast<char*>(&reserved), sizeof(reserved));

    char instrument_data[64];
    f.read(instrument_data, sizeof(instrument_data));
    instrument = std::string(instrument_data).substr(0, 64);

    char serial_data[64];
    f.read(serial_data, sizeof(serial_data));
    serial = std::string(serial_data).substr(0, 64);

    f.read(reinterpret_cast<char*>(&wavelength), sizeof(wavelength));
    f.read(reinterpret_cast<char*>(&out_pulse_width), sizeof(out_pulse_width));
    f.read(reinterpret_cast<char*>(&scan_pattern), sizeof(scan_pattern));
    f.read(reinterpret_cast<char*>(&num_facets), sizeof(num_facets));
    f.read(reinterpret_cast<char*>(&scan_frequency), sizeof(scan_frequency));
    f.read(reinterpret_cast<char*>(&scan_angle_min), sizeof(scan_angle_min));
    f.read(reinterpret_cast<char*>(&scan_angle_max), sizeof(scan_angle_max));
    f.read(reinterpret_cast<char*>(&pulse_frequency), sizeof(pulse_frequency));
    f.read(reinterpret_cast<char*>(&beam_diam), sizeof(beam_diam));
    f.read(reinterpret_cast<char*>(&beam_diverge), sizeof(beam_diverge));
    f.read(reinterpret_cast<char*>(&min_range), sizeof(min_range));
    f.read(reinterpret_cast<char*>(&max_range), sizeof(max_range));

    char description_data[64];
    f.read(description_data, sizeof(description_data));
    description = std::string(description_data).substr(0, 64);
}

PulseDecriptor::PulseDecriptor(std::ifstream& f) {
    f.read(reinterpret_cast<char*>(&size), sizeof(size));
    f.read(reinterpret_cast<char*>(&reserved), sizeof(reserved));
    f.read(reinterpret_cast<char*>(&optical_center), sizeof(optical_center));
    f.read(reinterpret_cast<char*>(&num_extra_wave_bytes), sizeof(num_extra_wave_bytes));
    f.read(reinterpret_cast<char*>(&num_samplings), sizeof(num_samplings));
    f.read(reinterpret_cast<char*>(&sample_units), sizeof(sample_units));
    f.read(reinterpret_cast<char*>(&compression), sizeof(compression));
    f.read(reinterpret_cast<char*>(&scanner_index), sizeof(scanner_index));

    char description_data[64];
    f.read(description_data, sizeof(description_data));
    description = std::string(description_data).substr(0, 64);
}

SamplingRecord::SamplingRecord(std::ifstream& f) {
    char descriptionData[64];
    f.read(descriptionData, sizeof(descriptionData));
    description = std::string(descriptionData).substr(0, 64);
}


// Constructor implementation for PulseWaves class
PulseWaves::PulseWaves(const std::string& pls_file) {
    if (pls_file.substr(pls_file.length() - 3) != "pls") {
        std::cerr << "error: reader assumes lower case file endings and only works for the uncompressed format (.pls)." << std::endl;
        std::exit(EXIT_FAILURE);
    }

    std::ifstream f(pls_file, std::ios::binary);
    if (!f.is_open()) {
        std::cerr << "error: could not open file: " << pls_file << std::endl;
        std::exit(EXIT_FAILURE);
    }

    char file_sig[16];
    f.read(file_sig, 16);
    std::string file_signature(file_sig);
    if (file_signature != "PulseWavesPulse") {
        std::cerr << "error: " << pls_file << " is not in a valid pulse file format." << std::endl;
        std::exit(EXIT_FAILURE);
    }

    // Read and unpack various attributes from the file
    // Initialize member variables of PulseWaves class
    // ...

    // Unpack global parameters;
    uint32_t global_params;
    if (!f.read(reinterpret_cast<char*>(&global_params), sizeof(global_params))){
        std::cerr << "Error reading global_params." << std::endl;
    }

    // Unpack file_id;
    uint32_t file_id;
    if (!f.read(reinterpret_cast<char*>(&file_id), sizeof(file_id))){
        std::cerr << "Error reading file_id." << std::endl;
    }

    // Unpack proj_GUID1;
    uint32_t proj_GUID1;
    if (!f.read(reinterpret_cast<char*>(&proj_GUID1), sizeof(proj_GUID1))){
        std::cerr << "Error reading proj_GUID1." << std::endl;
    }

    // Unpack proj_GUID2;
    uint16_t proj_GUID2;
    if (!f.read(reinterpret_cast<char*>(&proj_GUID2), sizeof(proj_GUID2))){
        std::cerr << "Error reading proj_GUID2." << std::endl;
    }

    // Unpack proj_GUID3;
    uint16_t proj_GUID3;
    if (!f.read(reinterpret_cast<char*>(&proj_GUID3), sizeof(proj_GUID3))){
        std::cerr << "Error reading proj_GUID3." << std::endl;
    }

    // Unpack Project ID - GUID data 4;
    unsigned char proj_GUID4[8];
    if (!f.read(reinterpret_cast<char*>(&proj_GUID4), sizeof(proj_GUID4))){
        std::cerr << "Error reading proj_GUID4." << std::endl;
    }

    // Unpack System Identifier;
    char sysIdentifier[64];
    if (!f.read(sysIdentifier, sizeof(sysIdentifier))){
        std::cerr << "Error reading sysIdentifier." << std::endl;
    };
    std::string systemIdentifier(sysIdentifier);

    // Unpack Generating Software;
    char genSoftware[64];
    if (!f.read(genSoftware, sizeof(genSoftware))){
        std::cerr << "Error reading gensoftware." << std::endl;
    };
    std::string generateSoftware(genSoftware);

    // Unpack File Creation Day of Year;
    uint16_t fileDay;
    if (!f.read(reinterpret_cast<char*>(&fileDay), sizeof(fileDay))){
        std::cerr << "Error reading fileDay." << std::endl;
    }

    // Unpack File Creation Year;
    uint16_t fileYear;
    if (!f.read(reinterpret_cast<char*>(&fileYear), sizeof(fileYear))){
        std::cerr << "Error reading fileYear." << std::endl;
    }

    // Unpack Version Major;
    uint8_t versionMajor;
    if (!f.read(reinterpret_cast<char*>(&versionMajor), sizeof(versionMajor))){
        std::cerr << "Error reading versionMajor." << std::endl;
    }

    // Unpack Version Minor;
    uint8_t versionMinor;
    if (!f.read(reinterpret_cast<char*>(&versionMinor), sizeof(versionMinor))){
        std::cerr << "Error reading versionMinor." << std::endl;
    }

    // Unpack Header size;
    uint16_t headerSize;
    if (!f.read(reinterpret_cast<char*>(&headerSize), sizeof(headerSize))){
        std::cerr << "Error reading headerSize." << std::endl;
    }

    // Unpack Offset to Pulse Data;
    uint64_t offsetPulse;
    if (!f.read(reinterpret_cast<char*>(&offsetPulse), sizeof(offsetPulse))){
        std::cerr << "Error reading offsetPulse." << std::endl;
    }

    // Unpack Number of Pulses;
    uint64_t numberPulse;
    if (!f.read(reinterpret_cast<char*>(&numberPulse), sizeof(numberPulse))){
        std::cerr << "Error reading numberPulse." << std::endl;
    }

    // Unpack Pulse Format;
    uint32_t pulseFormat;
    if (!f.read(reinterpret_cast<char*>(pulseFormat), sizeof(pulseFormat))){
        std::cerr << "Error reading pulseFormat." << std::endl;
    }

    // Unpack Pulse Attributes;
    uint32_t pulseAttributes;
    if (!f.read(reinterpret_cast<char*>(pulseAttributes), sizeof(pulseAttributes))){
        std::cerr << "Error reading pulseAttributes." << std::endl;
    }

    // Unpack Pulse Size;
    uint32_t pulseSize;
    if (!f.read(reinterpret_cast<char*>(pulseSize), sizeof(pulseSize))){
        std::cerr << "Error reading pulseSize." << std::endl;
    }

    // Unpack Pulse Compression;
    uint32_t pulseCompression;
    if (!f.read(reinterpret_cast<char*>(pulseCompression), sizeof(pulseCompression))){
        std::cerr << "Error reading pulseCompression." << std::endl;
    }

    // Unpack Reserved;
    uint64_t reserved;
    if (!f.read(reinterpret_cast<char*>(reserved), sizeof(reserved))){
        std::cerr << "Error reading reserved." << std::endl;
    }

    // Unpack Number of Variable Length Records;
    uint32_t numberVariableLengthRecord;
    if (!f.read(reinterpret_cast<char*>(numberVariableLengthRecord), sizeof(numberVariableLengthRecord))){
        std::cerr << "Error reading numberVariableLengthRecord." << std::endl;
    }

    // Unpack Number of Appended Variable Length Records;
    uint32_t numberAppendedVariableLengthRecord;
    if (!f.read(reinterpret_cast<char*>(numberAppendedVariableLengthRecord), sizeof(numberAppendedVariableLengthRecord))){
        std::cerr << "Error reading numberAppendedVariableLengthRecord." << std::endl;
    }

    // Unpack T Scale Factor;
     double tScaleFactor;
    if (!f.read(reinterpret_cast<char*>(&tScaleFactor), sizeof(tScaleFactor))){
        std::cerr << "Error reading tScaleFactor." << std::endl;
    }

    // Unpack T Offset;
     double tOffset;
    if (!f.read(reinterpret_cast<char*>(&tOffset), sizeof(tOffset))){
        std::cerr << "Error reading tOffset." << std::endl;
    }

    // Unpack Min T;
    uint64_t minT;
    if (!f.read(reinterpret_cast<char*>(minT), sizeof(minT))){
        std::cerr << "Error reading minT." << std::endl;
    }

    // Unpack Max T;
    uint64_t maxT;
    if (!f.read(reinterpret_cast<char*>(maxT), sizeof(maxT))){
        std::cerr << "Error reading maxT." << std::endl;
    }

    // Unpack X ScaleFactor;
     double xScaleFactor;
    if (!f.read(reinterpret_cast<char*>(&xScaleFactor), sizeof(xScaleFactor))){
        std::cerr << "Error reading xScaleFactor." << std::endl;
    }

    // Unpack Y ScaleFactor;
     double yScaleFactor;
    if (!f.read(reinterpret_cast<char*>(&yScaleFactor), sizeof(yScaleFactor))){
        std::cerr << "Error reading yScaleFactor." << std::endl;
    }

    // Unpack Z ScaleFactor;
     double zScaleFactor;
    if (!f.read(reinterpret_cast<char*>(&zScaleFactor), sizeof(zScaleFactor))){
        std::cerr << "Error reading zScaleFactor." << std::endl;
    }

    // Unpack X Offset;
     double xOffset;
    if (!f.read(reinterpret_cast<char*>(&xOffset), sizeof(xOffset))){
        std::cerr << "Error reading xOffset." << std::endl;
    }

    // Unpack Y Offset;
     double yOffset;
    if (!f.read(reinterpret_cast<char*>(&yOffset), sizeof(yOffset))){
        std::cerr << "Error reading yOffset." << std::endl;
    }

    // Unpack Z Offset;
     double zOffset;
    if (!f.read(reinterpret_cast<char*>(&zOffset), sizeof(zOffset))){
        std::cerr << "Error reading zOffset." << std::endl;
    }

    // Unpack X Minimum;
     double xMin;
    if (!f.read(reinterpret_cast<char*>(&xMin), sizeof(xMin))){
        std::cerr << "Error reading xMin." << std::endl;
    }

    // Unpack Y Minimum;
     double yMin;
    if (!f.read(reinterpret_cast<char*>(&yMin), sizeof(yMin))){
        std::cerr << "Error reading yMin." << std::endl;
    }

    // Unpack Z Minimum;
     double zMin;
    if (!f.read(reinterpret_cast<char*>(&zMin), sizeof(zMin))){
        std::cerr << "Error reading zMin." << std::endl;
    }

    // Unpack X Maximum;
     double xMax;
    if (!f.read(reinterpret_cast<char*>(&xMax), sizeof(xMax))){
        std::cerr << "Error reading xMax." << std::endl;
    }

    // Unpack Y Maximum;
     double yMax;
    if (!f.read(reinterpret_cast<char*>(&yMax), sizeof(yMax))){
        std::cerr << "Error reading yMax." << std::endl;
    }

    // Unpack Z Maximum;
     double zMax;
    if (!f.read(reinterpret_cast<char*>(&zMax), sizeof(zMax))){
        std::cerr << "Error reading zMax." << std::endl;
    }

    // Read variable length records (VLR)
    for (int num_vlr = 0; num_vlr < numberVariableLengthRecord; num_vlr++) {
        VLR vlr(f);

        // Handle different VLR types
        if (vlr.recordID >= 100001 && vlr.recordID < 100255) {
            vlr.record = Scanner(f);
        } else if (vlr.recordID >= 200001 && vlr.recordID < 200255) {
            // Read pulse descriptor
            vlr.record = PulseDecriptor(f);
            vlr.samplingRecords.clear();

            // Access the underlying PulseDecriptor object
            PulseDecriptor& pulseDescriptor = std::any_cast<PulseDecriptor&>(vlr.record);

            // Read sampling records
            for (int x = 0; x < pulseDescriptor.num_samplings; x++) {
                SamplingRecord samplingRecord(f);
                vlr.samplingRecords[samplingRecord.description] = samplingRecord;
            }
        } else {
            // VLR is neither a scanner nor a pulse descriptor
            std::vector<char> rawData(vlr.recordLength); // Create a buffer to read raw data
            f.read(rawData.data(), vlr.recordLength);    // Read raw data into the buffer
            vlr.record = rawData; // Store the raw data in the vlr.record using std::vector<char>
        }

        // Add the VLR to the vlrs and avlrs containers
        vlrs[vlr.recordID] = vlr; // Assuming you have a container vlrs to store VLR objects with recordID as the key
    }
    // Close the file
    f.close();
    
    PulseRecord getPulse(int pulseNumber){
        if (pulseNumber > numberPulse || pulseNumber < 0){
            std::cerr << "Pulse number outside the range of expected values" << std::endl;
            std::exit(EXIT_FAILURE);
        }
        return PulseRecord(pulseNumber);
    }
}

// Add definitions for other member functions of PulseWaves class here
// ...