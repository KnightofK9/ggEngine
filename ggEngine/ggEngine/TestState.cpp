#include "TestState.h"
SpriteAnimation *character;
Group *group;
const double charMoveSpeed = 10.0f;
const double jumpForce = 5.0f;
const double jumpTime = 500;
TileMap *tileMap;
Grid *grid;
Timer jumpTimer;
TestState::TestState(Game *game):State(game)
{
}
TestState::~TestState()
{
}
void TestState::Init(){

}
void TestState::Preload(){
	this->preload->Texture("character", "Resource/char.png");
	this->preload->TileSet("Resource/scene1.png", "Resource/scene1.json");
}
void TestState::Create()
{
	tileMap = this->add->TileMap("Json/scene.json");
	group = this->add->Group();

	character = this->add->SpriteAnimation(GAME_WIDTH / 2.0, GAME_HEIGHT / 2.0, "character", 32, 48, group,0,0,1000/10);
	character->CreateAnimation("down", 0, 3, true);
	character->CreateAnimation("left", 4, 7, true);
	character->CreateAnimation("right", 8, 11, true);
	character->CreateAnimation("up", 12, 15, true);
	game->physics->EnablePhysics(character);
	character->body->CreateRectangleRigidBody(32, 48);
	character->body->allowGravity = true;
	character->body->allowBounciness = false;
	character->body->allowWorldBlock = true;
	game->eventManager->EnableKeyBoardInput(character);
	jumpTimer.reset();
	character->SetScale(1.5, 1.5);
	character->events->onKeyPress = [this](GameObject *go, KeyBoardEventArg e) {
		SpriteAnimation  *current = dynamic_cast<SpriteAnimation*>(go);
		if (current != NULL) {
			double time = game->logicTimer.getDeltaTime();
			if (e.isPress(DIK_A)) {
				character->PlayAnimation("left");
				if (character->body->velocity.x > 0) character->body->velocity.x = 0;
				character->body->velocity.x -= charMoveSpeed* time;
			}
			else if (e.isPress(DIK_D)) {
				character->PlayAnimation("right");
				if (character->body->velocity.x < 0) character->body->velocity.x = 0;
				character->body->velocity.x += charMoveSpeed*time;
			}
			if (e.isPress(DIK_SPACE)) {
				if (jumpTimer.stopwatch(jumpTime)) {
					character->body->velocity.y = 0;
					character->body->AddForce(jumpForce, Vector(0, -1));
				}

			}
		}
	};
	//grid = this->add->Grid(0, 0, 10, 10, GAME_WIDTH, GAME_HEIGHT, group);
	Box box(1, 2, 3, 4, 5, 6);
	box.SaveJsonTo("Json/box.json");
	//box.ParseJson("Json/box.json");
	//std::ofstream ofs("box_backup");
	//{
	//	boost::archive::text_oarchive oa(ofs);
	//	// write class instance to archive
	//	oa << box;
	//	// archive and stream closed when destructors are called
	//}

	//box = new Box(0, 0, 0, 0, 0, 0);
	//{
	//	// create and open an archive for input
	//	std::ifstream ifs("box_backup");
	//	boost::archive::text_iarchive ia(ifs);
	//	// read class state from archive
	//	ia >> box;
	//	// archive and stream closed when destructors are called
	//}
}
void TestState::Update()
{
	
}
void TestState::PreRender()
{
}
void TestState::Render()
{
	character->body->Render();
	

}
void TestState::Pause()
{
}
void TestState::Resume()
{
}
void TestState::ShutDown()
{

}

