#pragma once
#include <xaudio2.h>
#include <string>

class AudioInfo
{
private:
	WAVEFORMATEX waveFormat;
	XAUDIO2_BUFFER buffer;
	BYTE * waveData;


public:
	AudioInfo(std::string fileName = "");
	~AudioInfo();

	inline const XAUDIO2_BUFFER* GetBuffer() { return &buffer; }
	inline const DWORD AudioInfo::GetChunkSize();
	inline WAVEFORMATEX* GetWaveFormat() { return &waveFormat; }

	bool Load(std::string fileName);
};

