#include "DriverInfoManager.h"

DriverInfoManager::DriverInfoManager(IDirect3D9 &d3d)
{
	d3d.GetAdapterIdentifier(D3DADAPTER_DEFAULT, 0, &pIdentifier);
}

DriverInfoManager::~DriverInfoManager()
{
}

D3DADAPTER_IDENTIFIER9 DriverInfoManager::getIdentifier()
{
	return pIdentifier;
}
