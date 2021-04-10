#include "../include/Rasteriser.h"
#include "../include/Display.h"
#include <algorithm>


Rasteriser::Rasteriser(std::shared_ptr<Display> disp, const LineDrawingMethod& line_draw, const TriangleDrawingMethod& tri_draw) :
	_display(disp),
	_line_draw_method{line_draw},
	_triangle_draw_method{tri_draw}
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
	_line_draw_method = line_draw;
}

void Rasteriser::setTriangleDrawingMethod(const TriangleDrawingMethod& tri_draw)
{
	_triangle_draw_method = tri_draw;
}

void Rasteriser::drawDDALine(const Vector2& vec1, const Vector2& vec2, Uint32 colour)
{
	//Vector2 delta(int(vec1.getX()) - int(vec2.getX()), int(vec1.getY()) - int(vec2.getY()));
	Vector2 delta = vec1 - vec2;
	int side_length = std::abs(delta.getX()) >= abs(delta.getY()) ? std::abs(delta.getX()) : std::abs(delta.getY());
	Vector2 increment = delta / (float)side_length;
	Vector2 current_pos(vec2);

	for (int i = 0; i <= side_length; i++) {
		_display->drawPixel(int(round(current_pos.getX())), int(round(current_pos.getY())), colour);
		current_pos += increment;
	}
}

void Rasteriser::drawLine(const Vector2& vec1, const Vector2& vec2, Uint32 colour)
{
	Vector2 vec1_int(vec1);
	Vector2 vec2_int(vec2);

	vec1_int.integise();
	vec2_int.integise();

	switch (_line_draw_method) {
		case LineDrawingMethod::DDA:
			drawDDALine(vec1_int, vec2_int, colour);
			break;
		case LineDrawingMethod::BRESENHAM:
			break;
		case LineDrawingMethod::XIAOLINWU:
			break;

	}
}

void Rasteriser::drawTriangleWireframe(const Triangle& tri, Uint32 colour) {
	drawLine(tri.points[0], tri.points[1], colour);
	drawLine(tri.points[1], tri.points[2], colour);
	drawLine(tri.points[2], tri.points[0], colour);
}

Vector2 getFBFTTriMidPoint(const Vector2& p0, const Vector2& p1, const Vector2& p2) {
	float mid_y = p1.getY();
	float mid_x = (((p1.getY() - p0.getY()) * (p2.getX() - p0.getX())) / (p2.getY() - p0.getY())) + p0.getX();
	return Vector2(mid_x, mid_y);
}

void Rasteriser::drawTriangleFBFT(const Triangle& tri, Uint32 colour) {
	//sort in order of vertices
	std::vector<Vector2> verts{ tri.points[0], tri.points[1], tri.points[2] };
	//cheeky little lambda function to sort the verts easily
	std::sort(verts.begin(), verts.end(), [](Vector2& vec1, Vector2& vec2) {return vec1.getY() < vec2.getY(); });
	
	if (verts[1].getY() == verts[2].getY()) {
		fillTriangleFlatBot(Triangle(verts[0], verts[1], verts[2]), colour);
	}

	else if (verts[0].getY() == verts[1].getY()) {
		fillTriangleFlatTop(Triangle(verts[0], verts[1], verts[2]), colour);
	}
	else {

		Vector2 mid_point = getFBFTTriMidPoint(verts[0], verts[1], verts[2]);
		Triangle flat_bot(verts[0], verts[1], mid_point);
		Triangle flat_top(verts[1], mid_point, verts[2]);


		fillTriangleFlatBot(flat_bot, colour);
		fillTriangleFlatTop(flat_top, colour);
	}
}

void Rasteriser::fillTriangleFlatBot(const Triangle& tri, Uint32 colour) {
	//compute inverse clope -- change in x with respect to y, as we are using scanline, moving incrementally in y.

	float slope1 = (float)(tri.points[1].getX() - tri.points[0].getX()) / (tri.points[1].getY() - tri.points[0].getY());
	float slope2 = (float)(tri.points[2].getX() - tri.points[0].getX()) / (tri.points[2].getY() - tri.points[0].getY());

	float x_start, x_end;
	x_start = x_end = int(tri.points[0].getX());

	int y0 = int(tri.points[0].getY());
	int y2 = int(tri.points[2].getY());
	for (int y = y0; y <= y2; ++y) {
		drawLine(Vector2(x_start, y), Vector2(x_end, y), colour);
		x_start += slope1;
		x_end += slope2;
		}
}

void Rasteriser::fillTriangleFlatTop(const Triangle& tri, Uint32 colour) {

	float slope1 = (float)(tri.points[2].getX() - tri.points[0].getX()) / (tri.points[2].getY() - tri.points[0].getY());
	float slope2 = (float)(tri.points[2].getX() - tri.points[1].getX()) / (tri.points[2].getY() - tri.points[1].getY());

	float x_start, x_end;
	x_start = x_end = int(tri.points[2].getX());

	int y2 = int(tri.points[2].getY());
	int y1 = int(tri.points[1].getY());
	for (int y = y2; y >= y1; --y) {
		drawLine(Vector2(x_start, y), Vector2(x_end, y), colour);
		x_start -= slope1;
		x_end -= slope2;
	}
}


void Rasteriser::drawTriangle(const Triangle &tri, Uint32 colour)
{	
	Triangle tri_int(tri);
	tri_int.integise();

	switch (_triangle_draw_method) {
		case TriangleDrawingMethod::WIREFRAME:
			drawTriangleWireframe(tri_int, colour);
			break;
		case TriangleDrawingMethod::FBFT:
			drawTriangleFBFT(tri_int, colour);
			break;
	}
	
}

Rasteriser::~Rasteriser() {
}