#include "Car.h"

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

void Car::callMoveIfFrontIsFreeSignal(string& param)
{
	Directions direction = (Directions)this->getState();
	int new_x, new_y;
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

void Car::printCarCordsHandler(string param)
{
	string command;
	this->emit_signal(SIGNAL_D(Car::printCarCordsSignal), command);
}

void Car::moveHandler(string param)
{
	string command = to_string(this->x) + " " + to_string(this->y);
	TrafficLight::Colors color = (TrafficLight::Colors) stoi(param);
	//Вызвать сигнал onMove с текущими координатами
	Directions direction = (Directions)this->getState();
	
	bool willMove = false;
	if (abs(x) > 2 || abs(y) > 2)
	{
		willMove = true;
	}
	else
	{
		switch (color)
		{
		case TrafficLight::Green:
			if (
				((direction == Directions::Right) && (x == -2 && y == -1)) ||
				((direction == Directions::Left) && (x == 2 && y == 1))
			)
			{
				willMove = true;
			}
			break;
		case TrafficLight::Yellow:
			break;
		case TrafficLight::Red:
			if (
				((direction == Directions::Top) && (x == 1 && y == -2)) ||
				((direction == Directions::Bottom) && (x == -1 && y == 2))
			)
			{
				willMove = true;
			}
			break;
		case TrafficLight::Yellow2:
			break;
		}
	}

	if (
		(x == -2 && y == 1) ||
		(x == 1 && y == 2) ||
		(x == 2 && y == -1) ||
		(x == -1 && y == -2) ||
		(abs(x) <= 1 && abs(y) <= 1)
	)
	{
		willMove = true;
	}

	if (!willMove)
	{
		return;
	}

	switch (direction)
	{
	case Car::Top:
		this->y = y + 1;
		if (this->y == 0)
		{
			y++;
		}
		break;
	case Car::Right:
		this->x = x + 1;
		if (this->x == 0)
		{
			x++;
		}
		break;
	case Car::Left:
		this->x = x - 1;
		if (this->x == 0)
		{
			x--;
		}
		break;
	case Car::Bottom:
		this->y = y - 1;
		if (this->y == 0)
		{
			y--;
		}
		break;
	};
	this->emit_signal(
		SIGNAL_D(Car::onMoveSignal),
		command
	);
}

void Car::doTactHandler(string param)
{
	string command;
	this->emit_signal(
		SIGNAL_D(Car::callMoveIfFrontIsFreeSignal),
		command
	);
}