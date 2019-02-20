#ifndef OBJLOADER_H
#define OBJLOADER_H
#include "main.h"

bool loadOBJ(
	const char * path,
	std::vector<GLfloat> & out_vertices,
	std::vector<GLfloat> & out_uvs,
	std::vector<GLfloat> & out_normals
);

bool loadOBJRect(
	const char * path,
	std::vector<GLfloat> & out_vertices,
	std::vector<GLfloat> & out_uvs,
	std::vector<GLfloat> & out_normals
);
bool loadOBJwoUV(
	const char * path,
	std::vector<GLfloat> & out_vertices,
	std::vector<GLfloat> & out_normals
);
bool loadOBJRectwoUV(
	const char * path,
	std::vector<GLfloat> & out_vertices,
	std::vector<GLfloat> & out_normals
);
#endif
