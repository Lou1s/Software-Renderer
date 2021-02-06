#pragma once
#include "../include/MathUtils.h"
#include "../include/Mesh.h"
#include <memory>
#include <vector>
#include <iostream>

class Display;
class Rasteriser;
class Mesh;

class Engine
{
private:
	std::unique_ptr<Rasteriser> _rasteriser;
	std::shared_ptr<Display> _display;
	bool _is_running;
	float _fov_factor;
	int _previous_frame_time;
	Vector3 cube_rotation;
	Vector3 _camera_pos;
	std::unique_ptr<Mesh> _mesh;
	std::vector<Triangle> _rendering_triangles;

	Vector2 project(const Vector3& vec);
	

public:
	Engine();
	~Engine();
	void init();
	void setup();
	bool isRunning();
	void processInput();
	void update();
	void render();
	void shutdown();
};
//misc functions for testing, from the course

//computes then draws a cube point cloud composed of num_pts^3 points from min to max on all axes
inline void generatePointCube(int num_pts, float min, float max, std::vector<Vector3> &cube_points) {
	cube_points.clear();
	float step = (max - min) / float(num_pts);
	for (float x = min; x <= max; x += step) {
		for (float y = min; y <= max; y += step) {
			for (float z = min; z <= max; z += step) {
				Vector3 new_point(x, y, z);
				cube_points.push_back(new_point);
			}
		}
	}
}


inline void generatePointCube(std::vector<Vector3>& cube_points) {
	for (float x = -1; x <= 1; x += 0.25) {
		for (float y = -1; y <= 1; y += 0.25) {
			for (float z = -1; z <= 1; z += 0.25) {
				Vector3 new_point(x,y,z);
				cube_points.push_back(new_point);
			}
		}
	}
}