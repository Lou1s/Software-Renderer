#include "../include/Shader.h"
#include <algorithm>

Shader::Shader():
	_global_light(Vector3(0.0, 0.0, 1)),
	_flat_colour(0xFF007BA7),
	_wire_colour(0xFFD3D3D3)
{

}
Shader::Shader(const Light& l) :
	_global_light(l),
	_flat_colour(0xFF007BA7),
	_wire_colour(0xFFD3D3D3)
{

}

Uint32 Shader::getFlatShadeColour(Triangle3D &tri) {
	float intensity = -tri.normal().dot(_global_light.direction);
	intensity = std::max(0.0, std::min(double(intensity), 1.0));

	Uint32 a = _flat_colour & 0xFF000000;
	Uint32 r = (_flat_colour & 0x00FF0000) * intensity;
	Uint32 g = (_flat_colour & 0x0000FF00) * intensity;
	Uint32 b = (_flat_colour & 0x000000FF) * intensity;
	Uint32 shaded_col = a | (r & 0x00FF0000) | (g & 0x0000FF00) | (b & 0x000000FF);

	return shaded_col;
}

Uint32 Shader::getFlatColour() {
	return _flat_colour;
}

Uint32 Shader::getWireframeColour() {
	return _wire_colour;
}