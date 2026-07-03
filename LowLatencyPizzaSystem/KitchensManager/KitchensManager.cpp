//
// Created by bird on 14/04/25.
//

#include "ManagerKitchens.hpp"

ManagerKitchens::ManagerKitchens() {

}

const std::vector<BuiltKitchen>& ManagerKitchens::getKitchens() const{
  return kitchens;
}

void ManagerKitchens::setParentPid(const pid_t& pid) {
  parent = pid;
}

const pid_t& ManagerKitchens::getParentPid() const{
  return parent;
}

const BuiltKitchen& ManagerKitchens::getLastKitchen() const {
  return kitchens.back();
}


int ManagerKitchens::findKitchensSize() {
    int v = 1;
    if (kitchens.empty()) return -2;
    for (int i = 0; i < kitchens.size(); i++)
    {
      if (kitchens[i].counter != v) return i + 1;
      else if (kitchens.size() != v)  v++;
    }
    std::cout << "size: " << kitchens.size() << " v:" << v<< std::endl;
    if (kitchens.size() == v)
      return 0;
    return -1;
}