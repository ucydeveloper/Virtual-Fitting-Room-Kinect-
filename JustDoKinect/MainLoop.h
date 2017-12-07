#pragma once
#ifndef MAINLOOP_H
#define MAINLOOP_H


#include "KinectSkeleton.h"

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>



int window;
GLuint gl_rgb_tex;
int mx=-1,my=-1;        // Prevous mouse coordinates
int rotangles[2] = {0}; // Panning angles
float zoom = 1;         // zoom factor
int color = 1;          // Use the RGB texture or just draw it as color

int cnt1 = 0;

USHORT realDepth;




#endif 