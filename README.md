## 🚀 Comment compiler et lancer le projet (Linux)

Avant de compiler, vous devez installer les dépendances graphiques requises par la SFML à l'aide du script fourni :

```bash
# 1. Donner les droits d'exécution au script
chmod +x setup.sh

# 2. Lancer le script d'installation
./setup.sh

# 3. Compiler le projet avec CMake
mkdir build && cd build
cmake ..
cmake --build .

#4
./game