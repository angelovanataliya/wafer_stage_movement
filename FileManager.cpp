#include <chrono>
#include <iomanip>
#include <sstream>
#include <ctime>

#include "FileManager.h"

// Parametrized Constructor
FileManager::FileManager(const std::string& filename, std::ios::openmode mode) 
{
    fileStream.open(filename, mode);

    if (!fileStream.is_open()) 
    {
        throw std::runtime_error("Unable to open file.");
    }
}

// Destructor
FileManager::~FileManager() 
{
    if (fileStream.is_open()) 
    {
        fileStream.close(); 
    }
}

// Reads a line from a file
bool FileManager::ReadLine(std::string& line) 
{
    return std::getline(fileStream, line) ? true : false;
}

// Writes a line to a file
void FileManager::WriteLine(const std::string& line) 
{
    if (fileStream.is_open()) 
    {
        fileStream << line << std::endl;
    }
    else 
    {
        throw std::runtime_error("File is not open.");
    }
}

// Interprets the lines from the file and adds Move objects to the vector.
std::vector<Movement> MovesParser::ParseMoves(const std::string& filename)
{
    FileManager reader(filename, std::ios::in);
    std::vector<Movement> moves;
    std::string line;

    while (reader.ReadLine(line))
    {
        std::istringstream iss(line);
        double pos, spd;
        if (iss >> pos >> spd)
        {
            moves.emplace_back(pos, spd);
        }
    }
    // FileManager object goes out of scope here, closing the file

    // Return the vector. For C++ 11 and later RVO (Return Value Optimization) or move semantics is applied. 
    return moves;
}

// Parametrized Constructor
Logger::Logger(const std::string& filename)
    : file(filename, std::ios::out | std::ios::app)
{
}

// Logs the current position of the wafer stage along with the date and time that it occurred
void Logger::LogPosition(double currentPosition)
{
    // Get the current time
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);

    // Convert to local time using localtime_s
    std::tm now_tm;
    localtime_r(&now_c, &now_tm);  // Use localtime_s for thread-safe conversion

    // Format the date and time
    std::ostringstream dateTimeStream;
    dateTimeStream << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S");

    // Create the log line
    std::ostringstream logLine;
    logLine << "Time: " << dateTimeStream.str() << ", Position: "
        << std::fixed << std::setprecision(2) << currentPosition;

    // Write the log line to the file
    this->file.WriteLine(logLine.str());
}

// Logs the expected and actual duration of the Move
void Logger::LogDuration(double startPosition, double targetPosition, double expectedDuration, double actualDuration)
{
    std::ostringstream logLine;
    logLine << "Move from " << startPosition << " to " << targetPosition
        << " - Expected Duration: " << expectedDuration << " seconds, "
        << "Actual Duration: " << actualDuration << " seconds\n";

    this->file.WriteLine(logLine.str());
}
