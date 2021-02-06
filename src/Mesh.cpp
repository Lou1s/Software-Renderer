#include "../include/Mesh.h"
#include "../include/MathUtils.h"
Mesh::Mesh()
{
}

Mesh::Mesh(const std::vector<Vector3>& verts, const std::vector<Face>& f):
	vertices(verts),
	faces(f)
{
}

void Mesh::rotate(const Vector3& rot)
{
	for(Vector3 &vec : vertices)
	{
		vec.rotate(rot);
	}

	_rotation += rot;
}

void Mesh::translate(const Vector3& trans)
{
	for(Vector3 &vec : vertices)
	{
		vec += trans;
	}
	_translation += trans;
}

void Mesh::scale(const float &x, const float &y, const float &z) 
{
	for(Vector3 &vec : vertices)
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