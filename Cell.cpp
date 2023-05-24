#include "Cell.h"

Cell::Cell(int x, int y, TreeBase* car)
{
	this->x = x;
	this->y = y;
	this->car = car;
}

bool Cell::isEmpty()
{
	return this->car == nullptr;
}
