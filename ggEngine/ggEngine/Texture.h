#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include "Helper.h"
#include "GGObject.h"
#include "Debug.h"

namespace ggEngine {
	class Texture : public GGObject {
	public:
		Texture(LPDIRECT3DDEVICE9 device, std::string fileSource, D3DCOLOR transcolor = D3DCOLOR_XRGB(255, 0, 255));
		~Texture();
		int GetWidth();
		int GetHeight();
		void Destroy();
		LPDIRECT3DTEXTURE9 GetDxTexture() { return this->texture; }
	private:
		LPDIRECT3DTEXTURE9 texture;
		D3DXIMAGE_INFO info;
	};
}