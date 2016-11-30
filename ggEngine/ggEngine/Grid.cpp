#include "Grid.h"
#include "Camera.h"
#include "NiseVector.h"
#include "Game.h"
namespace ggEngine {
	Grid::Grid(Game *game) :GameObject(game)
	{
		SetAnchor(0, 0);
		this->camera = game->camera;
	}

	Grid::~Grid()
	{
	}


	void Grid::Draw()
	{

		double cX, cY;

		NiseVector point = NiseVector(this->worldPosition.x, this->worldPosition.y);
		point.SetTransform(this->camera->GetTranslatedMatrix());
		cX = point.x;
		cY = point.y;
		for (int i = 0; i < numberOfLineHorizontal; i++) {
			this->drawManager->DrawLine(Vector(cX, 0), Vector(cX, height), DEFAULT_COLOR);
			cX += cellWidth;
		}
		for (int i = 0; i < numberOfLineVertical; i++) {
			this->drawManager->DrawLine(Vector(0, cY), Vector(width, cY), DEFAULT_COLOR);
			cY += cellHeight;
		}
	}

	void Grid::SetWidth(double width)
	{
		GameObject::SetWidth(width);
		numberOfLineHorizontal = (int)width / cellWidth;

	}

	void Grid::SetHeight(double height)
	{
		GameObject::SetHeight(height);
		numberOfLineVertical = (int)height / cellHeight;
	}


}