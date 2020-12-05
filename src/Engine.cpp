#include "../include/Engine.h"
#include "../include/Display.h"
#include "../include/Rasteriser.h"
#include <math.h>
#include <SDL_stdinc.h>
#include <array>

Engine::Engine() :
	_rasteriser(nullptr),
	_display(nullptr),
	_is_running(false)
{

}

Engine::~Engine()
{
	//shutdown();
}
void Engine::init() {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_DisplayMode display_mode;
	SDL_GetCurrentDisplayMode(0, &display_mode);
	_display = std::make_shared<Display>(display_mode.w, display_mode.h, "Software Renderer");
	_rasteriser = std::make_unique<Rasteriser>(_display);
	_is_running = true;
}

bool Engine::isRunning() {
	return _is_running;
}

void Engine::processInput() {
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		_is_running = false;
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE) {
			_is_running = false;
		}

	}
}

void Engine::update() {
	_rasteriser->drawGrid(0xFF0000FF);
	const int pts_num = 9;
	std::vector<Vector3> cube_points;
	cube_points.reserve(pts_num * pts_num * pts_num);
	generatePointCube(9, -1, 1, cube_points);
	int point_count = 0;
	for (const Vector3& vec : cube_points) {
		Vector2 projected_point = _rasteriser->project(vec);
			_rasteriser->drawRectangle(
			projected_point.getX() + _display->getWidth() /2,
			projected_point.getY() + _display->getHeight() / 2,
			4,
			4,
			0xFFFFFF00);
	}
	cube_points.clear();
}

void Engine::render() {
	_display->update();
}

void Engine::shutdown() {
	//delete _display;
	//delete _raytracer;
}





