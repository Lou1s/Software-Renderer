#pragma once
#include "../include/MathUtils.h"
#include "../include/Mesh.h"
#include "../include/Display.h"
#include "../include/Rasteriser.h"
#include <memory>
#include <vector>
#include <iostream>


class Engine
{
private:
	std::unique_ptr<Rasteriser> _rasteriser;
	std::shared_ptr<Display> _display;
	bool _is_running;
	int _previous_frame_time;
	Vector3 _mesh_rotation;
	Vector3 _camera_pos;
	std::unique_ptr<Mesh> _mesh;
	std::vector<Triangle> _rendering_triangles;
	bool _backface_cull;

	Vector2 project(const Vector4& vec);
	Triangle project(const Triangle3D& tri);

	Vector4 project3D(const Vector4& vec);
	Triangle3D project3D(const Triangle3D& tri);

	void SortTrianglesPainterAlgorithm();
	float _translate_factor_x;

	Mat4 _projection_matrix;

public:
	Engine();
	void init();
	void setup();
	void setFlags(bool backface);
	bool isRunning();
	void processInput();
	void update();
	void render();
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