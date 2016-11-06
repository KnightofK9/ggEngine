#include "TestState.h"
#include "Audio.h"

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
	this->preload->Font("sketches 90px","sketches", "Resource/Font/sketches.ttf", 90);
}
void TestState::Create()
{
	
	tileMap = this->add->TileMap("Json/scene.json");
	tileMap->name = "TileMap";
	tileMap->SetScale(2, 2);

	group = this->add->Group();
	// Text
	Style style;
	style.fontColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	//style.fontColor = D3DCOLOR_ARGB(255,120, 180, 210);
	text = this->add->Text(GAME_WIDTH / 2.0, GAME_HEIGHT / 2.0, "sketches 90px", 200, 200, "TEST STATE", style, group);
	text->SetAnchor(0.5, 0.5);


	sound = this->add->Audio("Resource/Sound/sound.wav");
	

	character = this->add->SpriteAnimation(GAME_WIDTH / 2.0, GAME_HEIGHT / 2.0, "character", 32, 48, group,0,0,1000/10);
	character->CreateAnimation("down", 0, 3, true);
	character->CreateAnimation("left", 4, 7, true);
	character->CreateAnimation("right", 8, 11, true);
	character->CreateAnimation("up", 12, 15, true);
	character->SetAnchor(0, 0);
	game->physics->EnablePhysics(character);
	character->body->CreateRectangleRigidBody(32, 48);
	character->body->rigidBody->SetAnchor(0, 0);
	character->body->allowGravity = true;
	character->body->allowWorldBounciness = false;
	character->body->allowWorldBlock = true;
	character->body->allowObjectBlock = false;
	game->eventManager->EnableKeyBoardInput(character);
	jumpTimer.reset();
	character->SetScale(1.5, 1.5);
	character->events->onKeyPress = [this](GameObject *go, KeyBoardEventArg e) {
		SpriteAnimation  *current = dynamic_cast<SpriteAnimation*>(go);
		if (current != NULL) {
			double time = game->logicTimer.getDeltaTime();
			double force = charMoveSpeed* time;
			double currentJumpForce = jumpForce*time;
			if (e.isPress(DIK_A)) {
				character->PlayAnimation("left");
				character->body->velocity.x = - force;
			}
			else if (e.isPress(DIK_D)) {
				character->PlayAnimation("right");
				character->body->velocity.x = force;
			}
			if (e.isPress(DIK_SPACE)) {
				if (jumpTimer.stopwatch(jumpTime)) {
					character->body->velocity.y = -currentJumpForce;
				}
			}	
		}
	};
	character->events->onWorldBounds = [this](GameObject *go, ColliderArg e) {
		SpriteAnimation  *current = dynamic_cast<SpriteAnimation*>(go);
		if (current != NULL) {

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
	///Test
	
	if (this->game->GetInput()->KeyDown(DIK_P))
		sound->Play();
	if (this->game->GetInput()->KeyDown(DIK_S))
		sound->Stop();
	if (this->game->GetInput()->KeyDown(DIK_E))
		sound->Pause();
	if (this->game->GetInput()->KeyDown(DIK_R))
		sound->Resume();
	if (this->game->GetInput()->KeyDown(DIK_V))
		sound->FadeTo(30);
}
void TestState::PreRender()
{
}
void TestState::Render()
{
	character->body->Render();
	auto list = this->tileMap->GetCollisionCheckList();
	for (auto it = list.begin(); it != list.end(); ++it) {
		(*it)->body->Render();
	}
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

