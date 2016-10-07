#include "Physics.h"
#include "Body.h"
#include "Game.h"
#include "Sprite.h"
#include "Events.h"
#include <cmath>
namespace ggEngine {
	Physics::Physics(Game * game, PhysicsMode physicsMode)
	{
		this->game = game;
		this->physicsMode = physicsMode;
	}
	Physics::~Physics()
	{
		this->bodyList.clear();
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
		switch (physicsMode) {
		case PhysicsMode_AABB:
			CheckBoundAABB(go1, go2);
			break;
		case PhysicsMode_AABBSwept:
			CheckBoundSweptAABB(go1, go2);
			break;
		case PhysicsMode_None:
		default:
			break;
		}
	}

	void Physics::CheckBoundAABB(GameObject * go1, GameObject * go2)
	{
		Rectangle *rect1 = dynamic_cast<Rectangle*>(go1->body->rigidBody);
		Rectangle *rect2 = dynamic_cast<Rectangle*>(go2->body->rigidBody);
		RECT r1 = { rect1->p1.x, rect1->p1.y, rect1->p3.x, rect1->p3.y };
		RECT r2 = { rect2->p1.x, rect2->p1.y, rect2->p3.x, rect2->p3.y };
		RECT intersectRect;
		if (IntersectRect(&intersectRect, &r1, &r2) != 0) {
			ColliderArg arg1;
			ColliderArg arg2;
			Vector normalVector1;
			Vector normalVector2;
			float width = abs(intersectRect.right) - abs(intersectRect.left);
			float height = abs(intersectRect.bottom) - abs(intersectRect.top);
			if (width < height) {
				if (rect1->p1.x < rect2->p1.x) {
					normalVector1 = Vector(-1, 0);
					arg1.blockDirection.right = true;
					arg2.blockDirection.left = true;
				}
				else {
					normalVector1 = Vector(1, 0);
					arg1.blockDirection.left = true;
					arg2.blockDirection.right = true;
				}
				normalVector2 = -1 * normalVector1;
			}
			else {
				if (rect1->p1.y < rect2->p1.y) {
					normalVector1 = Vector(0, -1);
					arg1.blockDirection.down = arg2.blockDirection.up = true;
				}
				else {
					normalVector1 = Vector(0, 1);
					arg1.blockDirection.up = arg2.blockDirection.down = true;
				}
				normalVector2 = -1 * normalVector1;
			}
			arg1.bound = true;
			arg2.bound = true;
			arg1.normalSurfaceVector = normalVector1;
			arg2.normalSurfaceVector = normalVector2;
			if (go1->events->onCollide != nullptr)  go1->events->onCollide(go1, arg1);
			if (go2->events->onCollide != nullptr)  go2->events->onCollide(go2, arg2);
		}
	}

	void Physics::CheckBoundSweptAABB(GameObject * go1, GameObject * go2)
	{
		Rectangle *rect1 = dynamic_cast<Rectangle*>(go1->body->rigidBody);
		Rectangle *rect2 = dynamic_cast<Rectangle*>(go2->body->rigidBody);
		RECT r1 = { rect1->p1.x, rect1->p1.y, rect1->p3.x, rect1->p3.y };
		RECT r2 = { rect2->p1.x, rect2->p1.y, rect2->p3.x, rect2->p3.y };

		Vector relativeVelocity = go1->body->velocity - go2->body->velocity;
		float xEntry, xExit;
		float yEntry, yExit;
		if (relativeVelocity.x > 0.0f)
		{
			xEntry = r2.left - r1.right;
			xExit = r2.right - r1.left;
		}
		else
		{
			xEntry = r2.right - r1.left;
			xExit = r2.left - r1.right;
		}
		if (relativeVelocity.y > 0.0f)
		{
			yEntry = r2.top - r1.bottom;
			yExit = r2.bottom - r1.top;
		}
		else
		{
			yEntry = r2.bottom - r1.top;
			yExit = r2.top - r1.bottom;
		}
		float xTimeToEntry, xTimeToExit;
		float yTimeToEntry, yTimeToExit;
		if (relativeVelocity.x == 0)
		{
			xTimeToEntry = -std::numeric_limits<float>::infinity();
			xTimeToExit = std::numeric_limits<float>::infinity();
		}
		else
		{
			xTimeToEntry = xEntry / relativeVelocity.x;
			xTimeToExit = xExit / relativeVelocity.x;
		}

		if (relativeVelocity.y == 0)
		{
			yTimeToEntry = -std::numeric_limits<float>::infinity();
			yTimeToExit = std::numeric_limits<float>::infinity();
		}
		else
		{
			yTimeToEntry = yEntry / relativeVelocity.y;
			yTimeToExit = yExit / relativeVelocity.y;
		}

		float timeEntry = max(xTimeToEntry, yTimeToEntry);
		float timeExit = min(xTimeToExit, yTimeToExit);

		if (timeEntry > timeExit || xTimeToEntry < 0.0 && yTimeToEntry < 0.0 || xTimeToEntry > 1.0 || yTimeToEntry > 1.0)
		{
			return;
		}
		Debug::Log("velocity: " + std::to_string(relativeVelocity.x) + " ," + std::to_string(relativeVelocity.y));
		Debug::Log("time entry x: " + std::to_string(xTimeToEntry));
		Debug::Log("time entry y: " + std::to_string(yTimeToEntry));
		ColliderArg arg1;
		ColliderArg arg2;
		Vector normalVector1;
		Vector normalVector2;
		if (xTimeToEntry > yTimeToEntry)
		{
			if (rect1->p1.x < rect2->p1.x)
			{
				normalVector1 = Vector(-1, 0);
				arg1.blockDirection.right = true;
				arg2.blockDirection.left = true;
			}
			else
			{
				normalVector1 = Vector(1, 0);
				arg1.blockDirection.left = true;
				arg2.blockDirection.right = true;
			}
			normalVector2 = -1 * normalVector1;
		}
		else
		{
			if (rect1->p1.y < rect2->p1.y)
			{
				normalVector1 = Vector(0, -1);
				arg1.blockDirection.down = true;
				arg2.blockDirection.up = true;
			}
			else
			{
				normalVector1 = Vector(0, 1);
				arg1.blockDirection.up = true;
				arg2.blockDirection.down = true;
			}
			normalVector2 = -1 * normalVector1;
		}
		arg1.bound = true;
		arg2.bound = true;
		arg1.normalSurfaceVector = normalVector1;
		arg2.normalSurfaceVector = normalVector2;
		if (go1->events->onCollide != nullptr)  go1->events->onCollide(go1, arg1);
		if (go2->events->onCollide != nullptr)  go2->events->onCollide(go2, arg2);
	}

	void Physics::Reset(){
		bodyList.clear();
	}
}