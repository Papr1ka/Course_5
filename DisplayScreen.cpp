#include "DisplayScreen.h"

DisplayScreen::DisplayScreen(TreeBase* p_head_object, string s_name) : TreeBase(p_head_object, s_name) {}

void DisplayScreen::printHandler(string param)
{
	cout << param << endl;
}

void DisplayScreen::printHandlerNoEndl(string param)
{
	cout << param;
}
