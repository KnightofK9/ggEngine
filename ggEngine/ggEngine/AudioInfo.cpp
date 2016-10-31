#include "AudioInfo.h"
#include <fstream>

#define fourccRIFF 'RIFF'
#define fourccDATA 'data'
#define fourccFMT 'fmt '
#define fourccWAVE 'WAVE'
#define fourccXWMA 'XWMA'
#define fourccDPDS 'dpds'

AudioInfo::AudioInfo(std::string fileName)
{
	waveData = NULL;
	ZeroMemory(&waveFormat, sizeof(waveFormat));
	ZeroMemory(&buffer, sizeof(buffer));

	Load(fileName);
}


AudioInfo::~AudioInfo()
{
	if (waveData != NULL)
		delete waveData;
	waveData = NULL;
}

bool AudioInfo::Load(std::string fileName)
{
	if (fileName.empty())
		return false;

	std::ifstream file;
	file.open(fileName, std::ios::binary | std::ios::in);
	if (file.bad())
		return false;

	DWORD chunkId = 0;
	DWORD fileSize = 0;
	DWORD chunkSize = 0;
	DWORD fileFormat = 0;

	//get chunk id
	file.seekg(0, std::ios::beg);
	file.read(reinterpret_cast<char*>(&chunkId), sizeof(chunkId));
	if (chunkId != 'FFIR')
	{
		file.close();
		return false;
	}

	//get file size
	file.seekg(4, std::ios::beg);
	file.read(reinterpret_cast<char*>(&fileSize), sizeof(fileSize));
	if (fileSize <= 16)
	{
		file.close();
		return false;
	}

	//get format
	file.seekg(8, std::ios::beg);
	file.read(reinterpret_cast<char*>(&fileFormat), sizeof(fileFormat));
	if (fileFormat != 'EVAW')
	{
		file.close();
		return false;
	}

	//fmt
	bool fFormat = false;
	for (unsigned int i = 12; i < fileSize;)
	{
		file.seekg(i, std::ios::beg);
		file.read(reinterpret_cast<char*>(&chunkId), sizeof(chunkId));
		file.seekg(i + 4, std::ios::beg);
		file.read(reinterpret_cast<char*>(&chunkSize), sizeof(chunkSize));
		if (chunkId == ' tmf')
		{
			file.seekg(i + 8, std::ios::beg);
			file.read(reinterpret_cast<char*>(&waveFormat), sizeof(waveFormat));
			fFormat = true;
			break;
		}
		chunkSize += 9;		//include offset size
		chunkSize &= 0xfffffffe;

		i += chunkSize;
	}
	if (fFormat == false)
	{
		file.close();
		return false;
	}

	//'data'
	bool fData = false;
	for (unsigned int i = 12; i < fileSize;)
	{
		file.seekg(i, std::ios::beg);
		file.read(reinterpret_cast<char*>(&chunkId), sizeof(chunkId));
		file.seekg(i + 4, std::ios::beg);
		file.read(reinterpret_cast<char*>(&chunkSize), sizeof(chunkSize));
		if (chunkId == 'atad')
		{
			waveData = new BYTE[chunkSize];
			file.seekg(i + 8, std::ios::beg);
			file.read(reinterpret_cast<char*>(waveData), chunkSize);
			buffer.AudioBytes = chunkSize;
			buffer.pAudioData = waveData;
			buffer.PlayLength = 0;
			buffer.PlayBegin = 0;
			fData = true;
			break;
		}
		chunkSize += 9;		//include offset size
		chunkSize &= 0xfffffffe;
		i += chunkSize;
	}

	file.close();
	if (fData == false)
		return false;
	return true;
}



inline const DWORD AudioInfo::GetChunkSize()
{

}

//HRESULT AudioInfo::Load(const char * fileName, DWORD fourcc)
//{
//	if (INVALID_SET_FILE_POINTER == SetFilePointer(&fileName, 0, NULL, FILE_BEGIN));
//	return HRESULT_FROM_WIN32(GetLastError());
//
//
//	HRESULT result = S_OK;
//	DWORD chunkType;
//	DWORD chunkDataSize;
//	DWORD riffDataSize;		//RIFF
//	DWORD fileType;
//	DWORD bytes = 0;
//	DWORD offset = 0;
//
//	while (result == S_OK)
//	{
//		DWORD dwRead;
//		if (ReadFile(&fileName, &chunkType, sizeof(DWORD), &dwRead, NULL) == 0)
//		{
//			result = HRESULT_FROM_WIN32(GetLastError());
//
//			switch (chunkType)
//			{
//			case 'RIFF':
//				riffDataSize = chunkDataSize;
//				chunkDataSize = 4;
//				if (ReadFile(&fileName, &fileType, sizeof(DWORD), &dwRead, NULL))
//					result = HRESULT_FROM_WIN32(GetLastError());
//				break;
//
//			default:
//				if (INVALID_SET_FILE_POINTER == SetFilePointer(&fileName, chunkDataSize, NULL, FILE_CURRENT))
//					return HRESULT_FROM_WIN32(GetLastError());
//			}
//
//			offset += sizeof(DWORD) * 2;
//			if (chunkType == fourcc)
//			{
//				chunkType = chunkDataSize;
//				return S_OK;
//			}
//
//			offset += chunkDataSize;
//			if (bytes >= riffDataSize)
//				return S_FALSE;
//		}
//		return S_OK;
//	}
//
//
//}