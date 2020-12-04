#include "../include/Rasteriser.h"
#include "../include/Display.h"


Rasteriser::Rasteriser(std::shared_ptr<Display> disp) :
	_display(disp)
{
	_fov_factor = 128;
}

void Rasteriser::drawGrid(Uint32 grid_colour) {
	for (int i = 0; i < _display->getWidth(); i += 10) {
		for (size_t j = 0; j < _display->getHeight(); j += 10) {
			_display->drawPixel(i, j, grid_colour);
		}
	}
}

void Rasteriser::drawRectangle(int x, int y, int width, int height, Uint32 colour)
{
	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++) {
			_display->drawPixel(j + x, i + y, colour);
		}
	}

}


Vector2 Rasteriser::project(const Vector3& vec) {
	Vector2 proj_pt(vec.getX(), vec.getY());
	proj_pt *= _fov_factor;
	return proj_pt;
}

Rasteriser::~Rasteriser() {
}

