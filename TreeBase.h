#ifndef TREE_BASE_H
#define TREE_BASE_H

#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <queue>
#include <sstream>

#define SIGNAL_D( signal_f ) ( TreeBase::TYPE_SIGNAL ) ( & signal_f )
#define HANDLER_D( handler_f ) ( TreeBase::TYPE_HANDLER ) ( & handler_f )

struct Conn;

using namespace std;

class TreeBase
{
private:
	string s_name;
	TreeBase* p_head_object;
	vector<TreeBase*> p_sub_objects;
	vector <Conn*> connects;
	int state;
public:
	typedef void (TreeBase ::* TYPE_SIGNAL) (string&);
	typedef string (TreeBase ::* TYPE_HANDLER) (string);

	TreeBase(TreeBase* p_head_object, string s_name = "root");

	~TreeBase();

	bool set_name(string name); //true если на том же уровне иерархии нету объектов с таким же именем

	TreeBase* get_head();
	string get_name();
	TreeBase* get_sub_object(string name);
	int getState();
	void print_tree(string str = "");
	void printTreeReady(string str = "");
	TreeBase* searchSub(string name);
	TreeBase* searchRoot(string name);
	void setState(int state);
	bool reOrder(TreeBase* new_head);
	bool deleteSub(string name);
	TreeBase* getByPath(string name);
	string getAbsoluteCoordinate();
	void set_connect(TYPE_SIGNAL p_signal, TreeBase* p_object, TYPE_HANDLER p_object_handler);
	string emit_signal(TYPE_SIGNAL p_signal, string& s_command, TreeBase* handlerObject = nullptr);
	void delete_connect(TYPE_SIGNAL p_signal, TreeBase* p_object, TYPE_HANDLER p_object_handler);
	virtual void signal(string& param);
	virtual void handler(string param);
	TYPE_SIGNAL getSignal();
	TYPE_HANDLER getHandler();
	void setSubTreeReady();
	void replaceByName();
};

struct Conn                 // Структура задания одной связи
{
	TreeBase::TYPE_SIGNAL  p_signal;    // Указатель на метод сигнала
	TreeBase* p_object;   // Указатель на целевой объект
	TreeBase::TYPE_HANDLER p_handler;   // Указатель на метод обработчика
};

#endif