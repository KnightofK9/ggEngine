#pragma once
#include "TweenBase.h"
#include <list>
namespace ggEngine {
	class MultiTween : public TweenBase {
	public:
		MultiTween(std::list<TweenBase*> tweenList, TweenManager *tweenManager);
		~MultiTween();

		TweenBase* Start() override;
		double Update(double dt) override;
	private:
		std::list<TweenBase*> tweenList;
	};
}