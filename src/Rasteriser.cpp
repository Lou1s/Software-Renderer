#include "../include/Rasteriser.h"
#include "../include/Display.h"


Rasteriser::Rasteriser(std::shared_ptr<Display> disp, const LineDrawingMethod& line_draw) :
	_display(disp),
	_line_draw_method{line_draw}
{

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

void Rasteriser::setLineDrawingMethod(const LineDrawingMethod& line_draw)
{
}

void Rasteriser::drawDDALine(const Vector2& vec1, const Vector2& vec2, Uint32 colour)
{
	Vector2 delta = vec1 - vec2;
	int side_length = std::abs(delta.getX()) >= abs(delta.getY()) ? std::abs(delta.getX()) : std::abs(delta.getY());
	Vector2 increment = delta / (float)side_length;
	Vector2 current_pos(vec2);

	for (int i = 0; i <= side_length; i++) {
		_display->drawPixel(int(round(current_pos.getX())), int(round(current_pos.getY())), colour);
		current_pos += increment;
	}
}

void Rasteriser::drawLine(Vector2 vec1, Vector2 vec2, Uint32 colour)
{
	switch (_line_draw_method) {
		case LineDrawingMethod::DDA:
			drawDDALine(vec1, vec2, colour);
			break;
		case LineDrawingMethod::BRESENHAM:
			break;
		case LineDrawingMethod::XIAOLINWU:
			break;

	}
}

void Rasteriser::drawTriangle(const Triangle &tri, Uint32 colour)
{
	drawLine(tri.points[0], tri.points[1], colour);
	drawLine(tri.points[1], tri.points[2], colour);
	drawLine(tri.points[2], tri.points[0], colour);
}

Rasteriser::~Rasteriser() {
}