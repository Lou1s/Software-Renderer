#include "../include/Rasteriser.h"
#include <SDL_stdinc.h>
Rasteriser::Rasteriser(std::shared_ptr<Display> disp) :
	_display(disp)
{
}

Rasteriser::~Rasteriser()
{
}
