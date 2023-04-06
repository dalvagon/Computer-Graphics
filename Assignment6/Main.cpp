#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

#define dim 300

unsigned char prevKey;
GLint k;
// the size of the cube
GLdouble lat = 5;

void proiectieParalela(unsigned char);
void DisplayAxe();
void InitObiect();
void DisplayObiect();


void Init(void) {
	glClearColor(1, 1, 1, 1);

	glEnable(GL_DEPTH_TEST);

	// generation of one empty display list having the ID k
	k = glGenLists(1);
	InitObiect();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

void DisplayCabinet(double alpha) {
	double pi = 4 * atan(1);
	double cabinet[16] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		-cos(alpha * pi / 180) / 2, sin(alpha * pi / 180) / 2, 1, 0,
		0, 0, 0, 1
	};

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-4, 6, -4, 6, -20, 20);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glMultMatrixd(cabinet);
	DisplayAxe();
	DisplayObiect();
	glPopMatrix();
}

void DisplayOVP()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-10.0, 10.0, -10.0, 10.0, -10.0, 100.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	gluLookAt(0.0, 0.0, 5.0,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0);
	DisplayAxe();
	DisplayObiect();
	glPopMatrix();
}

void Display()
{
	switch (prevKey)
	{
	case '0':
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		DisplayAxe();
		break;
	case 'A':
		DisplayAxe();
		break;
	case 'C':
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		break;
	case 'X':
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		proiectieParalela('X');
		glMatrixMode(GL_MODELVIEW);
		glRotatef(10, 1, 0, 0);
		DisplayAxe();
		DisplayObiect();
		break;
	case 'Y':
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		proiectieParalela('Y');
		glMatrixMode(GL_MODELVIEW);
		glRotatef(10, 0, 1, 0);
		DisplayAxe();
		DisplayObiect();
		break;
	case 'Z':
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		proiectieParalela('Z');
		glMatrixMode(GL_MODELVIEW);
		glRotatef(10, 0, 0, 1);
		DisplayAxe();
		DisplayObiect();
		break;
	case 'q':
		// red face
		proiectieParalela('q');
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glPushMatrix();
		DisplayAxe();
		glTranslated(0, 0, -lat);
		DisplayObiect();
		glPopMatrix();
		break;
	case 'w':
		// yellow face
		proiectieParalela('w');
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glPushMatrix();
		glTranslated(0, 0, -lat);
		glTranslated(lat / 2.0, lat / 2.0, lat / 2.0);
		glRotated(-90, 0, 1, 0);
		glTranslated(-lat / 2.0, -lat / 2.0, -lat / 2.0);
		DisplayAxe();
		DisplayObiect();
		glPopMatrix();
		break;
	case 'e':
		// green face
		proiectieParalela('e');
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glPushMatrix();
		glRotated(-90, 1, 0, 0);
		glTranslated(lat / 2.0, lat / 2.0, lat / 2.0);
		glRotated(180, 1, 0, 0);
		glTranslated(-lat / 2.0, -lat / 2.0, -lat / 2.0);
		DisplayAxe();
		DisplayObiect();
		glPopMatrix();
		break;
	case 'r':
		// blue face
		proiectieParalela('r');
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glPushMatrix();
		glRotated(-90, 1, 0, 0);
		DisplayAxe();
		DisplayObiect();
		glPopMatrix();
		break;
	case 't':
		// magenta face
		proiectieParalela('t');
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glPushMatrix();
		glTranslated(0, 0, -lat);
		glTranslated(lat / 2.0, lat / 2.0, lat / 2.0);
		glRotated(90, 0, 1, 0);
		glTranslated(-lat / 2.0, -lat / 2.0, -lat / 2.0);
		DisplayAxe();
		DisplayObiect();
		glPopMatrix();
		break;
	case 'y':
		// cyan face
		proiectieParalela('y');
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glPushMatrix();
		glTranslated(0, 0, -lat);
		glTranslated(lat / 2.0, lat / 2.0, lat / 2.0);
		glRotated(180, 0, 1, 0);
		glTranslated(-lat / 2.0, -lat / 2.0, -lat / 2.0);
		DisplayAxe();
		DisplayObiect();
		glPopMatrix();
		break;
	case 'u':
		DisplayCabinet(-30);
		break;
	case 'i':
		DisplayCabinet(-45);
		break;
	case 'o':
		DisplayOVP();
		break;
	default:
		break;
	}
	glutSwapBuffers();
}

void Reshape(int w, int h) {
	h = (h == 0) ? 1 : h;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void KeyboardFunc(unsigned char key, int x, int y) {
	prevKey = key;
	if (key == 27)
		exit(0);
	glutPostRedisplay();
}

void MouseFunc(int button, int state, int x, int y) {
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);

	glutInitWindowSize(dim, dim);

	glutInitWindowPosition(100, 100);

	glutInitDisplayMode(GL_COLOR_BUFFER_BIT | GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutCreateWindow(argv[0]);

	Init();

	glutReshapeFunc(Reshape);

	glutKeyboardFunc(KeyboardFunc);

	glutMouseFunc(MouseFunc);

	glutDisplayFunc(Display);

	glutMainLoop();

	return 0;
}

void proiectieParalela(unsigned char c) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	switch (c) {
	case 'X':
	case 'Y':
	case 'Z':
		glOrtho(-10, 10, -10, 10, -20, 20);
		break;
	case 'q':
	case 'w':
	case 'e':
	case 'r':
	case 't':
	case 'y':
		glOrtho(-1, 6, -1, 6, -1, 20);
		break;
	default:
		break;
	}
}

void DisplayAxe() {
	int X, Y, Z;
	X = Y = 800;
	Z = 800;
	glLineWidth(2);

	// Ox axis - green
	glColor3f(0.1, 1, 0.1);
	glBegin(GL_LINE_STRIP);
	glVertex3f(0, 0, 0);
	glVertex3f(X, 0, 0);
	glEnd();

	// Oy axus - blue
	glColor3f(0.1, 0.1, 1);
	glBegin(GL_LINE_STRIP);
	glVertex3f(0, 0, 0);
	glVertex3f(0, Y, 0);
	glEnd();

	// Oz axis - red
	glColor3f(1, 0.1, 0.1);
	glBegin(GL_LINE_STRIP);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, Z);
	glEnd();

	glLineWidth(1);
}

void InitObiect() {
	glNewList(k, GL_COMPILE);
	// face 1
	glColor3f(1, 0, 0); // red
	glBegin(GL_QUADS);
	glVertex3d(0, lat, lat);
	glVertex3d(lat, lat, lat);
	glVertex3d(lat, 0, lat);
	glVertex3d(0, 0, lat);
	glEnd();
	// face 2
	glColor3f(1, 1, 0); // yellow
	glBegin(GL_QUADS);
	glVertex3d(lat, 0, 0);
	glVertex3d(lat, 0, lat);
	glVertex3d(lat, lat, lat);
	glVertex3d(lat, lat, 0);
	glEnd();
	// face 3
	glColor3f(0, 1, 0); // green
	glBegin(GL_QUADS);
	glVertex3d(0, lat, lat);
	glVertex3d(lat, lat, lat);
	glVertex3d(lat, lat, 0);
	glVertex3d(0, lat, 0);
	glEnd();
	// face 4
	glColor3f(0, 0, 1); // blue
	glBegin(GL_QUADS);
	glVertex3d(0, 0, 0);
	glVertex3d(lat, 0, 0);
	glVertex3d(lat, 0, lat);
	glVertex3d(0, 0, lat);
	glEnd();
	// face 5
	glColor3f(1, 0, 1);  // magenta
	glBegin(GL_QUADS);
	glVertex3d(0, 0, lat);
	glVertex3d(0, 0, 0);
	glVertex3d(0, lat, 0);
	glVertex3d(0, lat, lat);
	glEnd();
	// face 6
	glColor3f(0, 1, 1); // cyan
	glBegin(GL_QUADS);
	glVertex3d(0, lat, 0);
	glVertex3d(lat, lat, 0);
	glVertex3d(lat, 0, 0);
	glVertex3d(0, 0, 0);
	glEnd();
	glEndList();
}

void DisplayObiect()
{
	glCallList(k);
}

