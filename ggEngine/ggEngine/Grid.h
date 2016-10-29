#pragma once
#include "GameObject.h"
namespace ggEngine {
	class Camera;
	class Grid : public GameObject {
	public:
		Grid(Camera* camera,DrawManager *drawManager);
		~Grid();
		void SetCellWidth(int cellWidth) { this->cellWidth = cellWidth; }
		void SetCellHeight(int cellHeight) { this->cellHeight = cellHeight; }
		int GetCellWidth() { return this->cellWidth; }
		int GetCellHeight() { return this->cellHeight; }
		void Draw() override;
		void SetWidth(double width);
		void SetHeight(double height);
	private:
		Camera *camera;
		int cellWidth;
		int cellHeight;
		int numberOfLineVertical;
		int numberOfLineHorizontal;
	};
}