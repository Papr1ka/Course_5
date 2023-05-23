#include "RoadSection.h"

RoadSection::RoadSection(TreeBase* p_head_object, string s_name, int length) : TreeBase(p_head_object, s_name)
{
	this->length = length;
}

void RoadSection::setLengthHandler(string length)
{
	this->length = stoi(length);
}

void RoadSection::printRoadHandler(string param)
{
	int size = this->p_sub_objects.size();
	string command;

	for (int i = 0; i < size; i++)
	{
		this->emit_signal(
			SIGNAL_D(RoadSection::printCarCordsSignal),
			command,
			this->p_sub_objects[i]
		);
	}
}

void RoadSection::printCarCordsSignal(string& param)
{

}

void RoadSection::doTick(string param)
{
	//вызвать метод move у машин
}