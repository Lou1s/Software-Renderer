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
	_previous_frame_time(0),
	_mesh(nullptr)
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
	cube_rotation = Vector3(2, 1, 6);
	_is_running = true;
	_mesh = std::make_unique<Mesh>();

}

void Engine::setup() {
	_mesh->loadFromFile("D:\\Projects\\Software-Renderer\\assets\\f22.obj");
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
	float z = vec.getZ();
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
	_rendering_triangles.clear();
	_rasteriser->drawGrid(0xFF2F4F4F);

	//animate
	_mesh->rotate(Vector3(7, 5, 6));
	

	for (size_t i = 0; i < _mesh->faces.size(); i++) {
		Face mesh_face = _mesh->faces[i];
		Vector3 face_vertices[3]{
			_mesh->vertices[mesh_face.a - 1],
			_mesh->vertices[mesh_face.b - 1],
			_mesh->vertices[mesh_face.c - 1]
		};

		Triangle tri;
		for (size_t j = 0; j < 3; j++) {
			Vector3 transformed_vert = face_vertices[j];
			//translate vertex away from the camera in z
			transformed_vert.setZ(transformed_vert.getZ() - _camera_pos.getZ());
			//project the point
			Vector2 projected_point = project(transformed_vert);
			//scale and translate projected point ot the middle of the screen
			projected_point.setX(projected_point.getX() + _display->getWidth() / 2);
			projected_point.setY(projected_point.getY() + _display->getHeight() / 2);
			tri.points[j] = projected_point;
		}
		_rendering_triangles.push_back(tri);
	}


}

void Engine::render() {
	for (size_t i = 0; i < _rendering_triangles.size(); i++) {
		Triangle& tri = _rendering_triangles[i];

		for (size_t j = 0; j < 3; j++) {
			_rasteriser->drawRectangle(tri.points[j].getX(), tri.points[j].getY(), 3, 3, 0xFF00FFFF);
		}

		_rasteriser->drawTriangle(tri, 0xFF00FFFF);

	}
	_display->update();
}

void Engine::shutdown() {
	//delete _display;
	//delete _raytracer;
}





