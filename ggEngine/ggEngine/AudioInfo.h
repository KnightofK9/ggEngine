#pragma once
#include "Debug.h"
#include "Helper.h"
#include "dxutil.h"
#include "dsutil.h"
#include <DxErr.h>



namespace ggEngine {
	class Game;
	class AudioInfo
	{
	public:
		AudioInfo(Game *game, std::string filePath);
		virtual ~AudioInfo();


	private:
	};
}
