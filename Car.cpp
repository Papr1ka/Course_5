#include "Car.h"

string Car::printCarCordsHandler(string param)
{
	string response;
	string command;
	this->emit_signal(SIGNAL_D(Car::printCarCordsSignal), command);
	return response;
}

void Car::printCarCordsSignal(string& param)
{
	param = this->get_name() + " ( " + to_string(this->x) + ", " + to_string(this->y) + " )";
}

Car::Car(int x, int y, TreeBase* p_head_object, string s_name) : TreeBase(p_head_object, s_name)
{
	this->x = x;
	this->y = y;
	if (y <= 0)
	{
		if (y <= -1.5)
		{
			if (x <= 0)
			{
				this->setState(Directions::Bottom);
			}
			else
			{
				this->setState(Directions::Top);
			}
		}
		else
		{
			this->setState(Directions::Right);
		}
	}
	else
	{
		if (y <= 1.5)
		{
			this->setState(Directions::Left);
		}
		else
		{
			if (x <= 0)
			{
				this->setState(Directions::Bottom);
			}
			else
			{
				this->setState(Directions::Top);
			}
		}
	}
}

void Car::move()
{
}