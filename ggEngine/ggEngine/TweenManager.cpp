#include "TweenManager.h"
#include "Game.h"
#include "Tween.h"
ggEngine::TweenManager::TweenManager(Game * game)
{
	this->game = game;
	this->tweenerList.reserve(40);
}

void ggEngine::TweenManager::Update(double deltaTime)
{
	for (int i = 0; i < tweenerList.size(); i++) {
		Tween * tween = tweenerList[i];
		if (tween->IsAlive()) {
			if (tween->IsPlaying()) {
				tween->GetClawTweener()->update(deltaTime);
			}else if(tween->IsFinished()){
				delete tween;
				tweenerList[i] = nullptr;
			}
		}
		else {
			delete tween;
			tweenerList[i] = nullptr;
		}
	}
}

void ggEngine::TweenManager::AddTween(Tween *tween)
{
	int i;
	for ( i = 0; i < tweenerList.size(); i++) {
		if (tweenerList[i] == nullptr) {
			tweenerList[i] = (tween);
		}
	}
	if (i == tweenerList.size()) {
		tweenerList.push_back(tween);
	}
}

ggEngine::TweenManager::~TweenManager()
{
}
