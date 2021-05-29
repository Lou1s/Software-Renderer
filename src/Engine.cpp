#include "../include/Engine.h"
#include "../include/Display.h"
#include "../include/Rasteriser.h"
#include <math.h>
#include <SDL_stdinc.h>
#include <array>
#include <algorithm>

Engine::Engine() :
	_rasteriser(nullptr),
	_display(nullptr),
	_is_running(false),
	_fov_factor(640),
	_camera_pos(0, 0, -5),
	_previous_frame_time(0),
	_mesh_rotation(0, 2, 0),
	_mesh(),
	_backface_cull(true),
	_translate_factor_x(0.2)
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
	_mesh = std::make_unique<Mesh>();


}

void Engine::setup() {
	_mesh->loadFromFile("D:\\Projects\\Software-Renderer\\assets\\f22.obj");
	_mesh->translation.setZ(5);
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
	
	// add any extra scales, rotatations or translations here
	_mesh->rotation += Vector3(6, 12, 3);
	_mesh->computeTransform();

	std::vector<Vector4> verts(_mesh->vertices);

	for (Vector4& vert : verts) {
			vert = _mesh->transform * vert;
	}
	
	for (size_t i = 0; i < _mesh->faces.size(); i++) {
		Face mesh_face = _mesh->faces[i];
		Triangle3D tri_3D(verts[mesh_face.a - 1], verts[mesh_face.b - 1], verts[mesh_face.c - 1]);
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
		tri.avg_depth = tri_3D.getAverageDepth();
		_rendering_triangles.push_back(tri);
	}


}

void Engine::render() {
	//very naive painter's algo
	SortTrianglesPainterAlgorithm();
	_rasteriser->drawGrid(0xFF2F4F4F);
	for (size_t i = 0; i < _rendering_triangles.size(); i++) {
		_rasteriser->setTriangleDrawingMethod(TriangleDrawingMethod::FBFT);
		_rasteriser->drawTriangle(_rendering_triangles[i], 0xFFA9A9A9);
		_rasteriser->setTriangleDrawingMethod(TriangleDrawingMethod::WIREFRAME);
		_rasteriser->drawTriangle(_rendering_triangles[i], 0xFFD3D3D3);
	}
	_rendering_triangles.clear();
	_display->update();
}

void Engine::SortTrianglesPainterAlgorithm() {
	std::sort(_rendering_triangles.begin(), _rendering_triangles.end(), [](Triangle tri1, Triangle tri2) {return tri1.avg_depth > tri2.avg_depth; });
}






