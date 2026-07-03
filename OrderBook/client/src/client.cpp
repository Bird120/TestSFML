//
// Created by bird on 18/11/25.
//
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

void run_server() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    const int PORT = 8080;

    // 1. Créer le socket du serveur (File Descriptor)
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("échec de la création du socket");
        exit(EXIT_FAILURE);
    }

    // Attacher le socket au port 8080 (pour réutilisation)
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt a échoué");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // Écouter toutes les interfaces
    address.sin_port = htons(PORT);

    // 2. Attacher le socket à l'adresse et au port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("échec de la liaison (bind)");
        exit(EXIT_FAILURE);
    }

    // 3. Passer en mode écoute
    if (listen(server_fd, 3) < 0) {
        perror("échec de l'écoute (listen)");
        exit(EXIT_FAILURE);
    }

    std::cout << "Serveur Market Maker en écoute sur le port " << PORT << std::endl;

    // 4. Accepter une nouvelle connexion
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("échec de l'acceptation (accept)");
        exit(EXIT_FAILURE);
    }

    std::cout << "Client (Stratégie) connecté." << std::endl;

    // 5. Boucle de communication
    char buffer[1024] = {0};
    const char *hello = "Confirmation FIX: READY";

    // Envoyer un message de bienvenue (simulant un Logon FIX)
    send(new_socket, hello, strlen(hello), 0);
    std::cout << "Message envoyé au client : " << hello << std::endl;

    // Attendre un message du client (simulant un New Order Single)
    read(new_socket, buffer, 1024);
    std::cout << "Message FIX reçu : " << buffer << std::endl;

    // Fermer les sockets
    close(new_socket);
    close(server_fd);
}

 int main() { run_server(); return 0; }