#include "AudioInfo.h"

namespace ggEngine {
	AudioInfo::AudioInfo(std::string filePath)
	{
		//WCHAR strFilePath[MAX_PATH];
		//LPCWSTR strFilePath = Helper::StringToLPCWSTR(filePath);
		std:wstring tempFilePath;
		tempFilePath.assign(filePath.begin(), filePath.end());



		CoInitializeEx(NULL, COINITBASE_MULTITHREADED);

		HRESULT hr = XAudio2Create(&xaudio2, XAUDIO2_DEBUG_ENGINE);
		if (FAILED(hr)) {
			//g_debug.Log("Failed to init XAudio2 engine: " + hr);
			return;
		}

		if (FAILED(hr = xaudio2->CreateMasteringVoice(&masteringVoice))) {
			//g_debug.Log("Failed creating mastering voice");
			return;
		}

		if (FAILED(hr = wav.Open(&tempFilePath[0], NULL, WAVEFILE_READ))) {
			//g_debug.Log("Failed reading WAV file: ");
			return;
		}

		wfx = wav.GetFormat();
		//Caculate bytes & sample in wave
		DWORD cbWaveSize = wav.GetSize();
		//Read sample data
		BYTE *bWaveData = new BYTE[cbWaveSize];

		if (FAILED(hr = wav.Read(bWaveData, cbWaveSize, &cbWaveSize))) {
			g_debug.Log("Failed to read WAV data: " + hr);
			SAFE_DELETE_ARRAY(bWaveData);
			return;
		}

		//Create source voice
		if (FAILED(hr = xaudio2->CreateSourceVoice(&sourceVoice, wfx))) {
			g_debug.Log("Failed to read WAV data: " + hr);
			SAFE_DELETE_ARRAY(bWaveData);
			return;
		}

		//Submit to buffer
		buffer = { 0 };
		buffer.pAudioData = bWaveData;
		buffer.Flags = XAUDIO2_END_OF_STREAM;
		buffer.AudioBytes = cbWaveSize;

		if (FAILED(hr = sourceVoice->SubmitSourceBuffer(&buffer))) {
			g_debug.Log("Failed to submit source buffer: " + hr);
			SAFE_DELETE_ARRAY(bWaveData);
			return;
		}
	}


	AudioInfo::~AudioInfo()
	{
		if (sourceVoice != NULL) {
			sourceVoice->DestroyVoice();
			delete sourceVoice;
			sourceVoice = NULL;
		}
		if (xaudio2 != NULL) {
			CoUninitialize();
			delete xaudio2;
			xaudio2 = NULL;
		}
		if (masteringVoice != NULL) {
			delete masteringVoice;
			masteringVoice = NULL;
		}
		if (wfx != NULL) {
			delete wfx;
			wfx = NULL;
		}
	}
}