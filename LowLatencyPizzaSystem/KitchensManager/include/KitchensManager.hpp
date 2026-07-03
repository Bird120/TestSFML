//
// Created by bird on 14/04/25.
//

#ifndef MANAGERKITCHENS_HPP
#define MANAGERKITCHENS_HPP

#include <vector>
#include "socket.hpp"
#include <memory>

struct BuiltKitchen{
  pid_t pid;
  Socket* socket;
  int counter;
  BuiltKitchen(pid_t pid, Socket* socket, int counter);
};


class ManagerKitchens {
private:
  std::vector<BuiltKitchen> kitchens;
  pid_t parent;

public:
  ManagerKitchens();
  const std::vector<BuiltKitchen>& getKitchens() const;
  void setParentPid(const pid_t& pid);
  void setKitchen(BuiltKitchen& kitchen);
  const pid_t& getParentPid() const;
  int findKitchensSize();
  const BuiltKitchen& getLastKitchen() const;

};

#endif //MANAGERKITCHENS_HPP
