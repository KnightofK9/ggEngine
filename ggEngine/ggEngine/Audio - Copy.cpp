#include "Audio.h"
namespace ggEngine{
	Audio::Audio(HWND hWnd, const char * filePath, bool looping = false)
	{
		////call for COM
		//CoInitializeEx(NULL, COINIT_MULTITHREADED);

		////init Xaudio2
		//if (FAILED(XAudio2Create(&engine)))
		//{
		//	CoUninitialize();
		//	engine = NULL;
		//	return;
		//}

		//if (FAILED(engine->CreateMasteringVoice(&masterVoice)))
		//{
		//	engine->Release();
		//	CoUninitialize();
		//	engine = NULL;
		//	return;
		//}

		////helper class to load wave file
		//auInfo = new AudioInfo();
		//if (!auInfo->Load(fileName))
		//{
		//	engine->Release();
		//	CoUninitialize();
		//	engine = NULL;
		//	return;
		//}

		////create the source voice
		//if (FAILED(engine->CreateSourceVoice(&source, auInfo->GetWaveFormat())))
		//{
		//	engine->Release();
		//	CoUninitialize();
		//	engine = NULL;
		//	return;
		//}

		volume = 80;
		isLooping = looping;

		bool result = InitializeDirectSound(hWnd);
		if (!result)
			MessageBox(hWnd, "Could not initialize Direct Sound", "Error", MB_OK);
		result = LoadWaveFile(filePath, &secondBuffer);
		if (!result)
			MessageBox(hWnd, "Could not load wav resouce", "Error", MB_OK);
	}



	void Audio::Play()
	{
		
	}
	void Audio::Stop(){}
	void Audio::Loop(){}
	void Audio::Repeat(int numberOfRepeat){}
	void Audio::Pause(){}
	void Audio::Resume(){}
	void Audio::Destroy(bool clearFromCache)
	{
		if (!clearFromCache)
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
	}
	void Audio::Restart(){}
	//Play the audio, or restart if is playing. 
	void Audio::FadeIn(int duration, bool loop){}
	void Audio::FadeOut(int duration){}
	//Fade to the specific volume
	void Audio::FadeTo(float volume){}
}