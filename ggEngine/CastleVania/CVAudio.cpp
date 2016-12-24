#include "CVAudio.h"
CVAudio::CVAudio(CVGame *cvGame, std::string filePath)
{
	this->cvGame = cvGame;

	HRESULT hr;
	if (FAILED(hr = dSound->Initialize(game->hWnd, DSSCL_PRIORITY))) {
		g_debug.Log("Failed to initialize Sound Manager");
		return;
	}

	LPTSTR path = (TCHAR*)filePath.c_str();
	if (FAILED(hr = dSound->Create(&wave, path))) {
		g_debug.Log("Failed to create wave");
		return;
	}
}

CVAudio::~CVAudio()
{
	this->Stop();
	if (dSound != NULL) {
		delete dSound;
		dSound = NULL;
	}
	if (wave != NULL) {
		delete wave;
		wave = NULL;
	}
}

void CVAudio::Play()
{
	this->wave->Play();
}

void CVAudio::Stop()
{
	this->wave->Stop();
}

void CVAudio::PlayLoop()
{
	this->wave->Play(0, DSBPLAY_LOOPING);
}

void CVAudio::Repeat(int numberOfRepeat)
{
	this->wave->Play(numberOfRepeat, DSBPLAY_LOOPING);
}

void CVAudio::Pause()
{
	this->wave->Stop();
}

void CVAudio::Resume()
{
	this->wave->Play();
}

void CVAudio::Destroy(bool clearFromCache)
{

}

void CVAudio::Restart()
{
	this->wave->Reset();
	this->wave->Play();
}

void CVAudio::FadeIn(int duration, bool loop)
{

}

void CVAudio::FadeOut(int duration)
{

}

void CVAudio::FadeTo(float volume)	//with 100 levels
{
}