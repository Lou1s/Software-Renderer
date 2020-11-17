#pragma once
class Display;

#include <memory>

class Rasteriser
{	public:
	Rasteriser(std::shared_ptr<Display> disp);
	~Rasteriser();
	void drawLine();
	void drawTriangle();
private:
	std::shared_ptr<Display> _display;
};

