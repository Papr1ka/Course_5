#ifndef INPUT_OBJECT_H
#define INPUT_OBJECT_H

#include "Car.h"
#include "TrafficLightController.h"
#include "DisplayScreen.h"
#include "RoadSection.h"

class InputObject : public TreeBase
{
public:
	InputObject(TreeBase* p_head_object, string s_name = "InputObject");

	void inputRoadLength(string line);
	void inputCar(string line);
	void inputCommand(string line);
	void tact();

	void setRoadSizeSignal(string& param);
	void printCarCordsSignal(string& param);
	void printSignal(string& param);
	void printSignalNoEndl(string& param);
	void printColorSignal(string& param);
	void printRoadSignal(string& param);
	void incrementTrafficLightTicksSignal(string& param);
	void doTactSignal(string& param);

	void readHandler(string param);
};

#endif // !INPUT_OBJECT_H
