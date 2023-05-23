#include "IntersectionSystem.h"

IntersectionSystem::IntersectionSystem(TreeBase* p_head_object, string s_name) : TreeBase(p_head_object, s_name)
{
	this->tickNumber = 0;
	this->inputObject = nullptr;
}

void IntersectionSystem::callInputSignal(string& param)
{
	
}

void IntersectionSystem::build_tree_objects()
{
	TreeBase* buffer;
	TreeBase* buffer2;
	RoadSection* road;
	buffer = new TrafficLightController(this);
	new TrafficLight(buffer);
	road = new RoadSection(this);
	new DisplayScreen(this);
	this->inputObject = new InputObject(this);

	this->setSubTreeReady();

	this->set_connect(
		SIGNAL_D(IntersectionSystem::callInputSignal),
		this->get_sub_object("InputObject"),
		HANDLER_D(InputObject::readHandler)
	);

	this->get_sub_object("InputObject")->set_connect(
		SIGNAL_D(InputObject::setRoadSizeSignal),
		this->get_sub_object("RoadSection"),
		HANDLER_D(RoadSection::setLengthHandler)
	);

	this->get_sub_object("RoadSection")->set_connect(
		SIGNAL_D(RoadSection::getColorSignal),
		buffer->get_sub_object("TrafficLight"),
		HANDLER_D(TrafficLight::getColorHandler)
	);

	this->get_sub_object("TrafficLightController")->set_connect(
		SIGNAL_D(TrafficLightController::changeTrafficLightSignal),
		buffer->get_sub_object("TrafficLight"),
		HANDLER_D(TrafficLight::changeTrafficLightHandler)
	);

	this->inputObject->set_connect(
		SIGNAL_D(InputObject::printSignal),
		this->get_sub_object("DisplayScreen"),
		HANDLER_D(DisplayScreen::printHandler)
	);

	this->inputObject->set_connect(
		SIGNAL_D(InputObject::printSignal),
		buffer->get_sub_object("TrafficLight"),
		HANDLER_D(TrafficLight::changeTrafficLightHandler)
	);

	string command;
	do
	{
		command = this->emit_signal(SIGNAL_D(IntersectionSystem::callInputSignal), command);
	} while (command != "End of cars");
}

int IntersectionSystem::exec_app()
{
	string command;
	do
	{
		command = this->emit_signal(SIGNAL_D(IntersectionSystem::callInputSignal), command);
	} while (command != "Turn off the system");
	return 0;
}