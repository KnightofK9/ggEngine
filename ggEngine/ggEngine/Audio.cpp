#include "Audio.h"
namespace ggEngine{
	void Audio::Play(){

	}
	void Audio::Stop(){}
	void Audio::Loop(){}
	void Audio::Repeat(int numberOfRepeat){}
	void Audio::Pause(){}
	void Audio::Resume(){}
	void Audio::Destroy(bool clearFromCache){}
	void Audio::Restart(){}
	//Play the audio, or restart if is playing. 
	void Audio::FadeIn(int duration, bool loop){}
	void Audio::FadeOut(int duration){}
	//Fade to the specific volume
	void Audio::FadeTo(float volume){}
}