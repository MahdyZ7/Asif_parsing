#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#define WORD "__added_filler_instance_"

typedef std::map<std::string, std::vector<std::string> > map_vector_t;

std::string getFillName(std::string line);
void outputLines(std::ofstream &outfile, std::vector<std::string> lines);

int main(int argc, char **argv) {

	// check for correct no of args
	if (argc != 2)
	{
		std::cout << "Enter name of file as argument eg ./ioparsing filename.def \n";
		return (1);
	}
    std::ifstream inputFile(argv[1]);
    std::ofstream outputFile("sorted_output.txt");
    
    if (!inputFile.is_open() || !outputFile.is_open()) {
        std::cerr << "Could not open files!" << std::endl;
        return 1;
    }
    
    std::string line;
	map_vector_t linesWithNumbers;
    int lineNumber = 0;
    
    while (getline(inputFile, line)) {
        std::stringstream ss;
        ss << lineNumber << " " << line;
		if (line.find("FILL") != std::string::npos)
        	(linesWithNumbers[getFillName(line)]).push_back(line);
			// outputFile << line << '\n';
        ++lineNumber;
    }
    
    for (const auto &p : linesWithNumbers)
		outputLines(outputFile, p.second);
    
    inputFile.close();
    outputFile.close();
	std::remove("original.txt");
   	std::rename("temp.txt", "original.txt");
    
    return 0;
}

std::string getFillName(std::string line)
{
	std::stringstream ss(line);
	std::string word;
	while (ss >> word) {		
		if (word.find("FILL") != std::string::npos)
			return word;
	}
	return "";
}

void outputLines(std::ofstream &outfile, std::vector<std::string> lines)
{
	unsigned int i = 0;
	for (const auto &line : lines)
	{
		std::stringstream ss(line);
		std::string word;
		while (ss >> word) {		
			if (word.find(WORD) != std::string::npos)
				word = word.substr(0, word.rfind('_') + 1) + std::to_string(i++);
			outfile << word << " ";
		}
		outfile << std::endl;
	}
}