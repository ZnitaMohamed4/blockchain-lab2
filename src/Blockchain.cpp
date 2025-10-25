#include "Blockchain.h"
#include <iostream>

Blockchain::Blockchain(uint32_t diff, HashMode mode, uint32_t rule, size_t steps)
    : difficulty(diff), default_hash_mode(mode), ac_rule(rule), ac_steps(steps) {
    chain.push_back(std::unique_ptr<Block>(create_genesis_block()));
}

Block* Blockchain::create_genesis_block() {
    std::vector<std::string> genesis_transactions = {"Genesis Block"};
    return new Block(0, genesis_transactions, "0", default_hash_mode, 
                     ac_rule, ac_steps);
}

Block* Blockchain::get_latest_block() const {
    return chain.back().get();
}

void Blockchain::add_block(const std::vector<std::string>& transactions) {
    Block* previous_block = get_latest_block();
    uint32_t new_index = previous_block->get_index() + 1;
    
    Block* new_block = new Block(new_index, transactions, 
                                 previous_block->get_hash(),
                                 default_hash_mode, ac_rule, ac_steps);
    
    new_block->mine_block(difficulty);
    chain.push_back(std::unique_ptr<Block>(new_block));
}

bool Blockchain::is_chain_valid() const {
    for (size_t i = 1; i < chain.size(); i++) {
        const Block& current = *chain[i];
        const Block& previous = *chain[i - 1];
        
        // Vérifier le hash du bloc actuel
        if (!current.is_valid(difficulty)) {
            std::cout << "Block #" << current.get_index() 
                      << " has invalid hash!" << std::endl;
            return false;
        }
        
        // Vérifier le lien avec le bloc précédent
        if (current.get_previous_hash() != previous.get_hash()) {
            std::cout << "Block #" << current.get_index() 
                      << " has invalid previous hash!" << std::endl;
            return false;
        }
    }
    
    return true;
}

void Blockchain::print_chain() const {
    std::cout << "\n======== BLOCKCHAIN ========" << std::endl;
    std::cout << "Length: " << chain.size() << std::endl;
    std::cout << "Difficulty: " << difficulty << std::endl;
    std::cout << "Valid: " << (is_chain_valid() ? "Yes" : "No") << std::endl;
    std::cout << "============================\n" << std::endl;
    
    for (const auto& block : chain) {
        block->print();
    }
}