#include "Physics.h"
#include "Body.h"
#include "Game.h"
#include "Sprite.h"
#include "Events.h"
#include <cmath>
namespace ggEngine {
	Physics::Physics(Game * game)
	{
		this->game = game;
	}
	Physics::~Physics()
	{
		//TO DO remove all body here
	}
	void Physics::UpdatePhysics()
	{
		for (std::list<Body*>::iterator it = this->bodyList.begin();it != this->bodyList.end();) {
			if ((*it)->IsAlive()) {
				(*it)->Update();
				++it;
			}
			else {
				std::list<Body*>::iterator tempIt = it;
				++it;
				delete (*tempIt);
				bodyList.erase(tempIt);
			}
		}
	}
	void Physics::EnablePhysics(Sprite * sprite)
	{
		Body* body = new Body(game, sprite);
		bodyList.push_back(body);
		sprite->SetBody(body);
		if (sprite->events == NULL){
			sprite->events = new Events(game,sprite);
		}
	}
	void Physics::CheckBound(GameObject *go1, GameObject *go2){
		Rectangle *rect1 = dynamic_cast<Rectangle*>(go1->body->rigidBody);
		Rectangle *rect2 = dynamic_cast<Rectangle*>(go2->body->rigidBody);
		RECT r1 = { rect1->p1.x, rect1->p1.y, rect1->p3.x, rect1->p3.y };
		RECT r2 = { rect2->p1.x, rect2->p1.y, rect2->p3.x, rect2->p3.y };
		RECT intersectRect;
		if (IntersectRect(&intersectRect, &r1, &r2)!=0){
			ColliderArg arg1;
			ColliderArg arg2;
			Vector normalVector1;
			Vector normalVector2;
			float width = abs(intersectRect.right) - abs(intersectRect.left);
			float height = abs(intersectRect.bottom) - abs(intersectRect.top);
			if (width < height) {
				if (rect1->p1.x < rect2->p1.x){
					normalVector1 = Vector(-1, 0);
					arg1.blockDirection.right = true;
					arg2.blockDirection.left = true;
				}
				else{
					normalVector1 = Vector(1, 0);
					arg1.blockDirection.left = true;
					arg2.blockDirection.right = true;
				}
				normalVector2 = -1*normalVector1;
			}
			else{
				if (rect1->p1.y < rect2->p1.y){
					normalVector1 = Vector(0, -1);
					arg1.blockDirection.down = arg2.blockDirection.up = true;
				}
				else{
					normalVector1 = Vector(0, 1);
					arg1.blockDirection.up = arg2.blockDirection.down = true;
				}
				normalVector2 = -1 * normalVector1;
			}
			arg1.bound = true;
			arg2.bound = true;
			arg1.normalSurfaceVector = normalVector1;
			arg2.normalSurfaceVector = normalVector2;
			if (go1->events->onCollide != nullptr)  go1->events->onCollide(go1,arg1);
			if (go2->events->onCollide != nullptr)  go2->events->onCollide(go2,arg2);
		}
		//IntersectClipRect
	}

}