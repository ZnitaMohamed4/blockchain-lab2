# Atelier 2 – Automate Cellulaire et Fonction de Hachage dans la Blockchain

## 🎯 Objectif du projet
Ce projet explore l’utilisation d’un **automate cellulaire** pour concevoir une **fonction de hachage expérimentale (AC_HASH)** et l’intégrer dans une **blockchain simplifiée**, afin de comparer ses performances et propriétés avec celles de **SHA-256**.

---

## 👨‍💻 Réalisé par
- **Znita Mohamed**  
- **Wafik Reda**

**Encadrement :** Pr. *Ikram BENABDELOUAHAB*  
**Formation :** Master IASD – 2ᵉ année  
**Année universitaire :** 2025 / 2026  

---

## 📂 Structure du projet
```
blockchain-atelier2/
│
├── src/
│   ├── CellularAutomaton.h / .cpp     # Implémentation de l’automate cellulaire
│   ├── ac_hash.h / .cpp               # Fonction de hachage AC_HASH
│   ├── Block.h / .cpp                 # Structure d’un bloc
│   ├── Blockchain.h / .cpp            # Gestion de la blockchain
│   ├── test.cpp                       # Tests automatiques
│   └── main.cpp                       # Application principale
│
├── Makefile                           # Compilation automatisée
├── run_tests.sh                       # Script de test complet
├── results.txt                        # Résultats des tests
└── README.md                          # Ce fichier
```

---

## ⚙️ Installation et Exécution

### 1. Compilation
```bash
make clean
make
```

### 2. Exécution des tests
```bash
chmod +x run_tests.sh
./run_tests.sh
```

### 3. Exécution manuelle
```bash
./test       # Lancer les tests
./main       # Lancer la blockchain interactive
```

---

## 🧩 Fonctionnalités principales

### 1. Automate cellulaire
- Implémentation de **Rule 30** (Wolfram) validée.
- Fonction `evolve()` appliquant les règles de transition locales.
- Génération du pattern chaotique caractéristique.

### 2. Fonction de hachage `AC_HASH`
- Conversion du texte → bits → hachage 256 bits.
- Paramètres : règle (`rule`), nombre d’itérations (`steps`).
- Comparaison entre deux entrées distinctes : unicité validée.

### 3. Intégration Blockchain
- Option de hachage : `SHA256` ou `AC_HASH`.
- Minage adaptatif basé sur le mode choisi.
- Validation fonctionnelle réussie sur les blocs.

---

## 📊 Résultats Expérimentaux

| Test | Description | Résultat |
|------|--------------|----------|
| ✅ Rule 30 | Automate cellulaire fonctionnel | Succès |
| ✅ Unicité des hashs | Entrées distinctes → empreintes uniques | Succès |
| ✅ Validation blockchain | Hashage et minage intégrés | Succès |
| ❌ Performance minage | AC_HASH 50 000× plus lent que SHA256 | Échec |
| ❌ Effet avalanche | 10.94 % (au lieu de 50 %) | Échec |
| ⚠️ Distribution des bits | 45 % de bits à 1 | Acceptable |
| ⚠️ Collisions Rule 110 | 8 % de collisions détectées | Échec partiel |

---

## ⚖️ Analyse : AC_HASH vs SHA256

| Critère | SHA256 | AC_HASH | Verdict |
|----------|---------|----------|----------|
| Performance | ⚡ Très rapide | 🐢 Extrêmement lent | SHA256 |
| Avalanche | 50 % | 10.94 % | SHA256 |
| Distribution | Uniforme | Légèrement biaisée | SHA256 |
| Collisions | 0 | Jusqu’à 8 % | SHA256 |
| Sécurité prouvée | Oui (NIST) | Non | SHA256 |
| Valeur éducative | Moyenne | Excellente | AC_HASH |

---

## 🧠 Conclusions

### ✅ Points forts
- Implémentation réussie et intégrée à la blockchain.  
- Bon équilibre global des bits.  
- Excellente valeur pédagogique.  

### ❌ Limitations
- Performance catastrophique en minage.  
- Effet avalanche insuffisant.  
- Collisions et patterns cycliques.  
- Non viable pour usage cryptographique réel.  

---

## 💡 Recommandations

1. **Usage éducatif** → Recommandé (illustration de concepts cryptographiques).  
2. **Usage en production** → Non recommandé.  
3. **Amélioration proposée** → Hachage **hybride AC + SHA256**, combinant innovation et sécurité.  
4. **Pistes futures** → Automates 2D, règles dynamiques, implémentation GPU.

---

## 📜 Licence
Projet académique – Master IASD (Université, 2025/2026)  
Utilisation libre à des fins pédagogiques uniquement.
````
