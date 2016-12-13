#define NOMINMAX
#include "Body.h"
#include "Sprite.h"
#include "Game.h"
#include "Events.h"
#include "ColliderArg.h"
#include <Windows.h>
#include "Box.h"
#include "Physics.h"
#include "GameObject.h"
#include "World.h"
#include "Group.h"
namespace ggEngine {
	Body::Body(Game* game,GameObject * gameObject)
	{
		this->sprite = gameObject;
		this->width = sprite->GetWidth();
		this->height = sprite->GetHeight();
		this->orgWidth = sprite->GetOrgWidth();
		this->orgHeight = sprite->GetOrgHeight();
		this->enable = true;
		this->position = &sprite->position;
		this->game = game;
		this->isAlive = true;
		this->rigidBody = nullptr;
		this->colliderDirection.resize(4);
		this->worldRect = this->game->world->GetRect();
		SetPhysicsMode(PhysicsMode_AABBSwept);
	}
	Body::~Body()
	{
		this->sprite->GetParentObject()->RemoveBodyFromList(this);
		if (this->rigidBody != nullptr) {
			delete this->rigidBody;
			this->rigidBody = nullptr;
		}
	}
	void Body::MoveLeft(double d)
	{
		if (!blocked.left) {

		}
	}
	void Body::MoveRight(double d)
	{
	}
	void Body::Jump(double d, Vector direction)
	{
	}
	void Body::RunLeft(double force)
	{
	}
	void Body::RunRight(double force)
	{
	}
	void Body::AddListCheckCollisionTo(std::list<GameObject*> staticGoList)
	{
		this->staticGoList = staticGoList;
	}
	void Body::CheckCollisionTo(GameObject * staticGo)
	{
		//collisionObjectList.push_back(staticGo);
		this->staticGoList.push_back(staticGo);
	}

	void Body::RemoveCheckCollisionWith(GameObject * staticGo)
	{
		this->staticGoList.remove(staticGo);
		//collisionObjectList.remove(std::find(collisionObjectList.begin(), collisionObjectList.end(), staticGo), collisionObjectList.end());
	}
	ColliderArg Body::GetShortestEntryTimeCollidedFromPossibleCollidedList(Box &b1,std::list<GameObject*> &possibleCollidedList)
	{
		ColliderArg shortestArg;
		shortestArg.entryTime = 1;
		GameObject* shortestGo = nullptr;
		for (auto it = possibleCollidedList.begin(); it != possibleCollidedList.end(); ++it) {
			ColliderArg e;
			Box b2 = Physics::CreateBoxFromObject(*it, Vector::Zero());
			if (GetArgIfCollided(b1, b2, e)) {
				if (e < shortestArg) {
					shortestArg = e;
					shortestGo = b2.gameObject;
				}
			}
		}
		if(shortestGo != nullptr)
			possibleCollidedList.remove(shortestGo);
		return shortestArg;
	}
	std::priority_queue<ColliderArg> Body::GetCollidedArgList(Box &b1, Vector currentVelocity)
	{
		std::priority_queue<ColliderArg> collidedList;		
		for (auto it = staticGoList.begin(); it != staticGoList.end(); ++it) {
			(*it)->body->PreUpdate();
			Box b2 = Physics::CreateBoxFromObject(*it, Vector::Zero());
			ColliderArg e;
			if (GetArgIfCollided(b1, b2, e)) {
				collidedList.push(e);
			}
		}
		for (auto it = collisionObjectList.begin(); it != collisionObjectList.end(); ++it) {
			(*it)->body->PreUpdate();
			Box b2 = Physics::CreateBoxFromObject(*it, Vector::Zero());
			ColliderArg e;
			if (GetArgIfCollided(b1, b2, e)) {
				collidedList.push(e);
			}
		}
		return collidedList;
	}
	bool Body::GetArgIfCollided(Box &b1, Box &b2, ColliderArg &e)
	{
		e.b = b2;
		if (!IsCollided(b1, b2)) return false;

		double xInvEntry, yInvEntry;
		double xInvExit, yInvExit;
		Vector normalVector;
		if (b1.vx > 0.0f) {
			xInvEntry = b2.x - (b1.x + b1.w);
			xInvExit = (b2.x + b2.w) - b1.x;
		}
		if (b1.vx < 0.0f) {
			xInvEntry = (b2.r) - b1.x;
			xInvExit = b2.x - (b1.r);
		}
		if (b1.vy > 0.0f) {
			yInvEntry = (b2.y - (b1.d));
			yInvExit = ((b2.d) - b1.y);
		}
		if (b1.vy < 0.0f) {
			yInvEntry = (b2.d) - b1.y;
			yInvExit = b2.y - (b1.d);
		}
		double xEntry, yEntry;
		double xExit, yExit;

		if (b1.vx == 0.0f) {
			xEntry = -std::numeric_limits<double>::infinity();
			xExit = std::numeric_limits<double>::infinity();
		}
		else {
			xEntry = xInvEntry / (b1.vx);
			xExit = xInvExit / (b1.vx);
		}
		if (b1.vy == 0.0f) {
			yEntry = -std::numeric_limits<double>::infinity();
			yExit = std::numeric_limits<double>::infinity();
		}
		else {
			yEntry = yInvEntry / (b1.vy);
			yExit = yInvExit / (b1.vy);
		}
		double entryTime = std::max(xEntry, yEntry);
		double exitTime = std::min(xExit, yExit);
		if (entryTime > exitTime || xEntry<0.0f&&yEntry<0.0f || xEntry>1.0f || yEntry>1.0f) {
			normalVector.x = 0.0f;
			normalVector.y = 0.0f;
			// No collision found
			return false;
		}
		//g_debug.Log("EntryTime:" + std::to_string(entryTime) + "|ExitTime:" + std::to_string(exitTime) + "|xEntry:" + std::to_string(xEntry) );
		if (xEntry > yEntry) { //Get the max because object can collide with other axis already but not collided with box yet
			if (b1.vx < 0.0f) { // b2 | b1
				e.blockDirection.left =  true;
				normalVector.x = 1.0f;
				normalVector.y = 0.0f;
			}
			else { // b1 | b2
				e.blockDirection.right =  true;
				normalVector.x = -1.0f;
				normalVector.y = 0.0f;\
			}
		}
		else {
			if (b1.vy < 0.0f) { // b2/b1
				e.blockDirection.up =  true;
				normalVector.x = 0.0f;
				normalVector.y = 1.0f;
			}
			else { // b1/b2
				e.blockDirection.down = true;
				normalVector.x = 0.0f;
				normalVector.y = -1.0f;
			}
		}

		e.bound = true;
		e.normalSurfaceVector = normalVector;
		//Handle when collision happened
		e.entryTime = entryTime;
		e.remainingTime = 1 - entryTime;
		e.colliderObject = b2.gameObject;
		e.currentVelocity = Vector(b1.vx, b1.vy);
		return true;


	}
	bool Body::CheckCollisionFromThisTo(GameObject * gameObject)
	{
		double collideTime = 1.0f;
		if (this->physicsMode == PhysicsMode_AABBSwept) {
			collideTime = PerformCollisionSweptAABB(gameObject, temp);
		}
		else if (this->physicsMode == PhysicsMode_AABB) {
			collideTime = PerformCollisionAABB(gameObject, temp);
		}
		if (collideTime < 1.0f) {
			return true;
		}
		return false;
	}
	bool Body::IsCollided(Box &b1, Box &b2)
	{
		Rect broadPhaseRect = Physics::CreateSweptBroadPhaseRect(b1);
		Rect r2 = b2.GetRect();
		return Physics::AABBCheck(broadPhaseRect, r2);
	}
	void Body::CheckCollisionAABB(std::list<GameObject*> *gameObjectList)
	{
		Rect r1 = this->rigidBody->GetRect();
		for (auto it = gameObjectList->begin(); it != gameObjectList->end(); ++it) {
			GameObject *go = (*it);
			Rect r2 = go->body->GetRect();
			Rect i;
			if (Rect::intersect(i, r1, r2)) {
				ColliderArg e;
				e.colliderObject = go;
				if (i.right - i.left > i.bottom - i.top) {
					if (r1.top < r2.top) {
						e.blockDirection.down = true;
					}
					else {
						e.blockDirection.up = true;
					}
				}
				else {
					if (r1.left < r2.left) {
						e.blockDirection.right = true;
					}
					else {
						e.blockDirection.left = true;
					}
				}
				if(this->sprite->events->onOverlap != nullptr) 
					this->sprite->events->onOverlap(this->sprite, e);
			}
		}
	}
	void Body::PreUpdate()
	{

		if (this->immoveable) {
			this->rigidBody->Transform(this->sprite->worldPosition);
			return;
		}
		this->blocked.Reset();
		this->shortestCollider.Reset();
		//position = sprite->GetPosition();
		if (this->syncBounds) {
			this->width = sprite->GetOrgWidth() * (sprite->worldScale.x);
			this->height = sprite->GetOrgHeight() * (sprite->worldScale.y);
		}
		if (this->rigidBody != nullptr) {
			this->sprite->UpdateWorldPosition();
			if(this->syncBounds) this->rigidBody->Transform(this->sprite->worldPosition, this->width, this->height);
			else this->rigidBody->Transform(this->sprite->worldPosition);
		}
	}

	Rect Body::GetRect()
	{
		Rect r(this->rigidBody->GetLeft(), this->rigidBody->GetUp(), this->rigidBody->GetRight(), this->rigidBody->GetDown());
		return r;
	}

	bool Body::PerformCollisionCheck(Vector currentVelocity, bool isReCheckWithAABB)
	{
		//currentVelocity *= PIXEL_PER_CENTIMETER;
		bool isCollided = false;
		Box b1 = Physics::CreateBoxFromObject(this->sprite, currentVelocity);
		//TO DO, box being move down so it won't recognized
		std::list<GameObject*> possibleCollidedList = GetPossibleCollidedList(b1, currentVelocity);
		if (possibleCollidedList.empty()) {
			return false;
		}
		double remainingTime = 1;
		while (!possibleCollidedList.empty() || b1.vx != 0 && b1.vy != 0) {
			ColliderArg e = GetShortestEntryTimeCollidedFromPossibleCollidedList(b1, possibleCollidedList);

			isCollided = true;
			if (e.entryTime == 1) {
				break;
			}
			/*if (e.blockDirection.down) {
				g_debug.Log("down");
			}
			if (e.blockDirection.up) {
				g_debug.Log("up");
			}
			if (e.blockDirection.right) {
				g_debug.Log("right");
			}
			if (e.blockDirection.left) {
				g_debug.Log("left");
			}
			if (!IsCollided(b1, e.b)) continue;*/
			//g_debug.Log("Received");
			bool objectBlock = false;
			if (this->sprite->events->onCheckingCollide != nullptr) {
				objectBlock = this->sprite->events->onCheckingCollide(e.b.gameObject, e);
			}
			if (e.b.gameObject->tag == 6) {
				g_debug.Log("Found canle");

				if (true) {
					g_debug.Log(currentVelocity.ToString());
				}
			}
			if (objectBlock) {
				this->rigidBody->Translate(currentVelocity*e.entryTime*remainingTime);
				//remainingTime -= e.entryTime;
				if (e.blockDirection.down) {
					currentVelocity.y = 0;
					velocity.y = 0;
				}
				if (e.blockDirection.up) {
					currentVelocity.y = 0;
					velocity.y = 0;
				}
				if (e.blockDirection.right) {
					currentVelocity.x = 0;
					velocity.x = 0;
				}
				if (e.blockDirection.left) {
					currentVelocity.x = 0;
					velocity.x = 0;
				}
				b1.vx = currentVelocity.x;
				b1.vy = currentVelocity.y;
			}
			else {
				//this->rigidBody->Translate(currentVelocity.x, currentVelocity.y);
				e.entryTime = 0;
				e.remainingTime = 1;
			}
			remainingTime -= e.entryTime*(remainingTime);
			if (this->sprite->events->onCollide != nullptr) {
				Vector pivot = this->rigidBody->GetPivotPoint();
				this->position->x = pivot.x;
				this->position->y = pivot.y;
				this->sprite->events->onCollide(this->sprite, e);
				if(this->syncBounds) this->rigidBody->Transform(this->position, sprite->GetWidth(), sprite->GetHeight());
				else {
					this->rigidBody->Transform(this->position, this->width, this->height);
				}
			}

		}

			//break;
			//if (e.remainingTime == 0) break;
		
		this->rigidBody->Translate(currentVelocity*remainingTime);
		/*if (isCollided && this->allowObjectBlock) {
			this->rigidBody->Translate(currentVelocity*remainingTime);
		}*/
		if (isReCheckWithAABB) {
			CheckCollisionAABB(&possibleCollidedList);
		}
		return isCollided;
	}

	std::list<GameObject*> Body::GetPossibleCollidedList(Box &b1, Vector currentVelocity)
	{
		std::list<GameObject*> possibleCollidedBoxList;
		Rect broadPhaseRect = Physics::CreateSweptBroadPhaseRect(b1);
		for (auto it = staticGoList.begin(); it != staticGoList.end(); ++it) {
			(*it)->body->PreUpdate();
			Box b2 = Physics::CreateBoxFromObject(*it, Vector::Zero());
			Rect result;
			if (Rect::intersect(result, broadPhaseRect, b2.GetRect())) {
				possibleCollidedBoxList.push_back(b2.gameObject);
			}
		}
		for (auto it = collisionObjectList.begin(); it != collisionObjectList.end(); ++it) {
			(*it)->body->PreUpdate();
			Box b2 = Physics::CreateBoxFromObject(*it, Vector::Zero());
			Rect result;
			if (Rect::intersect(result, broadPhaseRect, b2.GetRect())) {
				possibleCollidedBoxList.push_back(b2.gameObject);
			}
		}
		return possibleCollidedBoxList;
	}

	

	double Body::PerformCollisionSweptAABB(GameObject * staticGo, Vector currentVelocity)
	{
		staticGo->body->PreUpdate();
		Shape* staticRigiBody = staticGo->body->rigidBody;
		double xInvEntry, yInvEntry;
		double xInvExit, yInvExit;
		Vector normalVector;
		ColliderArg e;
		Box b1;
		b1.x = this->rigidBody->GetLeft();
		b1.y = this->rigidBody->GetUp();
		b1.w = this->rigidBody->GetWidth();
		b1.h = this->rigidBody->GetHeight();
		b1.r = b1.x + b1.w;
		b1.d = b1.y + b1.h;
		b1.vx = currentVelocity.x*PIXEL_PER_CENTIMETER;
		b1.vy = currentVelocity.y*PIXEL_PER_CENTIMETER;
		Box b2;
		b2.x = staticRigiBody->GetLeft();
		b2.y = staticRigiBody->GetUp();
		b2.w = staticRigiBody->GetWidth();
		b2.h = staticRigiBody->GetHeight();
		b2.r = b2.x + b2.w;
		b2.d = b2.y + b2.h;
		b2.vx = b2.vy = 0;
		if (b1.vx > 0.0f) {
			xInvEntry = b2.x - (b1.x + b1.w);
			xInvExit = (b2.x + b2.w) - b1.x;
		}
		if (b1.vx < 0.0f) {
			xInvEntry = (b2.r) - b1.x;
			xInvExit = b2.x - (b1.r);
		}
		if (b1.vy > 0.0f) {
			yInvEntry = (b2.y - (b1.d));
			yInvExit = ((b2.d) - b1.y);
		}
		if (b1.vy < 0.0f) {
			yInvEntry = (b2.d) - b1.y;
			yInvExit = b2.y - (b1.d);
		}
		//BroadPhase check
		Rect broadPhaseRect = Physics::CreateSweptBroadPhaseRect(b1);
		Rect r2 = b2.GetRect();
		if (!Physics::AABBCheck(broadPhaseRect, r2)) {
			//g_debug.Log("BroadPhaseCheck success");
			return 1.0f;
		}
		

		double xEntry, yEntry;
		double xExit, yExit;

		if (b1.vx == 0.0f) {
			xEntry = -std::numeric_limits<double>::infinity();
			xExit = std::numeric_limits<double>::infinity();
		}
		else {
			xEntry = xInvEntry / (b1.vx);
			xExit = xInvExit / (b1.vx);
		}
		if (b1.vy == 0.0f) {
			yEntry = -std::numeric_limits<double>::infinity();
			yExit = std::numeric_limits<double>::infinity();
		}
		else {
			yEntry = yInvEntry / (b1.vy);
			yExit = yInvExit / (b1.vy);
		}
		double entryTime = std::max(xEntry, yEntry);
		double exitTime = std::min(xExit, yExit);
		if (entryTime > exitTime|| xEntry<0.0f&&yEntry<0.0f || xEntry>1.0f || yEntry>1.0f) {
			normalVector.x = 0.0f;
			normalVector.y = 0.0f;
			// No collision found
			return 1.0f;
		}
		//g_debug.Log("EntryTime:" + std::to_string(entryTime) + "|ExitTime:" + std::to_string(exitTime) + "|xEntry:" + std::to_string(xEntry) );
		ColliderArgDirection direction;
		if (xEntry > yEntry) { //Get the max because object can collide with other axis already but not collided with box yet
			if (b1.vx < 0.0f) { // b2 | b1
				e.blockDirection.left = blocked.left = true;
				normalVector.x = 1.0f;
				normalVector.y = 0.0f;
				direction = Collider_Left;
			}
			else { // b1 | b2
				e.blockDirection.right = blocked.right = true;
				normalVector.x = -1.0f;
				normalVector.y = 0.0f;
				direction = Collider_Right;
			}
		}
		else {
			if (b1.vy < 0.0f) { // b2/b1
				e.blockDirection.up = blocked.up = true;
				normalVector.x = 0.0f;
				normalVector.y = 1.0f;
				direction = Collider_Up;
			}
			else { // b1/b2
				e.blockDirection.down = blocked.down = true;
				normalVector.x = 0.0f;
				normalVector.y = -1.0f;
				direction = Collider_Down;
			}
		}
		
		e.bound = true;
		e.normalSurfaceVector = normalVector;
		//Handle when collision happened
		
		
		double remainingTime = 1 - entryTime;
		e.entryTime = entryTime;
		e.remainingTime = remainingTime;
		e.colliderObject = staticGo;
		e.currentVelocity = Vector(b1.vx, b1.vy);
		this->colliderDirection[(int)direction] = e;

		if (e.entryTime < shortestCollider.entryTime) {
			shortestCollider = e;
		}


		

		return entryTime;
	}
	double Body::PerformCollisionAABB(GameObject * staticGo, Vector currentVelocity)
	{
		return 0.0;
	}
	void Body::CheckCollisionAndUpdateMovement()
	{
		if (this->immoveable) {
			return;
		}
		//Debug::Log("Current position :" + std::to_string(position->y));
		double timeStep = game->logicTimer.getDeltaTime();
		Vector lastAcceleration = acceleration;
		Vector force = (CalculateAirForce() + CalculateGravityForce());
		temp = (velocity*timeStep + (0.5*lastAcceleration*timeStep*timeStep));
		Vector newAcceleration = force / mass;
		acceleration = (lastAcceleration + newAcceleration) / 2;
		//Debug::Log("Current acceleration " + std::to_string(acceleration.y) + "|Current blocked.down:" + std::to_string(blocked.down));
		velocity += acceleration*timeStep;

		temp *= PIXEL_PER_CENTIMETER;
		switch (this->physicsMode) {
		case PhysicsMode_AABBSweptMix:
			if (PerformCollisionCheck(temp),true) break;
			this->rigidBody->Translate(temp);
			break;
		case PhysicsMode_AABBSwept:
			if (PerformCollisionCheck(temp)) break;
			this->rigidBody->Translate(temp);
			break;
		case PhysicsMode_AABB:
			this->rigidBody->Translate(temp);
			CheckCollisionAABB(&this->staticGoList);
			break;
		case PhysicsMode_None:
			this->rigidBody->Translate(temp);
			break;
		}
	/*	if (this->physicsMode == PhysicsMode_AABBSwept) {
			if (PerformCollisionCheck(temp)) return;
			this->rigidBody->Translate(temp * PIXEL_PER_CENTIMETER);
		}
		else {
			this->rigidBody->Translate(temp * PIXEL_PER_CENTIMETER);
			CheckCollisionAABB();
		}*/
	}
	void Body::UpdateBounds()
	{
		if (this->immoveable) return;
		if (allowWorldBound && CheckWorldBounds()) {
			if (worldBlocked.down) {
				if (velocity.y > 0) {
					if (allowWorldBounciness) {
						velocity.y *= -bounciness;
					}
					else if (allowWorldBlock) {
						velocity.y = 0;
						acceleration.y = 0;
					}
				}
				this->rigidBody->Translate(Vector(0, GAME_HEIGHT - this->rigidBody->GetDown()));
			}
			if (worldBlocked.up) {
				if (velocity.y < 0) {
					if (allowWorldBounciness) velocity.y *= -bounciness;
				}
				this->rigidBody->Translate(Vector(0,0 - this->rigidBody->GetUp()));
			}
			if (worldBlocked.left) {
				if (velocity.x < 0) {
					if (allowWorldBounciness) velocity.x *= -bounciness;
				}
				this->rigidBody->Translate(Vector(0 - this->rigidBody->GetLeft(), 0));
			}
			if (worldBlocked.right) {
				if (velocity.x > 0) {
					if (allowWorldBounciness) velocity.x *= -bounciness;
				}
				this->rigidBody->Translate(Vector(GAME_WIDTH - this->rigidBody->GetRight(), 0));
			}
			if (this->sprite->events->onWorldBounds != nullptr)
			{
				ColliderArg e;
				e.blockDirection = worldBlocked;
				Vector pivot = this->rigidBody->GetPivotPoint();
				this->position->x = pivot.x;
				this->position->y = pivot.y;
				this->sprite->events->onWorldBounds(sprite, e);
				if (this->syncBounds) {
					this->rigidBody->Transform(this->position, this->sprite->GetWidth(), this->sprite->GetHeight());
				}
				else {
					this->rigidBody->Transform(this->position, this->width, this->height);
				}
			}
		}
	}
	void Body::PostUpdate()
	{

		if (this->immoveable) {
			return;
		}
		Vector pivot = this->rigidBody->GetPivotPoint();
		this->position->x = pivot.x;
		this->position->y = pivot.y;
		
	}
	bool Body::CheckWorldBounds()
	{
		worldBlocked.Reset();
		bool isBlocked = false;

		/*Vector pivot = this->rigidBody->GetPivotPoint();
		double distance = Vector::Distance(pivot,Vector(GAME_WIDTH / 2, GAME_HEIGHT / 2));
		if (distance >= 400) {
			isBlocked = true;
		}
		if (isBlocked) return isBlocked;*/
		if (this->rigidBody->GetLeft() <= this->worldRect.left) {
			worldBlocked.left = true;
		}
		if (this->rigidBody->GetRight() >= this->worldRect.right ) {
			worldBlocked.right = true;
		}
		if (this->rigidBody->GetDown() >= this->worldRect.bottom ) {
			worldBlocked.down = true;
		}
		if (this->rigidBody->GetUp() <= this->worldRect.top ) {
			worldBlocked.up = true;
		}
		return worldBlocked.Any();
	}
	
	
	void Body::Render(D3DCOLOR color, bool filled)
	{
		if(this->IsEnable())
			this->game->GetDrawManager()->DrawShape(rigidBody);
	}
	
	void Body::Update()
	{
		if (!this->isActive) return;
		PreUpdate();
		CheckCollisionAndUpdateMovement();
		UpdateBounds();
		PostUpdate();
	}
	void Body::AddForce(double force, double angleInRadian)
	{
		AddForce(force, new Vector(cos(angleInRadian), sin(angleInRadian)));
	}
	void Body::AddForce(double force, Vector angleInVector)
	{
		velocity += angleInVector.Normalize() *force;
	}
	void Body::SetForce(double force, float angleInRadian)
	{
		SetForce(force, new Vector(cos(angleInRadian), sin(angleInRadian)));
	}
	void Body::SetForce(double force, Vector angleInVector)
	{
		velocity = angleInVector.Normalize() *force;
	}
	void Body::CreateCircleRigidBody(double radius)
	{
		this->rigidBody = new Circle(radius);
	}
	void Body::CreateRectangleRigidBody(double width, double height)
	{
		this->rigidBody = new Rectangle(width, height);
		this->width = width;
		this->height = height;
	}
	Vector Body::CalculateAirForce()
	{
		if (!allowAirResistance) return Vector(0, 0);
		double a = -1 * 0.5*airDensity*objectCoeffecient*CalculateArea();
		Vector air(a*velocity.x*velocity.x, a*velocity.y*velocity.y);
		return air;
	}
	Vector Body::CalculateGravityForce()
	{
		if (!allowGravity) return Vector(0, 0);
		return Vector(0,mass*gravity);
	}
	//The damping need to be calculated
	Vector Body::CalculateDampingForce()
	{
		return Vector();
	}
	double Body::CalculateArea()
	{
		return rigidBody->GetArea()/10000;
	}
}
