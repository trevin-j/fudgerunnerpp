#ifndef ARG_PARSER_HPP
#define ARG_PARSER_HPP

#include <string>
#include <vector>
#include <algorithm>

// Simple class for parsing input arguments.
class ArgParser {

public:
	ArgParser(int& argc, char** argv) : emptyString{ "" } {
		for (int i = 1; i < argc; i++)
			this->tokens.push_back(std::string(argv[i]));
	}


	// Get the value of the specified command line argument.
	// Returns the value paired with the specified option.
	const std::string& getCmdOption(const std::string& option) const {

		std::vector<std::string>::const_iterator itr;
		itr = std::find(this->tokens.begin(), this->tokens.end(), option);

		if (itr != this->tokens.end() && ++itr != this->tokens.end()) {
			return *itr;
		}

		return emptyString;
	}


	// Check if an option exists.
	// Returns true if the option exists.
	bool cmdOptionExists(const std::string& option) const {
		return std::find(this->tokens.begin(), this->tokens.end(), option) != this->tokens.end();
	}


private:
	std::vector <std::string> tokens;
	const std::string emptyString;
};

#endif