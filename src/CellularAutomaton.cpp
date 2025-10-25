#include "CellularAutomaton.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <bitset>
#include <algorithm>

CellularAutomaton::CellularAutomaton(size_t size, uint32_t rule) 
    : rule(rule), size(size) {  // ← Ordre corrigé
    state.resize(size, 0);
}

void CellularAutomaton::init_state(const std::vector<uint8_t>& initial_state) {
    if (initial_state.size() > size) {
        state.assign(initial_state.begin(), initial_state.begin() + size);
    } else {
        state.assign(initial_state.begin(), initial_state.end());
        state.resize(size, 0);
    }
}

uint8_t CellularAutomaton::apply_rule(uint8_t left, uint8_t center, uint8_t right) const {
    uint8_t index = (left << 2) | (center << 1) | right;
    return (rule >> index) & 1;
}

void CellularAutomaton::evolve() {
    std::vector<uint8_t> new_state(size);
    
    for (size_t i = 0; i < size; i++) {
        uint8_t left = state[(i - 1 + size) % size];
        uint8_t center = state[i];
        uint8_t right = state[(i + 1) % size];
        
        new_state[i] = apply_rule(left, center, right);
    }
    
    state = new_state;
}

std::vector<uint8_t> CellularAutomaton::get_state() const {
    return state;
}

void CellularAutomaton::print_state() const {
    for (uint8_t bit : state) {
        std::cout << (bit ? "█" : " ");
    }
    std::cout << std::endl;
}

std::string CellularAutomaton::state_to_hex() const {
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    
    for (size_t i = 0; i < state.size(); i += 8) {
        uint8_t byte = 0;
        for (size_t j = 0; j < 8 && (i + j) < state.size(); j++) {
            byte |= (state[i + j] << (7 - j));
        }
        ss << std::setw(2) << static_cast<int>(byte);
    }
    
    return ss.str();
}

// VERSION OPTIMISÉE
std::string ac_hash(const std::string& input, uint32_t rule, size_t steps) {
    // OPTIMISATION 1: Limiter les steps pour le minage
    size_t actual_steps = std::min(steps, (size_t)16);  // Max 16 au lieu de 128!
    
    std::vector<uint8_t> bits;
    
    // Convertir chaque caractère en 8 bits
    for (char c : input) {
        for (int i = 7; i >= 0; i--) {
            bits.push_back((c >> i) & 1);
        }
    }
    
    size_t target_size = 256;
    
    // OPTIMISATION 2: Padding plus simple
    if (bits.size() < target_size) {
        size_t original_size = bits.size();
        bits.resize(target_size);
        for (size_t i = original_size; i < target_size; i++) {
            bits[i] = bits[i % original_size];
        }
    } else if (bits.size() > target_size) {
        std::vector<uint8_t> compressed(target_size, 0);
        for (size_t i = 0; i < bits.size(); i++) {
            compressed[i % target_size] ^= bits[i];
        }
        bits = compressed;
    }
    
    // Créer l'automate
    CellularAutomaton ca(target_size, rule);
    ca.init_state(bits);
    
    // OPTIMISATION 3: Beaucoup moins d'itérations
    for (size_t i = 0; i < actual_steps; i++) {
        ca.evolve();
    }
    
    // Retourner le hash
    std::string hash = ca.state_to_hex();
    
    if (hash.length() > 64) {
        hash = hash.substr(0, 64);
    } else if (hash.length() < 64) {
        hash.append(64 - hash.length(), '0');
    }
    
    return hash;
}