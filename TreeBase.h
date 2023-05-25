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
#define EMPTY_METHOD_D( method_f ) ( TreeBase::EMPTY_METHOD ) ( & method_f )

struct Conn;

using namespace std;

class TreeBase
{
protected:
	string s_name;
	TreeBase* p_head_object;
	vector <Conn*> connects;
	int state;
public:
	vector<TreeBase*> p_sub_objects;

	typedef void (TreeBase ::* TYPE_SIGNAL) (string&);
	typedef void (TreeBase ::* TYPE_HANDLER) (string);
	typedef void (TreeBase ::* EMPTY_METHOD) ();

	TreeBase(TreeBase* p_head_object, string s_name = "root", EMPTY_METHOD method = EMPTY_METHOD_D(TreeBase::insertNew));
	~TreeBase();

	bool set_name(string name); //true если на том же уровне иерархии нету объектов с таким же именем
	bool reOrder(TreeBase* new_head);
	bool deleteSub(string name);

	TreeBase* get_head();
	TreeBase* get_sub_object(string name); 
	TreeBase* searchSub(string name);
	TreeBase* searchRoot(string name);
	TreeBase* getByPath(string name);

	string get_name();
	string getAbsoluteCoordinate();

	int getState();

	void insertNew();
	void print_tree(string str = "");
	void printTreeReady(string str = "");
	void setState(int state);
	void setSubTreeReady();
	void replaceByName();
	void set_connect(TYPE_SIGNAL p_signal, TreeBase* p_object, TYPE_HANDLER p_object_handler);
	void emit_signal(TYPE_SIGNAL p_signal, string& s_command, TreeBase* handlerObject = nullptr);
	void delete_connect(TYPE_SIGNAL p_signal, TreeBase* p_object, TYPE_HANDLER p_object_handler);
	void deleteConnects();
};

struct Conn                 // Структура задания одной связи
{
	TreeBase::TYPE_SIGNAL  p_signal;    // Указатель на метод сигнала
	TreeBase* p_object;   // Указатель на целевой объект
	TreeBase::TYPE_HANDLER p_handler;   // Указатель на метод обработчика
};

#endif
