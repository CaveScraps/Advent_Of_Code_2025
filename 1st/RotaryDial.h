#ifndef ROTARY_DIAL_H
#define ROTARY_DIAL_H

class RotaryDial
{
public:

    RotaryDial();

    int GetTotalTimesPassingZero() const;

    int GetTotalTimesStoppedAtZero() const;

    void MoveDial(int places);

private:
        // Constraints on the size of the dial.
        const int m_minimumNumber;
        const int m_maximumNumber;

        int m_currentNumber; // The current number the dial is on.

        int m_totalTimesPassingZero; // How many times the dial has moved past zero in total.
        int m_totalTimesStoppedAtZero; // How many times a call to MoveDial has ended with the dial resting on zero.
};

#endif
