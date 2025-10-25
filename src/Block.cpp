#include "Block.h"
#include "CellularAutomaton.h"
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>
#include <iostream>

Block::Block(uint32_t idx, const std::vector<std::string>& txs, 
             const std::string& prev_hash, HashMode mode,
             uint32_t rule, size_t steps)
    : index(idx), transactions(txs), previous_hash(prev_hash),
      nonce(0), hash_mode(mode), ac_rule(rule), ac_steps(steps) {
    timestamp = time(nullptr);
    hash = calculate_hash();
}

std::string sha256_hash(const std::string& input) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(input.c_str()), 
           input.length(), hash);
    
    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') 
           << static_cast<int>(hash[i]);
    }
    return ss.str();
}

std::string Block::calculate_hash() const {
    std::stringstream ss;
    ss << index << timestamp << previous_hash << nonce;
    
    for (const auto& tx : transactions) {
        ss << tx;
    }
    
    std::string data = ss.str();
    
    if (hash_mode == HashMode::SHA256) {
        return sha256_hash(data);
    } else {
        return ac_hash(data, ac_rule, ac_steps);
    }
}

void Block::mine_block(uint32_t difficulty) {
    std::string target(difficulty, '0');
    
    std::cout << "Mining block " << index << "..." << std::endl;
    
    uint32_t iterations = 0;
    do {
        nonce++;
        hash = calculate_hash();
        iterations++;
        
        if (iterations % 10000 == 0) {
            std::cout << "  Iteration: " << iterations 
                      << ", Nonce: " << nonce << std::endl;
        }
    } while (hash.substr(0, difficulty) != target);
    
    std::cout << "Block mined! Hash: " << hash << std::endl;
    std::cout << "Iterations: " << iterations << std::endl;
}

void Block::print() const {
    std::cout << "=== Block #" << index << " ===" << std::endl;
    std::cout << "Timestamp: " << timestamp << std::endl;
    std::cout << "Previous Hash: " << previous_hash << std::endl;
    std::cout << "Hash: " << hash << std::endl;
    std::cout << "Nonce: " << nonce << std::endl;
    std::cout << "Hash Mode: " 
              << (hash_mode == HashMode::SHA256 ? "SHA256" : "AC_HASH") 
              << std::endl;
    if (hash_mode == HashMode::AC_HASH) {
        std::cout << "AC Rule: " << ac_rule << std::endl;
        std::cout << "AC Steps: " << ac_steps << std::endl;
    }
    std::cout << "Transactions:" << std::endl;
    for (const auto& tx : transactions) {
        std::cout << "  - " << tx << std::endl;
    }
    std::cout << std::endl;
}

bool Block::is_valid(uint32_t difficulty) const {
    std::string target(difficulty, '0');
    
    // Vérifier que le hash commence par le bon nombre de zéros
    if (hash.substr(0, difficulty) != target) {
        return false;
    }
    
    // Recalculer le hash et vérifier qu'il correspond
    Block temp_block = *this;
    std::string recalculated = temp_block.calculate_hash();
    
    return hash == recalculated;
}