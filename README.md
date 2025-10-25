# Blockchain avec Automate Cellulaire

**Atelier 2 - Module Blockchain**  
**Master IASD 2025/2026**  
**Pr. Ikram BENABDELOUAHAB**

## 📋 Description

Ce projet implémente une blockchain éducative en C++ qui utilise des automates cellulaires comme fonction de hachage alternative à SHA-256. L'objectif est d'explorer les propriétés cryptographiques des automates cellulaires (Rules 30, 90, 110) dans le contexte de la blockchain.

## 🏗️ Architecture du Projet

```
blockchain-cellular-automaton/
├── src/
│   ├── CellularAutomaton.h      # Définition de l'automate cellulaire
│   ├── CellularAutomaton.cpp    # Implémentation de l'automate
│   ├── Block.h                  # Définition d'un bloc
│   ├── Block.cpp                # Implémentation du bloc et minage
│   ├── Blockchain.h             # Définition de la blockchain
│   ├── Blockchain.cpp           # Implémentation de la blockchain
│   ├── main.cpp                 # Application interactive
│   └── test.cpp                 # Suite de tests automatisés
├── Makefile                     # Fichier de compilation
├── run_tests.sh                 # Script d'exécution des tests
├── README.md                    # Ce fichier
└── RAPPORT.md                   # Rapport détaillé avec réponses
```

## 🔧 Prérequis

- **Système**: Linux (WSL2 recommandé pour Windows)
- **Compilateur**: g++ avec support C++17
- **Bibliothèques**: OpenSSL

### Installation sur WSL/Ubuntu

```bash
sudo apt-get update
sudo apt-get install build-essential libssl-dev
```

## 🚀 Compilation et Exécution

### Méthode 1: Script automatique

```bash
chmod +x run_tests.sh
./run_tests.sh
```

### Méthode 2: Makefile

```bash
# Compiler tout
make

# Compiler et exécuter les tests
make test

# Exécuter l'application interactive
make run

# Nettoyer
make clean
```

### Méthode 3: Compilation manuelle

```bash
g++ -std=c++17 -Wall -Wextra -O2 -c CellularAutomaton.cpp
g++ -std=c++17 -Wall -Wextra -O2 -c Block.cpp
g++ -std=c++17 -Wall -Wextra -O2 -c Blockchain.cpp
g++ -std=c++17 -Wall -Wextra -O2 -c test.cpp

g++ -std=c++17 -o test CellularAutomaton.o Block.o Blockchain.o test.o -lssl -lcrypto
./test
```

## 📊 Tests Implémentés

Le programme `test.cpp` exécute automatiquement tous les tests requis:

1. **Test de l'automate cellulaire** (Q1.3)
   - Vérifie le bon fonctionnement de Rule 30
   - Affiche les 10 premières générations

2. **Test de différence de hash** (Q2.4)
   - Vérifie que deux entrées différentes produisent des hashes différents

3. **Comparaison de performance** (Q4)
   - Compare SHA256 vs AC_HASH
   - Mesure temps de minage sur 10 blocs
   - Calcule le nombre moyen d'itérations

4. **Effet avalanche** (Q5)
   - Mesure le pourcentage de bits différents
   - Teste sur 100 paires de messages

5. **Distribution des bits** (Q6)
   - Analyse sur 1000 hashes
   - Vérifie l'équilibre ~50% de bits à 1

6. **Comparaison des règles** (Q7)
   - Teste Rules 30, 90, et 110
   - Compare stabilité et performance

## 🎯 Fonctionnalités Principales

### Automate Cellulaire 1D

- **Règles implémentées**: Rule 30, Rule 90, Rule 110
- **Voisinage**: r = 1 (3 cellules)
- **État**: Binaire (0 ou 1)
- **Conditions limites**: Périodiques (wrap-around)

### Fonction de Hachage AC_HASH

```cpp
std::string ac_hash(const std::string& input, uint32_t rule, size_t steps);
```

**Paramètres**:
- `input`: Texte d'entrée à hacher
- `rule`: Règle d'automate (30, 90, ou 110)
- `steps`: Nombre d'itérations (typiquement 128)

**Processus**:
1. Conversion du texte en bits (8 bits par caractère)
2. Padding/compression à 256 bits
3. Initialisation de l'automate
4. Évolution pendant `steps` itérations
5. Extraction du hash final (256 bits / 64 caractères hex)

### Blockchain

- **Modes de hachage**: SHA256 ou AC_HASH
- **Preuve de travail**: Mining avec difficulté ajustable
- **Validation**: Vérification de l'intégrité de la chaîne

## 📈 Résultats Attendus

### Comparaison SHA256 vs AC_HASH (Rule 30)

| Métrique | SHA256 | AC_HASH | Ratio |
|----------|--------|---------|-------|
| Temps moyen/bloc | ~50 ms | ~200 ms | 4x |
| Itérations moyennes | ~1000 | ~1000 | 1x |
| Sécurité | Prouvée | Expérimentale | - |

### Effet Avalanche

- **Attendu**: ~50% de bits différents
- **AC_HASH Rule 30**: ~45-50% (bon)
- **AC_HASH Rule 90**: ~35-40% (moyen)

### Distribution des Bits

- **Attendu**: ~50% de bits à 1
- **AC_HASH Rule 30**: ~48-52% (équilibré)

## 🔍 Questions Répondues

### Q1: Implémentation de l'automate cellulaire ✓
- `CellularAutomaton` classe avec `init_state()` et `evolve()`
- Support des Rules 30, 90, 110

### Q2: Fonction de hachage basée sur AC ✓
- `ac_hash()` implémentée avec conversion texte→bits
- Hash final de 256 bits garanti

### Q3: Intégration dans la blockchain ✓
- Enum `HashMode` pour sélection SHA256/AC_HASH
- Minage fonctionnel avec les deux modes

### Q4-7: Tests et comparaisons ✓
- Tous les tests automatisés dans `test.cpp`
- Résultats exportés dans `results.txt`

### Q8: Avantages potentiels
- **Simplicité**: Règles locales très simples
- **Parallélisation**: Potentiel de calcul parallèle
- **Légèreté**: Moins de ressources que SHA-256
- **Diversité**: Alternative cryptographique innovante

### Q9: Faiblesses et vulnérabilités
- **Sécurité non prouvée**: Pas d'analyse cryptographique formelle
- **Performance**: Plus lent que SHA-256 optimisé
- **Résistance aux collisions**: Non démontrée mathématiquement
- **Attaques potentielles**: Vulnérabilité aux patterns spécifiques

### Q10: Amélioration proposée

**Hachage hybride AC+SHA256**:
```cpp
std::string hybrid_hash(const std::string& input) {
    // Première passe: AC_HASH pour la diffusion
    std::string ac_result = ac_hash(input, 30, 128);
    
    // Seconde passe: SHA256 pour la sécurité
    return sha256_hash(ac_result);
}
```

**Avantages**:
- Combine la non-linéarité de l'AC avec la sécurité de SHA-256
- Double couche de protection
- Performances raisonnables

## 📝 Mode d'Emploi

### Application Interactive

```bash
./main
```

Menu:
1. Blockchain avec SHA256
2. Blockchain avec AC_HASH (Rule 30)
3. Blockchain avec AC_HASH (Rule 90)
4. Blockchain avec AC_HASH (Rule 110)
5. Démonstration automate cellulaire
6. Quitter

### Tests Automatiques

```bash
./test > results.txt
```

Génère un rapport complet avec:
- Visualisation de l'automate
- Comparaisons de performance
- Analyses statistiques
- Tableaux de résultats

## 🎓 Contexte Académique

Ce projet s'inscrit dans le cadre du module Blockchain du Master IASD. Il vise à:
- Comprendre les fondements cryptographiques de la blockchain
- Explorer des alternatives aux fonctions de hachage classiques
- Analyser les propriétés requises pour une fonction de hachage sécurisée
- Expérimenter avec des systèmes dynamiques complexes

## 📚 Références

- Wolfram, S. (1983). "Statistical mechanics of cellular automata"
- Wolfram, S. (2002). "A New Kind of Science"
- Nakamoto, S. (2008). "Bitcoin: A Peer-to-Peer Electronic Cash System"

## 👨‍💻 Auteur

Étudiant Master IASD 2025/2026

## 📄 Licence

Projet éducatif - Master IASD