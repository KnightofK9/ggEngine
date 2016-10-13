#include "TweenManager.h"
#include "Game.h"
#include "Tween.h"
ggEngine::TweenManager::TweenManager(Game * game)
{
	this->game = game;
}

void ggEngine::TweenManager::Update(double deltaTime)
{
	for (auto it = tweenerList.begin(); it != tweenerList.end(); ) {
		Tween * tween = (*it);
		if (tween->IsAlive()) {
			if (tween->IsPlaying()) {
				tween->Update(deltaTime);
				++it;
			}else if(tween->IsFinished()){
				auto tempIt = it;
				++it;
				delete (*tempIt);
				tweenerList.erase(tempIt);
			}
			
		}
		else {
			auto tempIt = it;
			++it;
			delete (*tempIt);
			tweenerList.erase(tempIt);
		}
	}
}

void ggEngine::TweenManager::AddTween(Tween *tween)
{
	tweenerList.push_back(tween);
}

ggEngine::TweenManager::~TweenManager()
{
}
