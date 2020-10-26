#include "file.h"
#include <fstream>
#include <sstream>


std::vector<File*> fileread::read(std::string &levelname) {
	bool correct = false;
    std::ifstream file;
    file.open ("../levels/" +levelname+".txt");
    std::vector<File*> items;
    std::string word;
    
    while (file >> word)
    {
        if(word == "pig" && correct) {
            File *pig = new File();
            pig->name= word;
            file >> word;
            pig->color = word;
            file >> word;
            pig->x = std::stof(word);
            file >> word;
            pig->y = std::stof(word);
            items.push_back(pig);
        }
        else if(word == "block" && correct) {
            File *block = new File();
            block->name= word;
            file >> word;
            block->color = word;
            file >> word;
            float fx = std::stof(word);
            block->x =fx;
            file >> word;
            block->y = std::stof(word);
            items.push_back(block);
        }
        else if(word == "bird" && correct){
            File *bird = new File();
            bird->name= word;
            file >> word;
            bird->color = word;
            file >> word;
            float fx = std::stof(word);
            bird->x =fx;
            file >> word;
            bird->y = std::stof(word);
            items.push_back(bird);
	}
	else if(word == "highscore" && correct) {
		File *hs = new File();
		hs->name = word;
		file >> word;
		hs->color = word;
		file >> word;
		hs->x = std::stof(word);
		file >> word;
		hs->y = 0.0;
		items.push_back(hs);
	}
        else {
            if(levelname ==word) {
                correct = true;
            }
            else{
                correct = false;
            }
        }
    }
    file.close();
    
    return items;

}

bool fileread::write(std::vector<File*> items, std::string &levelname) {

    std::ifstream File;
    std::string filepath = "../levels/"+levelname+".txt";
    File.open(filepath.c_str(), std::ifstream::out | std::ifstream::trunc );
    if (!File.is_open() || File.fail())
    {
       File.close();
       printf("\nError : failed to erase file content !");
    }
    File.close();

    std::ofstream myfile("../levels/"+levelname+".txt");
        if(myfile.is_open()) {
        myfile << levelname<<'\n';
                for(auto i : items) {
            myfile << i->name << " " << i->color <<" "<< i->x <<" "<< i->y << '\n';
                delete i;
		}
                myfile.close();
                return true;
        }
        else {
                return false;
    }

}

bool fileread::write(std::vector<File> items, std::string &levelname) {

    std::ifstream File;
    std::string filepath = "../levels/"+levelname+".txt";
    File.open(filepath.c_str(), std::ifstream::out | std::ifstream::trunc );
    if (!File.is_open() || File.fail())
    {
       File.close();
       printf("\nError : failed to erase file content !");
    }
    File.close();

    std::ofstream myfile("../levels/"+levelname+".txt");
	if(myfile.is_open()) {
        myfile << levelname<<'\n';
		for(auto i : items) {
            myfile << i.name << " " << i.color <<" "<< i.x <<" "<< i.y << '\n';
		}
		myfile.close();
		return true;
	}
	else {
		return false;
    }

}
