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
	float avg_depth;
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
	Triangle3D(const Vector4& p1, const Vector4& p2, const Vector4& p3) : points{ Vector3(p1), Vector3(p2), Vector3(p3) } {};
	
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

	void transform(const Mat4& trans) {
		for (Vector3& vec : points) {
			Vector4 vec_4(vec);
			vec = Vector3(trans* vec_4);
		}
	}

	float getAverageDepth() {
		return (float(points[0].getZ() + points[1].getZ() + points[2].getZ())) / 3.0;
	}
};

class Mesh
{
public:

	std::vector<Vector4> vertices;
	std::vector<Face>  faces;
	Mat4 transform;

	//computed vertex properties:
	//std::vector<Vector3> normals;

	Mesh();
	Mesh(const std::string& path_to_mesh);
	Mesh(const std::vector<Vector4> &verts, const std::vector<Face> &f);

	void loadFromFile(const std::string& path_to_file);
	void transformMesh();
	void transformMesh(const Mat4& mat);


	Vector3 getFaceNormal(const int& face_index);

	

private:
	

};

