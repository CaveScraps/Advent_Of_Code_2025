#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <thread>
#include <future>

// The task that gets passed to the thread.
int BankMaxNumberTask(const std::vector<int>& bank)
{
    if (bank.size() < 2)
    {
        std::cerr << "Bank found with less than 2 batteries." << std::endl;
        exit(1);
    }
    else if (bank.size() == 2)
    {
        return bank[0] + bank[1];
    }

    // Loop through the numbers and keep track of the max values and their locations.
    int maxNumber = 0;
    std::vector<int> maxNumberLocations;
    for (int ii = 0; ii < static_cast<int>(bank.size()) - 1; ii++) // Dont want to count the last number as we need to be making a two digit number.
    {
        if (bank[ii] > maxNumber)
        {
            maxNumber = bank[ii];
            maxNumberLocations.clear();
            maxNumberLocations.push_back(ii);
        }
        else if (bank[ii] == maxNumber)
        {
            maxNumberLocations.push_back(ii);
        }
    }

    // If we only have one match then we just use it and the next number.
    if (maxNumberLocations.size() == 1)
    {
        return (10* maxNumber) + bank[maxNumberLocations[0] + 1];
    }

    int maxSecondNumber = 0;
    for(auto maxNumberLocation : maxNumberLocations)
    {
        if (bank[maxNumberLocation + 1] > maxSecondNumber)
        {
            maxSecondNumber = bank[maxNumberLocation + 1];
        }
    }

    return (10* maxNumber) + maxSecondNumber;
}

int main()
{
    const std::string fileName = "input.txt";
    std::ifstream file(fileName);

    if(!file.is_open())
    {
        std::cerr << "Error: Unable to open file: " << fileName << std::endl;
        exit(1);
    }

    std::string line;
    int total = 0;
    while(std::getline(file, line))
    {
        std::vector<int> numbers;
        std::transform(line.begin(), line.end(), std::back_inserter(numbers), [](char c) {return c - '0';});

        int result = BankMaxNumberTask(numbers);
        std::cout << result << std::endl;
        total += result;
    }

    file.close();

    std::cout << "The total of the banks is: " << total << std::endl;
    return 0;
}
