#include <random>
#include <iostream>
#include <fstream>
#include <string>

void generate(int minStrLen, int maxStrLen, int numOfStrings, const std::string& file) {
	std::ofstream ofs(file, std::ios::binary);
	if (!ofs.is_open()) {
		throw std::runtime_error("failed to open file");
	}

    std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> distribLenSize(minStrLen, maxStrLen);
    std::uniform_int_distribution<> distribLetter(0, 25);

    while (numOfStrings--) {
    	int curLen = distribLenSize(gen);
    	std::string s;
    	s.reserve(curLen);
    	for (int i = 0; i < curLen; ++i) {
    		s += char('a' + distribLetter(gen));
    	}
    	s += '\n';
    	ofs << s;
    }
}


int main(int argc, char **argv) {
	if (argc != 5) {
		std::cerr << "Failed. Wrong num of args. Example: ./gen <min_str_len> <max_str_len> <num_of_strings> <file>" << std::endl;
		return 1;
	}

	int minStrLen = 0;
	try {
		minStrLen = std::stoi(argv[1]);		
	} catch (const std::exception& ex) {
		std::cerr << "Failed: wrong minStrLen " << ex.what() << std::endl; 
		return 1;
	}

	int maxStrLen = 0;
	try {
		maxStrLen = std::stoi(argv[2]);		
	} catch (const std::exception& ex) {
		std::cerr << "Failed: wrong maxStrLen " << ex.what() << std::endl; 
		return 1;
	}

	int numOfStrings = 0;
	try {
		numOfStrings = std::stoi(argv[3]);		
	} catch (const std::exception& ex) {
		std::cerr << "Failed: wrong numOfStrings " << ex.what() << std::endl; 
		return 1;
	}

	if (minStrLen <= 0 || maxStrLen <= 0 || minStrLen > maxStrLen || numOfStrings < 0) {
		std::cerr << "Failed: minStrLen and maxStrLen must be > 0, minStrLen <= maxStrLen and numOfStrings >= 0" << std::endl;
		return 1;
	}

	try {
		generate(minStrLen, maxStrLen, numOfStrings, argv[4]);
	} catch (const std::exception& ex) {
		std::cerr << "Failed to generate. " << ex.what() << std::endl;
		return 1;
	}
	return 0;
}