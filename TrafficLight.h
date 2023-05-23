#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H
#include "TreeBase.h"

class TrafficLight : public TreeBase
{
	//Светофор
public:
	enum Colors
	{
		Green = 1,
		Yellow,
		Red,
		Yellow2
	};
private:
	//Цвет для горизонтальных полос
	//Состояния: 1 -> зелёный, 2 -> жёлтый после зелёного, 3 -> красный, 4 -> жёлтый после красного
	int ticksGreen;
	int ticksRed;
public:
	TrafficLight(TreeBase* p_head_object, string s_name = "TrafficLight", Colors color = Colors::Green, int ticksGreen = 5, int ticksRed = 5);
	void changeTrafficLightHandler(string param);
	void printColorHandler(string param);
	void printColorSignal(string& param);
};

#endif // !TRAFFIC_LIGHT_H
