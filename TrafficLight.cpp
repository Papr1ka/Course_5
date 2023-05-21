#include "TrafficLight.h"

TrafficLight::TrafficLight(TreeBase* p_head_object, string s_name, Colors color, int ticksGreen, int ticksRed) : TreeBase(p_head_object, s_name)
{
	this->setState(color);
	this->ticksGreen = ticksGreen;
	this->ticksRed = ticksRed;
}

string TrafficLight::changeTrafficLightHandler(string param)
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
	string response;
	return response;
}

string TrafficLight::getColorHandler(string param)
{
	int value = this->getState();
	string response = to_string(value);
	return response;
}