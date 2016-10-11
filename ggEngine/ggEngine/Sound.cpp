#include "Sound.h"
#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>
#include <stdio.h>
#include <string>
#include "ConstantEnum.h"

namespace ggEngine
{
	extern SoundMode soundMode = SoundMode_Enable;

	Sound::Sound(HWND hWnd, const char * filePath, SoundType type, bool looping)
	{
		volume = 80;
		isLooping = looping;
		this->type = type;

		bool result = InitializeDirectSound(hWnd);
		if (!result)
			MessageBox(hWnd, "Could not initialize Direct Sound", "Error", MB_OK);
		result = LoadWaveFile(filePath, &secondBuffer);
		if (!result)
			MessageBox(hWnd, "Could not load wav resouce", "Error", MB_OK);
	}

	Sound::~Sound()
	{

		if (primaryBuffer != NULL)
		{
			primaryBuffer->Release();
			primaryBuffer = NULL;
		}
		if (secondBuffer != NULL)
		{
			secondBuffer->Release();
			secondBuffer = NULL;
		}
		if (dSound != NULL)
		{
			dSound->Release();
			dSound = NULL;
		}
	}

	bool Sound::InitializeDirectSound(HWND hWnd)
	{
		HRESULT result;
		DSBUFFERDESC bufferDesc;
		WAVEFORMATEX waveFormat;

		// init direct sound for device
		result = DirectSoundCreate8(NULL, &dSound, NULL);
		if (FAILED(result))
			return false;

		// set cooperative level
		result = dSound->SetCooperativeLevel(hWnd, DSSCL_PRIORITY);
		if (FAILED(result))
			return false;

		// set the primary buffer
		bufferDesc.dwSize = sizeof(DSBUFFERDESC);
		bufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME;
		bufferDesc.dwBufferBytes = 0;
		bufferDesc.dwReserved = 0;
		bufferDesc.lpwfxFormat = NULL;
		bufferDesc.guid3DAlgorithm = GUID_NULL;

		result = dSound->CreateSoundBuffer(&bufferDesc, &primaryBuffer, NULL);
		if (FAILED(result))
			return false;

		// Set format of the primary buffer
		//.wav file recorded at 44.1kHz and 16-bit 2 channels (cd audio format)
		waveFormat.wFormatTag = WAVE_FORMAT_PCM;
		waveFormat.nSamplesPerSec = 44100;
		waveFormat.wBitsPerSample = 16;
		waveFormat.nChannels = 2;
		waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
		waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
		waveFormat.cbSize = 0;

		result = primaryBuffer->SetFormat(&waveFormat);
		if (FAILED(result))
			return false;
		return true;
	}

	bool Sound::LoadWaveFile(const char * fileName, LPDIRECTSOUNDBUFFER8 * secondBuffer)
	{
		int error;
		FILE *file;
		unsigned int count;
		WaveHeaderType waveFileHeader;
		WAVEFORMATEX waveFormat;
		DSBUFFERDESC bufferDesc;
		HRESULT result;
		LPDIRECTSOUNDBUFFER tempBuffer;
		unsigned char *waveData;
		unsigned char *buffer;
		unsigned long bufferSize;

		error = fopen_s(&file, fileName, "rb");
		if (error != 0)
			return false;

		count = fread(&waveFileHeader, sizeof(WaveHeaderType), 1, file);
		if (count != 1)
			return false;

		// Check if valid Standard (stereo CD 44.1KB/s, 2 channels)
		if (!CheckWaveFile(waveFileHeader))
			return false;

		// Set format of the secondary buffer
		waveFormat.wFormatTag = WAVE_FORMAT_PCM;
		waveFormat.nSamplesPerSec = 44100;
		waveFormat.wBitsPerSample = 16;
		waveFormat.nChannels = 2;
		waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8)*waveFormat.nChannels;
		waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
		waveFormat.cbSize = 0;

		// Set description of the secondary buffer
		bufferDesc.dwSize = sizeof(DSBUFFERDESC);
		bufferDesc.dwFlags = DSBCAPS_CTRLVOLUME;
		bufferDesc.dwBufferBytes = waveFileHeader.dataSize;
		bufferDesc.dwReserved = 0;
		bufferDesc.lpwfxFormat = &waveFormat;
		bufferDesc.guid3DAlgorithm = GUID_NULL;

		result = dSound->CreateSoundBuffer(&bufferDesc, &tempBuffer, NULL);
		if (FAILED(result))
			return false;
		result = tempBuffer->QueryInterface(IID_IDirectSoundBuffer8, (void**)&*secondBuffer);
		if (FAILED(result))
			return false;

		tempBuffer->Release();
		tempBuffer = NULL;

		//Move to begin the wave, starts at the end of data chunk header
		fseek(file, sizeof(WaveHeaderType), SEEK_SET);
		waveData = new unsigned char[waveFileHeader.dataSize];
		if (waveData == NULL)
			return false;

		count = fread(waveData, 1, waveFileHeader.dataSize, file);
		if (count != waveFileHeader.dataSize)
			return false;

		error = fclose(file);
		if (error != 0)
			return false;

		// Lock secondary buffer
		result = (*secondBuffer)->Lock
		(
			0,
			waveFileHeader.dataSize,
			(void**)&buffer,
			(DWORD*)&bufferSize,
			NULL,
			0,
			0
		);
		if (FAILED(result))
			return false;
		memcpy(buffer, waveData, waveFileHeader.dataSize);

		// Unlock
		result = (*secondBuffer)->Unlock((void*)buffer, bufferSize, NULL, 0);
		if (FAILED(result))
			return false;

		delete[] waveData;
		waveData = 0;
		return true;
	}

	bool Sound::CheckWaveFile(WaveHeaderType waveFileHeader)
	{
		// check wave file
		//RIFF format
		if ((waveFileHeader.chunkId[0] != 'R')
			|| (waveFileHeader.chunkId[1] != 'I')
			|| (waveFileHeader.chunkId[2] != 'F')
			|| (waveFileHeader.chunkId[3] != 'F'))
			return false;

		//WAVE format
		if ((waveFileHeader.format[0] != 'W')
			|| (waveFileHeader.format[1] != 'A')
			|| (waveFileHeader.format[2] != 'V')
			|| (waveFileHeader.format[3] != 'E'))
			return false;

		//fmt format
		if ((waveFileHeader.subChunkId[0] != 'f')
			|| (waveFileHeader.subChunkId[1] != 'm')
			|| (waveFileHeader.subChunkId[2] != 't')
			|| (waveFileHeader.subChunkId[3] != ' '))
			return false;

		if (waveFileHeader.audioFormat != WAVE_FORMAT_PCM)
			return false;
		if (waveFileHeader.numChannels != 2)
			return false;
		if (waveFileHeader.sampleRate != 44100)
			return false;
		if (waveFileHeader.bitsPerSample != 16)
			return false;

		// check data chunk header
		if ((waveFileHeader.dataChunkId[0] != 'd')
			|| (waveFileHeader.dataChunkId[1] != 'a')
			|| (waveFileHeader.dataChunkId[2] != 't')
			|| (waveFileHeader.dataChunkId[3] != 'a'))
			return false;

		return true;
	}

	void Sound::Start()
	{
		if (soundMode == SoundMode_Disable)
			return;
		secondBuffer->SetCurrentPosition(0);
		//secondBuffer->SetVolume(volume * 100 - 10000);
		secondBuffer->SetVolume(DSBVOLUME_MAX);
		secondBuffer->Play(0, 0, isLooping);
	}

	void Sound::Pause()
	{
		secondBuffer->Stop();
	}

	void Sound::Stop()
	{
		secondBuffer->Stop();
		secondBuffer->SetCurrentPosition(0);
	}

	void Sound::Resume()
	{
		if (soundMode == SoundMode_Disable)
			return;
		secondBuffer->Play(0, 0, isLooping);
	}

	void Sound::SetLooping(bool mode)
	{
		if (mode)
			isLooping = DSBPLAY_LOOPING;
		else
			isLooping = 0;
	}

	void Sound::SetVolume(int volume)
	{
		//this->volume = volume;
		//secondBuffer->SetVolume(volume);
		// finding set volume with dB: -20*log(2)
		// reference: http://soundfile.sapp.org/doc/WaveFormat/
	}
}