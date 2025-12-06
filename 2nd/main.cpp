#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

bool IsLineInvalidForPart1(const std::string& line)
{
    const std::regex InvalidIdSequence("^(\\d+)\\1$",  std::regex_constants::ECMAScript);
    if(std::regex_search(line, InvalidIdSequence))
    {
        return true;
    }
    return false;
}

bool IsLineInvalidForPart2(const std::string& line)
{
    const std::regex InvalidIdSequence("^(\\d+)\\1+$",  std::regex_constants::ECMAScript);
    if(std::regex_search(line, InvalidIdSequence))
    {
        return true;
    }
    return false;
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
    std::getline(file, line);
    file.close(); // Only one line expected.

    unsigned long invalidIdSumPart1 = 0;
    unsigned long invalidIdSumPart2 = 0;
    std::stringstream lineStream(line);
    while(lineStream.good())
    {
        std::string idRangeString;
        if(!getline(lineStream, idRangeString, ','))
        {
            std::cerr << "Input string is not in expected format." << std::endl;
            exit(1);
        }

        const size_t dashPosition = idRangeString.find("-");
        if(dashPosition == std::string::npos)
        {
            std::cerr << "ID range segment not as expected: '" << idRangeString << "'" << std::endl;
            exit(1);
        }

        // Probably should validate that startId and endId make sense before starting the loop, especially considering we dont print progress.
        // Has it frozen? Is it just taking a while? Who knows.
        const std::string startId = idRangeString.substr(0, dashPosition);
        const std::string endId = idRangeString.substr(dashPosition + 1, idRangeString.size());
        for(unsigned long id = std::stoul(startId); id <= std::stoul(endId); id++)
        {
            const std::string currentId = std::to_string(id);
            if(IsLineInvalidForPart1(currentId))
            {
                invalidIdSumPart1 += id;
            }
            if(IsLineInvalidForPart2(currentId))
            {
                invalidIdSumPart2 += id;
            }
        }
    }

    std::cout << "The total of the invalid IDs is for part 1 is: " << invalidIdSumPart1 << std::endl;
    std::cout << "The total of the invalid IDs is for part 2 is: " << invalidIdSumPart2 << std::endl;
    return 0;
}
