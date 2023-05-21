#ifndef ROAD_SECTION_H
#define ROAD_SECTION_H
#include "TrafficLight.h"

class RoadSection : public TreeBase
{
	//Пульт управления светофором

	//Длина участка дороги
private:
	int length;
	TrafficLight::Colors color;
public:
	RoadSection(TreeBase* p_head_object, string s_name = "RoadSection", int length = 5);
	void getColorSignal(string& param);

	string setLengthHandler(string length);
	string doTick(string param);
};

#endif // !ROAD_SECTION_H
