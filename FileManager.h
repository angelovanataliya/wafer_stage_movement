#pragma once

#include <fstream>
#include <string>
#include <stdexcept>
#include <vector>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <iostream>

#include "AbstractClasses.h"

/// <summary>
/// Class that handles file reading and writing by following the RAII principles
/// </summary>
class FileManager 
{
private:
    std::fstream fileStream;

public:

/////////////////////////////////////
// Contructors & Destructor

    // Parametrized Constructor
    FileManager(const std::string& filename, std::ios::openmode mode);

    // Destructor
    ~FileManager();

/////////////////////////////////////
// Readers & Writers

    // Reads line from a file
    bool ReadLine(std::string& line);

    // Write a line to the file
    void WriteLine(const std::string& line);
    
};

/// <summary>
/// This class parses the lines from the input file and adds Move objects to the vector.
/// </summary>
class MovesParser 
{
public:
    std::vector<Movement> ParseMoves(const std::string& filename);
};

/// <summary>
/// This class logs when there's an update in the current position of the wafer stage.
/// It also logs the expected and actual time for the execution of a Move.
/// </summary>
class Logger
{
private: 
    FileManager file;

public:

/////////////////////////////////////
// Contructors 

    // Parametrized Constructor
    Logger(const std::string& filename);

/////////////////////////////////////
// Logging Functions
    
    // Logs the current position of the wafer stage alon with the date and time that it occurred
    void LogPosition(double currentPosition);

    // Logs the expected and actual duration of the Move
    void LogDuration(double startPosition, double targetPosition, double expectedDuration, double actualDuration);

};