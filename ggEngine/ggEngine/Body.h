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
	class Sprite;
	class Game;
	class Body :GGObject {
	public:
		Body(Game *game,Sprite *sprite);
		~Body();
		void CheckCollisionTo(GameObject *staticGo);
		void RemoveCheckCollisionWith(GameObject *staticGo);
		int width;
		int height;
		int orgWidth;
		int orgHeight;
		double rotation = 0;
		double preRotation;
		Shape* rigidBody;
		bool syncBounce = true;
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
		bool allowBounciness = true;
		bool allowWorldBlock = true;


		Vector velocity;
		Vector newVelocity;
		Vector deltaMax;
		Vector acceleration;
		Vector drag;
		Vector bound;
		Vector worldBounce;
		Vector maxVelocity;
		Vector friction;
		double offsetX = 0;
		double offsetY = 0;
		double angularVelocity = 0;
		double angularAcceleration = 0;
		double angularDrag = 0;
		double maxAngular = 0;
		double angle = 0;
		double speed = 0;
		bool immovable = false;
		bool moves = true;
		bool customSeperateX = false;
		bool customeSeperateY = false;
		bool embedded = false;
		bool collideWorldBounds = false;
		Game* game;
		Sprite* sprite;
		Vector *position;
		Direction checkCollision;
		Direction touching ;
		Direction wasTouching;
		Direction blocked;
		bool enable = true;
		bool dirty = false;
		bool syncBounds = false;
		bool isMoving = false;
		bool stopVelocityOnCollide = true;
		int moveTimer = 0;
		int moveDistance = 0;
		int moveDuration = 0;
		void IncrementForce(double force);
		//TO DO: put a moveTarger here
		Vector moveEnd;
		GGObject *movementCallbackContext;
		//Public method 
		void StopMovement(bool stopVelocity);
		bool CheckWorldBounds();
		bool MoveTo(int duration, int distance, int directionAngle);
		void SetSize(int width, int height, int offsetX, int offsetY);
		void Reset(Vector newPosition);
		Body* GetBounds(Body *obj);
		bool HitTest(Vector position);
		bool OnFloor();
		bool OnCeiling();
		bool OnWall();
		void Destroy();
		void Render(D3DCOLOR color = DEFAULT_COLOR, bool filled = false);
		std::string ToString();
		void Update();
		bool IsAlive() { return this->isAlive; }
		void AddForce(double force, double angleInRadian);
		void AddForce(double force, Vector angleInVector);
		void CreateCircleRigidBody(double radius);
		void CreateRectangleRigidBody(double width, double height);
	private:
		std::vector<GameObject*> collisionObjectList;
		Vector CalculateAirForce();
		Vector CalculateGravityForce();
		Vector CalculateDampingForce();
		double CalculateArea();
		double PerformCollisionSweptAABB(GameObject *staticGo,Vector currentVelocity);
		void UpdateBounds();
		void PreUpdate();
		void CheckCollisionAndUpdateMovement();
		void PostUpdate();
		bool isAlive;
	};
}