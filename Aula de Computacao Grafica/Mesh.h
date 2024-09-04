#include "GL/glew.h"

class Mesh
{
public:
	Mesh();
	~Mesh();
	void CreateMesh(GLfloat*vertices, unsigned int numVertices, GLuint* indices, unsigned int numIndices);
	void RenderMesh();


private:
	GLuint VBO, VAO, IBO;
	unsigned int numIndices;
};

