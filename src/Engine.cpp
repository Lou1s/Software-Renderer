#include "../include/Engine.h"
#include <math.h>
#include <SDL_stdinc.h>
#include <array>
#include <algorithm>

Engine::Engine() :
	_rasteriser(nullptr),
	_display(nullptr),
	_is_running(false),
	_camera_pos(0, 0, -5),
	_previous_frame_time(0),
	_mesh_rotation(0, 2, 0),
	_mesh(),
	_backface_cull(true),
	_translate_factor_x(0.2),
	_projection_matrix()

{

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
	_mesh->loadFromFile("D:\\Projects\\Software-Renderer\\assets\\cube.obj");
	_mesh->translation.setZ(50);
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

Triangle Engine::project(const Triangle3D& tri) {
	Triangle3D temp_tri(tri);
	Triangle projected_tri(project(Vector4(temp_tri.a())), project(Vector4(temp_tri.b())), project(Vector4(temp_tri.c())));
	return projected_tri;
}


Vector4 Engine::project3D(const Vector4& vec) {
	Vector4 result = _projection_matrix * vec;

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
	_mesh->rotation += Vector3(6, 2, 4);
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
		
		Vector3 proj_mod_trans(_display->getWidth() / 2.0, _display->getHeight() / 2.0, 0.0);
		Vector3 proj_mod_scale(_display->getWidth() / 10.0, _display->getHeight() / 10.0, 1.0);
		
		//scale into the view
		proj_tri.scale(proj_mod_scale);
		
		//translate to the middle of the screen
		proj_tri.translate(proj_mod_trans);
		

		Triangle tri = proj_tri.to2D();
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






