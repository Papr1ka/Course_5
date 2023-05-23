#include "RoadSection.h"

RoadSection::RoadSection(TreeBase* p_head_object, string s_name, int length) : TreeBase(p_head_object, s_name)
{
	this->length = length;
}

string RoadSection::setLengthHandler(string length)
{
	this->length = stoi(length);
	string response;
	return response;
}

string RoadSection::printRoadHandler(string param)
{
	int size = this->p_sub_objects.size();
	string command, response;

	for (int i = 0; i < size; i++)
	{
		this->emit_signal(
			SIGNAL_D(RoadSection::printCarCordsSignal),
			command
		);
	}
	return response;
}

void RoadSection::getColorSignal(string& param)
{
	
}

void RoadSection::printCarCordsSignal(string& param)
{

}

string RoadSection::doTick(string param)
{
	string response;
	string color;
	color = this->emit_signal(SIGNAL_D(RoadSection::getColorSignal), color);
	//вызвать метод move у машин
	return response;
}