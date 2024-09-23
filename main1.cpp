//DDA Line Algorithm
#include <GL/glut.h> // open GL library
#include <iostream>
#include <cmath>

using namespace std;

int X1, Y1, X2, Y2;

void ddaLine(int X1, int Y1, int X2, int Y2) {
    int dx = X2 - X1;
    int dy = Y2 - Y1;
    int steps = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);
    float xIncrement = dx / (float)steps;
    float yIncrement = dy / (float)steps;
    float x = X1;
    float y = Y1;

    glBegin(GL_POINTS);
    for (int i = 0; i <= steps; i++) {
        glVertex2i(round(x), round(y));
        x += xIncrement;
        y += yIncrement;
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    ddaLine(X1, Y1, X2, Y2);
    glFlush();
}

int main(int argc, char** argv) {
    cout << "Enter X1, Y1, X2, Y2: ";
    cin >> X1 >> Y1 >> X2 >> Y2;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("DDA Line Drawing Algorithm");

    glOrtho(0, 800, 0, 600, -1, 1);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
