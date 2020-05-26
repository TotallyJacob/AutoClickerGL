#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(std::vector<const char*> shaders) {

	std::vector<int> shaders_compiled;
	shaders_compiled.reserve(shaders.size());

	program = glCreateProgram();

	//Attaches shaders to program
	for (int i = 0; i < shaders.size(); i++) {
		int shader = getShader(shaders.at(i));

		if (!(shader == -1)) { //If no errors
			glAttachShader(program, shader);
			shaders_compiled.push_back(shader);
		}
	}

	//Link program
	glLinkProgram(program);

	//Check for errors
	int success = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &success);

	//Print errors
	if(!success){
		char infoLog[512];
		glGetProgramInfoLog(program, GL_LINK_STATUS, NULL, infoLog);
		std::cout << infoLog << std::endl;

		glDeleteProgram(program);
	}

	//Delete unwanted shaders
	for (int i = 0; i < shaders_compiled.size(); i++) {
		glDeleteShader(shaders_compiled.at(i));
	}

}

int ShaderProgram::getShader(const char* fileName) {
	//Reading shader data
	std::fstream stream(fileName);
	std::stringstream stringStream[1];
	std::string line;

	//Reading shader
	while (getline(stream, line))
		stringStream[0] << line << "\n";

	//Shader data
	std::string type = split(fileName, 1, ".");
	std::string source = stringStream[0].str(); //To stop the shaderCode from being garbage
	const char* shaderCode = source.c_str();

	//creating the shader
	unsigned int shader = 0;
	int success;
	char infoLog[512];

	//creating and compiling shader
	shader = glCreateShader(getShaderType(type));
	glShaderSource(shader, 1, &shaderCode, NULL);
	glCompileShader(shader);

	//Checking if the shader is good
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	//Printing errors
	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << infoLog << std::endl;

		glDeleteShader(shader);
		return -1;
	}

	return shader;
}