#define GL_GLEXT_PROTOTYPES
#include "shaderutil.h"
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glext.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#define size(x) (sizeof(x) / sizeof(*(x)))
#define checkerrors if ((err = glGetError())) std::cerr << "An error has occurred on line " << std::dec << __LINE__ << ":" << std::hex << err <<std::dec << std::endl
extern GLenum err;

GLuint compile_shaders(char * filename)
{
	GLuint types[] = {GL_VERTEX_SHADER, GL_GEOMETRY_SHADER, GL_FRAGMENT_SHADER};
	const char * extensions[] = {".vs", ".gs", ".fs"};
	GLuint program = glCreateProgram();
	GLuint shaders[size(types)];
	unsigned i;
	for (i = 0; i < sizeof(types) / sizeof(*types); i++)
	{
		shaders[i] = -1;
		GLuint shader = glCreateShader(types[i]);

		char * fullname = new char[strlen(filename) + 4];
		strcpy(fullname, filename);
		strcpy(fullname + strlen(fullname), extensions[i]);
		
		FILE * file = fopen(fullname,"r");
		if (!file) continue;
		
		checkerrors;
		
		int length = 0;
		fseek(file, 0, SEEK_END);
		length = ftell(file);
		fseek(file, 0, SEEK_SET);

		char * source = new char[length + 1];
		fread(source, 1, length, file);
		source[length] = 0;
		//fprintf(stderr, "%s\n", source);
		fclose(file);

		glShaderSource(shader, 1, &source, NULL);
		delete [] source;
		checkerrors;
		glCompileShader(shader);

		int loglength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &loglength);
		char* log;
		if (loglength)
			log = new char [loglength];
		else
			log = "No errors, congrats!";
		glGetShaderInfoLog(shader, loglength, &loglength, log);
		fprintf (stderr, "Shader: %s\n %s\n", fullname, log); 
		checkerrors;
		glAttachShader(program, shader);
		delete [] fullname;
		shaders[i] = shader;
	}
	glLinkProgram(program);
	checkerrors;
	for (i = 0; i < size(shaders); i++)
	{
		if (shaders[i] == -1) continue; 
		GLuint shader = shaders[i];
		glDetachShader(program, shader);
		glDeleteShader(shader);
	}
	checkerrors;
	fprintf(stderr, "Program done!");
	return program;
}