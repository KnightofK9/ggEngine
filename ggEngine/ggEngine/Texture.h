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
		Texture(std::string fileSource, D3DCOLOR transcolor);
		~Texture();
		int GetWidth();
		int GetHeight();
		void Destroy();
		LPDIRECT3DTEXTURE9 GetTexture() { return this->texture; }
	private:
		LPDIRECT3DTEXTURE9 texture;
		D3DXIMAGE_INFO info;
	};
}