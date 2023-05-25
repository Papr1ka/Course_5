#include "RoadSection.h"

RoadSection::RoadSection(TreeBase* p_head_object, string s_name, int length) : TreeBase(p_head_object, s_name)
{
	this->length = length;

	this->cells.push_back(new Cell(-1, 1, nullptr));
	this->cells.push_back(new Cell(1, 1, nullptr));
	this->cells.push_back(new Cell(1, -1, nullptr));
	this->cells.push_back(new Cell(-1, -1, nullptr));

	int length_plus = length + 1;

	for (int i = 2; i < length_plus; i++)
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

Cell* RoadSection::getCell(int x, int y)
{
	Cell* cell;
	int size = this->cells.size();
	for (int i = 0; i < size; i++)
	{
		cell = this->cells[i];
		if (cell->x == x && cell->y == y)
		{
			return cell;
		}
	}
	return nullptr;
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

Car* RoadSection::createCarFactory(int x, int y, string name, TreeBase* object)
{
	RoadSection* obj = static_cast<RoadSection*> (object->searchRoot("RoadSection"));

	if (obj != nullptr)
	{
		Car* car = new Car(x, y, obj, name);
		obj->setCell(x, y, car);
		return car;
	}
	return nullptr;
}

void RoadSection::printCarCordsSignal(string& param) {}

void RoadSection::doTactSignal(string& param) {}

void RoadSection::emitCarFontStateAndColorSignal(string& param)
{
	param = to_string(this->currentColor);
}

void RoadSection::getColorSignal(string& param) {}

void RoadSection::printSignal(string& param) {}

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

void RoadSection::doTactHandler(string param)
{
	//вызвать метод move у машин
	string command;
	this->emit_signal(
		SIGNAL_D(RoadSection::getColorSignal),
		command
	);
	string command2;
	this->emit_signal(
		SIGNAL_D(RoadSection::doTactSignal),
		command2
	);
}

void RoadSection::emitColorHandler(string param)
{
	this->currentColor = stoi(param);
}

void RoadSection::CallMoveIfFrontIsFreeHandler(string param)
{
	stringstream query;
	query << param;

	string name;
	int x, y;

	query >> name >> x >> y;
	Cell* cell = this->getCell(x, y);
	string command;

	if (cell == nullptr || cell->isEmpty())
	{
		this->emit_signal(
			SIGNAL_D(RoadSection::emitCarFontStateAndColorSignal),
			command,
			this->get_sub_object(name)
		);
	}
}

void RoadSection::onCarMoveHandler(string param)
{
	stringstream query;
	query << param;
	int x_prev, y_prev, x, y;
	string name;
	query >> name >> x_prev >> y_prev >> x >> y;

	TreeBase* car = this->get_sub_object(name);

	if (abs(x) > this->length || abs(y) > this->length)
	{
		string command;
		setCell(x_prev, y_prev, nullptr);
		this->deleteSub(name);
	}
	else
	{
		setCell(x_prev, y_prev, nullptr);
		setCell(x, y, car);
	}
}
