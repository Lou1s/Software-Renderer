#pragma once
#include "../include/MathUtils.h"
#include <memory>
#include <vector>
#include <iostream>

class Display;
class Rasteriser;

class Engine
{
private:
	std::unique_ptr<Rasteriser> _rasteriser;
	std::shared_ptr<Display> _display;
	bool _is_running;
public:
	Engine();
	~Engine();
	void init();
	bool isRunning();
	void processInput();
	void update();
	void render();
	void shutdown();
};
//misc functions for testing, from the course

//computes then draws a cube point cloud composed of num_pts^3 points from min to max on all axes
inline void generatePointCube(int num_pts, float min, float max, std::vector<Vector3> &cube_points) {
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