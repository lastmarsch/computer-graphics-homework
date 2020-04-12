#!/usr/bin/env python3

from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *
import random
from math import * # trigonometry
import pygame # just to get a display
import sys
import time

glutInit()

# get an OpenGL surface
pygame.init() 
pygame.display.set_mode((800,800), pygame.OPENGL|pygame.DOUBLEBUF)

# Create and Compile a shader
# but fail with a meaningful message if something goes wrong

def createAndCompileShader(type,source):
    shader=glCreateShader(type)
    glShaderSource(shader,source)
    glCompileShader(shader)

    # get "compile status" - glCompileShader will not fail with 
    # an exception in case of syntax errors

    result=glGetShaderiv(shader,GL_COMPILE_STATUS)

    if (result != 1): # shader didn't compile
        raise Exception("Couldn't compile shader\nShader compilation Log:\n".encode()+glGetShaderInfoLog(shader))
    return shader

# Create and Compile fragment and vertex shaders
# Transfer data from fragment to vertex shader

vertex_shader=createAndCompileShader(GL_VERTEX_SHADER,"""
varying vec3 N;
varying vec3 v;

void main(void)
{

   v = vec3(gl_ModelViewMatrix * gl_Vertex);       
   N = normalize(gl_NormalMatrix * gl_Normal);

   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

}
""")

fragment_shader=createAndCompileShader(GL_FRAGMENT_SHADER,"""
varying vec3 N;
varying vec3 v;

void main(void)
{
   vec3 L = normalize(gl_LightSource[0].position.xyz - v);   
   vec4 Idiff = gl_FrontLightProduct[0].diffuse * max(dot(N,L), 0.0);  
   Idiff = clamp(Idiff, 0.0, 1.0); 

   gl_FragColor = Idiff;
}
""")

# build shader program

program = glCreateProgram()
glAttachShader(program,vertex_shader)
glAttachShader(program,fragment_shader)
glLinkProgram(program)

# try to activate/enable shader program
# handle errors wisely

try:
    glUseProgram(program)   
except OpenGL.error.GLError:
    print(glGetProgramInfoLog(program))
    raise

# init
glClearColor(0.2, 0.2, 0.2, 1.0)
glEnable(GL_DEPTH_TEST)
glMatrixMode(GL_PROJECTION)
glLoadIdentity()

angle_x = 0
angle_y = 0

while True:

    # event = None    
    # events = pygame.event.get()
    # for event in events:
    #     if event.type == pygame.KEYDOWN:
    #         if event.key == pygame.K_LEFT:
    #             angle_x -= 5
    #         if event.key == pygame.K_RIGHT:
    #             angle_x += 5 
    #         if event.key == pygame.K_UP:
    #             angle_y -= 5
    #         if event.key == pygame.K_DOWN:
    #             angle_y += 5     
    
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT)
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()

    gluLookAt(0.0, 0.0, 3.0,
    0.0, 0.0, 0.0,
    0.0, 1.0, 0.0)

    # calculate light source position
    lpos = [0.5, 0.0, 1.1, 1.0]
    # pass data to fragment shader
    glLightfv(GL_LIGHT0,GL_POSITION, lpos)

    # draw light
    glPushMatrix()
    glTranslatef(lpos[0], lpos[1], lpos[2])
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, [1, 1, 1, 1])
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, [1, 1, 1, 1])
    glutSolidSphere(0.025, 10, 8)
    glPopMatrix()
    
    # fallback
    glColor3f(1,1,1)

    glLoadIdentity()


    angle_x += 1
    angle_y += 1

    glRotatef(angle_x, 0.0, 1.0, 0.0)
    glRotatef(angle_y, 1.0, 0.0, 0.0)
         
    glColor3f(1, 0, 1) 
    glEnable(GL_COLOR_MATERIAL)      
    glutSolidCube(0.5)    

    glFlush()
    pygame.display.flip()