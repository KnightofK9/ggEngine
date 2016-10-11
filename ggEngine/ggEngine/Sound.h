#pragma once
#include <dsound.h>
#include <string>
#include "ConstantEnum.h"
#pragma comment (lib, "dsound.lib")

namespace ggEngine
{
	class Sound
	{
	private:
		struct WaveHeaderType
		{
			char chunkId[4];
			unsigned long chunkSize;
			char format[4];
			char subChunkId[4];
			unsigned long subChunkSize;
			unsigned short audioFormat;
			unsigned short numChannels;
			unsigned long sampleRate;
			unsigned long  bytesPerSecond;
			unsigned short blockAlign;
			unsigned short bitsPerSample;
			char dataChunkId[4];
			unsigned long dataSize;

		};

		LPDIRECTSOUND8 dSound;
		LPDIRECTSOUNDBUFFER primaryBuffer;
		LPDIRECTSOUNDBUFFER8 secondBuffer;
		SoundType type;

		int volume;	// volume max: 100
		int isLooping;
		bool isStopping;

		bool InitializeDirectSound(HWND hWnd);
		bool LoadWaveFile(const char * fileName, LPDIRECTSOUNDBUFFER8 * soundBuffer);
		bool CheckWaveFile(WaveHeaderType waveFileHeader);


	public:
		Sound(HWND hWnd, const char * filePath, SoundType type = SoundType_Sound, bool looping = false);
		~Sound();

		void Start();
		void Pause();
		void Stop();
		void Resume();
		void SetLooping(bool mode = false);
		void SetVolume(int volume);
		void SetSoundType(SoundType type) { this->type = type; }
		//void PlayWithDuration(int beginTime, int endTime); // milisecond
	};
}