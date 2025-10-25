# Atelier 2 – Automate Cellulaire et Fonction de Hachage dans la Blockchain

## 🎯 Objectif de l’atelier
Cet atelier a pour but d’explorer l’utilisation d’un **automate cellulaire** pour concevoir une **fonction de hachage expérimentale (AC_HASH)** et l’intégrer dans une **blockchain simplifiée**, afin d’analyser ses performances et propriétés face à la fonction standard **SHA-256**.

---

## 👨‍💻 Réalisé par
- **Znita Mohamed**  
- **Wafik Reda**

**Encadrement :** Pr. *Ikram BENABDELOUAHAB*  
**Formation :** Master IASD – 2ᵉ année  
**Année universitaire :** 2025 / 2026  

---

## 📂 Structure de l’atelier
```
atelier2-blockchain/
│
├── src/
│   ├── CellularAutomaton.h / .cpp     # Automate cellulaire 1D
│   ├── ac_hash.h / .cpp               # Fonction de hachage AC_HASH
│   ├── Block.h / .cpp                 # Structure et calcul du bloc
│   ├── Blockchain.h / .cpp            # Gestion simplifiée de la blockchain
│   ├── test.cpp                       # Tests automatiques
│   └── main.cpp                       # Programme principal
│
├── Makefile                           # Compilation
├── run_tests.sh                       # Script d’exécution des tests
├── results.txt                        # Résultats générés
└── README.md                          # Ce fichier
```

---

## ⚙️ Compilation et Exécution

### 1. Compiler le projet
```bash
make clean
make
```

### 2. Lancer les tests
```bash
chmod +x run_tests.sh
./run_tests.sh
```

### 3. Lancer manuellement
```bash
./test       # Exécuter les tests
./main       # Lancer la blockchain interactive
```

---

## 🧩 Contenu de l’atelier

### 1. Automate cellulaire
- Implémentation complète de **Rule 30** (Wolfram).
- Application de la règle locale via `evolve()`.
- Validation du comportement chaotique attendu.

### 2. Fonction de hachage `AC_HASH`
- Conversion texte → bits → hachage 256 bits.
- Paramètres : règle (`rule`) et nombre d’itérations (`steps`).
- Vérification de l’unicité des hashs générés.

### 3. Intégration Blockchain
- Double mode : `SHA256` ou `AC_HASH`.
- Minage et validation automatique des blocs.
- Fonctionnement correct validé sur plusieurs blocs.

---

## 📊 Résultats Expérimentaux

| Test | Description | Résultat |
|------|--------------|----------|
| ✅ Rule 30 | Automate cellulaire fonctionnel | Validé |
| ✅ Unicité des hashs | Deux entrées → deux empreintes distinctes | Validé |
| ✅ Intégration blockchain | Hachage et validation OK | Validé |
| ❌ Performance minage | AC_HASH ~50 000× plus lent que SHA256 | Échec |
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
| Valeur pédagogique | Moyenne | Excellente | AC_HASH |

---

## 🧠 Conclusions

### ✅ Points forts
- Automate cellulaire correctement implémenté et intégré.  
- Distribution globale acceptable.  
- Grande valeur pédagogique et expérimentale.  

### ❌ Limitations
- Performance très faible pour le minage.  
- Effet avalanche insuffisant pour la cryptographie.  
- Collisions et répétitions détectées.  
- Non adapté à un usage blockchain réel.  

---

## 💡 Recommandations

1. **Usage éducatif et recherche** → Fortement recommandé.  
2. **Usage en production** → Non recommandé.  
3. **Amélioration suggérée** → Approche **hybride AC + SHA256** pour combiner sécurité et innovation.  
4. **Pistes futures** → Automates 2D, règles adaptatives, implémentation GPU parallèle.

---

## 📜 Mention
Travail réalisé dans le cadre de **l’Atelier 2** du module *Blockchain* – Master IASD (2025/2026).  
Utilisation libre à des fins pédagogiques uniquement.
````
