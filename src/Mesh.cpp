#include "../include/Mesh.h"
#include "../include/MathUtils.h"
#include <iostream>
#include <fstream>
#include <sstream>
Mesh::Mesh()
{
}

Mesh::Mesh(const std::vector<Vector4>& verts, const std::vector<Face>& f) :
	vertices(verts),
	faces(f),
	transform()
	
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
				Vector4 vert(std::stof(line_data[0]), std::stof(line_data[1]), std::stof(line_data[2]),1.0);
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

Vector3 Mesh::getFaceNormal(const int& face_index) {
	Vector4 ab = vertices[faces[face_index].b - 1] - vertices[faces[face_index].a - 1];
	Vector4 ac = vertices[faces[face_index].c - 1] - vertices[faces[face_index].a - 1];
	return ab.cross(ac);
}

void Mesh::transformMesh() {
	for (Vector4& vec : vertices)
	{
		std::cout << "Vec: " << vec.getX() << ", " << vec.getY() << ", " << vec.getZ() << ", " << vec.getW() << std::endl;
		vec = transform * vec;
		std::cout << "Vec transformed: " << vec.getX() << ", " << vec.getY() << ", " << vec.getZ() << ", " << vec.getW() << std::endl;
	}
}