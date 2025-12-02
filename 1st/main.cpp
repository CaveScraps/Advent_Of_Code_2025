#include <iostream>
#include <fstream>
#include <cmath>

class RotaryDial
{
public:
    RotaryDial() : m_minimumNumber(0), m_maximumNumber(99), m_currentNumber(50), m_totalTimesPassingZero(0), m_totalTimesStoppedAtZero(0)
    {}

    int GetTotalTimesPassingZero() const
    {
        return m_totalTimesPassingZero;
    }

    int GetTotalTimesStoppedAtZero() const
    {
        return m_totalTimesStoppedAtZero;
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

            if(m_currentNumber == 0)
            {
                m_totalTimesPassingZero++;
            }
        }

        if(m_currentNumber == 0)
        {
            m_totalTimesStoppedAtZero++;
        }
    }

private:
        // Constraints on the size of the dial.
        const int m_minimumNumber;
        const int m_maximumNumber;

        int m_currentNumber; // The current number the dial is on.

        int m_totalTimesPassingZero; // How many times the dial has moved past zero in total.
        int m_totalTimesStoppedAtZero; // How many times a call to MoveDial has ended with the dial resting on zero.
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

    while(std::getline(file, line))
    {
        if(line[0] != 'L' && line[0] != 'R')
        {
            std::cerr << "Invalid content in input file: '" << line << "'" << std::endl;
        }

        int placesToMove = std::stoi(line.substr(1));
        int signModifier = line[0] == 'L' ? -1 : 1; // If we are moving left we need to modify the number to have a negative sign.

        dial.MoveDial(placesToMove * signModifier);
    }

    std::cout << "Dial ended rotation at zero: " << dial.GetTotalTimesStoppedAtZero() << " times." << std::endl;
    std::cout << "Dial passed zero a total of: " << dial.GetTotalTimesPassingZero() << " times." << std::endl;

    return 0;
}
