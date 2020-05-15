#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

class Shader {
public:
	unsigned int ID;

	Shader(const char* vertexPath, const char* fragmentPath) {
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try {
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream;
			std::stringstream fShaderStream;

			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			vShaderFile.close();
			fShaderFile.close();

			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure& e) {
			std::cout << "ERROR::Shader::shader ifstream error" << std::endl;
		}

		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();
		unsigned int vertex, fragment;
		//vertex
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		std::string vertexStr = "VERTEX";
		CheckCompileErrors(vertex,vertexStr);

		//fragment
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		//为什么这样错了
		//glShaderSource(fragment, 1, fShaderCode, NULL);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		std::string fragmentStr = "FRAGMENT";
		CheckCompileErrors(fragment, fragmentStr);
		//shader
		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		//std::string shaderProgramStr = "PROGRAM";
		shaderProgramStr = "PROGRAM";
		CheckCompileErrors(ID, shaderProgramStr);
		//link之后不再需要？？？
		glDeleteShader(vertex);
		glDeleteShader(fragment);
		
	}

	void Use() {
		glUseProgram(ID);
	}

	void SetBool(const std::string &name,bool value) const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}

	void SetInt(const std::string &name, bool value) const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}

	void SetFloat(const std::string &name, float value) const {
		glUniform1f(glGetUniformLocation(ID, name.c_str()),value);
	}


private :
	std::string shaderProgramStr = "PROGRAM";
	void CheckCompileErrors(unsigned int shader, std::string type) {

		int success;
		char infoLog[1024];
		if (type != shaderProgramStr) {
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::shader compile error type:" << type << "\n" << infoLog << std::endl;
			}
			else {
				glGetShaderiv(shader, GL_LINK_STATUS, &success);
				if (!success) {
					glGetShaderInfoLog(shader, 1024, NULL, infoLog);
					std::cout << "Error:: shader lint error type:" << type << "\n" << infoLog << std::endl;
				}
			}
		}
	}

};


#endif
