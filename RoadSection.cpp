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
			break;
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

void RoadSection::emitCarFrontStateAndColorSignal(string& param)
{
	param = to_string(this->currentColor);
}

void RoadSection::getColorSignal(string& param) {}

void RoadSection::printSignal(string& param) {}

void RoadSection::setLengthHandler(string param)
{
	this->length = stoi(param);
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
	//������� ����� move � �����
	string command, command2;
	this->emit_signal(
		SIGNAL_D(RoadSection::getColorSignal),
		command
	);

	for (int i = this->length; i > -this->length; i--)
	{
		if (i == 0 || i == -1)
		{
			continue;
		}
		Cell a = *this->getCell(i, -1);
		Cell b = *this->getCell(-i, 1);
		Cell c = *this->getCell(-1, -i);
		Cell d = *this->getCell(1, i);
		if (!a.isEmpty())
		{
			this->emit_signal(
				SIGNAL_D(RoadSection::doTactSignal),
				command2,
				a.car
			);
		}

		if (!b.isEmpty())
		{
			this->emit_signal(
				SIGNAL_D(RoadSection::doTactSignal),
				command2,
				b.car
			);
		}

		if (!c.isEmpty())
		{
			this->emit_signal(
				SIGNAL_D(RoadSection::doTactSignal),
				command2,
				c.car
			);
		}

		if (!d.isEmpty())
		{
			this->emit_signal(
				SIGNAL_D(RoadSection::doTactSignal),
				command2,
				d.car
			);
		}
	}
}

void RoadSection::emitColorHandler(string param)
{
	this->currentColor = stoi(param);
}

void RoadSection::callMoveIfFrontIsFreeHandler(string param)
{
	stringstream query;
	string name, command;
	int x, y;
	query << param;
	query >> name >> x >> y;

	Cell* cell = this->getCell(x, y);

	if (cell == nullptr || cell->isEmpty())
	{
		this->emit_signal(
			SIGNAL_D(RoadSection::emitCarFrontStateAndColorSignal),
			command,
			this->get_sub_object(name)
		);
	}
}

void RoadSection::onCarMoveHandler(string param)
{
	stringstream query;
	string name;
	int x_prev, y_prev, x, y;
	query << param;
	query >> name >> x_prev >> y_prev >> x >> y;
	setCell(x_prev, y_prev, nullptr);

	if (abs(x) > this->length || abs(y) > this->length)
	{
		this->deleteSub(name);
	}
	else
	{
		setCell(x, y, this->get_sub_object(name));
	}
}
