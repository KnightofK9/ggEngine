#pragma once
#include "GGObject.h"
#include <d3d9.h>
#include "Vector.h"
#include <cmath>
#include "ConstantEnum.h"
#include <string>
#include "Rectangle.h"
#include <functional>
#include "Circle.h"
#include "Direction.h"
#include <vector>
#include "GameObject.h"
#include <algorithm>
namespace ggEngine {
	enum ColliderArgDirection { Collider_Left = 0, Collider_Up, Collider_Right, Collider_Down };
	class Sprite;
	class Game;
	class Body :GGObject {
	public:
		Body(Game *game, GameObject * gameObject);
		~Body();
		int width;
		int height;
		int orgWidth;
		int orgHeight;
		Shape* rigidBody;
		//Force modifier
		/*Air*/
		double airDensity = 0.1;
		double objectCoeffecient = 0.47;
		bool allowAirResistance = false;
		/*Gravity*/
		double mass = 0.4;
		double gravity = 9.81;
		bool allowGravity = false;
		/*Vicious damping*/
		double dampingCoeffecient = 0.4;
		double alphaAngle = 0;
		bool allowDamping = true;
		/*Rotation*/

		/*Vector Force*/
		double bounciness = 1;

		bool allowWorldBounciness = true;
		bool allowWorldBlock = true;

		bool allowWorldBound = true;

		bool allowObjectBounciness = false;

		bool allowObjectBlock = true;

		GameObject* sprite;
		Vector *position;
		Direction blocked;
		Direction worldBlocked;
		bool syncBounds = true;
		bool isMoving = false;
		Vector velocity;
		//Public method 
		//TO DO, choose velocity or distance here
		void MoveLeft(double d);
		void MoveRight(double d);
		void Jump(double d,Vector direction = Vector(0,-1));

		void RunLeft(double force);
		void RunRight(double force);

		void Render(D3DCOLOR color = DEFAULT_COLOR, bool filled = false);
		void Update();
		void Destroy();
		bool IsAlive() { return this->isAlive; }

		void AddForce(double force, double angleInRadian);
		void AddForce(double force, Vector angleInVector);
		void SetForce(double force, float angleInRadian);
		void SetForce(double force, Vector angleInVector);

		void CreateCircleRigidBody(double radius);
		void CreateRectangleRigidBody(double width, double height);
		void SetPhysicsMode(PhysicsMode physicsMode) { this->physicsMode = physicsMode; }
		PhysicsMode GetPhysicsMode() { return this->physicsMode; }
		void SetEnable(bool enable) { this->enable = enable; }
		bool IsEnable() { return this->enable; }
		void AddListCheckCollisionTo(std::list<GameObject*> staticGoList);
		void CheckCollisionTo(GameObject *staticGo);
		void RemoveCheckCollisionWith(GameObject *staticGo);
		void PreUpdate();
	private:
		std::vector<ColliderArg> colliderDirection;
		ColliderArg shortestCollider;
		bool CheckCollisionFromThisTo(GameObject* gameObject);
		bool enable = true;
		PhysicsMode physicsMode;
		Game* game;
		bool CheckWorldBounds();
		Vector acceleration;
		Vector temp;
		std::list<GameObject*> staticGoList;
		std::vector<GameObject*> collisionObjectList;
		Vector CalculateAirForce();
		Vector CalculateGravityForce();
		Vector CalculateDampingForce();
		double CalculateArea();
		double PerformCollisionSweptAABB(GameObject *staticGo,Vector currentVelocity);
		double PerformCollisionAABB(GameObject *staticGo, Vector currentVelocity);
		void UpdateBounds();
		void CheckCollisionAndUpdateMovement();
		void PostUpdate();
		bool isAlive;
	};
}