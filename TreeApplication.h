#ifndef TREE_APPLICATION_H
#define TREE_APPLICATION_H

#include "TreeBase.h"

class TreeApplication : public TreeBase
{
public:
	TreeApplication(TreeBase* p_head_object);
	int build_tree_objects();
	void connect_tree_objects();
	int exec_app();
	void signal(string& param) override;
	void handler(string param) override;
	TYPE_SIGNAL getSignal();
	TYPE_HANDLER getHandler();
};
#endif
