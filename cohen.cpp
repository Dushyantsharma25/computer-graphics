#include <iostream>
#include <GL/glut.h>
#include <cmath>
#include <vector>

using namespace std;

int pntX1, pntY1, choice = 0, edges;
vector<int> pntX;
vector<int> pntY;
int transX, transY;
double scaleX, scaleY;
double angle, angleRad;

double round(double d) {
    return floor(d + 0.5);
}

void drawPolygon() {
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);
    for (int i = 0; i < edges; i++) {
        glVertex2i(pntX[i], pntY[i]);
    }
    glEnd();
}

void drawPolygonTrans(int x, int y) {
    glBegin(GL_POLYGON);
    glColor3f(0.0, 1.0, 0.0);
    for (int i = 0; i < edges; i++) {
        glVertex2i(pntX[i] + x, pntY[i] + y);
    }
    glEnd();
}

void drawPolygonScale(double x, double y) {
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 1.0);
    for (int i = 0; i < edges; i++) {
        glVertex2i(round(pntX[i] * x), round(pntY[i] * y));
    }
    glEnd();
}

void drawPolygonRotation(double angleRad) {
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 1.0);
    for (int i = 0; i < edges; i++) {
        int x = pntX[i];
        int y = pntY[i];
        glVertex2i(round(x * cos(angleRad) - y * sin(angleRad)),
                   round(x * sin(angleRad) + y * cos(angleRad)));
    }
    glEnd();
}

void myInit(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(4.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-640.0, 640.0, -480.0, 480.0);
}

void myDisplay(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);

    if (choice == 1) {
        drawPolygon();
        drawPolygonTrans(transX, transY);
    } else if (choice == 2) {
        drawPolygon();
        drawPolygonScale(scaleX, scaleY);
    } else if (choice == 3) {
        drawPolygon();
        drawPolygonRotation(angleRad);
    }
    glFlush();
}

int main(int argc, char** argv) {
    cout << "Enter your choice: " << endl;
    cout << "1. Translation" << endl;
    cout << "2. Scaling" << endl;
    cout << "3. Rotation" << endl;
    cout << "6. Exit" << endl;

    cin >> choice;

    if (choice == 6) {
        return 0;
    }

    cout << "\n\nFor Polygon: \n" << endl;
    cout << "Enter number of edges" << endl;
    cin >> edges;

    for (int i = 0; i < edges; i++) {
        cout << "Enter coordinates for vertex " << i + 1 << " : ";
        cin >> pntX1 >> pntY1;

        pntX.push_back(pntX1);
        pntY.push_back(pntY1);
    }

    if (choice == 1) {
        cout << "Enter the translation factors for X and Y: ";
        cin >> transX >> transY;
    } else if (choice == 2) {
        cout << "Enter scaling factors for X and Y: ";
        cin >> scaleX >> scaleY;
    } else if (choice == 3) {
        cout << "Enter rotation angle (in degrees): ";
        cin >> angle;
        angleRad = angle * 3.141592653589793 / 180.0;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("2D Transformations");
    myInit();
    glutDisplayFunc(myDisplay);
    glutMainLoop();

    return 0;
}
