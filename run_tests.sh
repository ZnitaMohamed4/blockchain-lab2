#!/bin/bash

# Script pour compiler et exécuter tous les tests
# Atelier 2 - Blockchain avec Automate Cellulaire

echo "======================================"
echo "  COMPILATION ET EXÉCUTION DES TESTS"
echo "======================================"
echo ""

# Vérifier si OpenSSL est installé
if ! pkg-config --exists openssl; then
    echo "⚠️  OpenSSL n'est pas installé!"
    echo "Sur WSL/Ubuntu, installez avec:"
    echo "  sudo apt-get update"
    echo "  sudo apt-get install libssl-dev"
    exit 1
fi

# Nettoyer les anciens fichiers
echo "🧹 Nettoyage des anciens fichiers..."
make clean 2>/dev/null

# Compiler
echo ""
echo "🔨 Compilation du projet..."
if make; then
    echo "✓ Compilation réussie!"
else
    echo "✗ Erreur de compilation!"
    exit 1
fi

# Exécuter les tests
echo ""
echo "🧪 Exécution des tests..."
echo ""
make test

# Sauvegarder les résultats
echo ""
echo "💾 Sauvegarde des résultats dans results.txt..."
./test > results.txt 2>&1

echo ""
echo "======================================"
echo "  TESTS TERMINÉS"
echo "======================================"
echo ""
echo "Les résultats sont disponibles dans:"
echo "  - results.txt (sortie complète)"
echo ""
echo "Pour exécuter l'application interactive:"
echo "  ./main"
echo ""