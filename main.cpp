#include "IntersectionSystem.h"

int main()
{
	// program here
	IntersectionSystem* app = new IntersectionSystem(nullptr);
	app->build_tree_objects();
	return app->exec_app();
}
//сделать обработку команды printCar через RoadSection, чтобы он вызывал сигнал у машины