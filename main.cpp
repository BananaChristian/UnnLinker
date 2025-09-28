#include <iostream>
#include "parser.hpp"

int main(int argc, char *argv[])
{
    // Check if a filename argument is provided
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <elf_file>\n";
        std::cerr << "Example: " << argv[0] << " test.o\n";
        return 1; // Return non-zero to indicate error
    }

    std::cout << "This is the UnnLinker\n";
    Parser elfParser;
    elfParser.parseObj(argv[1]); // Use the provided filename
    return 0;
}