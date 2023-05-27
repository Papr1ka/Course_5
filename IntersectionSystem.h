#ifndef INTERSECTION_SYSTEM_H
#define INTERSECTION_SYSTEM_H

#include "InputObject.h"
#include "TrafficLightController.h"
#include "TrafficLight.h"
#include "RoadSection.h"
#include "Car.h"
#include "DisplayScreen.h"

class IntersectionSystem : public TreeBase
{
	//Система перекрёстка
public:
	IntersectionSystem(TreeBase* p_head_object, string s_name = "IntersectionSystem");

	void build_tree_objects();
	int exec_app();

	void callInputSignal(string& param);
};

#endif // !INTERSECTION_SYSTEM_H
