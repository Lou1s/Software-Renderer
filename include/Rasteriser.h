#pragma once
class Display;
#include "../include/MathUtils.h"
#include "../include/Mesh.h"
#include <memory>
#include <SDL_stdinc.h>

enum class LineDrawingMethod {
	DDA,
	BRESENHAM,
	XIAOLINWU
};

class Rasteriser
{
public:

	Rasteriser(std::shared_ptr<Display> disp, const LineDrawingMethod& line_draw = LineDrawingMethod::DDA);
	~Rasteriser();
	void drawLine(Vector2 vec1, Vector2 vec2, Uint32 colour);
	void drawTriangle(const Triangle& tri, Uint32 colour);
	void drawGrid(Uint32 grid_colour);
	void drawRectangle(int x, int y, int width, int height, Uint32 colour);
	void setLineDrawingMethod(const LineDrawingMethod& line_draw);
	
private:
	std::shared_ptr<Display> _display;
	LineDrawingMethod _line_draw_method;

	void drawDDALine(const Vector2& vec1, const Vector2& vec2, Uint32 colour);
};



