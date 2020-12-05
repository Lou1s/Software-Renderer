#include "../include/Rasteriser.h"
#include "../include/Display.h"


Rasteriser::Rasteriser(std::shared_ptr<Display> disp) :
	_display(disp)
{
	_fov_factor = 640;
	_camera_pos = Vector3(0, 0, -5);
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
	//using similar triangles here to get the projected x and y (perspective divide), basically the bigger the z the further away the point is, so the smaller it is on our screen.
	float z = vec.getZ() - _camera_pos.getZ();
	Vector2 proj_pt(vec.getX(), vec.getY());
	proj_pt *= _fov_factor;
	proj_pt /= z;
	
	return proj_pt;
}

Rasteriser::~Rasteriser() {
}

