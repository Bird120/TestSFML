//
// Created by bird on 19/04/25.
//

#include <iostream>
#include <memory>
#include "include/ChildProcess.hpp"
#include "../Kitchen/include/Kitchen.hpp"
#include "../TCP/include/socket.hpp"
#include <sys/wait.h>  // para waitpid
#include <unistd.h>    // para fork

int main() {

   int socket[2];
  std::unique_ptr<Socket> socketsObj = std::make_unique<Socket>();
  socket[0] = socketsObj->getSocket(0);
  socket[1] = socketsObj->getSocket(1);

  pid_t  pid = fork();
  if (pid < 0)
    std::cerr << "Fork Failed" << std::endl;
  else if (pid == 0) {
      std::unique_ptr<Kitchen> kitchen = std::make_unique<Kitchen>(2, 2000, 6);
      std::unique_ptr<ChildProcess> child = std::make_unique<ChildProcess>(socket, std::move(kitchen));
  }

  else
    {
        close(socket[1]);
        writeBuffer(socket[0], "Can You receive an order ?");
        auto response = readBuffer(socket[0]);
        if (std::strcmp(response.c_str(), "YES"))
          writeBuffer(socket[0], "regina M 2000");
        int status;
        pid_t finished = waitpid(pid, &status, 0); // esperamos al hijo específico
  }

}