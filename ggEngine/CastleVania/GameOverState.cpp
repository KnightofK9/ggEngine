#include "GameOverState.h"

GameOverState::GameOverState(CVGame *game) : CVState(game)
{
}

GameOverState::~GameOverState()
{
}

void GameOverState::Init() {

}
void GameOverState::Preload() {
	this->cvPreload->Font(TextureConstant::GAME_FONT_TEXTURE, TextureConstant::GAME_FONT_NAME, TextureConstant::GAME_FONT_TEXTURE_PATH, 22);
	this->cvPreload->Texture(TextureConstant::HEART_MINI_TEXTURE, TextureConstant::HEART_MINI_TEXTURE_PATH);
}
void GameOverState::Create()
{
	Group* group = this->cvAdd->Group();
	Style style;
	style.fontColor = D3DCOLOR_RGBA(255, 255, 255, 255);
	int fontSize = 22;

	this->heart = this->cvAdd->Sprite(394 - fontSize * 5, 420, TextureConstant::HEART_MINI_TEXTURE, group);
	this->heart->SetAnchor(0.5, 0.5);
	this->heart->SetScale(3, 3);
	this->cvgame->eventManager->EnableKeyBoardInput(this->heart);
	this->heart->events->onKeyPress = [this](GameObject *go, KeyBoardEventArg e) {
		Sprite  *current = dynamic_cast<Sprite*>(go);
		if (current != NULL)
		{
			if (e.isPress(DIK_RETURN)){
				if (isToggleUp){

				}
				else {

				}
			}

			if (e.isPress(DIK_R) && isKeyPressed == false) {
				isKeyPressed = true;
				ToggleHeart(isToggleUp = !isToggleUp);
			}
			if (!e.isPress(DIK_R))
				isKeyPressed = false;
		}
	};

	this->gameOver = this->cvAdd->Text(384 - fontSize * 4, 291, TextureConstant::GAME_FONT_TEXTURE, 50, 50, "GAME OVER", style, group);
	this->cont = this->cvAdd->Text(384 - fontSize * 3, 411, TextureConstant::GAME_FONT_TEXTURE, 50, 50, "CONTINUE", style, group);
	this->end = this->cvAdd->Text(384 - fontSize * 3, 483, TextureConstant::GAME_FONT_TEXTURE, 50, 50, "END", style, group);
}
void GameOverState::Update()
{

}
void GameOverState::PreRender()
{
}
void GameOverState::Render()
{

}
void GameOverState::Pause()
{
}
void GameOverState::Resume()
{
}
void GameOverState::ShutDown()
{

}


void GameOverState::ChangeState()
{

}

void GameOverState::ToggleHeart(bool up)
{
	int fontSize = 22;

	if (up)
		heart->SetPosition(394 - fontSize * 5, 420);
	else
		heart->SetPosition(394 - fontSize * 5, 493);
}
