#include "CVAdd.h"
#include "TextureConstant.h"
#include "TypeEnum.h"
#include "CVState.h"
#include "CharacterConstant.h"
CVAdd::CVAdd(CVState* state , CVGame *cvgame):Add(cvgame->world, cvgame->cache, cvgame->tweenManager, cvgame->GetDrawManager(), cvgame->camera, cvgame->physics, cvgame->timeBasedEventManager, cvgame->eventManager)
{
	this->cvgame = cvgame;
	this->state = state;
}

CVAdd::~CVAdd()
{
}

Simon* CVAdd::CharSimon(double x, double y, ggEngine::Group * group)
{
	SpriteInfo* inf = this->cache->GetSpriteInfo(TextureConstant::SIMON_TEXTURE);
	Simon *simon = new Simon(this->drawManager, inf, 45, 40, 0);
	simon->SetPosition(x, y);
	simon->SetAnchor(0.5, 0.5);
	simon->CreateAnimation("move", 0, 3, true);
	simon->CreateAnimation("run", 5, 8, true);
	simon->CreateAnimation("knee", 8, 8, true);
	simon->CreateAnimation("up", 12, 15, true);

	this->physics->EnablePhysics(simon);
	simon->body->CreateRectangleRigidBody(45, 40);
	simon->body->rigidBody->SetAnchor(0.5, 0.5);
	simon->body->allowGravity = true;
	simon->body->allowWorldBounciness = false;
	simon->body->allowWorldBlock = true;
	simon->events->onCheckingCollide = [this](GameObject *otherObject, ColliderArg e) {
		Tag type = otherObject->tag;
		switch (type) {
		case ObjectType_Static:
			return true;
		default:
			return false;
		}
		return false;
		
	};
	simon->events->onCollide = [this](GameObject *otherObject, ColliderArg e) {
		Tag type = otherObject->tag;
		switch (type) {
		case ObjectType_Static:
			break;
		default:
			break;
		}

	};

	this->eventManager->EnableKeyBoardInput(simon);
	simon->events->onKeyPress = [this](GameObject *go, KeyBoardEventArg e) {
		Simon *simon = dynamic_cast<Simon*>(go);
		double time = cvgame->logicTimer.getDeltaTime();
		double force = CharacterConstant::SIMON_MOVE_FORCE* time;
		double currentJumpForce = CharacterConstant::SIMON_JUMP_FORCE*time;
		if (e.isPress(DIK_A)) {
			simon->PlayAnimation("move");
			simon->body->velocity.x = -force;
		}
		else {
			if (e.isPress(DIK_D)) {
				simon->PlayAnimation("move");
				simon->body->velocity.x = force;
			}
			else {
				simon->body->velocity.x = 0;
			}
		}

		if (e.isPress(DIK_SPACE)) {
			simon->body->velocity.y = -currentJumpForce;
		}
	};


	group->AddDrawObjectToList(simon);

	this->camera->Follow(simon);

	return simon;
}

InfoPanel*  CVAdd::UIInfoPanel()
{

	InfoPanel *infoPanel = new InfoPanel(this->drawManager);
	Style style;
	int fontSize = 22;
	int margin = 20;
	style.fontColor = D3DCOLOR_RGBA(255, 255, 255, 255);
	
	//Fist line
	infoPanel->score		= this->Text(	margin, margin, TextureConstant::GAME_FONT_TEXTURE, 50, 50, "SCORE-", style, infoPanel);
	infoPanel->scorePoint	= this->Text(	infoPanel->score->GetX() + fontSize*6,
											margin,
											TextureConstant::GAME_FONT_TEXTURE,
											50,
											50, 
											"000300",
											style,
											infoPanel);

	infoPanel->time			= this->Text(	GAME_WIDTH/2 - fontSize*4,
											margin,
											TextureConstant::GAME_FONT_TEXTURE,
											50,
											50,
											"TIME",
											style,
											infoPanel);

	infoPanel->timePoint	= this->Text(	infoPanel->time->GetX() + fontSize*5, 
											margin,
											TextureConstant::GAME_FONT_TEXTURE,
											50,
											50,
											"0012",
											style,
											infoPanel);

	infoPanel->stage		= this->Text(	GAME_WIDTH - fontSize*10, 
											margin,
											TextureConstant::GAME_FONT_TEXTURE,
											50,
											50,
											"STAGE",
											style,
											infoPanel);

	infoPanel->stagePoint	= this->Text(	infoPanel->stage->GetX() + fontSize*6,
											margin,
											TextureConstant::GAME_FONT_TEXTURE,
											50,
											50,
											"01",
											style,
											infoPanel);
	//second line
	infoPanel->player		= this->Text(	margin,
											margin + fontSize,
											TextureConstant::GAME_FONT_TEXTURE,
											50,
											50,
											"PLAYER",
											style,
											infoPanel);
	//third line
	infoPanel->enemy		= this->Text(	margin,
											margin + fontSize*2,
											TextureConstant::GAME_FONT_TEXTURE,
											50,
											50,
											"ENEMY",
											style,
											infoPanel);
	//P-H
	infoPanel->enemyPoint	= this->Text(	GAME_WIDTH/2 + 150,
											margin + fontSize,
											TextureConstant::GAME_FONT_TEXTURE,
											50,
											50,
											"-03",
											style,
											infoPanel);
	infoPanel->playerPoint	= this->Text(	GAME_WIDTH/2 + 150,
											margin + fontSize * 2,
											TextureConstant::GAME_FONT_TEXTURE,
											50,
											50,
											"P-02",
											style,
											infoPanel);

	world->AddGroup(infoPanel);
	return infoPanel;
}

