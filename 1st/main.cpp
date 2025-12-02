#include <iostream>
#include <fstream>
#include "RotaryDial.h"

int main()
{
    const std::string fileName = "input.txt";
    std::ifstream file(fileName);

    if(!file.is_open())
    {
        std::cerr << "Error: Unable to open file: " << fileName << std::endl;
        exit(1);
    }

    RotaryDial dial;
    std::string line;

    while(std::getline(file, line))
    {
        if(line[0] != 'L' && line[0] != 'R')
        {
            std::cerr << "Invalid content in input file: '" << line << "'" << std::endl;
            exit(1);
        }

        int placesToMove = std::stoi(line.substr(1));
        int signModifier = line[0] == 'L' ? -1 : 1; // If we are moving left we need to modify the number to have a negative sign.

        dial.MoveDial(placesToMove * signModifier);
    }

    std::cout << "Dial ended rotation at zero: " << dial.GetTotalTimesStoppedAtZero() << " times." << std::endl;
    std::cout << "Dial passed zero a total of: " << dial.GetTotalTimesPassingZero() << " times." << std::endl;

    return 0;
}
