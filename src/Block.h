#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <vector>
#include <ctime>
#include <cstdint>

enum class HashMode {
    SHA256,
    AC_HASH
};

class Block {
private:
    uint32_t index;
    time_t timestamp;
    std::vector<std::string> transactions;
    std::string previous_hash;
    uint32_t nonce;
    std::string hash;
    
    // Mode de hachage et paramètres
    HashMode hash_mode;
    uint32_t ac_rule;
    size_t ac_steps;

public:
    Block(uint32_t idx, const std::vector<std::string>& txs, 
          const std::string& prev_hash, HashMode mode = HashMode::SHA256,
          uint32_t rule = 30, size_t steps = 128);
    
    // Calcule le hash du bloc selon le mode choisi
    std::string calculate_hash() const;
    
    // Mine le bloc jusqu'à trouver un hash valide
    void mine_block(uint32_t difficulty);
    
    // Getters
    std::string get_hash() const { return hash; }
    std::string get_previous_hash() const { return previous_hash; }
    uint32_t get_index() const { return index; }
    uint32_t get_nonce() const { return nonce; }
    HashMode get_hash_mode() const { return hash_mode; }
    
    // Affichage
    void print() const;
    
    // Validation
    bool is_valid(uint32_t difficulty) const;
};

#endif // BLOCK_H