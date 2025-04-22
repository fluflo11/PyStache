#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#include <string>
#include <vector>
#include <map>

class ConfigParser{
	public:
		ConfigParser(const std::string& path);
		bool parse();
		std::string getVersion() const;
		std::vector<std::string> getDependencies() const;
		std::string getRequirementsPath() const;
		bool isValid() const;

	private:
		std::string filepath;
		std::string version;
		std::vector<std::string> dependencies;
		std::string requirements_path;
		bool is_valid;
};

#endif 
