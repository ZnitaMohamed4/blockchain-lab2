#ifndef CELLULAR_AUTOMATON_H
#define CELLULAR_AUTOMATON_H

#include <vector>
#include <string>
#include <cstdint>

class CellularAutomaton {
private:
    std::vector<uint8_t> state;
    uint32_t rule;
    size_t size;

    // Applique la règle de transition pour une cellule
    uint8_t apply_rule(uint8_t left, uint8_t center, uint8_t right) const;

public:
    CellularAutomaton(size_t size, uint32_t rule);
    
    // Initialise l'état à partir d'un vecteur de bits
    void init_state(const std::vector<uint8_t>& initial_state);
    
    // Fait évoluer l'automate d'un pas
    void evolve();
    
    // Obtient l'état actuel
    std::vector<uint8_t> get_state() const;
    
    // Affiche l'état (pour debug)
    void print_state() const;
    
    // Convertit l'état en chaîne hexadécimale
    std::string state_to_hex() const;
};

// Fonction de hachage basée sur l'automate cellulaire
std::string ac_hash(const std::string& input, uint32_t rule, size_t steps);

#endif // CELLULAR_AUTOMATON_H