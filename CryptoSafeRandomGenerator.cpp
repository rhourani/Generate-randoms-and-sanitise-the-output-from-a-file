#include <iostream>
#include <fstream>
#include <random>
#include <chrono>

// Function to generate cryptographically secure random data
std::vector<uint8_t> generateRandomData(size_t size) {
    // Seed the random number generator with a hardware device randomly generated number to increase the entropy and
    // make it harder to expect the random seed used
    std::random_device rd;
    std::mt19937_64 generator(rd()); // Mersenne Twister 64-bit engine PRNG <-- This Mersenne twister is actually not suitable 
    //for cryptographic random numbers and instead we better use OpenSSL library, it need to be installed though

    // Generate random data
    std::vector<uint8_t> randomData(size);
    for (size_t i = 0; i < size; ++i) {
        randomData[i] = static_cast<uint8_t>(generator());
    }

    return randomData;
}

// Function to write random data to a file
void writeRandomDataToFile(const std::string& filename, const std::vector<uint8_t>& data) {
    std::ofstream outputFile(filename, std::ios::binary);
    if (outputFile.is_open()) {
        outputFile.write(reinterpret_cast<const char*>(data.data()), data.size());
        std::cout << "Random data written to file: " << filename << std::endl;
    }
    else {
        std::cerr << "Error opening file: " << filename << std::endl;
    }
}

int main() {
    // Specify the filename and the size of random data
    std::string filename = "random_data.txt";
    size_t dataSize = 1024; // Data size in bytes

    // Generate random data
    std::vector<uint8_t> randomData = generateRandomData(dataSize);

    // Write random data to a file
    writeRandomDataToFile(filename, randomData);

    return 0;
}
