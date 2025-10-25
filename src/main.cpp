#include "Blockchain.h"
#include "CellularAutomaton.h"
#include <iostream>
#include <string>

using namespace std;

void print_menu() {
    cout << "\n========== MENU ==========" << endl;
    cout << "1. Créer blockchain avec SHA256" << endl;
    cout << "2. Créer blockchain avec AC_HASH (Rule 30)" << endl;
    cout << "3. Créer blockchain avec AC_HASH (Rule 90)" << endl;
    cout << "4. Créer blockchain avec AC_HASH (Rule 110)" << endl;
    cout << "5. Test automate cellulaire" << endl;
    cout << "6. Quitter" << endl;
    cout << "==========================" << endl;
    cout << "Choix: ";
}

void demo_cellular_automaton(uint32_t rule) {
    cout << "\n=== Démonstration Automate Cellulaire - Rule " << rule << " ===" << endl;
    
    CellularAutomaton ca(41, rule);
    vector<uint8_t> initial(41, 0);
    initial[20] = 1; // Un seul bit au centre
    
    ca.init_state(initial);
    
    cout << "État initial:" << endl;
    ca.print_state();
    
    cout << "\nÉvolution sur 15 générations:" << endl;
    for (int i = 0; i < 15; i++) {
        ca.evolve();
        ca.print_state();
    }
}

void run_blockchain_demo(HashMode mode, uint32_t rule = 30) {
    cout << "\n=== Démonstration Blockchain ===" << endl;
    
    uint32_t difficulty = 3;
    Blockchain blockchain(difficulty, mode, rule, 128);
    
    cout << "Blockchain créée avec:" << endl;
    cout << "  - Mode: " << (mode == HashMode::SHA256 ? "SHA256" : "AC_HASH") << endl;
    if (mode == HashMode::AC_HASH) {
        cout << "  - Règle AC: " << rule << endl;
    }
    cout << "  - Difficulté: " << difficulty << endl;
    
    // Ajouter quelques blocs
    cout << "\nAjout de blocs..." << endl;
    
    blockchain.add_block({"Alice -> Bob: 50 MAD", "Bob -> Charlie: 30 MAD"});
    blockchain.add_block({"Charlie -> Alice: 20 MAD"});
    blockchain.add_block({"Alice -> Dave: 15 MAD", "Dave -> Bob: 10 MAD"});
    
    // Afficher la blockchain
    blockchain.print_chain();
    
    // Valider
    cout << "\nValidation de la chaîne: " 
         << (blockchain.is_chain_valid() ? "✓ VALIDE" : "✗ INVALIDE") << endl;
}

int main() {
    cout << "=====================================" << endl;
    cout << "  BLOCKCHAIN AVEC AUTOMATE CELLULAIRE" << endl;
    cout << "  Atelier 2 - Master IASD 2025/2026" << endl;
    cout << "=====================================" << endl;
    
    int choice;
    bool running = true;
    
    while (running) {
        print_menu();
        cin >> choice;
        
        switch (choice) {
            case 1:
                run_blockchain_demo(HashMode::SHA256);
                break;
            case 2:
                run_blockchain_demo(HashMode::AC_HASH, 30);
                break;
            case 3:
                run_blockchain_demo(HashMode::AC_HASH, 90);
                break;
            case 4:
                run_blockchain_demo(HashMode::AC_HASH, 110);
                break;
            case 5: {
                cout << "\nChoisissez la règle (30, 90, ou 110): ";
                uint32_t rule;
                cin >> rule;
                demo_cellular_automaton(rule);
                break;
            }
            case 6:
                cout << "\nAu revoir!" << endl;
                running = false;
                break;
            default:
                cout << "\nChoix invalide!" << endl;
        }
    }
    
    return 0;
}