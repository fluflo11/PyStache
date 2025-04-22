#include <iostream>
#include <string>
#include <vector>
#include "ConfigParser.h"
#include "VenvManager.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: pystch <command>" << std::endl;
        return 1;
    }

    std::string command(argv[1]);
    if (command == "setup") {
        ConfigParser parser("pystache.yaml");
        if (!parser.parse()) {
            std::cerr << "Error: Invalid or missing pystache.yaml file" << std::endl;
            return 1;
        }

        if (!VenvManager::createVenv(parser.getVersion())) {
            return 1;
        }

        if (!parser.getRequirementsPath().empty()) {
            if (!VenvManager::installRequirements(parser.getRequirementsPath())) {
                return 1;
            }
        } else {
            if (!VenvManager::installDependencies(parser.getDependencies())) {
                return 1;
            }
        }

        std::cout << "Project setup completed successfully!" << std::endl;
        return 0;
    } else {
        std::cerr << "Error: Unknown command '" << command << "'" << std::endl;
        return 1;
    }
}