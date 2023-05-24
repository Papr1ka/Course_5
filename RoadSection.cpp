#include "RoadSection.h"

RoadSection::RoadSection(TreeBase* p_head_object, string s_name, int length) : TreeBase(p_head_object, s_name)
{
	this->length = length;

	this->cells.push_back(new Cell(-1, 1, nullptr));
	this->cells.push_back(new Cell(1, 1, nullptr));
	this->cells.push_back(new Cell(1, -1, nullptr));
	this->cells.push_back(new Cell(-1, -1, nullptr));

	for (int i = 2; i < length; i++)
	{
		this->cells.push_back(new Cell(-1, i, nullptr));
		this->cells.push_back(new Cell(-1, -i, nullptr));
		this->cells.push_back(new Cell(1, i, nullptr));
		this->cells.push_back(new Cell(1, -i, nullptr));
		this->cells.push_back(new Cell(i, 1, nullptr));
		this->cells.push_back(new Cell(-i, 1, nullptr));
		this->cells.push_back(new Cell(i, -1, nullptr));
		this->cells.push_back(new Cell(-i, -1, nullptr));
	}
}

RoadSection::~RoadSection()
{
	int size = this->cells.size();
	for (int i = 0; i < size; i++)
	{
		delete this->cells[i];
	}
}

void RoadSection::setLengthHandler(string length)
{
	this->length = stoi(length);
}

void RoadSection::printRoadHandler(string param)
{
	int size = this->p_sub_objects.size();
	string command;

	for (int i = 0; i < size; i++)
	{
		this->emit_signal(
			SIGNAL_D(RoadSection::printCarCordsSignal),
			command,
			this->p_sub_objects[i]
		);
	}
}

void RoadSection::printCarCordsSignal(string& param)
{

}

void RoadSection::doTick(string param)
{
	//вызвать метод move у машин
}

void RoadSection::CallMoveIfFrontIsFreeHandler(string param)
{
	stringstream query;
	query << param;

	string name;
	int x, y;

	query >> name >> x >> y;
}

void RoadSection::setCell(int x, int y, TreeBase* obj)
{
	Cell* cell;
	int size = this->cells.size();
	for (int i = 0; i < size; i++)
	{
		cell = this->cells[i];
		if (cell->x == x && cell->y == y)
		{
			cell->car = obj;
		}
	}
}

void RoadSection::printSignal(string& param)
{
	
}

void RoadSection::onCarMoveHandler(string param)
{
	stringstream query;
	query << param;
	int x_prev, y_prev, x, y;
	string name;
	query >> name >> x_prev >> y_prev >> x >> y;

	TreeBase* car = this->get_sub_object(name);

	if (x > this->length || y > this->length)
	{
		string command;
		command = name + " the car left the road section";
		setCell(x_prev, y_prev, nullptr);
		this->emit_signal(
			SIGNAL_D(RoadSection::printSignal),
			command
		);
		this->deleteSub(param);
	}
	else
	{
		setCell(x_prev, y_prev, nullptr);
		setCell(x, y, car);
	}
}