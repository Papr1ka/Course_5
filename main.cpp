#include "IntersectionSystem.h"

int main()
{
	// program here
	IntersectionSystem* app = new IntersectionSystem(nullptr);
	app->build_tree_objects();
	return app->exec_app();
}
