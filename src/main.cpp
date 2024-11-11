#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include <cstdint>
#include <cstring>

// Convert a 256-bit hash (32-byte array) to a hex string
std::string toHexString(const std::vector<uint8_t>& data) {
    std::ostringstream oss;
    for (auto byte : data) {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }
    return oss.str();
}

void mix(uint64_t& init1, uint64_t& init2, uint64_t& init3, uint64_t& init4) {
    init1 ^= init2; 
    init2 += init3;
    init3 ^= init4;
    init4 += init1;
}

// Simple custom hashing algorithm that produces a 256-bit hash
std::vector<uint8_t> customHash256(const std::string& input) {
    std::vector<uint8_t> hash(32, 0);  // 256-bit buffer (32 bytes)

    // Initialize the state with arbitrary values (64-bit primes)
    uint64_t state[4] = {
        0x243F6A8885A308D3, 0x13198A2E03707344,
        0xA4093822299F31D0, 0x082EFA98EC4E6C89
    };

    // Process the input string and XOR into the state
    for (size_t i = 0; i < input.size(); ++i) {
        state[i % 4] ^= static_cast<uint64_t>(input[i]) << (8 * (i % 8));
        mix(state[0], state[1], state[2], state[3]);  // Mix the state after each character
    }

    // Final mixing for better diffusion
    for (int i = 0; i < 64; ++i) {
        mix(state[0], state[1], state[2], state[3]);
    }

    // Convert the 256-bit state (4x64-bit) into a 32-byte hash using pointer casting
    std::memcpy(hash.data(), state, 32);  // Copy 32 bytes (256 bits) from state to hash

    return hash;
}

int main() {
    std::string input;
    std::cout << "Enter input to hash: ";
    std::getline(std::cin, input);

    // Generate the 256-bit hash
    std::vector<uint8_t> hash = customHash256(input);

    // Convert the hash to a hexadecimal string
    std::string hexHash = toHexString(hash);

    std::cout << "Hash (256-bit in hex): " << hexHash << std::endl;

    return 0;
}
