#define NOMINMAX
#include "Body.h"
#include "Sprite.h"
#include "Game.h"
#include "Events.h"
#include "ColliderArg.h"
#include <Windows.h>
#include "Physics.h"
namespace ggEngine {
	Body::Body(Game* game,Sprite * sprite)
	{
		this->sprite = sprite;
		this->width = sprite->GetWidth();
		this->height = sprite->GetHeight();
		this->orgWidth = sprite->GetImage()->GetWidth();
		this->orgHeight = sprite->GetImage()->GetHeight();
		this->enable = true;
		this->position = &sprite->position;
		this->game = game;
		this->isAlive = true;
		this->rigidBody = NULL;

	}
	Body::~Body()
	{
		delete rigidBody;
	}
	void Body::CheckCollisionTo(GameObject * staticGo)
	{
		collisionObjectList.push_back(staticGo);
	}
	void Body::RemoveCheckCollisionWith(GameObject * staticGo)
	{
		collisionObjectList.erase(std::remove(collisionObjectList.begin(), collisionObjectList.end(), staticGo), collisionObjectList.end());
	}
	void Body::StopMovement(bool stopVelocity)
	{
	}
	void Body::PreUpdate()
	{
		//position = sprite->GetPosition();
		this->width = sprite->GetWidth();
		this->height = sprite->GetHeight();
		if (this->rigidBody != nullptr) {
			this->rigidBody->Transform(this->position, this->width, this->height);
		}
	}

	double Body::PerformCollisionSweptAABB(GameObject * staticGo, Vector currentVelocity)
	{
		staticGo->body->rigidBody->Transform(staticGo->GetPosition(),staticGo->GetWidth(),staticGo->GetHeight());
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
		RECT broadPhaseRect = Physics::CreateSweptBroadPhaseRect(b1);
		RECT r2 = b2.GetRect();
		if (!Physics::AABBCheck(broadPhaseRect, r2)) {
			//g_debug.Log("BroadPhaseCheck success");
			if (staticGo->name == "Right Bat") {
				int i = 1;
			}
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
			if (staticGo->name == "Right Bat") {
				int i = 1;
			}
			return 1.0f;
		}
		//g_debug.Log("EntryTime:" + std::to_string(entryTime) + "|ExitTime:" + std::to_string(exitTime) + "|xEntry:" + std::to_string(xEntry) );

		if (xEntry > yEntry) { //Get the max because object can collide with other axis already but not collided with box yet
			if (b1.vx < 0.0f) { // b2 | b1
				e.blockDirection.left = true;
				normalVector.x = 1.0f;
				normalVector.y = 0.0f;
			}
			else { // b1 | b2
				e.blockDirection.right = true;
				normalVector.x = -1.0f;
				normalVector.y = 0.0f;
			}
		}
		else {
			if (b1.vy < 0.0f) { // b2/b1
				e.blockDirection.up = true;
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
		/*position->x += b1.vx*entryTime;
		position->y += b1.vy*entryTime;*/

		this->rigidBody->Translate(b1.vx*entryTime, b1.vy*entryTime);
		
		double remainingTime = 1 - entryTime;
		e.remainingTime = remainingTime;
		e.colliderObject = staticGo;
		
		event = e;
		if (this->sprite->events->onCollide != nullptr) {
			Vector pivot = this->rigidBody->GetPivotPoint();
			this->position->x = pivot.x;
			this->position->y = pivot.y;
			this->sprite->events->onCollide(this->sprite, event);
			this->rigidBody->Transform(this->position, sprite->GetWidth(), sprite->GetHeight());
		}

		return entryTime;
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
		if (blocked.down && allowWorldBlock) acceleration.y = 0;
		//Debug::Log("Current acceleration " + std::to_string(acceleration.y) + "|Current blocked.down:" + std::to_string(blocked.down));
		velocity += acceleration*timeStep;
		bool isCollided = false;
		for (std::vector<GameObject*>::iterator it = collisionObjectList.begin(); it != collisionObjectList.end(); ++it) {
			double collideTime = PerformCollisionSweptAABB((*it),temp);
			if (collideTime < 1.0f) {
				isCollided = true;
				isCollideWithObject = true;
				break;
			}
		}
		if (isCollided) {
			return;
		}
		this->rigidBody->Translate(temp * PIXEL_PER_CENTIMETER);
		/*(*position) += temp * PIXEL_PER_CENTIMETER;*/
	}
	void Body::UpdateBounds()
	{
		if (CheckWorldBounds()) {
			/*double width, height;
			width = rigidBody->GetWidth();
			height = rigidBody->GetHeight();
			Vector pivot = this->rigidBody->GetPivotPoint();*/
			this->isCollideWithWorld = true;
			if (blocked.down) {
				//Debug::Log("Meet world with " + std::to_string(velocity.y));
				if (velocity.y > 0) {
					if (allowBounciness) {
						velocity.y *= -bounciness;
					}
					else if (allowWorldBlock) {
						velocity.y = 0;
						acceleration.y = 0;
					}
				}
				//position->y = pivot.y;
				this->rigidBody->Translate(Vector(0, GAME_HEIGHT - this->rigidBody->GetDown()));
			}
			if (blocked.up) {
				if (velocity.y < 0) {
					if (allowBounciness) velocity.y *= -bounciness;
				}
				//position->y = pivot.y;
				this->rigidBody->Translate(Vector(0,0 - this->rigidBody->GetUp()));
			}
			if (blocked.left) {
				if (velocity.x < 0) {
					if (allowBounciness) velocity.x *= -bounciness;
				}
				//position->x = pivot.x;
				this->rigidBody->Translate(Vector(0 - this->rigidBody->GetLeft(), 0));
			}
			if (blocked.right) {
				if (velocity.x > 0) {
					if (allowBounciness) velocity.x *= -bounciness;
				}
				//position->x = pivot.x;
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
		//sprite->SetPosition(position);
		/*if (this->rigidBody != nullptr) {
			this->rigidBody->Transform(this->position);
		}*/
		Vector pivot = this->rigidBody->GetPivotPoint();
		this->position->x = pivot.x;
		this->position->y = pivot.y;
		
		
		if (isCollideWithObject) {
			
			isCollideWithObject = false;
		
		}
		else {
			if (isCollideWithWorld) {
				
				isCollideWithWorld = false;
			}
		}
	}
	bool Body::CheckWorldBounds()
	{
		blocked.Reset();
		bool isBlocked = false;

		/*Vector pivot = this->rigidBody->GetPivotPoint();
		double distance = Vector::Distance(pivot,Vector(GAME_WIDTH / 2, GAME_HEIGHT / 2));
		if (distance >= 400) {
			isBlocked = true;
		}
		if (isBlocked) return isBlocked;*/
		if (this->rigidBody->GetLeft() <= 0) {
			isBlocked = blocked.left = true;
		}
		if (this->rigidBody->GetRight() >= GAME_WIDTH ) {
			isBlocked = blocked.right = true;
		}
		if (this->rigidBody->GetDown() >= GAME_HEIGHT ) {
			isBlocked = blocked.down = true;
		}
		if (this->rigidBody->GetUp() <= 0 ) {
			isBlocked = blocked.up = true;
		}
		return isBlocked;
	}
	bool Body::MoveTo(int duration, int distance, int directionAngle)
	{
		return false;
	}
	void Body::SetSize(int width, int height, int offsetX, int offsetY)
	{
	}
	void Body::Reset(Vector newPosition)
	{
	}
	Body * Body::GetBounds(Body * obj)
	{
		return nullptr;
	}
	bool Body::HitTest(Vector position)
	{
		return false;
	}
	bool Body::OnFloor()
	{
		return false;
	}
	bool Body::OnCeiling()
	{
		return false;
	}
	bool Body::OnWall()
	{
		return false;
	}
	void Body::Destroy()
	{
		isAlive = false;
	}
	void Body::Render(D3DCOLOR color, bool filled)
	{
		this->game->GetDrawManager()->DrawShape(rigidBody);
	}
	std::string Body::ToString()
	{
		return std::string();
	}
	void Body::Update()
	{
		PreUpdate();
		CheckCollisionAndUpdateMovement();
		UpdateBounds();
		PostUpdate();
	}
	//Wrong, try to re-implemented it
	void Body::IncrementForce(double force)
	{
		int signX = 1;
		int signY = 1;
		if (velocity.x < 0) signX = -1;
		if (velocity.y < 0) signY = -1;
		AddForce(force, Vector(signX, signY));
	}
	void Body::AddForce(double force, double angleInRadian)
	{
		AddForce(force, new Vector(cos(angleInRadian), sin(angleInRadian)));
	}
	void Body::AddForce(double force, Vector angleInVector)
	{
		velocity += angleInVector.Normalize() *force;
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
