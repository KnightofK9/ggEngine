#pragma once
#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")
class DriverInfoManager {
public:
	DriverInfoManager(IDirect3D9 &d3d);
	~DriverInfoManager();
	D3DADAPTER_IDENTIFIER9 getIdentifier();
private:
	D3DADAPTER_IDENTIFIER9 pIdentifier;
};