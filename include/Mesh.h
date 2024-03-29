#pragma once
#include <vector>
#include <SDL_stdinc.h>
#include <string>
#include "../include/MathUtils.h"
struct Face {
	unsigned __int64 a;
	unsigned __int64 b;
	unsigned __int64 c;

	Face(const int& ind_a, const int& ind_b, const int& ind_c) : a(ind_a), b(ind_b), c(ind_c) {};
};

class Triangle3D {
private:
	Vector4 points[3];
public:

	Triangle3D(const Vector3& p1, const Vector3& p2, const Vector3& p3) : points{ p1, p2, p3 } {};
	Triangle3D(const Vector4& p1, const Vector4& p2, const Vector4& p3) : points{ p1, p2, p3 } {};

	Vector3 normal() {
		Vector3 ab = Vector3(points[1] - points[0]).normalise();
		Vector3 ac = Vector3(points[2] - points[0]).normalise();
		Vector3 normal = ab.cross(ac);
		normal.normalise();
		return normal;
	}

	Vector4 a() { return points[0]; }
	Vector4 b() { return points[1]; }
	Vector4 c() { return points[2]; }

	void translate(const Vector3& trans) {
		points[0] += trans;
		points[1] += trans;
		points[2] += trans;
	}

	void transform(const Mat4& trans) {
		for (Vector4& vec : points) {
			vec = trans * vec;
		}
	}

	void scale(const Vector3& scl) {
		for (Vector4& vec : points) {
			vec.setX(vec.getX() * scl.getX());
			vec.setY(vec.getY() * scl.getY());
			vec.setZ(vec.getZ() * scl.getZ());

		}
	}

	float getAverageDepth() {
		return (float(points[0].getZ() + points[1].getZ() + points[2].getZ())) / 3.0;
	}
};


struct Triangle {
	Vector2 points[3];
	float avg_depth;
	Uint32 colour;
	Triangle(const Vector2& p1, const Vector2& p2, const Vector2& p3) : points{ p1, p2, p3 }, avg_depth(0.0), colour(0xFF000000) {}
	Triangle(const Vector2& p1, const Vector2& p2, const Vector2& p3, const Uint32& col, float depth) : points{ p1, p2, p3 }, avg_depth(depth), colour(col) {};
	Triangle(Triangle3D tri_3D, const Uint32& col, float depth) : points{ Vector2(tri_3D.a()), Vector2(tri_3D.b()), Vector2(tri_3D.c()) }, avg_depth(depth), colour(col) {}
	
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


class Mesh
{
public:

	std::vector<Vector4> vertices;
	std::vector<Face>  faces;
	Mat4 transform;
	Vector3 scale;
	Vector3 rotation;
	Vector3 translation;

	//computed vertex properties:
	//std::vector<Vector3> normals;

	Mesh();
	Mesh(const std::string& path_to_mesh);
	Mesh(const std::vector<Vector4> &verts, const std::vector<Face> &f);

	void loadFromFile(const std::string& path_to_file);
	void transformMesh();
	void transformMesh(const Mat4& mat);
	void computeTransform();

	Vector3 getFaceNormal(const int& face_index);

	

private:
	

};

