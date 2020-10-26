#include <string>
#include <iostream>
#include <vector>

struct File {
	std::string name;
	std::string color;
	float x;
	float y;
};

namespace fileread {
	std::vector<File*> read(std::string &levelname);
	bool write(std::vector<File*> items,std::string &levelname);
    	bool write(std::vector<File> items,std::string &levelname);
};
