#define GLEW_STATIC
#include"GL/glew.h"

#include<iostream>
#include<vector>
#include <fstream>
#include <sstream>

#pragma once

class ShaderProgram
{
private:
	unsigned int program = 0;

	//Util
	inline std::string split(const char*line, unsigned int split, const char* splitBy) {

		std::stringstream ss(line);
		std::string splitString;

		const char* value;

		unsigned int splitSoFar = 0;

		while (getline(ss, splitString, *splitBy)) {
			if (splitSoFar == split) {
				return splitString;
			}

			splitSoFar++;
		}
			

		return nullptr;
	}
	inline static const unsigned int getShaderType(std::string type) {
		if (type == "frag") 
			return GL_FRAGMENT_SHADER;
		
		if (type == "vert")
			return GL_VERTEX_SHADER;

		if (type == "geo")
			return GL_GEOMETRY_SHADER;

		if (type == "tess_control")
			return GL_TESS_CONTROL_SHADER;

		if (type == "tess_evaluation")
			return GL_TESS_EVALUATION_SHADER;
	}

	int getShader(const char* fileName);

public:

	ShaderProgram(std::vector<const char*> shaders);

	operator unsigned int() const { return program; }

	//Other methods
	static inline void sendModelMatrix(unsigned int shader, const GLfloat* matrix) {
		glUniformMatrix4fv(glGetUniformLocation(shader, "modelMatrix"), 1, GL_FALSE, matrix);
	}

	static inline void sendPerspectiveMatrix(unsigned int shader, const GLfloat* matrix) {
		glUniformMatrix4fv(glGetUniformLocation(shader, "perspectiveMatrix"), 1, GL_FALSE, matrix);
	}

	static inline void sendViewMatrix(unsigned int shader, const GLfloat* matrix) {
		glUniformMatrix4fv(glGetUniformLocation(shader, "viewMatrix"), 1, GL_FALSE, matrix);
	}

};

