cmake_minimum_required(VERSION 3.30)

project(TestSFML CXX)


# La SFML 3 nécessite au moins le C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)





#-----------------------------


# 1. Inclure le module FetchContent de CMake
include(FetchContent)

# 2. Déclarer la SFML (branche master pour la dernière version)
FetchContent_Declare(
        src
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG        master
)

# Optionnel : Désactiver les modules inutiles pour compiler plus vite
set(SFML_BUILD_AUDIO OFF CACHE INTERNAL "")
set(SFML_BUILD_NETWORK OFF CACHE INTERNAL "")

# 3. Télécharger et rendre la SFML disponible
FetchContent_MakeAvailable(src)

# 4. Déclarer votre exécutable à partir du fichier main.cpp
add_executable(game src/main.cpp)

# 5. Lier les modules SFML nécessaires à votre exécutable
target_link_libraries(game PRIVATE SFML::Graphics SFML::Window SFML::System)