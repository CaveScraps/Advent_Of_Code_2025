#include <iostream>
#include <fstream>
#include <cmath>

class RotaryDial
{
public:
    RotaryDial() : m_minimumNumber(0), m_maximumNumber(99), m_currentNumber(50)
    {}

    int GetCurrentNumber() const
    {
        return m_currentNumber;
    }

    void MoveDial(int places)
    {
        if(places == 0)
        {
            return;
        }

        bool moveInPositiveDirection = places > 0;
        unsigned int numberOfPlacesLeftToMove = abs(places);

        while(numberOfPlacesLeftToMove != 0)
        {
            int newNumber = moveInPositiveDirection ? m_currentNumber + 1 : m_currentNumber - 1;
            if(newNumber > m_maximumNumber)
            {
                m_currentNumber = m_minimumNumber;
            }
            else if(newNumber < m_minimumNumber)
            {
                m_currentNumber = m_maximumNumber;
            }
            else
            {
                m_currentNumber = newNumber;
            }

            numberOfPlacesLeftToMove--;
        }
    }

private:
        const int m_minimumNumber;
        const int m_maximumNumber;
        int m_currentNumber;
};

int main()
{
    const std::string fileName = "input.txt";
    std::ifstream file(fileName);

    if(!file.is_open())
    {
        std::cerr << "Error: Unable to open file: " << fileName << std::endl;
    }

    RotaryDial dial;
    std::string line;
    int zeroCounter = 0;

    while(std::getline(file, line))
    {
        if(line[0] != 'L' && line[0] != 'R')
        {
            std::cerr << "Invalid content in input file: '" << line << "'" << std::endl;
        }

        int placesToMove = std::stoi(line.substr(1));
        int signModifier = line[0] == 'L' ? -1 : 1; // If we are moving left we need to modify the number to have a negative sign.

        std::cout << "Moving dial " << placesToMove * signModifier << std::endl;
        dial.MoveDial(placesToMove * signModifier);
        std::cout << "This leaves the dial at: " << dial.GetCurrentNumber() << std::endl;

        if(dial.GetCurrentNumber() == 0)
        {
            zeroCounter++;
        }
    }

    std::cout << "Dial was at zero: " << zeroCounter << " times." << std::endl;

    return 0;
}
