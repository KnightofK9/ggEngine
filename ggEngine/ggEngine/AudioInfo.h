#pragma once
#include <xaudio2.h>
#include <string>
#include <stdio.h>
#include <XAudio2.h>
#include <string>
#include "SDKwavefile.h"
#include "Debug.h"
#include "Helper.h"

namespace ggEngine {
	class AudioInfo
	{
	public:
		AudioInfo(std::string filePath);
		virtual ~AudioInfo();
		IXAudio2* GetXAudio2Engine() { return this->xaudio2; }

		IXAudio2SourceVoice * sourceVoice = nullptr;

	private:
		IXAudio2 *xaudio2 = nullptr;
		IXAudio2MasteringVoice *masteringVoice = nullptr;
		WAVEFORMATEX *wfx = nullptr;
		XAUDIO2_BUFFER buffer;
		Debug debug;
		CWaveFile wav;
	};
}
