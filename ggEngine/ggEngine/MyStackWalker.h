#pragma once
#include "StackWalker.h"
#include "Debug.h"
namespace ggEngine {
	class MyStackWalker : public StackWalker
	{
	public:
		MyStackWalker() : StackWalker() {}
	protected:
		virtual void OnOutput(LPCSTR szText)
		{
			g_debug.Error(szText); StackWalker::OnOutput(szText);
		}
	};
}