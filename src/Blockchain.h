#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "Block.h"
#include <vector>
#include <memory>

class Blockchain {
private:
    std::vector<std::unique_ptr<Block>> chain;
    uint32_t difficulty;
    HashMode default_hash_mode;
    uint32_t ac_rule;
    size_t ac_steps;

public:
    Blockchain(uint32_t diff = 4, HashMode mode = HashMode::SHA256,
               uint32_t rule = 30, size_t steps = 128);
    
    // Ajoute un bloc avec des transactions
    void add_block(const std::vector<std::string>& transactions);
    
    // Valide toute la chaîne
    bool is_chain_valid() const;
    
    // Affiche toute la chaîne
    void print_chain() const;
    
    // Getters
    size_t get_chain_length() const { return chain.size(); }
    const Block& get_block(size_t index) const { return *chain[index]; }
    
    // Change le mode de hachage
    void set_hash_mode(HashMode mode) { default_hash_mode = mode; }
    void set_ac_params(uint32_t rule, size_t steps) {
        ac_rule = rule;
        ac_steps = steps;
    }

private:
    Block* get_latest_block() const;
    Block* create_genesis_block();
};

#endif // BLOCKCHAIN_H