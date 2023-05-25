#include "TrafficLightController.h"

TrafficLightController::TrafficLightController(TreeBase* p_head_object, string s_name) : TreeBase(p_head_object, s_name)
{
	this->ticks = -1;
	this->ticksGreen = 5;
	this->ticksRed = 5;
}

void TrafficLightController::changeTrafficLightSignal(string& param)
{
	
}