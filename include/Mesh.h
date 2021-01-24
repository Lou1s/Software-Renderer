#pragma once
#include <vector>
#include "../include/MathUtils.h"

typedef struct {
	int a;
	int b;
	int c;
} face_t;

typedef struct {
	Vector2 points[3];
} triangle_t;

class Mesh
{
public:

	std::vector<Vector3> vertices;
	std::vector<face_t>  faces;

	//computed vertex properties:
	std::vector<Vector3> normals;

	Mesh();
	Mesh(const std::vector<Vector3> &verts, const std::vector<face_t> &f);


};

