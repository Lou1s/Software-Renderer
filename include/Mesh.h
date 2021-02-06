#pragma once
#include <vector>
#include "../include/MathUtils.h"

struct Face {
	unsigned __int64 a;
	unsigned __int64 b;
	unsigned __int64 c;

	Face() {};
	Face(const int& ind_a, const int& ind_b, const int& ind_c) : a(ind_a), b(ind_b), c(ind_c) {};
};

struct Triangle {
	Vector2 points[3];

	Triangle() {};
	Triangle(const Vector2& p1, const Vector2& p2, const Vector2& p3) : points{ p1, p2, p3 } {};
};

class Mesh
{
public:

	std::vector<Vector3> vertices;
	std::vector<Face>  faces;

	//computed vertex properties:
	std::vector<Vector3> normals;

	Mesh();
	Mesh(const std::vector<Vector3> &verts, const std::vector<Face> &f);
	
	void rotate(const Vector3 &rot);
	void translate(const Vector3 &trans);
	void scale(const float &x, const float& y, const float& z);

	Vector3 getRotation();
	Vector3 getScale();
	Vector3 getTranslation();

private:
	Vector3 _rotation;
	Vector3 _translation;
	Vector3 _scale;

};

