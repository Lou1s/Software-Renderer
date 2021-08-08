#include "../include/Engine.h"
#include <math.h>
#include <SDL_stdinc.h>
#include <array>
#include <algorithm>

Engine::Engine() :
	_rasteriser(nullptr),
	_display(nullptr),
	_shader(nullptr),
	_is_running(false),
	_camera_pos(0, 0, -5),
	_previous_frame_time(0),
	_mesh_rotation(0, 0, 0),
	_mesh(),
	_backface_cull(true),
	_translate_factor_x(0.2),
	_projection_matrix(),
	proj_mod_trans(),
	proj_mod_scale()

{

}

void Engine::init() {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_DisplayMode display_mode;
	SDL_GetCurrentDisplayMode(0, &display_mode);
	_display = std::make_shared<Display>(display_mode.w, display_mode.h, "Software Renderer");
	_rasteriser = std::make_unique<Rasteriser>(_display);
	_shader = std::make_unique<Shader>();
	_is_running = true;
	_mesh = std::make_unique<Mesh>();
	proj_mod_trans = Vector3(_display->getWidth() / 2.0, _display->getHeight() / 2.0, 0.0);
	proj_mod_scale = Vector3(_display->getWidth() / 10.0, _display->getHeight() / 10.0, 1.0);
	


}

void Engine::setup() {
	_mesh->loadFromFile("D:\\Projects\\Software-Renderer\\assets\\car_lowpoly.obj");
	_mesh->translation.setZ(50);
	_mesh->rotation.setX(180);
	_mesh->scale.set(1.0, 1.0, 1.0);
	_rasteriser->setTriangleDrawingMethod(TriangleDrawingMethod::FBFT);

	//set up perspective projection matrix
	 float aspect_ratio = float(_display->getHeight()) / float(_display->getWidth());
	 float fov_angle = 90.0;
	 float z_near = 0.1;
	 float z_far = 100.0;
	 _projection_matrix.makeProjection(fov_angle, aspect_ratio, z_near, z_far);
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

Vector2 Engine::project(const Vector4& vec) {
	Vector4 result = _projection_matrix * vec;
	
	if (result.getW() != 0.0) {
		result /= result.getW();
	}
	return Vector2(result.getX(), result.getY());
}



Vector4 Engine::project3D(const Vector4& vec) {
	//perpective projection
	Vector4 result = _projection_matrix * vec;
	//perspective divide - currently displays things that are behind the camera (dividing by negative simply flips the x and y)
	if (result.getW() != 0.0) {
		result /= result.getW();
	}
	return result;
}

Triangle3D Engine::project3D(const Triangle3D& tri) {
	Triangle3D temp_tri(tri);
	Triangle3D projected_tri(project3D(temp_tri.a()), project3D(temp_tri.b()), project3D(temp_tri.c()));
	return projected_tri;
}

void Engine::update() {
	int time_to_wait = _display->FRAME_TARGET_TIME - (SDL_GetTicks() - _previous_frame_time);
	if (time_to_wait > 0 && time_to_wait <= _display->FRAME_TARGET_TIME) {
		SDL_Delay(time_to_wait);
	}
	_previous_frame_time = SDL_GetTicks();
	
	// add any extra scales, rotatations or translations here
	_mesh->rotation += Vector3(0, 4, 0);
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
		Triangle3D proj_tri = project3D(tri_3D);
		
		
		
		//scale into the view
		proj_tri.scale(proj_mod_scale);
		
		//translate to the middle of the screen
		proj_tri.translate(proj_mod_trans);
		Triangle tri_2D(proj_tri, _shader->getFlatShadeColour(tri_3D), proj_tri.getAverageDepth());
		_rendering_triangles.push_back(tri_2D);
	}


}

void Engine::render() {
	//very naive painter's algo
	SortTrianglesPainterAlgorithm();
	//_rasteriser->drawGrid(0xFF2F4F4F);
	for (size_t i = 0; i < _rendering_triangles.size(); i++) {
		Triangle& tri = _rendering_triangles[i];
		_rasteriser->setTriangleDrawingMethod(TriangleDrawingMethod::FBFT);
		_rasteriser->drawTriangle(tri, tri.colour);
		//_rasteriser->setTriangleDrawingMethod(TriangleDrawingMethod::WIREFRAME);
		//_rasteriser->drawTriangle(_rendering_triangles[i], _shader->getWireframeColour());
	}
	_rendering_triangles.clear();
	_display->update();
}

void Engine::SortTrianglesPainterAlgorithm() {
	std::sort(_rendering_triangles.begin(), _rendering_triangles.end(), [](Triangle tri1, Triangle tri2) {return tri1.avg_depth > tri2.avg_depth; });
}






