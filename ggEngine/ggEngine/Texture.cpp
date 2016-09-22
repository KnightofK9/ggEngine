#include "Texture.h"
namespace ggEngine {
	Texture::Texture(LPDIRECT3DDEVICE9 device ,std::string filename, D3DCOLOR transcolor)
	{
		//standard Windows return value
		HRESULT result;
		LPCWSTR fileSrc = Helper::StringToLPCWSTR(filename);
		//get width and height from bitmap file
		result = D3DXGetImageInfoFromFile(fileSrc, &info);
		if (result != D3D_OK) {
			texture = NULL;
			Debug::Warning("Loading image failed. Src:" + filename);
			return;
		}

		////create the new texture by loading a bitmap image file
		result = D3DXCreateTextureFromFileEx(
			device, //Direct3D device object
			fileSrc,				//bitmap filename
			info.Width,            //bitmap image width
			info.Height,           //bitmap image height
			1,                     //mip-map levels (1 for no chain)
			D3DPOOL_DEFAULT,       //the type of surface (standard)
			D3DFMT_UNKNOWN,        //surface format (default)
			D3DPOOL_DEFAULT,       //memory class for the texture
			D3DX_DEFAULT,          //image filter
			D3DX_DEFAULT,          //mip filter
			transcolor,            //color key for transparency
			&info,                 //bitmap file info (from loaded file)
			NULL,                  //color palette
			&texture);            //destination texture

		//						  //make sure the bitmap textre was loaded correctly
		if (result != S_OK) {
			texture = NULL;
			Debug::Warning("Creating image failed. Src:" + filename);
			return;
		}

	}
	Texture::~Texture()
	{
		Destroy();
	}
	int Texture::GetWidth()
	{
		return info.Width;
	}
	int Texture::GetHeight()
	{
		return info.Height;
	}
	void Texture::Destroy()
	{
		if (texture != NULL)
			texture->Release();
	}
}
