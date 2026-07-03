//
// Created by bird on 03/07/26.
//

#include <print> // Fonctionnalité spécifique à C++23
#include "calcul.hpp"

int main() {
    int somme = ajouter(20, 23);

    // std::print est plus rapide et plus propre que std::cout
    std::print("Bienvenue en C++23 !\n");
    std::print("Le résultat de 20 + 23 est : {}\n", somme);

    return 0;
}