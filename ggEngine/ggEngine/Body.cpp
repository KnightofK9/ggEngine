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
		width = sprite->GetWidth();
		height = sprite->GetHeight();
	}

	double Body::PerformCollisionSweptAABB(GameObject * staticGo, Vector currentVelocity)
	{
		Rectangle *rect1 = dynamic_cast<Rectangle*>(this->rigidBody);
		Rectangle *rect2 = dynamic_cast<Rectangle*>(staticGo->body->rigidBody);
		double xInvEntry, yInvEntry;
		double xInvExit, yInvExit;
		Vector normalVector;
		ColliderArg e;
		Box b1;
		b1.x = rect1->p1.x;
		b1.y = rect1->p1.y;
		b1.w = rect1->p3.x-rect1->p1.x;
		b1.h = rect1->p3.y-rect1->p1.y;
		b1.vx = currentVelocity.x*PIXEL_PER_CENTIMETER;
		b1.vy = currentVelocity.y*PIXEL_PER_CENTIMETER;
		Box b2;
		b2.x = rect2->p1.x;
		b2.y = rect2->p1.y;
		b2.w = rect2->p3.x-rect2->p1.x;
		b2.h = rect2->p3.y-rect2->p1.y;
		b2.vx = b2.vy = 0;
		if (b1.vx > 0.0f) {
			xInvEntry = b2.x - (b1.x + b1.w);
			xInvExit = (b2.x + b2.w) - b1.x;
		}
		if (b1.vx < 0.0f) {
			if(b2.x > (b1.x + b1.w)) return 1.0f;
			xInvEntry = (b2.x + b2.w) - b1.x;
			xInvExit = b2.x - (b1.x + b1.w);
		}
		if (b1.vy > 0.0f) {
			yInvEntry = (b2.y - (b1.y + b1.h));
			yInvExit = ((b2.y + b2.h) - b1.y);
		}
		if (b1.vy < 0.0f) {
			yInvEntry = b1.y - (b2.y + b2.h);
			yInvExit = (b1.y + b1.h) - b2.y;
		}
		//BroadPhase check
		RECT broadPhaseRect = Physics::CreateSweptBroadPhaseRect(b1);
		RECT r2 = b2.GetRect();
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
		position->x += b1.vx*entryTime;
		position->y += b1.vy*entryTime;

		double remainingTime = 1 - entryTime;
		e.remainingTime = remainingTime;
		e.colliderObject = staticGo;
		if (this->sprite->events->onCollide != nullptr) this->sprite->events->onCollide(this->sprite, e);

		return entryTime;
	}
	void Body::CheckCollisionAndUpdateMovement()
	{
		if (!this->rigidBody->IsReady()) return;
		//Debug::Log("Current position :" + std::to_string(position->y));
		double timeStep = game->logicTimer.getDeltaTime();
		Vector lastAcceleration = acceleration;
		Vector force = (CalculateAirForce() + CalculateGravityForce());
		Vector temp = (velocity*timeStep + (0.5*lastAcceleration*timeStep*timeStep));
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
				break;
			}
		}
		if (isCollided) {
			return;
		}

		(*position) += temp * PIXEL_PER_CENTIMETER;
	}
	void Body::UpdateBounds()
	{
		if (CheckWorldBounds()) {
			Rectangle* rect = dynamic_cast<Rectangle*>(rigidBody);
			double width, height;
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
				position->y = WINDOW_HEIGHT  - sprite->GetHeight()*sprite->GetAnchor().y;
			}
			if (blocked.up) {
				if (velocity.y < 0) {
					if (allowBounciness) velocity.y *= -bounciness;
				}
				position->y = sprite->GetHeight()*sprite->GetAnchor().y;
			}
			if (blocked.left) {
				if (velocity.x < 0) {
					if (allowBounciness) velocity.x *= -bounciness;
				}
				position->x = sprite->GetWidth()*sprite->GetAnchor().x;
			}
			if (blocked.right) {
				if (velocity.x > 0) {
					if (allowBounciness) velocity.x *= -bounciness;
				}
				position->x = WINDOW_WIDTH - sprite->GetWidth()*sprite->GetAnchor().x;
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
