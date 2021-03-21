#pragma once
#include <vector>
#include "../include/MathUtils.h"
#include <string>
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
	void translate(const Vector2& trans) {
		points[0] += trans;
		points[1] += trans;
		points[2] += trans;
	}
	void integise() {
		points[0].integise();
		points[1].integise();
		points[2].integise();
	}
};

class Triangle3D {
private:
	Vector3 points[3];
public:
	Triangle3D() {};
	Triangle3D(const Vector3& p1, const Vector3& p2, const Vector3& p3) : points{ p1, p2, p3 } {};
	
	Vector3 normal() {
		Vector3 ab = (points[1] - points[0]).normalise();
		Vector3 ac = (points[2] - points[0]).normalise();
		Vector3 normal = ab.cross(ac);
		normal.normalise();
		return normal;
	}

	Vector3 a() { return points[0]; }
	Vector3 b() { return points[1]; }
	Vector3 c() { return points[2]; }

	void rotateInPlace(const Vector3& rot) {
		points[0].rotateInPlace(rot);
		points[1].rotateInPlace(rot);
		points[2].rotateInPlace(rot);
	}
	
	void translate(const Vector3& trans) {
		points[0] += trans;
		points[1] += trans;
		points[2] += trans;
	}
};

class Mesh
{
public:

	std::vector<Vector3> vertices;
	std::vector<Face>  faces;

	//computed vertex properties:
	std::vector<Vector3> normals;

	Mesh();
	Mesh(const std::string& path_to_mesh);
	Mesh(const std::vector<Vector3> &verts, const std::vector<Face> &f);

	void loadFromFile(const std::string& path_to_file);

	void rotate(const Vector3 &rot);
	void translate(const Vector3 &trans);
	void scale(const float &x, const float& y, const float& z);

	Vector3 getFaceNormal(const int& face_index);

	Vector3 getRotation();
	Vector3 getScale();
	Vector3 getTranslation();

private:
	Vector3 _rotation;
	Vector3 _translation;
	Vector3 _scale;

};

