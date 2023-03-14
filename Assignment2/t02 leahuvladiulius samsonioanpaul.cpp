#define _USE_MATH_DEFINES

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

#define dim 700

unsigned char prevKey;

void Display1() {
	double xmax, ymax, xmin, ymin;
	double a = 1, b = 2;
	double pi = 4 * atan(1.0);
	double ratia = 0.05;
	double t;

	xmax = a - b - 1;
	xmin = a + b + 1;
	ymax = ymin = 0;
	for (t = -pi / 2 + ratia; t < pi / 2; t += ratia) {
		double x1, y1, x2, y2;
		x1 = a + b * cos(t);
		xmax = (xmax < x1) ? x1 : xmax;
		xmin = (xmin > x1) ? x1 : xmin;

		x2 = a - b * cos(t);
		xmax = (xmax < x2) ? x2 : xmax;
		xmin = (xmin > x2) ? x2 : xmin;

		y1 = a * tan(t) + b * sin(t);
		ymax = (ymax < y1) ? y1 : ymax;
		ymin = (ymin > y1) ? y1 : ymin;

		y2 = a * tan(t) - b * sin(t);
		ymax = (ymax < y2) ? y2 : ymax;
		ymin = (ymin > y2) ? y2 : ymin;
	}

	xmax = (fabs(xmax) > fabs(xmin)) ? fabs(xmax) : fabs(xmin);
	ymax = (fabs(ymax) > fabs(ymin)) ? fabs(ymax) : fabs(ymin);

	glBegin(GL_LINE_STRIP);
	for (t = -pi / 2 + ratia; t < pi / 2; t += ratia) {
		double x1, y1, x2, y2;
		x1 = (a + b * cos(t)) / xmax;
		x2 = (a - b * cos(t)) / xmax;
		y1 = (a * tan(t) + b * sin(t)) / ymax;
		y2 = (a * tan(t) - b * sin(t)) / ymax;

		glColor3f(fabs(x1 + x2) / 2, fabs(y1 + y2) / 2, fabs(x1 + x2 + y1 + y2) / 4);
		glVertex2f(x1, y1);
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	for (t = -pi / 2 + ratia; t < pi / 2; t += ratia) {
		double x1, y1, x2, y2;
		x1 = (a + b * cos(t)) / xmax;
		x2 = (a - b * cos(t)) / xmax;
		y1 = (a * tan(t) + b * sin(t)) / ymax;
		y2 = (a * tan(t) - b * sin(t)) / ymax;

		glColor3f(fabs(x1 + x2) / 2, fabs(y1 + y2) / 2, fabs(x1 + x2 + y1 + y2) / 4);
		glVertex2f(x2, y2);
	}
	glEnd();
}

void Display2() {
	double pi = 4 * atan(1.0);
	double xmax = 8 * pi;
	double ymax = exp(1.1);
	double ratia = 0.05;
	glColor3f(1, 0.1, 0.1);
	glBegin(GL_LINE_STRIP);
	for (double x = 0; x < xmax; x += ratia) {
		double x1, y1;
		x1 = x / xmax;
		y1 = (fabs(sin(x)) * exp(-sin(x))) / ymax;

		glColor3f(x1, y1, 1 - x1 - y1);
		glVertex2f(x1, y1);
	}
	glEnd();
}

// graficul functiei f(x) = 1, x = 0 | f(x)= d(x)/x, 0 < x <= 100, d(x) = distanta de la x la cel mai apropiat intreg
void Display3() {
	double xmax = 100;
	double ymax = 0;
	double ratia = 2.5;

	for (double x = 0 + ratia; x <= xmax; x += ratia) {
		double x1, y1;
		x1 = x;
		double dx = fabs(floor(x) - x) > fabs(ceil(x) - x)
			? fabs(ceil(x) - x)
			: fabs(floor(x) - x);
		y1 = dx / x;
		ymax = (ymax < y1) ? y1 : ymax;

		glVertex2f(x1, y1);
	}

	glBegin(GL_LINE_STRIP);
	glVertex2f(0, 1);
	for (double x = 0 + ratia; x <= xmax; x += ratia) {
		double x1, y1, dx;
		x1 = x / xmax;
		dx = fabs(floor(x) - x) > fabs(ceil(x) - x) ? fabs(ceil(x) - x) : fabs(floor(x) - x);
		y1 = (dx / x) / ymax;

		glColor3f(dx, 1 - dx, 1 - dx);
		glVertex2f(x1, y1);
	}
	glEnd();
}

// trisectoarea lui Longchamps
void Display4() {
	double a = 0.2;
	double pi = 4 * atan(1.0);
	double ratia = 0.02;

	// arata mai bine cu linii decat cu puncte
	glBegin(GL_LINES);
	for (double t = -pi / 2 + ratia; t < pi / 2; t += ratia) {
		if (t != -pi / 6 && t != pi / 6) {
			double x1 = (a / (4 * cos(t) * cos(t) - 3));
			double y1 = ((a * tan(t)) / (4 * cos(t) * cos(t) - 3));

			glColor3f(fabs(x1 + y1) / 2, 1 - fabs(x1), 1 - fabs(y1));
			glVertex2f(x1, y1);
		}
	}
	glEnd();

	glColor3f(1.0, 0, 0);
	glBegin(GL_LINES);
	for (double t = -pi / 2 + ratia; t < pi / 2; t += ratia) {
		if (t != -pi / 6 && t != pi / 6) {
			double x1 = (a / (4 * cos(t) * cos(t) - 3));
			double y1 = ((a * tan(t)) / (4 * cos(t) * cos(t) - 3));

			if (x1 < 0 && y1 > 0) {
				glVertex2f(x1, y1);
				glVertex2f(-1.0, 1.0);
			}

		}
	}
	glEnd();
}

// cicloida
void Display5() {
	double a = 0.1;
	double b = 0.2;
	double ratia = 0.1;
	double tmin = 0;
	double tmax = 0;

	// gasesc valorile lui t pentru care x este in intervalul [-1, 1]
	double xmin = (a * tmin - b * sin(tmin));
	double xmax = (a * tmax - b * sin(tmax));
	while (xmin >= -1) {
		tmin -= ratia;
		xmin = (a * tmin - b * sin(tmin));
	}

	while (xmax <= 1) {
		tmax += ratia;
		xmax = (a * tmax - b * sin(tmax));
	}

	glBegin(GL_LINE_STRIP);
	for (double t = tmin; t <= tmax; t += ratia) {
		double x1 = (a * t - b * sin(t));
		double y1 = (a - b * cos(t));

		glColor3f(0, 1 - fabs(y1), 1 - fabs(x1));
		glVertex2f(x1, y1);
	}
	glEnd();
}

// lemniscata lui Bernoulli 
void Display6() {
	double a = 0.4;
	double pi = 4 * atan(1.0);
	// initializez ratia astfel incat sa ating t = 0 (obtin r din ecuatia -pi/4 + n*r = 0)
	double ratia = pi / (4 * 100);

	glBegin(GL_LINE_STRIP);
	for (double t = -pi / 4 + ratia; t < pi / 4; t += ratia) {
		double r = a * sqrt(2 * cos(2 * t));
		double x = r * cos(t);
		double y = r * sin(t);

		glColor3f(0, 1 - fabs(x), 1 - fabs(y));
		glVertex2f(x, y);
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	for (double t = -pi / 4 + ratia; t < pi / 4; t += ratia) {
		double r = a * sqrt(2 * cos(2 * t));
		double x = -r * cos(t);
		double y = -r * sin(t);

		glColor3f(0, 1 - fabs(x), 1 - fabs(y));
		glVertex2f(x, y);
	}
	glEnd();
}

// spirala logaritmica
void Display7() {
	double a = 0.02;
	double ratia = 0.005;
	double tmax = 0;
	while (a * exp(1 + tmax) < 1) {
		tmax += ratia;
	}

	glBegin(GL_LINE_STRIP);
	for (double t = 0 + ratia; t <= tmax; t += ratia) {
		double r = a * exp(1 + t);
		double x = r * cos(t);
		double y = r * sin(t);

		glColor3f(1 - t / tmax, t / tmax, t / tmax);
		glVertex2f(x, y);
	}
	glEnd();
}

void Init(void) {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glLineWidth(1.5);
	glPointSize(1.5);
	glPolygonMode(GL_FRONT, GL_LINE);
}

void Display(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	switch (prevKey) {
	case '1':
		Display1();
		break;
	case '2':
		Display2();
		break;
	case '3':
		Display3();
		break;
	case '4':
		Display4();
		break;
	case '5':
		Display5();
		break;
	case '6':
		Display6();
		break;
	case '7':
		Display7();
		break;
	}

	glFlush();
}

void Reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void KeyboardFunc(unsigned char key, int x, int y) {
	prevKey = key;
	if (key == 27) // escape
		exit(0);
	glutPostRedisplay();
}

void MouseFunc(int button, int state, int x, int y) {
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitWindowSize(dim, dim);

	glutInitWindowPosition(100, 100);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutCreateWindow(argv[0]);

	Init();

	glutReshapeFunc(Reshape);

	glutKeyboardFunc(KeyboardFunc);

	glutMouseFunc(MouseFunc);

	glutDisplayFunc(Display);

	glutMainLoop();

	return 0;
}
