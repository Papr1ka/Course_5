#include "DisplayScreen.h"

DisplayScreen::DisplayScreen(TreeBase* p_head_object, string s_name) : TreeBase(p_head_object, s_name)
{

}

string DisplayScreen::printHandler(string param)
{
	string response;
	cout << endl << param;
	return response;
}