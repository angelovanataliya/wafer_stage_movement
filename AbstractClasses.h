#pragma once

#include <atomic>

struct Movement
{
    double targetPosition;
    double speed;

    Movement(double targetPosition, double speed)
        : targetPosition(targetPosition), speed(speed)
    {
    }
};

class Moveable
{
public:
	virtual void Move(Movement movement, std::atomic<bool>& running) = 0;
};

class Printable
{
public:
	virtual void Print(std::atomic<bool>& running) const = 0;
};
