#include "Audio.h"
namespace ggEngine{
	Audio::Audio(std::string audioKey)
	{
		/*soundBuffer.loadFromFile(audioKey);
		sound.setBuffer(soundBuffer);*/
	}



	void Audio::Play()
	{
		//sound.play();
	}

	void Audio::Stop()
	{
		//sound.stop();
	}
	void Audio::Loop(bool isLoop)
	{
		//sound.setLoop(isLoop);
	}
	void Audio::Repeat(int numberOfRepeat)
	{		
	}
	void Audio::Pause()
	{
		//sound.pause();
	}
	void Audio::Resume()
	{
		//sound.play();
	}
	void Audio::Destroy(bool clearFromCache)
	{

	}
	void Audio::Restart()
	{
		/*sound.setPosition(0, 0, 0);
		sound.play();*/
	}

	//Play the audio, or restart if is playing. 
	void Audio::FadeIn(int duration, bool loop)
	{

	}
	void Audio::FadeOut(int duration){}
	//Fade to the specific volume
	void Audio::FadeTo(float volume)	//with 100 levels
	{
		//sound.setVolume(volume);
	}
}