#include "Helper.h"
#include "Group.h"
namespace ggEngine {
	LPCWSTR Helper::StringToLPCWSTR(const std::string & s)
	{
		int len;
		int slength = (int)s.length() + 1;
		len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
		wchar_t* buf = new wchar_t[len];
		MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
		std::wstring r(buf);
		delete[] buf;
		std::wstring stemp = r;
		return stemp.c_str();
	}

	std::string Helper::WCharToString(const LPCWSTR  s)
	{
		std::wstring ws(s);
		std::string test(ws.begin(), ws.end());
		return test;
	}

	RECT ggEngine::Helper::intersectRectAndGroup(RECT & srcRect, GameObject * go, Group * group)
	{
		RECT groupRect = { -go->position.x,-go->position.y,group->GetWidth() - go->position.x,group->GetHeight() - go->position.y };
		RECT insRect;
		IntersectRect(&insRect, &srcRect, &groupRect);
		return insRect;
	}
}

