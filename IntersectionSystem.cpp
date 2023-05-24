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
	RoadSection* road;
	this->inputObject = new InputObject(this);
	buffer = new TrafficLightController(this);
	new TrafficLight(buffer);
	road = new RoadSection(this);
	new DisplayScreen(this);

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

	this->inputObject->set_connect(
		SIGNAL_D(InputObject::printColorSignal),
		buffer->get_sub_object("TrafficLight"),
		HANDLER_D(TrafficLight::printColorHandler)
	);

	buffer->get_sub_object("TrafficLight")->set_connect(
		SIGNAL_D(TrafficLight::printColorSignal),
		this->get_sub_object("DisplayScreen"),
		HANDLER_D(DisplayScreen::printHandler)
	);

	this->get_sub_object("TrafficLightController")->set_connect(
		SIGNAL_D(TrafficLightController::changeTrafficLightSignal),
		buffer->get_sub_object("TrafficLight"),
		HANDLER_D(TrafficLight::changeTrafficLightHandler)
	);

	this->get_sub_object("RoadSection")->set_connect(
		SIGNAL_D(RoadSection::printSignal),
		this->get_sub_object("DisplayScreen"),
		HANDLER_D(DisplayScreen::printHandler)
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

	this->inputObject->set_connect(
		SIGNAL_D(InputObject::printRoadSignal),
		this->get_sub_object("RoadSection"),
		HANDLER_D(RoadSection::printRoadHandler)
	);

	this->get_sub_object("RoadSection")->set_connect(
		SIGNAL_D(RoadSection::getColorSignal),
		buffer->get_sub_object("TrafficLight"),
		HANDLER_D(TrafficLight::getColorHandler)
	);
	buffer->get_sub_object("TrafficLight")->set_connect(
		SIGNAL_D(TrafficLight::emitColorSignal),
		this->get_sub_object("RoadSection"),
		HANDLER_D(RoadSection::emitColorHandler)
	);

	this->get_sub_object("InputObject")->set_connect(
		SIGNAL_D(InputObject::doTactSignal),
		buffer->get_sub_object("TrafficLight"),
		HANDLER_D(TrafficLight::doTactHandler)
	);

	this->get_sub_object("InputObject")->set_connect(
		SIGNAL_D(InputObject::doTactSignal),
		this->get_sub_object("RoadSection"),
		HANDLER_D(RoadSection::doTactHandler)
	);

	string command;
	while (this->getState() == 1)
	{
		this->emit_signal(SIGNAL_D(IntersectionSystem::callInputSignal), command);
	}
}

int IntersectionSystem::exec_app()
{
	string command;
	while (this->getState() == 3)
	{
		this->emit_signal(SIGNAL_D(IntersectionSystem::callInputSignal), command);
	}
	return 0;
}
