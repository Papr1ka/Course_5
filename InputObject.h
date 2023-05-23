#ifndef INPUT_OBJECT_H
#define INPUT_OBJECT_H

#include "Car.h"
#include "TrafficLightController.h"
#include "DisplayScreen.h"

class InputObject : public TreeBase
{
private:
	TreeBase* roadSectionObject;
	TreeBase* trafficLightControllerObject;
	TreeBase* displayScreenObject;
public:
	InputObject(TreeBase* p_head_object, string s_name = "InputObject");

	string readHandler();
	void inputRoadLength(string line);
	void inputCar(string line);
	void inputCommand(string line);

	void setRoadSizeSignal(string& param);
	void printCarCordsSignal(string& param);
	void printSignal(string& param); 
	void getColorSignal(string& param);
};

#endif // !INPUT_OBJECT_H
