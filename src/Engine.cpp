#include "../include/Engine.h"
#include "../include/Display.h"
#include "../include/Rasteriser.h"
#include <math.h>
#include <SDL_stdinc.h>
#include <array>

Engine::Engine() :
	_rasteriser(nullptr),
	_display(nullptr),
	_is_running(false),
	_fov_factor(640),
	_camera_pos(0, 0, -5),
	_previous_frame_time(0)
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
	cube_rotation = Vector3(0.0, 0.0, 0.0);
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

Vector2 Engine::project(const Vector3& vec) {
	//using similar triangles here to get the projected x and y (perspective divide), basically the bigger the z the further away the point is, so the smaller it is on our screen.
	float z = vec.getZ() - _camera_pos.getZ();
	Vector2 proj_pt(vec.getX(), vec.getY());
	proj_pt *= _fov_factor;
	proj_pt /= z;

	return proj_pt;
}


void Engine::update() {
	int time_to_wait = _display->FRAME_TARGET_TIME - (SDL_GetTicks() - _previous_frame_time);
	if (time_to_wait > 0 && time_to_wait <= _display->FRAME_TARGET_TIME) {
		SDL_Delay(time_to_wait);
	}

	cube_rotation += Vector3(5.7, 5.7, 5.7);
	_rasteriser->drawGrid(0xFF0000FF);
	const int pts_num = 9;
	std::vector<Vector3> cube_points;
	cube_points.reserve(pts_num * pts_num * pts_num);
	generatePointCube(cube_points);

	for (const Vector3& vec : cube_points) {
		Vector3 transformed_point(vec);
		transformed_point.rotateZ(cube_rotation.getZ());
		transformed_point.rotateY(cube_rotation.getY());
		transformed_point.rotateX(cube_rotation.getX());

		Vector2 projected_point = project(transformed_point);
		_rasteriser->drawRectangle(
			projected_point.getX() + _display->getWidth() / 2,
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





