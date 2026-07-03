//
// Created by bird on 08/04/25.
//

#ifndef PROCESSCOMMANDCOORDINATOR_HPP
#define PROCESSCOMMANDCOORDINATOR_HPP

#include "Pizza.hpp"
#include "serverSocket.hpp"
#include <iostream>

class ProcessCommandCoordinator {
private:


public:
    ProcessCommandCoordinator();
    ~ProcessCommandCoordinator();
    bool sendToClients(const Pizza& pizza, ServerSocket* obj);

};


#endif //PROCESSCOMMANDCOORDINATOR_HPP
