#define _USE_MATH_DEFINES

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <list>
#include <utility>
#include <iterator>

#define dim 500

unsigned char prevKey;

void swap(int& a, int& b) {
	int aux = a;
	a = b;
	b = aux;
}

std::list<std::pair<int, int>> A1(int x0, int y0, int xn, int yn) {
	double m, k;
	std::list<std::pair<int, int>> M;

	if (xn == x0) {
		k = x0;

		if (y0 > yn) {
			swap(y0, yn);
			swap(x0, xn);
		}

		for (int y = y0; y <= yn; y++) {
			int x = k;
			auto pixel = std::pair<int, int>(x, floor(y + 0.5));
			M.push_back(pixel);
		}
	}
	else {
		m = (yn - y0) / ((xn - x0) * 1.0);
		k = y0 - m * x0;

		if (x0 > xn) {
			swap(y0, yn);
			swap(x0, xn);
		}

		for (int x = x0; x <= xn; x++) {
			double y;
			y = m * x + k;
			auto pixel = std::pair<int, int>(x, floor(y + 0.5));
			M.push_back(pixel);
		}
	}

	return M;
}

std::list<std::pair<int, int>> A2(int x0, int y0, int xn, int yn) {
	double m, k;
	std::list<std::pair<int, int>> M;

	if (xn == x0) {
		k = x0;

		if (y0 > yn) {
			swap(y0, yn);
			swap(x0, xn);
		}

		for (int y = y0; y <= yn; y++) {
			int x = k;
			auto pixel = std::pair<int, int>(x, floor(y + 0.5));
			M.push_back(pixel);
		}
	}
	else {
		m = (yn - y0) / ((xn - x0) * 1.0);
		k = y0 - m * x0;

		if (x0 > xn) {
			swap(y0, yn);
			swap(x0, xn);
		}

		double y = y0;

		for (int x = x0; x <= xn; x++) {
			auto pixel = std::pair<int, int>(x, floor(y + 0.5));
			M.push_back(pixel);
			y += m;
		}
	}

	return M;
}

std::list<std::pair<int, int>> A3(int x0, int y0, int xn, int yn) {
	std::list<std::pair<int, int>> M;

	if (x0 > xn) {
		swap(y0, yn);
		swap(x0, xn);
	}

	int yoff = (y0 > yn) ? -1 : 1;

	int dx = xn - x0;
	int dy = yn - y0;
	int d = 2 * dy * yoff - dx;
	int dE = 2 * dy * yoff;
	int dNE = 2 * (dy * yoff - dx);
	int x = x0;
	int y = y0;
	M.push_back(std::pair<int, int>(x, y));

	while (x < xn) {
		if (d <= 0) {
			d += dE;
			x++;
		}
		else {
			d += dNE;
			x++;
			y += yoff;
		}

		M.push_back(std::pair<int, int>(x, y));
	}

	return M;
}

std::list<std::pair<int, int>> A1Circle(int R) {
	std::list<std::pair<int, int>> M;

	for (int x = 0; x <= R; x++) {
		M.push_back(std::pair<int, int>(x, floor(sqrt(R * R - x * x) + 0.5)));
	}

	return M;
}

std::list<std::pair<int, int>> A4Circle(int R) {
	std::list<std::pair<int, int>> M;
	int x = 0;
	int y = R;
	int d = 1 - R;
	int dE = 3, dSE = -2 * R + 5;

	while (y >= x) {
		//M.push_back(std::pair<int, int>(x, y));
		M.push_back(std::pair<int, int>(y, x));
		M.push_back(std::pair<int, int>(y + 1, x));
		M.push_back(std::pair<int, int>(y - 1, x));

		if (d < 0) {
			d += dE;
			dE += 2;
			dSE += 2;
		}
		else {
			d += dSE;
			dE += 2;
			dSE += 4;
			y--;
		}
		x++;
	}

	return M;
}

class Grid {
private:
	int n;	// the number of rows / columns
	double r;	// the radius of the circle 

	// Map the i-th row / column to the corresponding c coordinate
	double map(double i) {
		double c = i / (n * 1.0);
		// Map x from [0, 1] to [-1, 1]
		c = 2 * c - 1;

		return c;
	}

public:
	Grid(int n) {
		this->n = n;
		this->r = 1 / (n * 1.9);
	}

	~Grid() {}

	void draw() {
		glColor3f(0.6, 0.7, 0.9);
		glLineWidth(1);
		// vertical lines
		glBegin(GL_LINES);
		for (int i = 0; i <= n; i++) {
			double x = this->map(i);
			glVertex2f(x, 1.0);
			glVertex2f(x, -1.0);
		}
		glEnd();

		// horizontal lines
		glBegin(GL_LINES);
		for (int i = 0; i <= n; i++) {
			double y = this->map(i);
			glVertex2f(1.0, y);
			glVertex2f(-1.0, y);
		}
		glEnd();
	}

	void writePixel(int i, int j) {
		double x = this->map(i);
		double y = this->map(j);
		double pi = 4 * atan(1.0);

		int sides = 8;
		glPolygonMode(GL_FRONT, GL_FILL);
		glColor3f(0.1, 0.1, 0.1);
		glBegin(GL_POLYGON);
		for (int i = 0; i < sides; i++) {
			glVertex2f(r * cos(i * 2 * pi / sides) + x, r * sin(i * pi * 2 / sides) + y);
		}
		glEnd();
	}

	void drawLine(int i, int j, int k, int l) {
		// Map the coordinates
		double x1 = this->map(i);
		double y1 = this->map(j);
		double x2 = this->map(k);
		double y2 = this->map(l);

		glColor3f(0.1, 0.2, 0.3);
		glLineWidth(2);
		glBegin(GL_LINES);
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
		glEnd();

		// Choose the algorithm
		auto pixels = A3(i, j, k, l);
		for (auto it = pixels.begin(); it != pixels.end(); ++it) {
			writePixel(it->first, it->second);
		}
	}

	void drawCircle(int R) {
		// Choose the algorithm
		auto pixels = A4Circle(R);

		// Draw the circle with red
		double pi = 4 * atan(1.0);
		glColor3f(0.1, 0.2, 0.3);
		glLineWidth(4);
		/*glBegin(GL_LINE_STRIP);
		for (double i = 0; i <= pi / 2; i += pi / 30) {
			printf("%f %f\n", map(R * cos(i)), map(R * sin(i)));
			glVertex2f(map(R * cos(i)), map(R * sin(i)));
		}
		glEnd();*/

		for (auto it = pixels.begin(); it != pixels.end(); ++it) {
			writePixel(it->first, it->second);
		}
	}

	int getN() {
		return n;
	}
};

void Init(void) {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glLineWidth(1);
	glPolygonMode(GL_FRONT, GL_LINE);
}

void Display1(void) {
	Grid grid(20);
	grid.draw();

	//grid.drawLine(1, 1, 4, 3);
	//grid.drawLine(11, 17, 5, 1);
	//grid.drawLine(1, 19, 1, 15);
	//grid.drawLine(7, 1, 9, 3);
	//grid.drawLine(15, 1, 19, 1);
	//grid.drawLine(19, 5, 15, 5);
	//grid.drawLine(13, 8, 19, 16);

	grid.drawLine(0, 15, 15, 10);
	grid.drawLine(15, 7, 0, 0);
}

void Display2() {
	/*Grid grid(20);
	grid.draw();

	grid.drawCircle(13);*/

	Grid grid(1000);
	grid.drawCircle(900);
}

void Display() {
	glClear(GL_COLOR_BUFFER_BIT);

	switch (prevKey) {
	case '1':
		Display1();
		break;
	case '2':
		Display2();
	default:
		break;
	}

	glFlush();
}

void Reshape(int w, int h) {
	glutReshapeWindow(dim, dim);
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
