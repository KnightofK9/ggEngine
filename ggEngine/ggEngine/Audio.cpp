#include "Audio.h"
namespace ggEngine{
	Audio::Audio(std::string filePath)
	{
		//call for COM
		CoInitializeEx(NULL, COINIT_MULTITHREADED);

		//init Xaudio2
		if (FAILED(XAudio2Create(&engine)))
		{
			CoUninitialize();
			engine = NULL;
			return;
		}

		if (FAILED(engine->CreateMasteringVoice(&masterVoice)))
		{
			engine->Release();
			CoUninitialize();
			engine = NULL;
			return;
		}

		//helper class to load wave file
		auInfo = new AudioInfo();
		if (!auInfo->Load(filePath))
		{
			engine->Release();
			CoUninitialize();
			engine = NULL;
			return;
		}

		//create the source voice
		if (FAILED(engine->CreateSourceVoice(&source, auInfo->GetWaveFormat())))
		{
			engine->Release();
			CoUninitialize();
			engine = NULL;
			return;
		}
		buffer = *auInfo->GetBuffer();
		isPlayed = isPausing = false;
	}



	void Audio::Play()
	{
		//if (isPlayed == false)
		//{
			Stop();
			source->FlushSourceBuffers();
			if (FAILED(source->SubmitSourceBuffer(&buffer)))
				MessageBox(NULL, "Error: Buffer is unavailable to play this Audio. " +
					GetLastError(), "Error", MB_OK);
			source->SetVolume(1, XAUDIO2_COMMIT_NOW);
			source->Start(0);

			//isPlayed = true;
		//}
	}
	void Audio::Stop()
	{
		source->Stop();
		source->FlushSourceBuffers();
		//isPlayed = false;
		isPausing = false;
	}
	void Audio::Loop()
	{
		Stop();
		if (FAILED(source->SubmitSourceBuffer(&buffer)))
			MessageBox(NULL, "Error: Buffer is unavailable to play this Audio. " +
				GetLastError(), "Error", MB_OK);
		source->SetVolume(1, XAUDIO2_COMMIT_NOW);
		source->Start(0);
	}
	void Audio::Repeat(int numberOfRepeat)
	{		
		buffer.LoopCount = numberOfRepeat - 1;
	}
	void Audio::Pause()
	{
		if (isPausing == false)
		{
			source->Stop();
			isPausing = true;
		}
	}
	void Audio::Resume()
	{
		if (isPausing == true)
		{
			source->Start();
			isPausing = false;
		}
	}
	void Audio::Destroy(bool clearFromCache)
	{
		if (!clearFromCache)
		{
			engine->Release();
			CoUninitialize();
			delete auInfo;
		}
	}
	void Audio::Restart()
	{
		source->FlushSourceBuffers();
		if (FAILED(source->SubmitSourceBuffer(&buffer)))
			MessageBox(NULL, "Error: Buffer is unavailable to play this Audio. " +
				GetLastError(), "Error", MB_OK);
		source->SetVolume(1, XAUDIO2_COMMIT_NOW);
		source->Start(0);

		isPlayed = isPausing = false;
	}

	//Play the audio, or restart if is playing. 
	void Audio::FadeIn(int duration, bool loop)
	{
		//if (isPlayed == false)
		//{
		//	source->FlushSourceBuffers();
		//	if (FAILED(source->SubmitSourceBuffer(&buffer)))
		//		MessageBox(NULL, "Error: Buffer is unavailable to play this Audio. " +
		//			GetLastError(), "Error", MB_OK);
		//	source->Start(0);
		//	isPlayed = true;
		//}
	}
	void Audio::FadeOut(int duration){}
	//Fade to the specific volume
	void Audio::FadeTo(float volume)	//with 100 levels
	{
		//source->SetVolume(volume / 100);
	}
}