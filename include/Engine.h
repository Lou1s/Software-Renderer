#pragma once
#include "../include/MathUtils.h"
#include "../include/Mesh.h"
#include "../include/Display.h"
#include "../include/Rasteriser.h"
#include "../include/Shader.h"
#include <memory>
#include <vector>
#include <iostream>


class Engine
{
private:
	std::unique_ptr<Rasteriser> _rasteriser;
	std::shared_ptr<Display> _display;
	std::unique_ptr<Shader> _shader;

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
	Vector3 proj_mod_trans;
	Vector3 proj_mod_scale;

	


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
