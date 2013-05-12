
/*
 * Gokhan Kiziltepe 040080168
 * 
 * 
 * This project is developed under Ubuntu 13.04 (Based on Debian/Ubuntu)
 * 
 * A debian based operating system (Debian/Ubuntu/Pardus2013/Mint...) can compile 
 * and run this code with correctly installed packages.
 * 
 * OpenGL Version: 3.0 Mesa 9.1.1
 * OpenGL Extension Wrangler 1.8.0 (GLEW)
 * Assimp 3.0
 * GLSL Version 1.3.0
 * 
 * To compile the code use 'Makefile' and 
 * the executable output 'ramp' will be created 
 * 
 * You can also use this line from terminal
 * #g++ -Wall main.cpp -lGLEW -lGL -lglut -lGLU -lSOIL -lassimp -lm -o ramp 
 * 
 * Changed and created files are
 * TextureEffectLoader.h
 * texture_effect_shader.frag
 * Util.h
 * main.cpp
*/

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include "Scene.h"
#include "ScreenSpaceShaderNode.h"
#include "NormalShaderNode.h"
#include "ColorFillNode.h"
#include "DiffusePerPixelNode.h"
#include "DiffusePerVertexNode.h"
#include "SimpleEffect.h"
#include "TextureEffectLoader.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"

#define WINDOW_TITLE_PREFIX "Odev 4"

void IdleFunction(void);
void ResizeFunction(int Width, int Height);
void setupScene();

unsigned FrameCount = 0;

int CurrentWidth = 484,
CurrentHeight = 596,
WindowHandle = 0, mouseX = 0, mouseY = 0;

Light* light;
Camera *camera;
Scene* scene;

static void Draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    scene->draw();
    
    glutSwapBuffers();
    FrameCount++;
}

GLboolean wire = false;

void ResizeFunction(int Width, int Height)
{
	CurrentWidth = Width;
	CurrentHeight = Height;
	glViewport(0, 0, CurrentWidth, CurrentHeight);
    scene->resize();
}

static void timerCallback (int value)
{
    if (0 != value) {
		char* TempString = (char*)
        malloc(512 + strlen(WINDOW_TITLE_PREFIX));
        
		sprintf(
                TempString,
                "%s: %d Frames Per Second @ %d x %d",
                WINDOW_TITLE_PREFIX,
                FrameCount * 4,
                CurrentWidth,
                CurrentHeight
                );
        
		glutSetWindowTitle(TempString);
		free(TempString);
	}
	FrameCount = 0;
	glutTimerFunc(250, timerCallback, 1);
}

void IdleFunction(void)
{
	glutPostRedisplay();
}

void setupScene(){
    scene = new Scene();
    camera = new Camera();
    camera->translate(0.f, 100.f, 300.f);
    scene->setCamera(camera);
    TextureEffect *textureEffect = new TextureEffect(CurrentWidth,CurrentHeight);
    scene->addEffect(textureEffect);
    
    light = new Light();
    light->translate(0, 300.f, 400.f);
    scene->addLight(light);
}

int main (int argc, char ** argv)
{
    GLenum type;
    
	glutInit(&argc, argv);
	glutInitWindowSize(CurrentWidth,CurrentHeight);
	type = GLUT_RGB;
	type |= GLUT_DOUBLE;
	type |= GLUT_DEPTH;
    type |= GLUT_MULTISAMPLE;
	glutInitDisplayMode(type);
	glutCreateWindow("");
    GLenum err = glewInit();
	if (GLEW_OK != err)
	{
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
    
    printf("GLSL Version: %s\n",glslVersion);
    
    const GLubyte* glVersion = glGetString(GL_VERSION);
    
    printf("GL Version: %s\n",glVersion);
    
    glClearColor(0.0, 1.0, 0.0, 1.0);
    
    glEnable(GL_DEPTH_TEST);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE); 
    setupScene();
    timerCallback(0);
    glutReshapeFunc(ResizeFunction);
    glutDisplayFunc(Draw);
    glutIdleFunc(IdleFunction);
    glutMainLoop();
    
    return 0;
}


