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

void Car::moveHandler(string param)
{
	string command = to_string(this->x) + " " + to_string(this->y);
	TrafficLight::Colors color = (TrafficLight::Colors) stoi(param);
	//Вызвать сигнал onMove с текущими координатами
	Directions direction = (Directions)this->getState();
	
	bool willMove = false;

	switch (color)
	{
	case TrafficLight::Green:
		if (this->state == Directions::Right || this->state == Directions::Left)
		{
			willMove = true;
		}
	case TrafficLight::Yellow:
		
		if (abs(this->x) <= 1 && abs(this->y) <= 1)
		{
			willMove = true;
		}

	case TrafficLight::Red:
		if (this->state == Directions::Top || this->state == Directions::Bottom)
		{
			willMove = true;
		}
		break;
	case TrafficLight::Yellow2:
		if (abs(this->x) <= 1 && abs(this->y) <= 1)
		{
			willMove = true;
		}
		break;
	}

	if (!willMove)
	{
		return;
	}

	switch (direction)
	{
	case Car::Top:
		this->y = y + 1;
		break;
	case Car::Right:
		this->x = x + 1;
		break;
	case Car::Left:
		this->x = x - 1;
		break;
	case Car::Bottom:
		this->y = y - 1;
		break;
	};
	this->emit_signal(
		SIGNAL_D(Car::onMoveSignal),
		command
	);
}

void Car::CallMoveIfFrontIsFreeSignal(string& param)
{
	Directions direction = (Directions) this->getState();
	int new_x;
	int new_y;
	switch (direction)
	{
	case Car::Top:
		new_x = x;
		new_y = y + 1;
		break;
	case Car::Right:
		new_x = x + 1;
		new_y = y;
		break;
	case Car::Left:
		new_x = x - 1;
		new_y = y;
		break;
	case Car::Bottom:
		new_x = x;
		new_y = y - 1;
		break;
	}
	param = this->get_name() + " " + to_string(new_x) + " " + to_string(new_y);
}

void Car::onMoveSignal(string& param)
{
	param = this->get_name() + " " + param + " " + to_string(this->x) + " " + to_string(this->y);
}

void Car::doTactHandler(string param)
{
	string command;
	this->emit_signal(
		SIGNAL_D(Car::CallMoveIfFrontIsFreeSignal),
		command
	);
}