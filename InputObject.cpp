#include "InputObject.h"

InputObject::InputObject(TreeBase* p_head_object, string s_name) : TreeBase(p_head_object, s_name) {}

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
	Car* obj = RoadSection::createCarFactory(x, y, carNumber, this->get_head());

	this->set_connect(
		SIGNAL_D(InputObject::printCarCordsSignal),
		obj,
		HANDLER_D(Car::printCarCordsHandler)
	);
	obj->set_connect(
		SIGNAL_D(Car::printCarCordsSignal),
		this->searchRoot("DisplayScreen"),
		HANDLER_D(DisplayScreen::printHandler)
	);
	this->searchRoot("RoadSection")->set_connect(
		SIGNAL_D(RoadSection::printCarCordsSignal),
		obj,
		HANDLER_D(Car::printCarCordsHandler)
	);
	this->searchRoot("RoadSection")->set_connect(
		SIGNAL_D(RoadSection::doTactSignal),
		obj,
		HANDLER_D(Car::doTactHandler)
	);
	obj->set_connect(
		SIGNAL_D(Car::onMoveSignal),
		this->searchRoot("RoadSection"),
		HANDLER_D(RoadSection::onCarMoveHandler)
	);
	obj->set_connect(
		SIGNAL_D(Car::callMoveIfFrontIsFreeSignal),
		this->searchRoot("RoadSection"),
		HANDLER_D(RoadSection::callMoveIfFrontIsFreeHandler)
	);
	this->searchRoot("RoadSection")->set_connect(
		SIGNAL_D(RoadSection::emitCarFrontStateAndColorSignal),
		obj,
		HANDLER_D(Car::moveHandler)
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
	query >> command;
	if (command == "SHOWTREE")
	{
		this->get_head()->printTreeReady();
		this->setState(++state);
		this->getByPath("/")->setState(state);
		return;
	}
	else
	{
		query >> other;
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
				this->searchRoot("TrafficLightController")->emit_signal(
					SIGNAL_D(TrafficLightController::changeTrafficLightSignal),
					commandToSend
				);
			}
		}
		else if (command == "Car")
		{
			TreeBase* car = this->searchRoot("RoadSection")->searchSub(other);
			if (car != nullptr)
			{
				this->emit_signal(
					SIGNAL_D(InputObject::printCarCordsSignal),
					commandToSend,
					car
				);
			}
			else
			{
				commandToSend = other + " the car left the road section";
				this->emit_signal(
					SIGNAL_D(InputObject::printSignal),
					commandToSend
				);
			}
		}
		else if (command == "Display")
		{
			string command2;
			this->emit_signal(SIGNAL_D(InputObject::printColorSignal), commandToSend);
			this->emit_signal(SIGNAL_D(InputObject::printRoadSignal), command2);
		}
	}
}

void InputObject::tact()
{
	string command2, command3;
	this->emit_signal(
		SIGNAL_D(InputObject::doTactSignal),
		command2,
		this->searchRoot("TrafficLightController")
	);
	this->emit_signal(
		SIGNAL_D(InputObject::doTactSignal),
		command3,
		this->searchRoot("RoadSection")
	);
}

void InputObject::setRoadSizeSignal(string& param) {}

void InputObject::printCarCordsSignal(string& param) {}

void InputObject::printSignal(string& param) {}

void InputObject::printSignalNoEndl(string& param) {}

void InputObject::printColorSignal(string& param) {}

void InputObject::printRoadSignal(string& param) {}

void InputObject::doTactSignal(string& param) {}

void InputObject::readHandler(string param)
{
	string line;
	getline(cin, line);

	int state = this->getState();
	if (line == "End of cars")
	{
		string command = "Ready to work";
		this->setState(++state);
		this->getByPath("/")->setState(state);
		this->emit_signal(
			SIGNAL_D(InputObject::printSignal),
			command
		);
		return;
	}
	else if (line == "Turn off the system")
	{
		string command = "Turn off the system";
		this->setState(++state);
		this->getByPath("/")->setState(state);
		this->emit_signal(
			SIGNAL_D(InputObject::printSignalNoEndl),
			command
		);
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
		this->tact();
		break;
	}
}
