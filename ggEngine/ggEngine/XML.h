#pragma once
#include <ole2.h>
#include <xmllite.h>
#include <stdio.h>
#include <shlwapi.h>
#include <string>
#include "GGObject.h"
#include <map>
#include <list>
#include <vector>
#pragma comment(lib,"xmllite.lib")
#pragma comment(lib,"Shlwapi.lib")
namespace ggEngine {
	struct AtlasSpriteInfo {
		std::string name;
		double x, y, width, height;
	};
	class XML : public GGObject {
	public:
		XML(std::string path);
		virtual ~XML();
		std::vector<AtlasSpriteInfo> GetSpriteList();
		bool IsLoaded() { return !this->fileNotFound; }
	private:
		bool fileNotFound = false;
		std::vector<AtlasSpriteInfo> spriteList;
		std::vector<AtlasSpriteInfo> ConstructAtlasSpriteInfo(IXmlReader *pReader, IStream *pFileStream);
		void SafeRelease(IStream *pStream);
		void SafeRelease(IXmlReader *pReader);
		HRESULT WriteAttributes(IXmlReader* pReader, AtlasSpriteInfo *atlasSpriteInfo);
	};
}