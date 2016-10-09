#define NOMINMAX
#include "Body.h"
#include "Sprite.h"
#include "Game.h"
#include "Events.h"
#include "ColliderArg.h"
#include "Box.h"
#include <Windows.h>
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
		width = sprite->GetWidth();
		height = sprite->GetHeight();
	}

	float Body::PerformCollisionSweptAABB(GameObject * staticGo)
	{
		Rectangle *rect1 = dynamic_cast<Rectangle*>(this->rigidBody);
		Rectangle *rect2 = dynamic_cast<Rectangle*>(staticGo->body->rigidBody);
		if (!rect1->isReady || !rect2->isReady) return 1.0f;
		float xInvEntry, yInvEntry;
		float xInvExit, yInvExit;
		Vector normalVector;
		ColliderArg e;
		Box b1;
		b1.x = rect1->p1.x;
		b1.y = rect1->p1.y;
		b1.w = rect1->width;;
		b1.h = rect1->height;
		b1.vx = velocity.x;
		b1.vy = velocity.y;
		Box b2;
		b2.x = rect2->p1.x;
		b2.y = rect2->p1.y;
		b2.w = rect2->width;
		b2.h = rect2->height;
		b2.vx = b2.vy = 0;
		//b1 is moving right
		if (b1.vx > 0.0f) { 
			xInvEntry = b2.x - (b1.x + b1.w); //Shortest x distance
			xInvExit = (b2.x + b2.w) - b1.x; //Longest x distance
		}
		//b1 is moving left
		else { 
			xInvEntry = (b2.x + b2.w) - b1.x;
			xInvExit = b2.x - (b1.x + b1.w);
		}
		//b1 is moving down
		if (b1.vy > 0.0f) { 
			yInvEntry = b2.y - (b1.x + b1.h);
			yInvExit = (b2.y + b2.h) - b1.y;
		}
		//b1 is moving up
		else {
			yInvEntry = (b2.y + b2.h) - b1.y;
			yInvExit = b2.y - (b1.y + b1.h);
		}

		float xEntry, yEntry;
		float xExit, yExit;

		if (b1.vx == 0.0f) {
			xEntry = -std::numeric_limits<float>::infinity();
			xExit = std::numeric_limits<float>::infinity();
		}
		else {
			xEntry = xInvEntry / b1.vx;
			xExit = xInvExit / b1.vx;
		}
		if (b1.vy == 0.0f) {
			yEntry = -std::numeric_limits<float>::infinity();
			yExit = std::numeric_limits<float>::infinity();
		}
		else {
			yEntry = yInvEntry / b1.vy;
			yExit = yInvExit / b1.vy;
		}
		float entryTime = std::max(xEntry, yEntry);
		float exitTime = std::min(xExit, yExit);
		if (entryTime > exitTime || xEntry<0.0f&&yEntry<0.0f || xEntry>1.0f || yEntry>1.0f) {
			normalVector.x = 0.0f;
			normalVector.y = 0.0f;
			// No collision found
			return 1.0f;
		}
		else {
			if (xEntry > yEntry) { //Get the max because object can collide with other axis already but not collided with box yet
				if (xInvEntry < 0.0f) { // b2 | b1
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
				if (yInvEntry < 0.0f) { // b2/b1
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
		}
		e.bound = true;
		e.normalSurfaceVector = normalVector;
		//Handle when collision happened
		position->x += velocity.x*entryTime;
		position->y += velocity.y*entryTime;

		float remainingTime = 1 - entryTime;
		e.remainingTime = remainingTime;
		if (this->sprite->events->onCollide != nullptr) this->sprite->events->onCollide(this->sprite, e);

		return entryTime;
	}
	void Body::CheckCollisionAndUpdateMovement()
	{
		bool isCollided = false;
		for (std::vector<GameObject*>::iterator it = collisionObjectList.begin(); it != collisionObjectList.end(); ++it) {
			float collideTime = PerformCollisionSweptAABB((*it));
			if (collideTime < 1.0f) {
				isCollided = true;
				break;
			}
		}
		if (isCollided) {
			return;
		}
		//Debug::Log("Current position :" + std::to_string(position->y));
		float timeStep = game->logicTimer.getDeltaTime();
		Vector lastAcceleration = acceleration;
		Vector force = (CalculateAirForce() + CalculateGravityForce());
		Vector temp = (velocity*timeStep + (0.5*lastAcceleration*timeStep*timeStep));
		(*position) += temp * 100;
		Vector newAcceleration = force / mass;
		acceleration = (lastAcceleration + newAcceleration) / 2;
		if (blocked.down && allowWorldBlock) acceleration.y = 0;
		//Debug::Log("Current acceleration " + std::to_string(acceleration.y) + "|Current blocked.down:" + std::to_string(blocked.down));
		velocity += acceleration*timeStep;
	}
	void Body::UpdateBounds()
	{
		if (CheckWorldBounds()) {
			Rectangle* rect = dynamic_cast<Rectangle*>(rigidBody);
			float width, height;
			width = height = 0;
			if (rect != NULL) {
				width = rect->width;
				height = rect->height;
			}
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
				position->y = WINDOW_HEIGHT - height / 2;
			}
			if (blocked.up) {
				if (velocity.y < 0) {
					if (allowBounciness) velocity.y *= -bounciness;
				}
				position->y = height / 2;
			}
			if (blocked.left) {
				if (velocity.x < 0) {
					if (allowBounciness) velocity.x *= -bounciness;
				}
				position->x = width / 2;
			}
			if (blocked.right) {
				if (velocity.x > 0) {
					if (allowBounciness) velocity.x *= -bounciness;
				}
				position->x = WINDOW_WIDTH - width / 2;
			}
			if (this->sprite->events->onWorldBounds != nullptr)
			{
				ColliderArg e;
				e.blockDirection = blocked;
				this->sprite->events->onWorldBounds(sprite, e);
			}
		}
	}
	void Body::PostUpdate()
	{
		//sprite->SetPosition(position);
	}
	bool Body::CheckWorldBounds()
	{
		blocked.Reset();
		bool isBlocked = false;
		if (position->x - width/2 <= 0) {
			isBlocked = blocked.left = true;
		}
		if (position->x + width/2 >= WINDOW_WIDTH) {
			isBlocked = blocked.right = true;
		}
		if (position->y + height/2 >= WINDOW_HEIGHT) {
			isBlocked = blocked.down = true;
		}
		if (position->y - height/2 <= 0) {
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
	void Body::IncrementForce(float force)
	{
		int signX = 1;
		int signY = 1;
		if (velocity.x < 0) signX = -1;
		if (velocity.y < 0) signY = -1;
		AddForce(force, Vector(signX, signY));
	}
	void Body::AddForce(float force, float angleInRadian)
	{
	}
	void Body::AddForce(float force, Vector angleInVector)
	{
		velocity += angleInVector.Normalize() *force;
	}
	void Body::CreateCircleRigidBody(float radius)
	{
		this->rigidBody = new Circle(radius);
	}
	void Body::CreateRectangleRigidBody(float width, float height)
	{
		this->rigidBody = new Rectangle(width, height);
	}
	Vector Body::CalculateAirForce()
	{
		if (!allowAirResistance) return Vector(0, 0);
		float a = -1 * 0.5*airDensity*objectCoeffecient*CalculateArea();
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
	float Body::CalculateArea()
	{
		return rigidBody->GetArea()/10000;
	}
}
