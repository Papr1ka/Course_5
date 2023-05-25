#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H
#include "TreeBase.h"

class TrafficLight : public TreeBase
{
	//��������
public:
	enum Colors
	{
		Green = 1,
		Yellow,
		Red,
		Yellow2
	};
private:
	//���� ��� �������������� �����
	//���������: 1 -> ������, 2 -> ����� ����� �������, 3 -> �������, 4 -> ����� ����� ��������
	int ticksGreen;
	int ticksRed;
	int ticks;
public:
	TrafficLight(TreeBase* p_head_object, string s_name = "TrafficLight", Colors color = Colors::Green, int ticksGreen = 5, int ticksRed = 5);
	void changeTrafficLightHandler(string param);
	void printColorHandler(string param);
	void getColorHandler(string param);
	void printColorSignal(string& param);
	void emitColorSignal(string& param);

	void doTactHandler(string param);
};

#endif // !TRAFFIC_LIGHT_H
