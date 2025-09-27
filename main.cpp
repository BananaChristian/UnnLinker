#include <iostream>
#include "parser.hpp"

int main()
{
    std::cout << "This is the UnnLinker\n";
    Parser elfParser;
    elfParser.parseObj("test.o");
    return 0;
}