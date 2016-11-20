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
	style.fontColor = D3DCOLOR_RGBA(255, 255, 255, 255);
	infoPanel->score = this->Text(20, 20, TextureConstant::GAME_FONT_TEXTURE, 50, 50, "SCORE-", style, infoPanel);


	world->AddGroup(infoPanel);
	return infoPanel;
}

