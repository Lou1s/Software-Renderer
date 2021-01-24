#include "../include/Mesh.h"
#include "../include/MathUtils.h"
Mesh::Mesh()
{
}

Mesh::Mesh(const std::vector<Vector3>& verts, const std::vector<face_t>& f):
	vertices(verts),
	faces(f)
{
}
