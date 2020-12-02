#pragma once
class Display;

#include <memory>
#include <SDL_stdinc.h>

class Rasteriser
{	public:
	Rasteriser(std::shared_ptr<Display> disp);
	~Rasteriser();
	void drawLine();
	void drawTriangle();
	void drawGrid();
	void drawRectangle(int x, int y, int width, int height, Uint32 colour);
	void projectionTest();
private:
	std::shared_ptr<Display> _display;
};

