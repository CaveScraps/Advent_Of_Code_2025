#include "RotaryDial.h"
#include <cmath>

RotaryDial::RotaryDial() : m_minimumNumber(0), m_maximumNumber(99), m_currentNumber(50), m_totalTimesPassingZero(0), m_totalTimesStoppedAtZero(0)
{}

int RotaryDial::GetTotalTimesPassingZero() const
{
    return m_totalTimesPassingZero;
}

int RotaryDial::GetTotalTimesStoppedAtZero() const
{
    return m_totalTimesStoppedAtZero;
}

void RotaryDial::MoveDial(int places)
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
