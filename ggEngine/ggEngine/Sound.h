#pragma once
#include <dsound.h>
#include <string>
#pragma comment (lib, "dsound.lib")

class Sound
{
private:
	enum SoundType { SoundEffect, Music};
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
	SoundType soundType;
	int volume;	// volume max: 100
	int isLooping;
	bool isStopping;

	bool InitializeDirectSound(HWND hWnd);
	bool LoadWaveFile(const char * fileName, LPDIRECTSOUNDBUFFER8 * soundBuffer);
	bool CheckWaveFile(WaveHeaderType waveFileHeader);


public:

	Sound();
	Sound(HWND hWnd, const char * fileName);
	~Sound();

	void Start();
	void Pause();
	void Stop();
	void Resume();
	void SetLooping(bool mode = false);
	void SetVolume(int volume);
	void SetSoundType(SoundType type) { this->soundType = type; }
};

