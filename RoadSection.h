#ifndef ROAD_SECTION_H
#define ROAD_SECTION_H
#include "TrafficLight.h"

#include "Car.h"
#include "Cell.h"


class RoadSection : public TreeBase
{
	//Пульт управления светофором

	//Длина участка дороги
private:
	int length;
	TrafficLight::Colors color;
	vector<Cell*> cells;
	int currentColor;
public:
	RoadSection(TreeBase* p_head_object, string s_name = "RoadSection", int length = 5);
	~RoadSection();

	Cell* getCell(int x, int y);
	void setCell(int x, int y, TreeBase* obj);

	static Car* createCarFactory(int x, int y, string name, TreeBase* object);

	void printCarCordsSignal(string& param);
	void printSignal(string& param);
	void doTactSignal(string& param);
	void emitCarFontStateAndColorSignal(string& param);
	void getColorSignal(string& param);

	void emitColorHandler(string param);
	void setLengthHandler(string length);
	void doTactHandler(string param);
	void printRoadHandler(string param);
	void CallMoveIfFrontIsFreeHandler(string param);
	void onCarMoveHandler(string param);
};

#endif // !ROAD_SECTION_H
