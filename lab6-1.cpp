
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <iostream>


// Light 1
static float lpos1[] = { 0.5, 0.0, 1.1, 1.0 };
static float light1_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
static float light1_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };

// Defined Colors
static float white[] = { 1.0, 1.0, 1.0, 1.0 };
static float black[] = { 0.0, 0.0, 0.0, 1.0 };
static float red[] = { 1.0, 0.0, 0.0, 1.0 };
static float blue[] = { 0.0, 0.0, 1.0, 1.0 };
static float green[] = { 0.0, 1.0, 0.0, 1.0 };
static float yellow[] = { 1.0, 1.0, 0.0, 1.0 };
static float purple[] = { 1.0, 0.0, 1.0, 1.0 };
static float cyan[] = { 0.0, 1.0, 1.0, 1.0 };

// Boolean flags
static int flag = 0;//used for color change
bool fullscreen = false;
bool mouseDown = false;
bool tog1 = false;
bool tog2 = false;

// Transformations
float x_rot = 0.0f;
float y_rot = 0.0f;
float x_diff = 0.0f;
float y_diff = 0.0f;
float x_trans = 0.0f;
float y_trans = 0.0f;
float x_rotate = 0.0f;
float y_rotate = 0.0f;
float x_scl_st = 0.0f;
float y_scl_st = 0.0f;
float x_loc = 0.0f;
float y_loc = 0.0f;
float scale = 1.0f;
float x_start = 0.0f;
float y_start = 0.0f;
int p = 0;

// Min and max Function
#define min(x,y) ((x)<(y) ? (x) : (y))
#define max(x,y) ((x)>(y) ? (x) : (y))


void draw_shape() {
	glColor3f(1, 0, 1);
	glutSolidCube(1);
}

// Initiates some parameters and writes to console directions
bool init() {
	//glClearColor(0.93f, 0.93f, 0.93f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0f);
	return true;
}

void display() {
	// Setup
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW); // Necessary for drawShape();
	glLoadIdentity();

	// Camera
	gluLookAt(
		0.0f, 0.0f, 3.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	);

	// Light 0 Settings
	glLightfv(GL_LIGHT0, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light1_diffuse); 
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.5);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.5);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 1.0);
	glLightfv(GL_LIGHT0, GL_POSITION, lpos1);

	// Draw Light 1 position
	glPushMatrix();
	glTranslatef(lpos1[0], lpos1[1], lpos1[2]);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, white);
	glutSolidSphere(0.025, 10, 8);
	glPopMatrix();

	// Rotate Mode
	glRotatef(x_rotate, 1.0f, 0.0f, 0.0f);
	glRotatef(y_rotate, 0.0f, 1.0f, 0.0f);


	glMaterialfv(GL_FRONT, GL_EMISSION, black);

	// Make the back blue
	glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, blue);

	// Redraw the frame and shape
	glutPostRedisplay();
	draw_shape();

	// Flush and swap buffers
	glFlush();
	glutSwapBuffers();
}

// Resize Window Function
void resize(const int w, const int h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45.0f, 1.0f * w / h, 1.0f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// For Fullscreen keyboard
void special_keyboard(const int key, int x, int y) {
	if (key == GLUT_KEY_F1) {
		fullscreen = !fullscreen;

		if (fullscreen)
			glutFullScreen();
		else {
			glutReshapeWindow(500, 500);
			glutPositionWindow(50, 50);
		}
	}
}

// For mice
void mouse(const int button, const int state, const int x, const int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		mouseDown = true;
		x_diff = x - y_rot;
		y_diff = -y + x_rot;				
	}
	else mouseDown = false;
}

void mouse_motion(const int x, const int y) {
	if (mouseDown) {
		y_rot = x - x_diff;
		x_rot = y + y_diff;
		y_rotate = y_rot;
		x_rotate = x_rot;			
		glutPostRedisplay();
	}
}


int main(int argc, char *argv[]) {
	glutInit(&argc, argv);

	glutInitWindowPosition(50, 50);
	glutInitWindowSize(500, 500);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	int win = glutCreateWindow("lab6-1");

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);

	glEnable(GL_LIGHTING);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	glEnable(GL_DEPTH_TEST);

	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	glutDisplayFunc(display);
	glutSpecialFunc(special_keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(mouse_motion);
	glutReshapeFunc(resize);

	if (!init()) return 1;
	glutMainLoop();
	return 0;
}
