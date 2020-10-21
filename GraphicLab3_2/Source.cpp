#include<math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <iterator> 
#include <vector>

#if defined(linux) || defined(_WIN32)
#include"GL\glut.h"/*ÄëÿLinux è Windows*/
#else
#include<GLUT/GLUT.h>/*Äëÿ Mac OS*/
#endif


using namespace std;

struct Point {
	float x;
	float y;
};

const int MINX = 0, MINY = 0, MAXX = 30, MAXY = 30;


vector <Point> pointsA;
list <int> codeA;

vector <Point> pointsS;
list <int> codeS;

int moveOne = 0;

Point currPoint;
float m[16];

void readFromFile(string path, vector <Point> * points, list<int> * code);
void reshape(int w, int h);
void display();
void pressedKey(int key, int x, int y);
void processNormalKeys(unsigned char key, int x, int y);

int main(int argc, char* argv[]) {
	readFromFile("a.txt", &pointsA, &codeA);
	readFromFile("s.txt", &pointsS, &codeS);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800, 500);
	glutCreateWindow("OpenGL lesson 3");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);

	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(pressedKey);
	glGetFloatv(GL_MODELVIEW_MATRIX, m);
	glutMainLoop();
	return 0;
}
void processNormalKeys(unsigned char key, int x, int y) {
	if (key == '=' || key == '+') {
		glPopMatrix();
		moveOne = 0;
		glMatrixMode(GL_MODELVIEW);
		glScaled(1.05, 1.05, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, m);
		glPushMatrix();
		display();
	}
	if ((key == '-') || (key == '_')) {
		glPopMatrix();
		moveOne = 0;
		glMatrixMode(GL_MODELVIEW);
		glScaled(0.95, 0.95, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, m);
		glPushMatrix();
		display();
	}
	if (key == 'a') {
		//glMatrixMode(GL_MODELVIEW);
		moveOne = 0;
		glPopMatrix();
		glPopMatrix();
		glLoadIdentity();
		glGetFloatv(GL_MODELVIEW_MATRIX, m);
		display();
	}
}



void pressedKey(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		glPopMatrix();
		moveOne = 0;
		glMatrixMode(GL_MODELVIEW);
		glTranslated(-0.5, 0, 0);
		glGetFloatv(GL_MODELVIEW_MATRIX, m);
		glPushMatrix();
		display();
		break;
	case GLUT_KEY_RIGHT:
		glPopMatrix();
		moveOne = 0;
		glMatrixMode(GL_MODELVIEW);
		glTranslated(0.5, 0, 0);
		glGetFloatv(GL_MODELVIEW_MATRIX, m);
		glPushMatrix();
		display();
		break;
	case GLUT_KEY_DOWN:
		glPopMatrix();
		moveOne = 0;
		glMatrixMode(GL_MODELVIEW);
		glTranslated(0, -0.5, 0);
		glGetFloatv(GL_MODELVIEW_MATRIX, m);
		glPushMatrix();
		display();
		break;
	case GLUT_KEY_UP:
		glPopMatrix();
		moveOne = 0;
		glMatrixMode(GL_MODELVIEW);
		glTranslated(0, 0.5, 0);
		glGetFloatv(GL_MODELVIEW_MATRIX, m);
		glPushMatrix();
		display();
		break;
	case GLUT_KEY_HOME:
		glPopMatrix();
		moveOne = 0;
		glMatrixMode(GL_MODELVIEW);
		glRotatef(5, 0, 0, 1);
		glGetFloatv(GL_MODELVIEW_MATRIX, m);
		glPushMatrix();
		display();
		break;
	case GLUT_KEY_END:
		glPopMatrix();
		moveOne = 0;
		glMatrixMode(GL_MODELVIEW);
		glRotatef(-5, 0, 0, 1);
		glGetFloatv(GL_MODELVIEW_MATRIX, m);
		glPushMatrix();
		display();
		break;
	case GLUT_KEY_PAGE_UP:
		glMatrixMode(GL_MODELVIEW);
		
		glPushMatrix();
		glLoadMatrixf(m);
		glRotatef(5, 0, 0, 1);
		moveOne = 1;
		display();
		glGetFloatv(GL_MODELVIEW_MATRIX, m);
		glPopMatrix();
		glPopMatrix();
		glRotatef(-5, 0, 0, 1);
		moveOne = 2;
		display();
		glPushMatrix();

		break;
	}
}


void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(MINX, MAXX, MINY, MAXY);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void readFromFile(string path, vector <Point> * points, list<int> * code)
{
	fstream f(path, ios::in);
	cout << path << endl;
	if (f.is_open()) {
		if ((*points).empty()) {
			int pointNumber;
			Point p;
			f >> pointNumber;
			for (int i = 0; i < pointNumber; i++)
			{
				f >> p.x >> p.y;
				(*points).push_back(p);

			}
			cout << endl;
			int movesNumber, m;
			f >> movesNumber;
			for (int i = 0; i < movesNumber; i++)
			{
				f >> m;
				(*code).push_back(m);
				cout << m << endl;
			}
		}
		else {
			int shiftForDots = (*points).size();
			int pointNumber;
			Point p;
			f >> pointNumber;
			for (int i = 0; i < pointNumber; i++)
			{
				f >> p.x >> p.y;
				(*points).push_back(p);

			}
			cout << endl;
			int movesNumber, m;
			f >> movesNumber;
			for (int i = 0; i < movesNumber; i++)
			{
				f >> m;
				m < 0 ? m -= shiftForDots : m += shiftForDots;
				(*code).push_back(m);
				cout << m << endl;
			}
		}

	}
	f.close();
}


void moveTo(int mto, vector <Point> * points, list<int> * code) {
	mto = abs(mto) - 1;
	currPoint.x = (*points)[mto].x;
	currPoint.y =(*points)[mto].y;

}

void drawTo(int dto, vector <Point> * points, list<int> * code) {
	dto = dto - 1;
	Point p = (*points)[dto];
	glColor3d(1, 1, 1);
	glBegin(GL_LINES);
	glVertex2i(currPoint.x, currPoint.y);
	glVertex2i(p.x, p.y);

	glEnd();
	currPoint.x = p.x;
	currPoint.y = p.y;
}

void drawOrMove(vector <Point> * points, list<int> * code) {

	for (auto it = (*code).begin(); it != (*code).end(); it++) {
		if ((*it) < 0) {
			moveTo((*it), points, code);
		}
		else {
			drawTo((*it), points, code);
		}
	}

}

void display() {

	if (moveOne == 0) {
		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT);
		drawOrMove(&pointsA, &codeA);
		drawOrMove(&pointsS, &codeS);
	}

	else {
		if (moveOne == 1) {
			glClearColor(0, 0, 0, 0);
			glClear(GL_COLOR_BUFFER_BIT);
			drawOrMove(&pointsA, &codeA);
		}
		else {
			drawOrMove(&pointsS, &codeS);
		}
	}


	glutSwapBuffers();
}