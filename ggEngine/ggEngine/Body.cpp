#define NOMINMAX
#include "Body.h"
#include "Sprite.h"
#include "Game.h"
#include "Events.h"
#include "ColliderArg.h"
#include <Windows.h>
#include "Physics.h"
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
		SetPhysicsMode(PhysicsMode_AABBSwept);
	}
	Body::~Body()
	{
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
		collisionObjectList.push_back(staticGo);
	}
	void Body::RemoveCheckCollisionWith(GameObject * staticGo)
	{
		collisionObjectList.erase(std::remove(collisionObjectList.begin(), collisionObjectList.end(), staticGo), collisionObjectList.end());
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
	void Body::PreUpdate()
	{
		blocked.Reset();
		//position = sprite->GetPosition();
		this->width = sprite->GetOrgWidth() * (sprite->worldScale.x);
		this->height = sprite->GetOrgHeight() * (sprite->worldScale.y);
		if (this->rigidBody != nullptr) {
			if(this->syncBounds) this->rigidBody->Transform(this->sprite->worldPosition, this->width, this->height);
			else this->rigidBody->Transform(this->sprite->worldPosition);
		}
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

		if (xEntry > yEntry) { //Get the max because object can collide with other axis already but not collided with box yet
			if (b1.vx < 0.0f) { // b2 | b1
				e.blockDirection.left = blocked.left = true;
				normalVector.x = 1.0f;
				normalVector.y = 0.0f;
			}
			else { // b1 | b2
				e.blockDirection.right = blocked.right = true;
				normalVector.x = -1.0f;
				normalVector.y = 0.0f;
			}
		}
		else {
			if (b1.vy < 0.0f) { // b2/b1
				e.blockDirection.up = blocked.up = true;
				normalVector.x = 0.0f;
				normalVector.y = 1.0f;
			}
			else { // b1/b2
				e.blockDirection.down = blocked.down = true;
				normalVector.x = 0.0f;
				normalVector.y = -1.0f;
			}
		}
		if (blocked.down) g_debug.Log("down");
		if (blocked.up) g_debug.Log("up");
		if (blocked.right) g_debug.Log("right");
		if (blocked.left) g_debug.Log("left");
		e.bound = true;
		e.normalSurfaceVector = normalVector;
		//Handle when collision happened
		if (allowObjectBlock) {
			this->rigidBody->Translate(b1.vx*entryTime, b1.vy*entryTime);
		}
		else  this->rigidBody->Translate(b1.vx, b1.vy);
		
		double remainingTime = 1 - entryTime;
		e.remainingTime = remainingTime;
		e.colliderObject = staticGo;
		
		//if (this->stopVelocityOnCollide) {
		/*if (blocked.Any()) {
			if (blocked.down) {
				if (velocity.y > 0) {
					if (allowObjectBounciness) {
						velocity.y *= -bounciness;
					}
				}
			}
			if (blocked.up) {
				if (velocity.y < 0) {
					if (allowObjectBounciness) velocity.y *= -bounciness;
				}
			}
			if (blocked.left) {
				if (velocity.x < 0) {
					if (allowObjectBounciness) velocity.x *= -bounciness;
				}
			}
			if (blocked.right) {
				if (velocity.x > 0) {
					if (allowObjectBounciness) velocity.x *= -bounciness;
				}
			}
		}*/


		if (this->sprite->events->onCollide != nullptr) {
			Vector pivot = this->rigidBody->GetPivotPoint();
			this->position->x = pivot.x;
			this->position->y = pivot.y;
			this->sprite->events->onCollide(this->sprite, e);
			this->rigidBody->Transform(this->position, sprite->GetWidth(), sprite->GetHeight());
		}

		return entryTime;
	}
	double Body::PerformCollisionAABB(GameObject * staticGo, Vector currentVelocity)
	{
		return 0.0;
	}
	void Body::CheckCollisionAndUpdateMovement()
	{
		//Debug::Log("Current position :" + std::to_string(position->y));
		double timeStep = game->logicTimer.getDeltaTime();
		Vector lastAcceleration = acceleration;
		Vector force = (CalculateAirForce() + CalculateGravityForce());
		temp = (velocity*timeStep + (0.5*lastAcceleration*timeStep*timeStep));
		Vector newAcceleration = force / mass;
		acceleration = (lastAcceleration + newAcceleration) / 2;
		//Debug::Log("Current acceleration " + std::to_string(acceleration.y) + "|Current blocked.down:" + std::to_string(blocked.down));
		velocity += acceleration*timeStep;
		bool isCollided = false;
		if (this->physicsMode == PhysicsMode_AABB) {
			this->rigidBody->Translate(temp * PIXEL_PER_CENTIMETER);
		}
		for (auto it = staticGoList.begin(); it != staticGoList.end(); ++it) {
			if (isCollided) break;
			isCollided = CheckCollisionFromThisTo(*it) || isCollided;
			//if (isCollided) g_debug.Log("Collision found with " + std::to_string((*it)->position.x)+ "-"+ std::to_string((*it)->position.y));
		}
		for (auto it = collisionObjectList.begin(); it != collisionObjectList.end(); ++it) {
			if (isCollided) break;
			isCollided = CheckCollisionFromThisTo((*it)) || isCollided;
		}
		if (isCollided) {
			if (allowObjectBlock) {
				/*if (blocked.up&&temp.y < 0 || blocked.down) {
					temp.y = 0;
					velocity.y = 0;
					acceleration.y = 0;
				}
				if (blocked.left || blocked.right) {
					temp.x = 0;
					velocity.x = 0;
					acceleration.x = 0;
				}*/
			}
			
			return;
		}
		if (this->physicsMode == PhysicsMode_AABBSwept) {
			this->rigidBody->Translate(temp * PIXEL_PER_CENTIMETER);
		}
	}
	void Body::UpdateBounds()
	{
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
				e.blockDirection = blocked;
				Vector pivot = this->rigidBody->GetPivotPoint();
				this->position->x = pivot.x;
				this->position->y = pivot.y;
				this->sprite->events->onWorldBounds(sprite, e);
				this->rigidBody->Transform(this->position, sprite->GetWidth(), sprite->GetHeight());
			}
		}
	}
	void Body::PostUpdate()
	{
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
		if (this->rigidBody->GetLeft() <= 0) {
			worldBlocked.left = true;
		}
		if (this->rigidBody->GetRight() >= GAME_WIDTH ) {
			worldBlocked.right = true;
		}
		if (this->rigidBody->GetDown() >= GAME_HEIGHT ) {
			worldBlocked.down = true;
		}
		if (this->rigidBody->GetUp() <= 0 ) {
			worldBlocked.up = true;
		}
		return worldBlocked.Any();
	}
	
	void Body::Destroy()
	{
		isAlive = false;
	}
	void Body::Render(D3DCOLOR color, bool filled)
	{
		this->game->GetDrawManager()->DrawShape(rigidBody);
	}
	
	void Body::Update()
	{
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
