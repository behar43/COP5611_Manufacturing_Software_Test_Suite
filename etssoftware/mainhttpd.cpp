// Author: Ben Prishtina
// Purpose: Semester Project
// Class: COP 5611 Operating Systems Design Principles
#include <iostream>
#include <thread>
#include <string>
#include "lightwebserver.h"
#include "url.h"

int main(void)
{
    std::string cmd;

    std::cout << "//////////////////////////////" << std::endl;
    std::cout << "####### #######  #####"         << std::endl;
    std::cout << "#          #    #     #"        << std::endl;
    std::cout << "#          #    #"              << std::endl;
    std::cout << "#####      #     #####"         << std::endl;
    std::cout << "#          #          #"        << std::endl;
    std::cout << "#          #    #     #"        << std::endl;
    std::cout << "#######    #     #####"         << std::endl;
    std::cout << "//////////////////////////////" << std::endl;

    LWS::lightwebserver servObj(8080);

    for (std::string line; std::cout << "ETS->" && std::getline(std::cin, line); )
    {
        if (line == "exit") 
        {
            std::cout << "exiting..." << std::endl;
            servObj.stop(); 
            break;
        }
        else if(line == "runserv")
        {
            std::cout << "running server" << std::endl;
            servObj.runMultiThread();
        }
        else if(line == "stopserv")
        {
            std::cout << "stop server" << std::endl;
            servObj.stop();
        }
        else if(line == "help")
        {
            std::cout << "exit - Exit program" << std::endl;
            std::cout << "runserv - run server" << std::endl;
            std::cout << "stopserv - stop server" << std::endl;
        }
    }
    return 0;
}

