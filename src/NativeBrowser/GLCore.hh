#pragma once

#include <GL/glew.h>
#include <GL/gl.h>

namespace GLCore
{
	GLuint compileShaderFromCode(GLenum shader_type, const char *src);
	GLuint compileShaderFromFile(GLenum shader_type, const char *filepath);

	GLuint createShaderProgram(const char *vert, const char *frag);
	GLuint createShaderProgram(GLuint vert, GLuint frag);
  GLuint createShaderProgramFromCode(const char *vert, const char *frag);

	bool deleteShader(GLuint shader);
	bool deleteProgram(GLuint program);
};
