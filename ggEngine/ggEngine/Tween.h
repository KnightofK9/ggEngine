#pragma once
#include "GGObject.h"
#include <claw/tween/single_tweener.hpp>
#include <boost\function.hpp>
#pragma comment(lib,"libclaw_application.lib")
#pragma comment(lib,"libclaw_configuration_file.lib")
#pragma comment(lib,"libclaw_dynamic_library.lib")
#pragma comment(lib,"libclaw_graphic.lib")
#pragma comment(lib,"libclaw_logger.lib")
#pragma comment(lib,"libclaw_net.lib")
#pragma comment(lib,"libclaw_tween.lib")

namespace ggEngine {
	class TweenManager;
	class Tween :public GGObject {
	public:
		Tween(TweenManager* tweenManager,double &val, double end, double duration , boost::function<double(double)> easingFunction);
		Tween(TweenManager* tweenManager,double init, double end, double duration, std::function<void(double)> update, boost::function<double(double)> easingFunction);
		~Tween();
		void SetOnFinish(std::function<void()> onFinish);
		bool IsPlaying();
		bool IsFinished();
		void Destroy();
		void Start();
		void Pause();
		bool IsAlive() { return this->isAlive; }
		claw::tween::single_tweener* GetClawTweener() { return this->tweener; }
		void CallFinish();
	private:
		claw::tween::single_tweener *tweener = nullptr;
		std::function<void()> onFinish = nullptr;
		TweenManager* tweenManager;
		bool isPlaying;
		bool isAlive;
	};
}