#pragma once
#include <d3d9.h>
#pragma commnet(lib,"d3d9.lib");

struct TransformedColouredVertex{
	float x, y, z, rhw;
	DWORD colour;
	static const DWORD FORMAT = D3DFVF_XYZRHW | D3DFVF_DIFFUSE;
	static const int STRIDE_SIZE = 20;
};