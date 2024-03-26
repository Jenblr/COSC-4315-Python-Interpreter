#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char* argv[]) {
    // Parse command line arguments
    if (argc != 2) { 
        std::cerr << "Usage: " << argv[0] << "<file.py>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << argv[1] << std::endl;
        return 1;
    }

    std::ostringstream oss;
    oss << file.rdbuf();
    std::string fileContents = oss.str();
}