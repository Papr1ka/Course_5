#ifndef CELL_H
#define CELL_H

#include "TreeBase.h"

struct Cell
{
	int x;
	int y;
	TreeBase* car;
	Cell(int x, int y, TreeBase* car);
	bool isEmpty();
	void setCar(TreeBase* car);
};

#endif // !CELL_H
