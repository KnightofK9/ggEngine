#include "GGObject.h"
#include <xaudio2.h>
#include <string>
#include <dsound.h>
#include "AudioInfo.h"
#include "ConstantEnum.h"

#pragma comment (lib, "dsound.lib")

namespace ggEngine{

	class Audio : public GGObject{
	public:
		Audio(HWND hWnd, const char * filePath, bool looping = false, SoundMode mode = SoundMode_Enable);

		void Play();
		void Stop();
		void Loop();
		void Repeat(int numberOfRepeat);
		void Pause();
		void Resume();
		void Destroy(bool clearFromCache = false);
		void Restart();
		//Play the audio, or restart if is playing. 
		void FadeIn(int duration, bool loop = false);
		void FadeOut(int duration);
		//Fade to the specific volume
		void FadeTo(float volume);

		void SetSoundMode(SoundMode mode);

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

		int volume;	// volume max: 100
		int isLooping;
		bool isStopping;
		SoundMode mode;

		bool InitializeDirectSound(HWND hWnd);
		bool LoadWaveFile(const char * fileName, LPDIRECTSOUNDBUFFER8 * soundBuffer);
		bool CheckWaveFile(WaveHeaderType waveFileHeader);

	};
}