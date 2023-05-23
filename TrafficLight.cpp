#include "TrafficLight.h"

TrafficLight::TrafficLight(TreeBase* p_head_object, string s_name, Colors color, int ticksGreen, int ticksRed) : TreeBase(p_head_object, s_name)
{
	this->setState(color);
	this->ticksGreen = ticksGreen;
	this->ticksRed = ticksRed;
}

void TrafficLight::changeTrafficLightHandler(string param)
{
	stringstream query;
	query << param;
	int value;
	Colors colorEdit;
	int ticks;

	query >> value >> ticks;
	colorEdit = (Colors) value;
	if (ticks > 2)
	{
		switch (colorEdit)
		{
		case Colors::Green:
			this->ticksGreen = ticks;
			break;
		case Colors::Red:
			this->ticksRed = ticks;
			break;
		}
	}
}

void TrafficLight::printColorHandler(string param)
{
	string command;
	this->emit_signal(
		SIGNAL_D(TrafficLight::printColorSignal),
		command
	);
}

void TrafficLight::printColorSignal(string& param)
{
	Colors state = (Colors) this->getState();
	param = "Traffic light color is ";

	switch (state)
	{
	case TrafficLight::Green:
		param += "green";
		break;
	case TrafficLight::Red:
		param += "red";
		break;
	case TrafficLight::Yellow:
		param += "yellow";
		break;
	case TrafficLight::Yellow2:
		param += "yellow";
		break;
	}
}