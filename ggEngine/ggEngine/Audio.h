#pragma once
#include "GGObject.h"
#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>
#include <stdio.h>
#include <string>
#include <SFML\Audio.hpp>
#pragma comment (lib, "sfml-audio-d.lib")

namespace ggEngine{
	class Audio : public GGObject{
	public:
		Audio(std::string audioKey);

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
		sf::SoundBuffer soundBuffer;
		sf::Sound sound;
	};
}