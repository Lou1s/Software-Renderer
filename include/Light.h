#pragma once
#include "MathUtils.h"
#include "Display.h"

class Light
{	
	Vector3 direction;

	Light();
	Light(const Vector3 &dir) : direction(dir) {}
	Uint32 applyIntensity(const Uint32 original_colour, float intensity);

	
};

