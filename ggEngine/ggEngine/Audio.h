#pragma once
#include "GGObject.h"
#include "Debug.h"
#include "AudioInfo.h"

namespace ggEngine{
	class Game;
	class Audio : public GGObject{
	public:
		Audio(Game *game, AudioInfo *audioInfo);
		virtual ~Audio();

		void Play();
		void Stop();
		void Loop(bool isLoop);
		void Repeat(int numberOfRepeat);
		void Pause();
		void Resume();
		void Destroy(bool clearFromCache = false);
		void Restart();
		//Play the audio, or restart if is playing. 
		void FadeIn(int duration, bool loop = false);
		void FadeOut(int duration);
		//Fade to the specific volume
		void FadeTo(float volume);
		
	private:
		Game *game = nullptr;
		AudioInfo *audioInfo = nullptr;
	};
}