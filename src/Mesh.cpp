#include "../include/Mesh.h"
#include "../include/MathUtils.h"
#include <iostream>
#include <fstream>
#include <sstream>
Mesh::Mesh()
{
}

Mesh::Mesh(const std::vector<Vector3>& verts, const std::vector<Face>& f) :
	vertices(verts),
	faces(f)
{
}

void getLineData(std::stringstream &ss_in, char delim, std::vector<std::string>& line_data_out) {
	line_data_out.clear();
	std::string data;
	while (std::getline(ss_in, data, delim)) {
		line_data_out.push_back(data);
	}

}

Mesh::Mesh(const std::string& path_to_file) {
	loadFromFile(path_to_file);
}

void Mesh::loadFromFile(const std::string& path_to_file) {
	std::ifstream mesh_file(path_to_file);
	std::string line;
	std::string first_str;

	std::vector<std::string> line_data;
	std::vector<std::string> ind_data;

	while (std::getline(mesh_file, line)) {
		std::stringstream ss(line);
		//split line by spaces
		if (std::getline(ss, first_str, ' ')) {
			int i = 0;
			//reading vert
			if (first_str == "v") {
				getLineData(ss, ' ', line_data);
				Vector3 vert(std::stof(line_data[0]), std::stof(line_data[1]), std::stof(line_data[2]));
				vertices.push_back(vert);
				//std::cout << " added vert: (" << vert.getX() << ", " << vert.getY() << ", " << vert.getZ() << ")" << std::endl;
			}
			//reading face
			else if (first_str == "f") {
				getLineData(ss, ' ', line_data);
				std::vector<std::string> face_vals;
				for (std::string dat : line_data) {
					std::stringstream f_ss(dat);
					getLineData(f_ss, '/', ind_data);
					face_vals.push_back(ind_data[0]);
				}
				//only take in triangulated mesh
				if (face_vals.size() == 3) {
					Face fc(std::stoi(face_vals[0]), std::stoi(face_vals[1]), std::stoi(face_vals[2]));
					faces.push_back(fc);
					//std::cout << " added face: (" << fc.a << ", " << fc.b << ", " << fc.c << ")" << std::endl;
				}
			}
		}

	}
}

void Mesh::rotate(const Vector3& rot)
{
	for (Vector3& vec : vertices)
	{
		vec.rotate(rot);
	}

	_rotation += rot;
}

void Mesh::translate(const Vector3& trans)
{
	for (Vector3& vec : vertices)
	{
		vec += trans;
	}
	_translation += trans;
}

void Mesh::scale(const float& x, const float& y, const float& z)
{
	for (Vector3& vec : vertices)
	{
		vec.set(vec.getX() * x, vec.getY() * y, vec.getZ() * z);

	}
	_scale.set(_scale.getX() * x, _scale.getY() * y, _scale.getZ() * z);
}

Vector3 Mesh::getRotation() {
	return _rotation;
}

Vector3 Mesh::getScale() {
	return _scale;
}

Vector3 Mesh::getTranslation() {
	return _translation;
}