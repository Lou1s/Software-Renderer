#pragma once
class Display;
#include "../include/MathUtils.h"
#include <memory>
#include <SDL_stdinc.h>

class Rasteriser
{
public:
	Rasteriser(std::shared_ptr<Display> disp);
	~Rasteriser();
	void drawLine();
	void drawTriangle();
	void drawGrid(Uint32 grid_colour);
	void drawRectangle(int x, int y, int width, int height, Uint32 colour);
	
private:
	std::shared_ptr<Display> _display;
	
};

