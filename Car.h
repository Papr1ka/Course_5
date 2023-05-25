#ifndef Car_H
#define Car_H
#include "TrafficLight.h"

#define SET_BIT(value, n) (value = value | (1 << n)) //устанавливает бит под номером n в 1
#define UNSET_BIT(value, n) (value = value & (1 << n)) //устанавливает бит под номером n в 0

class Car : public TreeBase
{
public:
	enum Directions
	{
		Top = 1,
		Right,
		Left,
		Bottom,
	};
public:
	int x; //horizontal, left to right
	int y; //vertical, bottom to up
	Directions direction;

public:
	Car(int x, int y, TreeBase* p_head_object, string s_name);
	void insertNew();

	void printCarCordsSignal(string& param);
	void CallMoveIfFrontIsFreeSignal(string& param);
	void onMoveSignal(string& param);

	void printCarCordsHandler(string param);
	void moveHandler(string param);
	void doTactHandler(string param);
};

#endif // !Car_H
