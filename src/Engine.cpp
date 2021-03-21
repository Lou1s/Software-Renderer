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
	_mesh(nullptr),
	_backface_cull(true)
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
	mesh_rotation = Vector3(0, 0, 0);
	_is_running = true;
	_mesh = std::make_unique<Mesh>();

}

void Engine::setup() {
	_mesh->loadFromFile("D:\\Projects\\Software-Renderer\\assets\\cube.obj");
	_rasteriser->setTriangleDrawingMethod(TriangleDrawingMethod::FBFT);
}

void Engine::setFlags(bool backface) {
	_backface_cull = backface;
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

Triangle Engine::project(const Triangle3D& tri) {
	Triangle3D temp_tri(tri);
	Triangle projected_tri(project(temp_tri.a()), project(temp_tri.b()), project(temp_tri.c()));
	return projected_tri;
}


void Engine::update() {
	int time_to_wait = _display->FRAME_TARGET_TIME - (SDL_GetTicks() - _previous_frame_time);
	if (time_to_wait > 0 && time_to_wait <= _display->FRAME_TARGET_TIME) {
		SDL_Delay(time_to_wait);
	}
	_previous_frame_time = SDL_GetTicks();
	_rendering_triangles.clear();
	
	mesh_rotation += Vector3(6,2,4);

	for (size_t i = 0; i < _mesh->faces.size(); i++) {
		Face mesh_face = _mesh->faces[i];
		Triangle3D tri_3D(_mesh->vertices[mesh_face.a - 1], _mesh->vertices[mesh_face.b - 1], _mesh->vertices[mesh_face.c - 1]);

		//apply rotation
		tri_3D.rotateInPlace(mesh_rotation);
		//translate away from the camera in z
		tri_3D.translate(Vector3(0, 0, 5));

		//backface culling
		if (_backface_cull) {
			Vector3 camera_ray = (_camera_pos - tri_3D.a()).normalise();
			if (camera_ray.dot(tri_3D.normal()) < 0.0) {
				continue;
			}
		}

		//project
		Triangle tri = project(tri_3D);
		//send to the middle f the screen
		tri.translate(Vector2(_display->getWidth() / 2, _display->getHeight() / 2));

		_rendering_triangles.push_back(tri);
	}


}

void Engine::render() {
	_rasteriser->drawGrid(0xFF2F4F4F);
	for (size_t i = 0; i < _rendering_triangles.size(); i++) {
		//for (size_t j = 0; j < 3; j++) {
			//_rasteriser->drawRectangle(tri.points[j].getX(), tri.points[j].getY(), 3, 3, 0xFF00FFFF);
		//}
		_rasteriser->setTriangleDrawingMethod(TriangleDrawingMethod::FBFT);
		_rasteriser->drawTriangle(_rendering_triangles[i], 0xFF0088FF);
		_rasteriser->setTriangleDrawingMethod(TriangleDrawingMethod::WIREFRAME);
		_rasteriser->drawTriangle(_rendering_triangles[i], 0xFF0000FF);
	}
	_rendering_triangles.clear();
	_display->update();
	//_display->clearPixelBuffer(0xFF000000);
}

void Engine::shutdown() {
	//delete _display;
	//delete _raytracer;
}





