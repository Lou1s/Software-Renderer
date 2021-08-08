#pragma once
#include "MathUtils.h"
#include "Display.h"

class Light
{	
public:
	Vector3 direction;

	Light();
	Light(const Vector3 &dir) : direction(dir) {}
	

	
};

