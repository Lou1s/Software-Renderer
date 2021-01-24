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
	_mesh()
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

void Engine::setup() {
	_mesh.vertices.push_back(Vector3(-1.0, -1.0, -1.0));
	_mesh.vertices.push_back(Vector3(-1.0, 1.0, -1.0));
	_mesh.vertices.push_back(Vector3(1.0, 1.0, -1.0));
	_mesh.vertices.push_back(Vector3(1.0, -1.0, -1.0));
	_mesh.vertices.push_back(Vector3(1.0, 1.0, 1.0));
	_mesh.vertices.push_back(Vector3(1.0, -1.0, 1.0));
	_mesh.vertices.push_back(Vector3(-1.0, 1.0, 1.0));
	_mesh.vertices.push_back(Vector3(-1.0, -1.0, 1.0));

	//front
	_mesh.faces.push_back(face_t{1, 2, 3});
	_mesh.faces.push_back(face_t{ 1, 3, 4 });
	//right
	_mesh.faces.push_back(face_t{ 4, 3, 5 });
	_mesh.faces.push_back(face_t{ 4, 5, 6 });
	//back
	_mesh.faces.push_back(face_t{ 6, 5, 7 });
	_mesh.faces.push_back(face_t{ 6, 7, 8 });
	//left
	_mesh.faces.push_back(face_t{ 8, 7, 2 });
	_mesh.faces.push_back(face_t{ 8, 2, 1 });
	//top
	_mesh.faces.push_back(face_t{ 2, 7, 5 });
	_mesh.faces.push_back(face_t{ 2, 5, 3 });
	//bottom
	_mesh.faces.push_back(face_t{ 6, 8, 1 });
	_mesh.faces.push_back(face_t{ 6, 1, 4 });
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
	cube_rotation += Vector3(0.6, 0.6, 0.6);
	_rasteriser->drawGrid(0xFF0000FF);
	
	for (size_t i = 0; i < _mesh.faces.size(); i++) {
		face_t mesh_face = _mesh.faces[i];
		Vector3 face_vertices[3];

		face_vertices[0] = _mesh.vertices[mesh_face.a - 1];
		face_vertices[1] = _mesh.vertices[mesh_face.b - 1];
		face_vertices[2] = _mesh.vertices[mesh_face.c - 1];

		triangle_t tri;
		for (size_t j = 0; j < 3; j++) {
			Vector3 transformed_vert = face_vertices[j];
			transformed_vert.rotate(cube_rotation);
			/*
			transformed_vert.rotateZ(cube_rotation.getZ());
			transformed_vert.rotateY(cube_rotation.getY());
			transformed_vert.rotateX(cube_rotation.getX());
			*/

			//translate vertex away from the camera in z
			transformed_vert.setZ(transformed_vert.getZ() - _camera_pos.getZ());

			Vector2 projected_point = project(transformed_vert);
			

			//scale and translate projected point ot the middle of the screen
			projected_point.setX(projected_point.getX() + _display->getWidth() / 2);
			projected_point.setY(projected_point.getY() + _display->getHeight() / 2);
			tri.points[j] = projected_point;
		}
		_rendering_triangles.push_back(tri);
	}
	
	/*
	const int pts_num = 9;
	std::vector<Vector3> cube_points;
	cube_points.reserve(pts_num * pts_num * pts_num);
	generatePointCube(cube_points);
	
	for (const Vector3& vec : cube_points) {
		Vector3 transformed_point(vec);
		transformed_point.rotateZ(cube_rotation.getZ());
		transformed_point.rotateY(cube_rotation.getY());
		transformed_point.rotateX(cube_rotation.getX());

		transformed_point.setZ(transformed_point.getZ() - _camera_pos.getZ());
		Vector2 projected_point = project(transformed_point);
		_rasteriser->drawRectangle(
			projected_point.getX() + _display->getWidth() / 2,
			projected_point.getY() + _display->getHeight() / 2,
			4,
			4,
			0xFFFFFF00);
	}
	cube_points.clear();
	*/
}

void Engine::render() {
	for (size_t i = 0; i < _rendering_triangles.size(); i++) {
		triangle_t &tri = _rendering_triangles[i];
		for (size_t j = 0; j < 3; j++) {
			_rasteriser->drawRectangle(tri.points[j].getX(), tri.points[j].getY(), 3, 3, 0xFFFFFF00);
		}
		
	}
	_display->update();
}

void Engine::shutdown() {
	//delete _display;
	//delete _raytracer;
}





