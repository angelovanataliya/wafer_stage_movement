#pragma once

#include "AbstractClasses.h"
#include "FileManager.h"

/// <summary>
/// Class that is used to wrap the logic of a wafer stage.
/// It has two methods, inherited from the Moveable and Printable abstract classes.
/// </summary>
class WaferStage : public Moveable, public Printable
{
private:
	double currentPosition;
	Logger logger;

public:
/////////////////////////////////////
// Contructors

	// Empty Constructor
	WaferStage();

	// Parametrized Constructor
	WaferStage(double const currentPosition);

/////////////////////////////////////
// Virtual Functions

	// In this method the current position will be updated to reach the target position with a specific speed.
	// There will be logging to a file each time the currentPosition is updated.
	// The visualization thread will get the current position and display the wafer stage on the console.
	void Move(Movement movement, std::atomic<bool>& running);

	// In this method the wafer stage will be displayed to the console until it reaches its target position.
	// It runs simultaneously with the method which updates the current position of the wafer stage according to its acceleration.
	void Print(std::atomic<bool>& running) const;

};
