#include "AudioManager.h"
#include "AudioConstant.h"



AudioManager::AudioManager(CVGame *cvGame) : ManagerBase(cvGame)
{

}


AudioManager::~AudioManager()
{
	SAFE_RELEASE(this->level3Music);
	SAFE_RELEASE(this->level4Music);
	SAFE_RELEASE(this->bossBattleMusic);
	SAFE_RELEASE(this->gameOverMusic);
	SAFE_RELEASE(this->levelClearMusic);
	SAFE_RELEASE(this->lifeLoseMusic);

	SAFE_RELEASE(this->collectHeartSound);
	SAFE_RELEASE(this->collectWeaponSound);
	SAFE_RELEASE(this->decreaseWeaponPointSound);
	SAFE_RELEASE(this->fallCastleSound);
	SAFE_RELEASE(this->fallingSound);
	SAFE_RELEASE(this->getScoreTimerSound);
	SAFE_RELEASE(this->getScoreWeaponSound);
	SAFE_RELEASE(this->hitCannonSound);
	SAFE_RELEASE(this->holyCrossSound);
	SAFE_RELEASE(this->holyWaterSound);
	SAFE_RELEASE(this->onWeaponContactSound);
	SAFE_RELEASE(this->openDoorSound);
	SAFE_RELEASE(this->pauseSound);
	SAFE_RELEASE(this->selectSound);
	SAFE_RELEASE(this->usingWhipSound);
}

void AudioManager::PreloadAll()
{
	this->level3Music = new CVAudio(this->cvGame, AudioConstant::LEVEL_3_MUSIC_PATH);
	this->level4Music = new CVAudio(this->cvGame, AudioConstant::LEVEL_4_MUSIC_PATH);
	this->bossBattleMusic = new CVAudio(this->cvGame, AudioConstant::BOSS_BATTLE_MUSIC_PATH);
	this->gameOverMusic = new CVAudio(this->cvGame, AudioConstant::GAME_OVER_MUSIC_PATH);
	this->levelClearMusic = new CVAudio(this->cvGame, AudioConstant::LEVEL_CLEAR_MUSIC_PATH);
	this->lifeLoseMusic = new CVAudio(this->cvGame, AudioConstant::LIFE_LOST_MUSIC_PATH);

	this->collectHeartSound = new CVAudio(this->cvGame, AudioConstant::COLLECT_HEART_SOUND_PATH);
	this->collectWeaponSound = new CVAudio(this->cvGame, AudioConstant::COLLECT_WEAPON_SOUND_PATH);
	this->decreaseWeaponPointSound = new CVAudio(this->cvGame, AudioConstant::DECREASE_WEAPON_POINT_SOUND_PATH);
	this->fallCastleSound = new CVAudio(this->cvGame, AudioConstant::FALL_CASTLE_SOUND_PATH);
	this->fallingSound = new CVAudio(this->cvGame, AudioConstant::FALLING_SOUND_PATH);
	this->getScoreTimerSound = new CVAudio(this->cvGame, AudioConstant::GET_SCORE_TIMER_SOUND_PATH);
	this->getScoreWeaponSound = new CVAudio(this->cvGame, AudioConstant::GET_SCORE_WEAPON_SOUND_PATH);
	this->hitCannonSound = new CVAudio(this->cvGame, AudioConstant::HIT_CANNON_SOUND_PATH);
	this->holyCrossSound = new CVAudio(this->cvGame, AudioConstant::HOLY_CROSS_SOUND_PATH);
	this->holyWaterSound = new CVAudio(this->cvGame, AudioConstant::HOLY_WATER_SOUND_PATH);
	this->onWeaponContactSound = new CVAudio(this->cvGame, AudioConstant::ON_WEAPON_CONTACT_SOUND_PATH);
	this->openDoorSound = new CVAudio(this->cvGame, AudioConstant::OPEN_DOOR_SOUND_PATH);
	this->pauseSound = new CVAudio(this->cvGame, AudioConstant::PAUSE_SOUND_PATH);
	this->selectSound = new CVAudio(this->cvGame, AudioConstant::SELECT_SOUND_PATH);
	this->usingWhipSound = new CVAudio(this->cvGame, AudioConstant::USING_WHIP_SOUND_PATH);
}
