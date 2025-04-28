
#include <thread>
#include <chrono>
#include <iostream>

#include "WaferStage.h"
#include "FileManager.h"
#include "defines.h"

using namespace std::literals::chrono_literals;

// Empty Constructor
WaferStage::WaferStage()
	: currentPosition(0.0), logger(LOG_FILENAME)
{
}

// Parametrized Constructor
WaferStage::WaferStage(double currentPosition)
	:currentPosition(currentPosition), logger(LOG_FILENAME)
{
}

void WaferStage::Move(Movement movement, std::atomic<bool>& running)
{
	double startPosition = this->currentPosition;

	// Validate input parameter
	if (movement.targetPosition < 0 || movement.targetPosition > ROW_LENGTH || movement.speed < 0)
	{
		return;
	}

	// Calculate the distance
	double distance = movement.targetPosition - this->currentPosition;

	// Calculate the overall time that we'll need to move the wafer stage from the current position to the desired position
	// t = S / V (uniform motion) = [seconds]
	double time = std::abs(distance) / movement.speed;

	// Total frames for the desired FPS
	int totalFrames = static_cast<int> (time  * FPS);

	// Ensure we have at least one frame
	if (totalFrames < 1) 
	{
		totalFrames = 1; // At least one frame for immediate moves
	}

	// Step size for each frame
	double step = distance / totalFrames; 

	// Calculate the elapsed time for logging purposes
	auto startTime = std::chrono::high_resolution_clock::now();

	// Move until the desired position is reached
	for (int frame = 0; frame < totalFrames; ++frame) 
	{
		// Update position
		this->currentPosition += step;

		// Log the update of the current position
		logger.LogPosition(this->currentPosition);

		std::this_thread::sleep_for(std::chrono::milliseconds(1000 / FPS));
	}

	// Set final position
	this->currentPosition = movement.targetPosition;

	logger.LogPosition(this->currentPosition);

	// Calculate the actual duration taken
	auto endTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> actualDuration = endTime - startTime;

	// Log expected and actual duration to the log file
	logger.LogDuration(startPosition, movement.targetPosition, time, actualDuration.count());
}

void WaferStage::Print(std::atomic<bool>& running) const
{
	while (running) 
	{
		// Map position [0.0, 1.0] to [0, totalLength-1]
		int currentPos = static_cast<int>(this->currentPosition * (ROW_LENGTH - 1)); 

		// Create the line and place '@' at the current position
		std::string line(ROW_LENGTH, ' ');

		line[currentPos] = '@';

		// Output the line, ensuring to stay on the same line using '\r' and no line break
		std::cout << "\r|" << line << "|" << std::flush;

		// Sleep for smooth visualization
		std::this_thread::sleep_for(std::chrono::milliseconds(1000 / FPS));
	}
}
