#include "InputObject.h"

void InputObject::setRoadSizeSignal(string& param)
{
}

void InputObject::printCarCordsSignal(string& param)
{

}

void InputObject::printSignal(string& param)
{

}

void InputObject::printColorSignal(string& param)
{
	
}

void InputObject::printRoadSignal(string& param)
{

}

InputObject::InputObject(TreeBase* p_head_object, string s_name) : TreeBase(p_head_object, s_name)
{
	this->roadSectionObject = this->searchRoot("RoadSection");
	this->trafficLightControllerObject = this->searchRoot("TrafficLightController");
	this->displayScreenObject = this->searchRoot("DisplayScreen");
}

void InputObject::readHandler()
{
	string line;
	getline(cin, line);

	int state = this->getState();
	if (line == "End of cars" || line == "Turn off the system")
	{
		this->setState(++state);
		this->getByPath("/")->setState(state);
		return;
	}

	switch (state)
	{
	case 1:
		this->inputRoadLength(line);
		break;
	case 2:
		this->inputCar(line);
		break;
	case 3:
		this->inputCommand(line);
		break;
	}
}

void InputObject::inputRoadLength(string line)
{
	int roadLength = stoi(line);
	string param = to_string(roadLength);
	this->emit_signal(SIGNAL_D(InputObject::setRoadSizeSignal), param);
	this->setState(this->getState() + 1);
}

void InputObject::inputCar(string line)
{
	stringstream query;
	string carNumber;
	int x, y;

	query << line;
	query >> carNumber >> x >> y;
	Car* obj = new Car(x, y, this->roadSectionObject, carNumber);
	this->set_connect(
		SIGNAL_D(InputObject::printCarCordsSignal),
		obj,
		HANDLER_D(Car::printCarCordsHandler)
	);
	obj->set_connect(
		SIGNAL_D(Car::printCarCordsSignal),
		this->displayScreenObject,
		HANDLER_D(DisplayScreen::printHandler)
	);
	this->roadSectionObject->set_connect(
		SIGNAL_D(RoadSection::printCarCordsSignal),
		obj,
		HANDLER_D(Car::printCarCordsHandler)
	);
	this->set_connect(
		SIGNAL_D(InputObject::printRoadSignal),
		this->roadSectionObject,
		HANDLER_D(RoadSection::printRoadHandler)
	);
}

void InputObject::inputCommand(string line)
{
	stringstream query;
	string command;
	string other;
	string commandToSend;

	int value;
	bool colorCondition = false;
	query << line;
	query >> command >> other;
	if (command == "Switching")
	{
		query >> other;
		query >> other;
		query >> value;
		if (other == "red")
		{
			colorCondition = true;
			commandToSend += to_string(3);
		}
		else if (other == "green")
		{
			colorCondition = true;
			commandToSend += to_string(1);
		}
		if (colorCondition)
		{
			commandToSend += " ";
			commandToSend += to_string(value);
			this->trafficLightControllerObject->emit_signal(
				SIGNAL_D(TrafficLightController::changeTrafficLightSignal),
				commandToSend
			);
		}
	}
	else if (command == "Car")
	{
		string command;
		TreeBase* car = this->roadSectionObject->searchSub(other);
		if (car != nullptr)
		{
			this->emit_signal(
				SIGNAL_D(InputObject::printCarCordsSignal),
				command,
				car
			);
		}
	}
	else if (command == "Display")
	{
		string command, command2;
		this->emit_signal(SIGNAL_D(InputObject::printColorSignal), command);
		this->emit_signal(SIGNAL_D(InputObject::printRoadSignal), command2);
	}
}