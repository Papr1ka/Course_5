#include "Car.h"

void Car::printCarCordsHandler(string param)
{
	string command;
	this->emit_signal(SIGNAL_D(Car::printCarCordsSignal), command);
}

void Car::insertNew()
{
	TreeBase* head = this->get_head();
	if (head == nullptr)
	{
		return;
	}
	auto end = head->p_sub_objects.cend();
	bool pasted = false;

	for (auto iter = head->p_sub_objects.cbegin(); iter != end; iter++)
	{
		if ((*iter)->get_name() > this->s_name)
		{
			head->p_sub_objects.insert(iter, this);
			pasted = true;
			break;
		}
	}
	if (not pasted)
	{
		head->p_sub_objects.push_back(this);
	}
}

void Car::printCarCordsSignal(string& param)
{
	param = this->get_name() + " ( " + to_string(this->x) + ", " + to_string(this->y) + " )";
}

Car::Car(int x, int y, TreeBase* p_head_object, string s_name) : TreeBase(p_head_object, s_name, EMPTY_METHOD_D(Car::insertNew))
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
	//Вызвать сигнал onMove с текущими координатами
}

void Car::CallMoveIfFrontIsFreeSignal(string& param)
{
	param = this->get_name() + " " + to_string(this->x) + " " + to_string(this->y);
}

void Car::onMoveSignal(string& param)
{
	param = this->get_name() + " " + param + " " + to_string(this->x) + " " + to_string(this->y);
}