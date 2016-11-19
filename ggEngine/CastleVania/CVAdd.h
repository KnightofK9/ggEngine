#pragma once
#include <ggEngine.h>
using namespace ggEngine;
class CVAdd : public Add {
public:
	CVAdd(World *world, Cache *cache, TweenManager *tweenManager, DrawManager *drawManager, Camera *camera, Physics *physics, TimeBasedEventManager *timeBasedEventManager);
	~CVAdd();
private:

};