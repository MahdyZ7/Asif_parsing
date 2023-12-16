#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <set>
#include <vector>
#define WORD "__added_filler_instance_"
#define RESETCLR "\033[0m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"

typedef std::map<std::string, std::vector<std::string> > map_vector_t;

std::string getFillName(std::string line);
void outputLines(std::ofstream &outfile, std::vector<std::string> lines);
void findAndReplaceFill(std::string infile, bool replace);
void replaceFill(std::ifstream &inputfile, std::ofstream &outputfile);

int main(int argc, char **argv) {

	bool replace = false;
	if (argc < 2)
	{
		std::cout << "Enter name of file as argument \eg ./fillparsing filename.def \n";
		return (1);
	}
	if (std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help")
	{
		std::cout << "Usage: ./fillparsing filename.def \n";
		std::cout << " -h : print this help message \n";
		std::cout << " -r : replace files in place \n";
		return (0);
	}
	if (std::string(argv[1]) == "-r" || std::string(argv[1]) == "--replace")
		replace = true;
	for(int i = 1 + replace; i < argc; i++)
		findAndReplaceFill(argv[i], replace);
	
	return 0;
}

void findAndReplaceFill(std::string infile, bool replace)
{
	std::string outfile = std::string("ordered_").append(infile);
	std::ifstream inputfile(infile.c_str());
	if (!inputfile.is_open())
	{
		std::cerr << RED << " Error: Could not open file \"" << infile 
				<< "\"" << RESETCLR<< std::endl;
		return;
	}
	
	std::ofstream outputfile(outfile);
	if (!outputfile.is_open())
	{
		inputfile.close();
		std::cerr << RED << " Error: Could not open file \"" << outfile 
			<< "\"" << RESETCLR<< std::endl;
		return;
	}

	replaceFill(inputfile, outputfile);
	inputfile.close();
	outputfile.close();
	if (replace)
	{
		std::remove(infile.c_str());
		if (rename(outfile.c_str() ,infile.c_str() ) != 0)
		{
			perror("Error renaming file");
			std::cout << RED << " Error: Could not rename file \"" << outfile << "\"" << RESETCLR<< std::endl;
		}
	}
	std::cout << GREEN <<" Done with file \"" << infile << "\" \n" << RESETCLR;
}

void replaceFill(std::ifstream &inputfile, std::ofstream &outputfile)
{
	std::string line;
	map_vector_t fill_lines;
	while (getline(inputfile, line))
	{
		if (line.find("FILL") != std::string::npos)
			(fill_lines[getFillName(line)]).push_back(line);
		else if (line == "END COMPONENTS")
		{
			for (const auto &p : fill_lines)
				outputLines(outputfile, p.second);
			fill_lines.clear();
			outputfile << "END COMPONENTS" << std::endl;
		}
		else
			outputfile << line << std::endl;
	}
}

std::string getFillName(std::string line)
{
	std::stringstream ss(line);
	std::string word;
	while (ss >> word) 
	{
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
		while (ss >> word)
		{
			if (word.find(WORD) != std::string::npos)
				word = word.substr(0, word.rfind('_') + 1) + std::to_string(i++);
			outfile << " " << word;
		}
		outfile << std::endl;
	}
}