#include "EventManager.h"
#include "Game.h"
#include "GameObject.h"
#include "SpriteAnimation.h"
#include "Events.h"
ggEngine::EventManager::EventManager(Game * game)
{
	this->game = game;
}

ggEngine::EventManager::~EventManager()
{
	Destroy();
}

void ggEngine::EventManager::Destroy()
{
	Reset();
}

void ggEngine::EventManager::EnableKeyBoardInput(GameObject * go)
{
	InitEvents(go);
	receivedKeyBoardList.push_back(go);
}

void ggEngine::EventManager::EnableSpriteAnimationEvent(SpriteAnimation * go)
{
	InitEvents(go);
}

void ggEngine::EventManager::DisableKeyBoardInput(GameObject * go, bool isClearEvent)
{
	if (isClearEvent) {
		go->events->onKeyPress = nullptr;
	}
	receivedKeyBoardList.remove(go);
}

void ggEngine::EventManager::EnableMouseInput(GameObject * go)
{
	InitEvents(go);
	receivedMouseList.push_back(go);
}

void ggEngine::EventManager::DisableMouseInput(GameObject * go, bool isClearEvent)
{
	if (isClearEvent) {
		go->events->onMousePress = nullptr;
	}
	receivedMouseList.remove(go);
}



void ggEngine::EventManager::DispatchKeyBoardEvent(char * keyStates)
{
	KeyBoardEventArg arg;
	arg.keyState = keyStates;
	for (std::list<GameObject*>::iterator it = receivedKeyBoardList.begin(); it != receivedKeyBoardList.end();) {
		if ((*it)->IsAlive()) {
			if((*it)->events->onKeyPress!=nullptr) (*it)->events->onKeyPress((*it), arg);
			++it;
		}
	}

}

void ggEngine::EventManager::DispatchMouseEvent(double mouseX, double mouseY, bool isPress)
{
	MouseEventArg arg;
	for (std::list<GameObject*>::iterator it = receivedMouseList.begin(); it != receivedMouseList.end();) {
		if ((*it)->IsAlive()) {
			if ((*it)->events->onKeyPress != nullptr) (*it)->events->onMousePress((*it), arg);
			++it;
		}
	}
}

void ggEngine::EventManager::InitEvents(GameObject * go)
{
	if (go->events == NULL) {
		go->events = new Events(game, go);
	}
}
char ggEngine::EventManager::ScanToChar(DWORD scanCode) const
{
	//obtain keyboard information
	static HKL layout = GetKeyboardLayout(0);
	static UCHAR keyboardState[256];
	if (GetKeyboardState(keyboardState) == false)
		return 0;

	//translate keyboard press scan code identifier to a char
	UINT vk = MapVirtualKeyEx(scanCode, 1, layout);
	USHORT asciiValue;
	ToAscii(vk, scanCode, keyboardState, &asciiValue, 0);

	return static_cast<char>(asciiValue);
}

void ggEngine::EventManager::Reset(){
	this->receivedKeyBoardList.clear();
	this->receivedMouseList.clear();
}