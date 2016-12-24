#pragma once
#include <ggEngine.h>
#include "dxutil.h"
#include "dsutil.h"
#include <string>

#pragma comment (lib, "dxerr.lib")
#pragma comment (lib, "winmm.lib")

using namespace ggEngine;
class CVGame;
class CVAudio : public GameObject {
public:
	CVAudio (CVGame *game, std::string filePath);
	virtual ~CVAudio();

	void Play();
	void Stop();
	void PlayLoop();
	void Repeat(int numberOfRepeat);
	void Pause();
	void Resume();
	void Destroy(bool clearFromCache = false);
	void Restart();
	void FadeIn(int duration, bool loop = false);
	void FadeOut(int duration);
	void FadeTo(float volume);

private:
	CVGame *cvGame = nullptr;

	CSound *wave = nullptr;
	CSoundManager *dSound = nullptr;
};

