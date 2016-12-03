#include "Audio.h"
#include "Game.h"

namespace ggEngine{
	Audio::Audio(Game *game, AudioInfo *audioInfo)
	{
		this->game = game;
		this->audioInfo = audioInfo;
	}

	Audio::~Audio()
	{
		if (game != NULL){
			delete game;
			game = NULL;
		}
		if (audioInfo != NULL) {
			delete audioInfo;
			audioInfo = NULL;
		}
	}



	void Audio::Play()
	{
		//BOOL isRunning = TRUE;
		//while (SUCCEEDED(hr) && isRunning)
		//{
		//	XAUDIO2_VOICE_STATE state;
		//	audioInfo->sourceVoice->GetState(&state);
		//	isRunning = (state.BuffersQueued > 0) != 0;

		//	Sleep(10);
		//}
	}

	void Audio::Stop()
	{
	}
	void Audio::Loop(bool isLoop)
	{
		
	}
	void Audio::Repeat(int numberOfRepeat)
	{		
	}
	void Audio::Pause()
	{
		
	}
	void Audio::Resume()
	{
		
	}
	void Audio::Destroy(bool clearFromCache)
	{

	}
	void Audio::Restart()
	{

	}

	//Play the audio, or restart if is playing. 
	void Audio::FadeIn(int duration, bool loop)
	{

	}
	void Audio::FadeOut(int duration){}
	//Fade to the specific volume
	void Audio::FadeTo(float volume)	//with 100 levels
	{
		
	}
}