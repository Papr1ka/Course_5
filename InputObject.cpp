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

void InputObject::getColorSignal(string& param)
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

string InputObject::readHandler()
{
	string line;
	getline(cin, line);

	int state = this->getState();
	if (line == "End of cars" || line == "Turn off the system")
	{
		this->setState(++state);
		return line;
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
	return line;
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
	query << line;
	query >> command >> other;
	if (command == "Switching")
	{
		query >> other;
		query >> other;
		query >> value;
		if (other == "red")
		{
			commandToSend += to_string(3);
			commandToSend += " ";
			commandToSend += to_string(value);
			this->trafficLightControllerObject->emit_signal(
				SIGNAL_D(TrafficLightController::changeTrafficLightSignal),
				commandToSend
			);
		}
		else if (other == "green")
		{
			commandToSend += to_string(1);
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
		string response = this->emit_signal(
			SIGNAL_D(InputObject::printCarCordsSignal),
			command,
			car
		);
	}
	else if (command == "Display")
	{
		string response;
		string command;
		response = this->emit_signal(SIGNAL_D(InputObject::getColorSignal), command);
		if (response == "1")
		{
			response = "green";
		}
		else if (response == "4")
		{
			response = "red";
		}
		else
		{
			response = "yellow";
		}
		string toOut = "Traffic light color is " + response;
		string test;
		this->emit_signal(SIGNAL_D(InputObject::printSignal), toOut);
		this->emit_signal(SIGNAL_D(InputObject::printRoadSignal), test);
	}
}