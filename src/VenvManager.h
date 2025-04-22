#ifndef VENV_MANAGER_H
#define VENV_MANAGER_H

#include <string>
#include <vector>

class VenvManager{
	public:
		static bool createVenv(const std::string& version);
		static bool installDependencies(const std::vector<std::string>& dependencies);
		static bool installRequirements(const std::string& requirements_path);
};

#endif
