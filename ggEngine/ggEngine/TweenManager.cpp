#include "TweenManager.h"
#include "Game.h"
#include "TweenBase.h"
ggEngine::TweenManager::TweenManager(Game * game)
{
	this->game = game;
}

void ggEngine::TweenManager::Update(double deltaTime)
{
	for (auto it = tweenerList.begin(); it != tweenerList.end(); ) {
		TweenBase * tween = (*it);
		if (tween->IsAlive()) {
			if (tween->IsPlaying()) {
				tween->Update(deltaTime);
				++it;
			}else if(tween->IsFinished()){
				if (tween->IsLoop()) {
					tween->Restart();
				}
				else {
					auto tempIt = it;
					++it;
					delete (*tempIt);
					tweenerList.erase(tempIt);
				}
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

void ggEngine::TweenManager::AddTween(TweenBase *tween)
{
	tweenerList.push_back(tween);
}
void ggEngine::TweenManager::RemoveTween(TweenBase *tween)
{
	tweenerList.remove(tween);
}
void ggEngine::TweenManager::Reset()
{
	for (auto it = tweenerList.begin(); it != tweenerList.end(); ++it) {
		delete (*it);
	}
	tweenerList.clear();
}

ggEngine::TweenManager::~TweenManager()
{
}
