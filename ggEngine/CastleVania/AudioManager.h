#pragma once
#include <ggEngine.h>
#include "CVAudio.h"
#include "ManagerBase.h"
//#define SAFE_RELEASE(p) if(p){ delete p; p = nullptr;}

using namespace ggEngine;
class CVGame;
class CVPreload;
class AudioManager : public ManagerBase
{
public:
	AudioManager(CVGame *game);
	virtual ~AudioManager();
	void PreloadAll();
	void PauseAllSound();
	void PauseAllMusic();


	CVAudio *level3Music;
	CVAudio *level4Music;
	CVAudio *bossBattleMusic;
	CVAudio *gameOverMusic;
	CVAudio *levelClearMusic;
	CVAudio *lifeLoseMusic;

	CVAudio *collectHeartSound;
	CVAudio *collectMoneySound;
	CVAudio *collectWeaponSound;
	CVAudio *decreaseWeaponPointSound;
	CVAudio *fallCastleSound;
	CVAudio *fallingSound;
	CVAudio *getScoreTimerSound;
	CVAudio *getScoreWeaponSound;
	CVAudio *hitCannonSound;
	CVAudio *holyCrossSound;
	CVAudio *holyWaterSound;
	CVAudio *onContactSound;
	CVAudio *openDoorSound;
	CVAudio *pauseSound;
	CVAudio *selectSound;
	CVAudio *usingWhipSound;
	CVAudio *contactBreakableBrick;
	
private:
	vector<CVAudio*> listMusic;
	vector<CVAudio*> listSound;
};

