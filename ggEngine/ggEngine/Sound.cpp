#include "Sound.h"
#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>
#include <stdio.h>




Sound::Sound()
{
	dSound = 0;
	primaryBuffer = 0;
	secondBuffer = 0;
}

Sound::Sound(HWND hWnd)
{
	HRESULT result;
	InitializeDirectSound(hWnd);
}

Sound::~Sound()
{
	if (dSound != NULL)
	{
		dSound->Release();
		dSound = NULL;
	}
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
	waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8)*waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize = 0;
	
	result = primaryBuffer->SetFormat(&waveFormat);
	if (FAILED(result))
		return false;
	return true;
}

bool Sound::LoadWaveFile(char * fileName, LPDIRECTSOUNDBUFFER8 * soundBuffer)
{
	int error;
	FILE *file;
	
	WaveHeaderType waveFileHeader;
	WAVEFORMATEX waveFormat;
	DSBUFFERDESC bufferDesc;
	HRESULT result;
	unsigned int count;
	LPDIRECTSOUNDBUFFER tempBuffer;
	unsigned char *waveData;
	unsigned char *buffer;
	unsigned long bufferSize;

	error = fopen_s(&file, fileName, "rb");
	if (error != 0)
		return false;

	count = fread(&waveFileHeader, sizeof(waveFileHeader), 1, file);
	if (count != 1)
		return false;

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
	result = tempBuffer->QueryInterface(IID_IDirectSound, (void**)&*secondBuffer);
	if (FAILED(result))
		return false;

	tempBuffer->Release();
	tempBuffer = NULL;

	//Move to begin the wave, starts at the end of data chunk header
	fseek(file, sizeof(waveFileHeader), SEEK_SET);
	// hold wave data
	waveData = new unsigned char[waveFileHeader.dataSize];
	if (waveData == NULL)
		return false;

	count = fread(waveData, 1, waveFileHeader.dataSize, file);
	if (count != waveFileHeader.dataSize)
		return false;

	if (!fclose(file))
		return false;

	// Lock secondary buffer
	result = (secondBuffer)->Lock
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
	result = (secondBuffer)->Unlock(buffer, bufferSize, NULL, 0);
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
	if ((waveFileHeader.chunkId[0] != 'W')
		|| (waveFileHeader.chunkId[1] != 'A')
		|| (waveFileHeader.chunkId[2] != 'V')
		|| (waveFileHeader.chunkId[3] != 'E'))
		return false;

	//fmt format
	if ((waveFileHeader.chunkId[0] != 'f')
		|| (waveFileHeader.chunkId[1] != 'm')
		|| (waveFileHeader.chunkId[2] != 't')
		|| (waveFileHeader.chunkId[3] != ' '))
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

bool Sound::PlaySound(int volume)
{
	HRESULT result;
	result = secondBuffer->SetCurrentPosition(0);
	if (FAILED(result))
		return false;
	result = secondBuffer->SetVolume(volume - 10000);
	if (FAILED(result))
		return false;
	result = secondBuffer->Play(0, 0, 0);
	if (FAILED(result))
		return false;
	
	return true;
}

bool Sound::StopSound()
{
	return false;
}