#pragma once

#define ROW_LENGTH		80			// The length of the row in the console in which the wafer stage will be moving
#define FPS				24			// Frames Per Second
#define FRAME_DURATION	1000 / FPS	// The duration of each frame according to the FPS

#define LOG_FILENAME	"log.txt"	// The name of the file which will be used to log each update of the current position of the wafer stage