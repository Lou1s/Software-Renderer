#include "../include/Rasteriser.h"
#include "../include/Display.h"
#include <SDL_stdinc.h>
Rasteriser::Rasteriser(std::shared_ptr<Display> disp) :
	_display(disp)
{
}

void Rasteriser::drawGrid() {
	Uint32 grid_colour1 = 0xFF0000FF;
	Uint32 grid_colour2 = 0xFF00FFFF;
	for (int i = 0; i < _display->getWidth(); i += 100) {
		for (size_t j = 0; j < _display->getHeight(); j++) {
			_display->drawPixel(i, j, grid_colour1);
		}
	}

	for (int i = 0; i < _display->getHeight(); i += 100) {
		for (size_t j = 0; j < _display->getWidth(); j++) {
			_display->drawPixel(j, i, grid_colour2);
		}
	}
}

Rasteriser::~Rasteriser()
{
}

