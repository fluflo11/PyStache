#include "ConfigParser.h"
#include <fstream>
#include <sstream>
#include <iostream>

ConfigParser::ConfigParser(const std::string& path) 
    : filepath(path), is_valid(false) {}

//TODO : Utiliser une vraie lib yaml mdr.
bool ConfigParser::parse() {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filepath << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.find("python_version:") != std::string::npos) {
            size_t pos = line.find(":");
            version = line.substr(pos + 1);
            // Nettoyer les guillemets et espaces
            version.erase(0, version.find_first_not_of(" \"'"));
            version.erase(version.find_last_not_of(" \"'") + 1);
        }
        else if (line.find("dependencies:") != std::string::npos) {
            while (std::getline(file, line)) {
                if (line.empty() || line[0] == ' ') {
                    if (line.find("- ") != std::string::npos) {
                        size_t pos = line.find("- ");
                        std::string dep = line.substr(pos + 2);
                        dep.erase(0, dep.find_first_not_of(" \"'"));
                        dep.erase(dep.find_last_not_of(" \"'") + 1);
                        if (!dep.empty()) {
                            dependencies.push_back(dep);
                        }
                    }
                    else if (line.find("requirements:") != std::string::npos) {
                        size_t pos = line.find(":");
                        requirements_path = line.substr(pos + 1);
                        requirements_path.erase(0, requirements_path.find_first_not_of(" \"'"));
                        requirements_path.erase(requirements_path.find_last_not_of(" \"'") + 1);
                    }
                }
                else {
                    break;
                }
            }
        }
    }

    is_valid = !version.empty() && 
              (!dependencies.empty() || !requirements_path.empty());
    return is_valid;
}

std::string ConfigParser::getVersion() const {
    return version;
}

std::vector<std::string> ConfigParser::getDependencies() const {
    return dependencies;
}

std::string ConfigParser::getRequirementsPath() const {
    return requirements_path;
}

bool ConfigParser::isValid() const {
    return is_valid;
}