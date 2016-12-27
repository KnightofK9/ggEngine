#include "AudioManager.h"
#include "AudioConstant.h"



AudioManager::AudioManager(CVGame *cvGame) : ManagerBase(cvGame)
{
}


AudioManager::~AudioManager()
{
	for (int i = 0; i < listSound.size(); i++)
		if (listSound.at(i) != nullptr) {
			listSound.at(i)->Pause();
			delete listSound.at(i);
			listSound.at(i) = nullptr;
		}
	listSound.clear();

	for (int i = 0; i < listMusic.size(); i++)
		if (listMusic.at(i) != nullptr) {
			listMusic.at(i)->Pause();
			delete listMusic.at(i);
			listMusic.at(i) = nullptr;
		}
	listMusic.clear();
}

void AudioManager::PreloadAll()
{
	listMusic.push_back(this->level3Music = new CVAudio(this->cvGame, AudioConstant::LEVEL_3_MUSIC_PATH));
	listMusic.push_back(this->level4Music = new CVAudio(this->cvGame, AudioConstant::LEVEL_4_MUSIC_PATH));
	listMusic.push_back(this->bossBattleMusic = new CVAudio(this->cvGame, AudioConstant::BOSS_BATTLE_MUSIC_PATH));
	listMusic.push_back(this->gameOverMusic = new CVAudio(this->cvGame, AudioConstant::GAME_OVER_MUSIC_PATH));
	listMusic.push_back(this->levelClearMusic = new CVAudio(this->cvGame, AudioConstant::LEVEL_CLEAR_MUSIC_PATH));
	listMusic.push_back(this->lifeLoseMusic = new CVAudio(this->cvGame, AudioConstant::LIFE_LOST_MUSIC_PATH));

	listSound.push_back(this->collectHeartSound = new CVAudio(this->cvGame, AudioConstant::COLLECT_HEART_SOUND_PATH));
	listSound.push_back(this->collectMoneySound = new CVAudio(this->cvGame, AudioConstant::COLLECT_MONEY_SOUND_PATH));
	listSound.push_back(this->collectWeaponSound = new CVAudio(this->cvGame, AudioConstant::COLLECT_WEAPON_SOUND_PATH));
	listSound.push_back(this->decreaseWeaponPointSound = new CVAudio(this->cvGame, AudioConstant::DECREASE_WEAPON_POINT_SOUND_PATH));
	listSound.push_back(this->fallCastleSound = new CVAudio(this->cvGame, AudioConstant::FALL_CASTLE_SOUND_PATH));
	listSound.push_back(this->fallingSound = new CVAudio(this->cvGame, AudioConstant::FALLING_SOUND_PATH));
	listSound.push_back(this->getScoreTimerSound = new CVAudio(this->cvGame, AudioConstant::GET_SCORE_TIMER_SOUND_PATH));
	listSound.push_back(this->getScoreWeaponSound = new CVAudio(this->cvGame, AudioConstant::GET_SCORE_WEAPON_SOUND_PATH));
	listSound.push_back(this->hitCannonSound = new CVAudio(this->cvGame, AudioConstant::HIT_CANNON_SOUND_PATH));
	listSound.push_back(this->holyCrossSound = new CVAudio(this->cvGame, AudioConstant::HOLY_CROSS_SOUND_PATH));
	listSound.push_back(this->holyWaterSound = new CVAudio(this->cvGame, AudioConstant::HOLY_WATER_SOUND_PATH));
	listSound.push_back(this->onContactSound = new CVAudio(this->cvGame, AudioConstant::ON_CONTACT_SOUND_PATH));
	listSound.push_back(this->openDoorSound = new CVAudio(this->cvGame, AudioConstant::OPEN_DOOR_SOUND_PATH));
	listSound.push_back(this->pauseSound = new CVAudio(this->cvGame, AudioConstant::PAUSE_SOUND_PATH));
	listSound.push_back(this->selectSound = new CVAudio(this->cvGame, AudioConstant::SELECT_SOUND_PATH));
	listSound.push_back(this->usingWhipSound = new CVAudio(this->cvGame, AudioConstant::USING_WHIP_SOUND_PATH));
	listSound.push_back(this->contactBreakableBrick = new CVAudio(this->cvGame, AudioConstant::BREAKABLE_BRICK_CONTACT_SOUND_PATH));
}

void AudioManager::PauseAllSound()
{
	for (int i = 0; i < listSound.size(); i++)
		listSound.at(i)->Pause();
}

void AudioManager::PauseAllMusic()
{
	for (int i = 0; i < listMusic.size(); i++)
		listMusic.at(i)->Pause();
}
