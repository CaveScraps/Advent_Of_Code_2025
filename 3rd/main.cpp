#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

/**
 * Given a vector of single digit integers, find the maximum two digit number
 * that can be formed by taking any two digits in the order they appear in the vector.
 */
int MaxDoubleDigitNumberGivenLine(const std::vector<int>& bank)
{
    if (bank.size() < 2)
    {
        std::cerr << "Bank found with less than 2 batteries." << std::endl;
        exit(1);
    }

    const auto maxNumberLocation = std::max_element(bank.begin(), bank.end());
    if (maxNumberLocation == bank.end() - 1) // If the max number is at the end
    {
        // Search back from this point for the next largest.
        const auto secondMaxNumberLocation = std::max_element(bank.begin(), maxNumberLocation);
        // Use this number as the second number and use the next largest as the first;
        return (10* *secondMaxNumberLocation) + (*maxNumberLocation);
    }
    else
    {
        // Search onwards from this point for the next largest
        const auto secondMaxNumberLocation = std::max_element(maxNumberLocation + 1, bank.end());
        return (10* *maxNumberLocation) + (*secondMaxNumberLocation);
    }
}

int main()
{
    const std::string FileName = "input.txt";
    std::ifstream file(FileName);
    if(!file.is_open())
    {
        std::cerr << "Error: Unable to open file: " << FileName << "\n";
        exit(1);
    }

    std::string line;
    int total = 0;
    while(std::getline(file, line))
    {
        // Convert the chars into ints
        std::vector<int> numbers;
        std::transform(line.begin(), line.end(), std::back_inserter(numbers), [](char c) {return c - '0';});

        // Accumulate the result
        const int result = MaxDoubleDigitNumberGivenLine(numbers);
        total += result;
    }

    std::cout << "The total of the banks is: " << total << std::endl;
    return 0;
}
