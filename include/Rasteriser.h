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

enum class TriangleDrawingMethod {
	WIREFRAME,
	FBFT
};

class Rasteriser
{
public:

	Rasteriser(std::shared_ptr<Display> disp, const LineDrawingMethod& line_draw = LineDrawingMethod::DDA, const TriangleDrawingMethod& tri_draw = TriangleDrawingMethod::WIREFRAME);
	~Rasteriser();
	void drawLine(const Vector2& vec1, const Vector2& vec2, Uint32 colour);
	void drawTriangle(const Triangle& tri, Uint32 colour);
	void drawGrid(Uint32 grid_colour);
	void drawRectangle(int x, int y, int width, int height, Uint32 colour);
	void setLineDrawingMethod(const LineDrawingMethod& line_draw);
	void setTriangleDrawingMethod(const TriangleDrawingMethod& tri_draw);
	
private:
	std::shared_ptr<Display> _display;
	LineDrawingMethod _line_draw_method;
	TriangleDrawingMethod _triangle_draw_method;

	void drawDDALine(const Vector2& vec1, const Vector2& vec2, Uint32 colour);
	void drawTriangleWireframe(const Triangle& tri, Uint32 colour);
	void drawTriangleFBFT(const Triangle& tri, Uint32 colour);
	void fillTriangleFlatBot(const Triangle& tri, Uint32 colour);
	void fillTriangleFlatTop(const Triangle& tri, Uint32 colour);

};



