#ifndef ROAD_SECTION_H
#define ROAD_SECTION_H
#include "TrafficLight.h"

//удалить
#include "Car.h"

class RoadSection : public TreeBase
{
	//Пульт управления светофором

	//Длина участка дороги
private:
	int length;
	TrafficLight::Colors color;
public:
	RoadSection(TreeBase* p_head_object, string s_name = "RoadSection", int length = 5);
	void printColorSignal(string& param);
	void printCarCordsSignal(string& param);

	void setLengthHandler(string length);
	void doTick(string param);
	void printRoadHandler(string param);
};


#endif // !ROAD_SECTION_H
