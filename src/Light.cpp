#include "../include/Light.h"

Uint32 Light::applyIntensity(Uint32 original_colour, float intensity)
{
	Uint32 a = original_colour & 0xFF000000;
	Uint32 r = intensity * (original_colour & 0x00FF0000);
	Uint32 g = original_colour & 0x0000FF00;
	Uint32 b = original_colour & 0x000000FF;

	return Uint32();
}
