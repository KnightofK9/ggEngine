#pragma once
#include <ggEngine.h>
#include "ManagerBase.h"

using namespace ggEngine;
class CVGame;
class CVPreload;
class AudioManager : public ManagerBase
{
public:
	AudioManager(CVGame *game);
	virtual ~AudioManager();

	void PreloadAllAudio();


private:
	Audio *stage4Music;
};

