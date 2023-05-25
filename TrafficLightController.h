#ifndef TRAFFIC_LIGHT_CONTROLLER_H
#define TRAFFIC_LIGHT_CONTROLLER_H
#include "TrafficLight.h"

class TrafficLightController : public TreeBase
{
	//Пульт управления светофором
private:
	int ticksGreen;
	int ticksRed;
	int ticks;
public:
	TrafficLightController(TreeBase* p_head_object, string s_name = "TrafficLightController");

	void changeTrafficLightSignal(string& param);
	void doTactSignal(string& param);

	void doTactHandler(string param);
};

#endif // !TRAFFIC_LIGHT_CONTROLLER_H
