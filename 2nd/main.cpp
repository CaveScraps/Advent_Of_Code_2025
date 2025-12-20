#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <thread>
#include <future>

bool IsLineInvalidForPart1(const std::string& line)
{
    if(line.size() % 2 != 0)
    {
        return false; // Odd length lines cannot be made up of two identical halves.
    }
    // Regex matches from line start (^) any sequence of one or more digits (\d+) that is immediately repeated (\1) exactally once with no characters in between.
    const std::regex InvalidIdSequence("^(\\d+)\\1$",  std::regex_constants::ECMAScript);
    if(std::regex_search(line, InvalidIdSequence))
    {
        return true;
    }
    return false;
}

bool IsLineInvalidForPart2(const std::string& line)
{
    // Regex matches from line start (^) any sequence of one or more digits (\d+) that is immediately repeated (\1) once or more (+) with no characters in between.
    const std::regex InvalidIdSequence("^(\\d+)\\1+$",  std::regex_constants::ECMAScript);
    if(std::regex_search(line, InvalidIdSequence))
    {
        return true;
    }
    return false;
}

// The task that gets passed to the thread.
std::pair<size_t,size_t> RangeValidationTask(const std::string& startRange, const std::string& endRange)
{
    size_t invalidIdSumPart1 = 0;
    size_t invalidIdSumPart2 = 0;
    for(size_t id = std::stoull(startRange); id <= std::stoull(endRange); id++)
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
    return std::pair<size_t, size_t>(invalidIdSumPart1, invalidIdSumPart2);
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

    std::string line{};
    std::getline(file, line);

    std::vector<std::future<std::pair<size_t, size_t>>> workers{};
    std::stringstream lineStream(line);
    while(lineStream.good())
    {
        std::string idRangeString{};
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
        workers.push_back(std::async(RangeValidationTask, startId, endId));
    }

    std::cout << "Threads launched, waiting for results..." << std::endl;

    size_t invalidIdSumPart1 = 0;
    size_t invalidIdSumPart2 = 0;
    for(auto& workingThread : workers)
    {
        auto resultPair = workingThread.get();
        invalidIdSumPart1 += resultPair.first;
        invalidIdSumPart2 += resultPair.second;
    }

    std::cout << "The total of the invalid IDs is for part 1 is: " << invalidIdSumPart1 << std::endl;
    std::cout << "The total of the invalid IDs is for part 2 is: " << invalidIdSumPart2 << std::endl;
    return 0;
}
