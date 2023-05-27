#include "TrafficLightController.h"

TrafficLightController::TrafficLightController(TreeBase* p_head_object, string s_name) : TreeBase(p_head_object, s_name) {}

void TrafficLightController::changeTrafficLightSignal(string& param)
{
	
}

void TrafficLightController::doTactSignal(string& param)
{

}

void TrafficLightController::doTactHandler(string param)
{
	string command;
	this->emit_signal(
		SIGNAL_D(TrafficLightController::doTactSignal),
		command
	);
}
