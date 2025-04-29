#include <thread>

#include "WaferStage.h"
#include "FileManager.h"
#include "defines.h"


int main(int argc, char *argv[])
{
	WaferStage stage(0.0);
	MovesParser movesParser;
	std::vector<Movement> moves;

	if (argc != 2)
	{
		std::cout << "Argument 'moves-file' not supplied!\n";
		return 1;
	}

	const std::string filename = argv[1];
	// Read the different moves from the file
	moves = movesParser.ParseMoves(filename);

	// Check if the file with Moves was read properly
	if (moves.empty()) 
	{
		// Return an error
		std::cerr << "No valid moves found in the file. Press Enter to exit..." << std::endl;

		std::cin.get();
		return 0;
	}

	// Loop the moves from the file and don't continue to the next iteration until the current position matches the target position from the file.
	// In this loop we call the Move function and we print according to the desired FPS until we reach the desired position.
	for (auto& movement : moves) 
	{
		// Flag to control the visualization loop
		std::atomic<bool> isMoving(true); 

		// Start visualization in a separate thread
		std::thread printingThread(&WaferStage::Print, &stage, std::ref(isMoving));

		// Start the moving process
		stage.Move(movement, isMoving);

		isMoving = false; 

		// Wait for the visualization thread to finish
		printingThread.join(); 
	}

	std::cout << std::endl << "Moves are over. Press Enter to exit..." << std::endl;
	std::cin.get();
	return 0;
}

