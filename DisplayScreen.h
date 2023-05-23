#ifndef DISPLAY_SCREEN_H
#define DISPLAY_SCREEN_H
#include "TreeBase.h"

class DisplayScreen : public TreeBase
{
	//Экран отображения информации
public:
	DisplayScreen(TreeBase* p_head_object, string s_name = "DisplayScreen");

	void printHandler(string param);
};

#endif // !DISPLAY_SCREEN_H
