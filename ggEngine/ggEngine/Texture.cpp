#include "Texture.h"
namespace ggEngine {
	Texture::Texture(LPDIRECT3DDEVICE9 device ,std::string filename, D3DCOLOR transcolor)
	{
		//standard Windows return value
		HRESULT result;
		//get width and height from bitmap file
		result = D3DXGetImageInfoFromFile(filename.c_str(), &info);
		if (result != S_OK) {
			texture = NULL;
			g_debug.Warning("Loading image failed. Src:" + (filename));
			return;
		}

		////create the new texture by loading a bitmap image file
		result = D3DXCreateTextureFromFileEx(
			device, //Direct3D device object
			filename.c_str(),				//bitmap filename
			info.Width,            //bitmap image width
			info.Height,           //bitmap image height
			1,                     //mip-map levels (1 for no chain)
			D3DPOOL_DEFAULT,       //the type of surface (standard)
			D3DFMT_UNKNOWN,        //surface format (default)
			D3DPOOL_DEFAULT,       //memory class for the texture
			D3DX_DEFAULT,          //image filter
			D3DX_DEFAULT,          //mip filter
			NULL,            //color key for transparency
			&info,                 //bitmap file info (from loaded file)
			NULL,                  //color palette
			&texture);            //destination texture

		//						  //make sure the bitmap textre was loaded correctly
		if (result != S_OK) {
			texture = NULL;
			g_debug.Warning("Creating image failed. Src:" + filename);
			return;
		}
		this->width = info.Width;
		this->height = info.Height;

	}
	Texture::Texture(LPDIRECT3DDEVICE9 device, int width, int height, D3DCOLOR transcolor)
	{
		D3DXCreateTexture(device,
			width,
			height,
			1,
			D3DUSAGE_RENDERTARGET,
			D3DFMT_A8R8G8B8,
			D3DPOOL_DEFAULT,
			&texture
		);
		texture->GetSurfaceLevel(0, &textureSurface);
		this->width = width;
		this->height = height;
	}
	Texture::~Texture()
	{
		if (texture != NULL)
			texture->Release();
	}
	int Texture::GetWidth()
	{
		return this->width;
	}
	int Texture::GetHeight()
	{
		return this->height;
	}
	
}
