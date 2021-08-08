#pragma once
#include "../include/Light.h"
#include "../include/Mesh.h"
class Shader
{
public:
	Shader();
	Shader(const Light& l);
	Uint32 getFlatShadeColour(Triangle3D &tri);
	Uint32 getFlatColour();
	Uint32 getWireframeColour();

private:
	Light _global_light;
	Uint32 _flat_colour;
	Uint32 _wire_colour;
};

