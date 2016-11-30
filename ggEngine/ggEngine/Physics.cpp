#include "Physics.h"
#include "Body.h"
#include "Game.h"
#include "Sprite.h"
#include "Events.h"
#include "TileMap.h"
#include "Rect.h"
#include <cmath>
namespace ggEngine {
	double timeEntrySAABB;
	Physics::Physics(Game * game, PhysicsMode physicsMode)
	{
		this->game = game;
		this->physicsMode = physicsMode;
	}
	Physics::~Physics()
	{
		this->bodyList.clear();
		this->tileMapList.clear();
	}
	void Physics::Update(double dt)
	{
		UpdatePhysics();
	}
	void Physics::UpdatePhysics()
	{
		UpdateCollisionList();
		UpdateBody();
	}
	void Physics::EnablePhysics(GameObject * gameObject)
	{
		Body* body = new Body(game, gameObject);
		bodyList.push_back(body);
		gameObject->SetBody(body);
		if (gameObject->events == NULL){
			gameObject->events = new Events(game, gameObject);
		}
	}

	void Physics::AttachBodyTo(GameObject * gameObject)
	{
		Body* body = new Body(game, gameObject); gameObject->SetBody(body);
		if (gameObject->events == NULL) {
			gameObject->events = new Events(game, gameObject);
		}
	}
	void Physics::RemoveBodyFromList(Body * body)
	{
		bodyList.remove(body);
	}
	void Physics::Reset(){
		bodyList.clear();
	}
	void Physics::AddTileMap(TileMap * tileMap)
	{
		this->tileMapList.push_back(tileMap);
	}
	void Physics::RemoveTileMap(TileMap * tileMap)
	{
		for (auto it = this->tileMapList.begin(); it != this->tileMapList.end(); ++it) {
			if ((*it) == tileMap) {
				this->tileMapList.erase(it);
				break;
			}
		}
	}
	Rect Physics::CreateSweptBroadPhaseRect(Box b)
	{
		double top, left, right, bottom;
		left = b.vx > 0 ? b.x : b.x + b.vx;
		top = b.vy > 0 ? b.y : b.y + b.vy;
		right = b.vx > 0 ? b.r + b.vx  :b.r;
		bottom = b.vy > 0 ? b.d + b.vy  :b.d;
		Rect r{ left,top,right,bottom };
		return r;
	}
	bool Physics::AABBCheck(Rect b1, Rect b2)
	{
		Rect rI;
		return Rect::intersect(rI, b1, b2);
	}
	Box Physics::CreateBoxFromObject(GameObject * go, Vector velocity)
	{
		Shape *rigidBody = go->body->rigidBody;
		Box b1;
		b1.gameObject = go;
		b1.x = rigidBody->GetLeft();
		b1.y = rigidBody->GetUp();
		b1.w = rigidBody->GetWidth();
		b1.h = rigidBody->GetHeight();
		b1.r = b1.x + b1.w;
		b1.d = b1.y + b1.h;
		b1.vx = velocity.x;
		b1.vy = velocity.y;
		return b1;
	}
	ColliderArg Physics::CreateOppositeColliderArg(ColliderArg e, GameObject * otherObject)
	{
		ColliderArg o = e;
		o.colliderObject = otherObject;
		o.blockDirection.Revert();
		auto entry = o.remainingTime;
		o.remainingTime = o.entryTime;
		o.entryTime = entry;
		o.currentVelocity = Vector(0,0);
		o.normalSurfaceVector *= -1;
		return o;
	}
	
	void Physics::UpdateCollisionList()
	{
		this->collisionList.clear();
		for (auto it = this->tileMapList.begin(); it != this->tileMapList.end(); ++it) {
			collisionList.splice(collisionList.end(), (*it)->GetCollisionCheckList());
		}
	}
	void Physics::UpdateBody()
	{
		for (auto it = this->bodyList.begin(); it != this->bodyList.end();++it) {
			if ((*it)->IsAlive()) {
				if ((*it)->IsEnable()) {
					((*it))->AddListCheckCollisionTo(this->collisionList);
					(*it)->Update();
				}
			}
			/*else {
				std::list<Body*>::iterator tempIt = it;
				++it;
				delete (*tempIt);
				bodyList.erase(tempIt);
			}*/
		}
	}
}