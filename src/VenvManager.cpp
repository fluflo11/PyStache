#include "VenvManager.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>

bool VenvManager::createVenv(const std::string& version) {
    std::string command = "python" + version + " -m venv venv";
    int result = std::system(command.c_str());
    
    if (result != 0) {
        std::cerr << "Error: Failed to create virtual environment with Python " 
                  << version << std::endl;
        return false;
    }
    
    return true;
}

bool VenvManager::installDependencies(const std::vector<std::string>& dependencies) {
    if (dependencies.empty()) return true;
    
    // Ayae caramba windows 
#ifdef _WIN32
    std::string activate_cmd = "venv\\Scripts\\activate && pip install ";
#else
    std::string activate_cmd = "source venv/bin/activate && pip install ";
#endif

    std::string install_cmd = activate_cmd;
    for (const auto& dep : dependencies) {
        install_cmd += dep + " ";
    }
    
    int result = std::system(install_cmd.c_str());
    if (result != 0) {
        std::cerr << "Error: Failed to install dependencies" << std::endl;
        return false;
    }
    
    return true;
}

bool VenvManager::installRequirements(const std::string& requirements_path) {
    if (requirements_path.empty()) return true;
    
#ifdef _WIN32
    std::string command = "venv\\Scripts\\activate && pip install -r " + requirements_path;
#else
    std::string command = "source venv/bin/activate && pip install -r " + requirements_path;
#endif
    
    int result = std::system(command.c_str());
    if (result != 0) {
        std::cerr << "Error: Failed to install from requirements file" << std::endl;
        return false;
    }
    
    return true;
}