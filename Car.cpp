#include "Car.h"

string Car::getCarCordsHandler(string param)
{
	string response;
	response = to_string(this->x) + " " + to_string(this->y);
	return response;
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