#include "GameOverScreen.h"
#include "CVGame.h"

GameOverScreen::GameOverScreen(CVGame *game) : ScreenGroup(game)
{
	this->cvGame = game;
	this->isEnableKey = false;
}

GameOverScreen::~GameOverScreen()
{
}

void GameOverScreen::Draw()
{
	if (this->isEnableKey) {
		this->drawManager->DrawRectangleToWorld(0, 0, GAME_WIDTH, GAME_HEIGHT, D3DCOLOR_RGBA(0, 0, 0, 255));
		ScreenGroup::Draw();
	}
}

//void GameOverScreen::Preload() {
//	this->preload->Font(TextureConstant::GAME_FONT_TEXTURE, TextureConstant::GAME_FONT_NAME, TextureConstant::GAME_FONT_TEXTURE_PATH, 22);
//	this->preload->Texture(TextureConstant::HEART_MINI_TEXTURE, TextureConstant::HEART_MINI_TEXTURE_PATH);
//}
//void GameOverScreen::Create()
//{
//	Group* group = this->add->Group();
//	Style style;
//	style.fontColor = D3DCOLOR_RGBA(255, 255, 255, 255);
//	int fontSize = 22;
//
//	this->heart = this->add->Sprite(394 - fontSize * 5, 420, TextureConstant::HEART_MINI_TEXTURE, group);
//	this->heart->SetAnchor(0.5, 0.5);
//	this->heart->SetScale(3, 3);
//	this->cvgame->eventManager->EnableKeyBoardInput(this->heart);
//	this->heart->events->onKeyPress = [this](GameObject *go, KeyBoardEventArg e) {
//		Sprite  *current = dynamic_cast<Sprite*>(go);
//		if (current != NULL)
//		{
//			if (e.isPress(DIK_RETURN)){
//				if (isToggleUp){
//
//				}
//				else {
//
//				}
//			}
//
//			if (e.isPress(DIK_R) && isKeyPressed == false) {
//				isKeyPressed = true;
//				ToggleHeart(isToggleUp = !isToggleUp);
//			}
//			if (!e.isPress(DIK_R))
//				isKeyPressed = false;
//		}
//	};
//
//	this->gameOver = this->add->Text(384 - fontSize * 4, 291, TextureConstant::GAME_FONT_TEXTURE, 50, 50, "GAME OVER", style, group);
//	this->cont = this->add->Text(384 - fontSize * 3, 411, TextureConstant::GAME_FONT_TEXTURE, 50, 50, "CONTINUE", style, group);
//	this->end = this->add->Text(384 - fontSize * 3, 483, TextureConstant::GAME_FONT_TEXTURE, 50, 50, "END", style, group);
//}

void GameOverScreen::ToggleHeart(bool isUp)
{
	int fontSize = 22;

	if (isUp)
		heart->SetPosition(394 - fontSize * 5, 420);
	else
		heart->SetPosition(394 - fontSize * 5, 493);
}

void GameOverScreen::SetEnable(bool isEnable)
{
	this->SetVisible(isEnable);
	this->isEnableKey = isEnable;
}

void GameOverScreen::SetEventToggleHeart(std::function<void(void)> onToggleUp, std::function<void(void)> onToggleDown)
{
	if (this->heart == NULL)
		return;
	this->onToggleUp = onToggleUp;
	this->onToggleDown = onToggleDown;

	this->cvGame->eventManager->EnableKeyBoardInput(this->heart);
	this->heart->events->onKeyPress = [this](GameObject *go, KeyBoardEventArg e) {
		if (!this->isEnableKey)
			return;

		Sprite  *current = dynamic_cast<Sprite*>(go);
		if (current != NULL)
		{
			if (e.isPress(DIK_RETURN)) {
				if (this->isToggleUp) {
					this->onToggleUp();
				}
				else {
					this->onToggleDown();
				}
				this->SetEnable(false);
			}

			if (e.isPress(DIK_R) && isKeyPressed == false) {
				isKeyPressed = true;
				ToggleHeart(isToggleUp = !isToggleUp);
			}
			if (!e.isPress(DIK_R))
				isKeyPressed = false;
		}
	};
}
