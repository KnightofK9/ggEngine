#pragma once
#include <dsound.h>
#pragma comment (lib, "dsound.lib")

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
		unsigned short bitsPerSample;
		char dataChunkId[4];
		unsigned long dataSize;
	};

	LPDIRECTSOUND8 dSound;
	LPDIRECTSOUNDBUFFER primaryBuffer;
	LPDIRECTSOUNDBUFFER8 secondBuffer;

	bool InitializeDirectSound(HWND hWnd);
	bool LoadWaveFile(char * fileName, LPDIRECTSOUNDBUFFER8 * soundBuffer);
	bool CheckWaveFile(WaveHeaderType waveFileHeader);


public:
	Sound();
	Sound(HWND hWnd);
	~Sound();

	bool PlaySound(int volume = 10000);
	bool StopSound();
};

