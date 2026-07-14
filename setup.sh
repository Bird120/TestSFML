#!/bin/bash

# Couleurs pour le terminal
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

echo -e "${GREEN}🔍 Vérification des privilèges et préparation...${NC}"

# 1. Vérification des droits sudo
if [ "$EUID" -ne 0 ] && ! command -v sudo &> /dev/null; then
    echo -e "${RED}❌ Erreur : Ce script nécessite les privilèges 'sudo' pour installer les paquets système.${NC}"
    echo "Si vous n'êtes pas administrateur, demandez l'installation manuelle de :"
    echo "libxrandr-dev libxcursor-dev libxi-dev libudev-dev libgl1-mesa-dev libfreetype-dev libharfbuzz-dev"
    exit 1
fi

echo -e "${GREEN}📦 Mise à jour des dépôts et installation des dépendances SFML 3...${NC}"

# 2. Installation groupée de toutes les dépendances requises
if [ "$EUID" -eq 0 ]; then
    apt-get update && apt-get install -y \
        libxrandr-dev \
        libxcursor-dev \
        libxi-dev \
        libudev-dev \
        libgl1-mesa-dev \
        libfreetype-dev \
        libharfbuzz-dev
else
    sudo apt-get update && sudo apt-get install -y \
        libxrandr-dev \
        libxcursor-dev \
        libxi-dev \
        libudev-dev \
        libgl1-mesa-dev \
        libfreetype-dev \
        libharfbuzz-dev
fi

# 3. Message de confirmation final
if [ $? -eq 0 ]; then
    echo -e "${GREEN}✅ Toutes les dépendances ont été installées avec succès !${NC}"
    echo "Vous pouvez maintenant aller dans votre dossier 'build' et lancer :"
    echo "  cmake .."
    echo "  cmake --build ."
else
    echo -e "${RED}❌ Une erreur est survenue lors de l'installation des paquets.${NC}"
    exit 1
fi