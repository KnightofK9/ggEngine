#include "Tile.h"

ggEngine::Tile::Tile(Game *game, SpriteInfo * image) : Sprite(game,image)
{
}

ggEngine::Tile::~Tile()
{
}

void ggEngine::Tile::Draw(double x, double y)
{
	x += position.x;
	y += position.y;
	RECT srcRect = image->GetRect();
	D3DXVECTOR3 posRect(x, y,0);
	color = (color & 0x00FFFFFF) | (opacity << 24);
	spriteHandle->Draw(this->GetImage()->GetTexture()->GetDxTexture(), &srcRect, NULL, &posRect, color);
}
