#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <GL/glut.h>

#define dim 600

unsigned char prevKey;

enum EObiect {
	cubw, cubs, sferaw, sferas
};

EObiect ob = cubw;

double vertices[3][3]{};

void DisplayAxe() {
	int X, Y, Z;
	X = Y = 200;
	Z = 200;

	glLineWidth(2);

	// Ox axis - green
	glColor3f(0, 1, 0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(0, 0, 0);
	glVertex3f(X, 0, 0);
	glEnd();

	// Oy axis - blue
	glColor3f(0, 0, 1);
	glBegin(GL_LINE_STRIP);
	glVertex3f(0, 0, 0);
	glVertex3f(0, Y, 0);
	glEnd();

	// Oz axis - red
	glColor3f(1, 0, 0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, Z);
	glEnd();

	glLineWidth(1);
}

// wireframe cube
void Display1() {
	glColor3f(1, 0, 0);
	glutWireCube(1);
}

// solid cube
void Display2() {
	glColor3f(1, 0, 0);
	glutSolidCube(1);
}

// wireframe sphere
void Display3() {
	glColor3f(0, 0, 1);
	glutWireSphere(1, 10, 10);
}

// solid sphere
void Display4() {
	glColor3f(0, 0, 1);
	glutSolidSphere(1, 10, 10);
}

void DisplayTriangle() {
	glBegin(GL_LINE_LOOP);
	glVertex3f(vertices[0][0], vertices[0][1], vertices[0][2]);
	glVertex3f(vertices[1][0], vertices[1][1], vertices[1][2]);
	glVertex3f(vertices[2][0], vertices[2][1], vertices[2][2]);
	glEnd();
}

// Display triangle 
void Display5() {
	double pi = 4 * atan(1.0);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			do {
				vertices[i][j] = ((double)rand() / RAND_MAX * 2 - 1) * 3;
			} while (fabs(vertices[i][j]) < 2.1);
		}
	}

	double x1 = vertices[0][0];
	double y1 = vertices[0][1];
	double z1 = vertices[0][2];
	double x2 = vertices[1][0];
	double y2 = vertices[1][1];
	double z2 = vertices[1][2];
	double x3 = vertices[2][0];
	double y3 = vertices[2][1];
	double z3 = vertices[2][2];

	//printf("x1 = %f, y1 = %f, z1 = %f\n", x1, y1, z1);
	//printf("x2 = %f, y2 = %f, z2 = %f\n", x2, y2, z2);
	//printf("x3 = %f, y3 = %f, z3 = %f\n", x3, y3, z3);

	/*double x1 = vertices[0][0] = -1.910;
	double y1 = vertices[0][1] = -3.822;
	double z1 = vertices[0][2] = -3.128;
	double x2 = vertices[1][0] = -1.9603;
	double y2 = vertices[1][1] = 1.9113;
	double z2 = vertices[1][2] = -2.8713;
	double x3 = vertices[2][0] = -2.155;
	double y3 = vertices[2][1] = -3.0150;
	double z3 = vertices[2][2] = 3.079;*/

	glColor3f(1.0, 0.0, 0.0);
	DisplayTriangle();

	double D1 = sqrt((x2 - x1) * (x2 - x1) + (z2 - z1) * (z2 - z1));
	double theta;
	if (x2 - x1 > 0) {
		if (z2 - z1 > 0) {
			theta = -acos((z2 - z1) / D1);
		}
		else {
			theta = acos((z2 - z1) / D1) + pi;
		}
	}
	else {
		if (z2 - z1 > 0) {
			theta = acos((z2 - z1) / D1);
		}
		else {
			theta = -acos((z2 - z1) / D1) - pi;
		}
	}

	double D2 = sqrt((y2 - y1) * (y2 - y1) + D1 * D1);
	double phi;
	if (y2 - y1 > 0) {
		phi = acos(D1 / D2);
	}
	else {
		phi = -acos(D1 / D2);
	}

	// x3'', y3'', z3''
	double x3s = ((z2 - z1) * (x3 - x1) - (z3 - z1) * (x2 - x1)) / D1;
	double y3s = y3 - y1;
	double z3s = ((x2 - x1) * (x3 - x1) + (z2 - z1) * (z3 - z1)) / D1;
	// x3''', y3''', z3'''
	double x3ss = x3s;
	double y3ss = (y3s * D1 + z3s * (-y2 + y1)) / D2;
	double z3ss = ((y2 - y1) * y3s + D1 * z3s) / D2;

	double D3 = sqrt(x3ss * x3ss + y3ss * y3ss);
	double alpha;
	if (x3ss > 0) {
		if (y3ss > 0) {
			alpha = -acos(y3ss / D3);
		}
		else {
			alpha = acos(y3ss / D3) + pi;
		}
	}
	else {
		if (y3ss > 0) {
			alpha = acos(y3ss / D3);
		}
		else {
			alpha = -acos(y3ss / D3) - pi;
		}
	}

	printf("%f %f %f\n", alpha * 180 / pi, phi * 180 / pi, theta * 180 / pi);
	glRotated(alpha * 180 / pi, 0.0, 0.0, 1.0);
	glRotated(phi * 180 / pi, 1.0, 0.0, 0.0);
	glRotated(theta * 180 / pi, 0.0, 1.0, 0.0);
	glTranslated(-x1, -y1, -z1);

	glColor3f(0.0, 1.0, 0.0);
	DisplayTriangle();
}

void Display6() {
	double N = 30;

	glColor3f(0.3, 0.7, 0.8);

	glRotated(45, 0.0, 1.0, 0.0);
	glRotated(N, 0.0, 0.0, 1.0);
	glRotated(-45, 0.0, 1.0, 0.0);
	glTranslated(1.5, 1.5, 1.5);

	glutWireCube(3);
}

void DisplayObiect()
{
	switch (ob)
	{
	case cubw:
		Display1();
		break;
	case cubs:
		Display2();
		break;
	case sferaw:
		Display3();
		break;
	case sferas:
		Display4();
		break;
	default:
		break;
	}
}

// the rotation with 10 degrees about the Ox axis
void DisplayX() {
	glMatrixMode(GL_MODELVIEW);
	glRotated(10, 1, 0, 0);
}

// the rotation with 10 degrees about the Oy axis
void DisplayY() {
	glMatrixMode(GL_MODELVIEW);
	glRotated(10, 0, 1, 0);
}

// the rotation with 10 degrees about the Oz axis
void DisplayZ() {
	glMatrixMode(GL_MODELVIEW);
	glRotated(10, 0, 0, 1);
}

// translation by 0.2, 0.2, 0.2
void DisplayT() {
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(0.2, 0.2, 0.2);
}

// scaling by 1.2, 1.2, 1.2
void DisplayS() {
	glMatrixMode(GL_MODELVIEW);
	glScalef(1.2, 1.2, 1.2);
}

void Init(void) {
	glClearColor(1, 1, 1, 1);
	glLineWidth(2);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10, 10, -10, 10, 30, -30);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotated(20, 1, 0, 0);
	glRotated(-20, 0, 1, 0);
}

void Display(void) {
	switch (prevKey)
	{
	case 'a':
		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		DisplayAxe();
		break;
	case '0':
		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glRotated(20, 1, 0, 0);
		glRotated(-20, 0, 1, 0);
		DisplayAxe();
		break;
	case '1':
		glClear(GL_COLOR_BUFFER_BIT);
		DisplayAxe();
		Display1();
		ob = cubw;
		break;
	case '2':
		glClear(GL_COLOR_BUFFER_BIT);
		DisplayAxe();
		Display2();
		ob = cubs;
		break;
	case '3':
		glClear(GL_COLOR_BUFFER_BIT);
		DisplayAxe();
		Display3();
		ob = sferaw;
		break;
	case '4':
		glClear(GL_COLOR_BUFFER_BIT);
		DisplayAxe();
		Display4();
		ob = sferas;
		break;
	case '5':
		glClear(GL_COLOR_BUFFER_BIT);
		DisplayAxe();
		Display5();
		break;
	case '6':
		glClear(GL_COLOR_BUFFER_BIT);
		DisplayAxe();
		Display6();
		break;
	case 'x':
		glClear(GL_COLOR_BUFFER_BIT);
		DisplayX();
		DisplayAxe();
		break;
	case 'y':
		glClear(GL_COLOR_BUFFER_BIT);
		DisplayY();
		DisplayAxe();
		break;
	case 'z':
		glClear(GL_COLOR_BUFFER_BIT);
		DisplayZ();
		DisplayAxe();
		break;
	case 't':
		glClear(GL_COLOR_BUFFER_BIT);
		DisplayT();
		DisplayAxe();
		break;
	case 's':
		glClear(GL_COLOR_BUFFER_BIT);
		DisplayS();
		DisplayAxe();
		break;
	default:
		break;
	}
	glutSwapBuffers();
}

void Reshape(int w, int h) {
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

	srand(time(NULL));

	glutInit(&argc, argv);

	glutInitWindowSize(dim, dim);

	glutInitWindowPosition(100, 100);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glutCreateWindow(argv[0]);

	Init();

	glutReshapeFunc(Reshape);

	glutKeyboardFunc(KeyboardFunc);

	glutMouseFunc(MouseFunc);

	glutDisplayFunc(Display);

	glutMainLoop();

	return 0;
}