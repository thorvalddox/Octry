#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glext.h>
#include "Octree/octree.h"
#include "worldgen.h"
#include <stdio.h>
#include <string.h>

#include "graphics/shaderutil.h"
#include "worldgen.h"
#include <ctime>
octree<int>* worldmap;
#ifdef checkerrors
#error "ERROR"
#endif
#define checkerrors if ((err = glGetError())) std::cerr << "An error has occurred on line " << std::dec << __LINE__ << ":" << std::hex << err <<std::dec << std::endl


std::vector<cube<int> > glworlddata;

int altmain()
{
    srand(time(NULL));
    std::cout << "Testing worldgen\n";
    std::ofstream outfile("worldgen.txt");
    worldgen::HeightMap heightmap(10, 40, 10);
    heightmap.calculate();
    worldmap = heightmap.build_slow();
    glworlddata = worldmap->graphify();
    std::cout << "Done\n";
    std::cout << "Size: " << (worldmap->getsize() * sizeof(oc_node<int>)) << "\n";
    return 0;
}


GLuint program;
GLuint vao;
GLuint buffer;

void DrawAQuad() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_QUADS);
		glColor3f(1., 0., 0.); glVertex3f(-.75, -.75, 0.);
		glColor3f(0., 1., 0.); glVertex3f( .75, -.75, 0.);
		glColor3f(0., 0., 1.); glVertex3f( .75,  .75, 0.);
		glColor3f(1., 1., 0.); glVertex3f(-.75,  .75, 0.);
	glEnd();
	glFlush();
} 


GLenum err;

int gui_init()
{
	altmain();
	program = compile_shaders("shaders/terrain");
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube<int>) * glworlddata.size(), (GLvoid*) &glworlddata[0], GL_DYNAMIC_DRAW);
	glEnable(GL_DEPTH_TEST); 
	glVertexAttribPointer(0, 3, GL_INT,GL_FALSE, sizeof(cube<int>),(GLvoid*) 0);
	glVertexAttribIPointer(1, 1, GL_INT, sizeof(cube<int>),(GLvoid*) 12);
	for (int i = 0; i < 8; i++)
		glVertexAttribIPointer(2 + i, 1, GL_INT, sizeof(cube<int>),(GLvoid*) (16 + 4*i));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	for (int i = 0; i < 8; i++)
	glEnableVertexAttribArray(2 + i);
	glPointSize(2);
	checkerrors;
}
int gui_draw()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glUseProgram(program);
	checkerrors;
	std::cerr << "Worldsize: " << glworlddata.size() << "\noffset" <<offsetof (cube<int>, data[1]) << std::endl;
	for (int i = 0; i < 10; i++)
	{
		std::cerr << glworlddata[i].x << ' ' << glworlddata[i].y << ' ' << glworlddata[i].z << ' ' << glworlddata[i].depth << std::endl;
		for (int j = 0; j < 8; j++)
			std::cerr << glworlddata[i].data[j] << ' ';
		std::cerr << std::endl;
	}
	glDrawArrays(GL_POINTS, 0, glworlddata.size());
	
}
int gui_close()
{

}