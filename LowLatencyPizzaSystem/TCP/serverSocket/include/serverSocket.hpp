//
// Created by bird on 27/02/25.
//

#ifndef SERVERSOCKET_HPP
#define SERVERSOCKET_HPP

#include <iostream>
#include <vector>
#include <sys/socket>
#include <sys/types.h>
#include <unistd.h>

#define SOCKET_PATH "/tmp/socket_parent/"

class ServerSocket {

private:
  int server_fd;
  std::vector<int> pids;

public:
  ServerSocket();
  ~ServerSocket();
  void acceptClients(int numClients);
};


#endif //SERVERSOCKET_HPP
