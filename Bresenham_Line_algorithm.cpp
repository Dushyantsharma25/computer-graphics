#include <GL/glut.h>
#include <iostream>
#include <cmath>

int X1, Y1, X2, Y2;

void myInit() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 500, 0, 500);
}

void draw_pixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void draw_line(int X1, int Y1, int X2, int Y2) {
    int dx = X2 - X1;
    int dy = Y2 - Y1;
    int incx = (dx >= 0) ? 1 : -1;
    int incy = (dy >= 0) ? 1 : -1;

    dx = std::abs(dx);
    dy = std::abs(dy);

    int e, inc1, inc2;
    int x = X1, y = Y1;

    if (dx > dy) {
        draw_pixel(x, y);
        e = 2 * dy - dx;
        inc1 = 2 * (dy - dx);
        inc2 = 2 * dy;
        for (int i = 0; i < dx; i++) {
            if (e >= 0) {
                y += incy;
                e += inc1;
            } else {
                e += inc2;
            }
            x += incx;
            draw_pixel(x, y);
        }
    } else {
        draw_pixel(x, y);
        e = 2 * dx - dy;
        inc1 = 2 * (dx - dy);
        inc2 = 2 * dx;
        for (int i = 0; i < dy; i++) {
            if (e >= 0) {
                x += incx;
                e += inc1;
            } else {
                e += inc2;
            }
            y += incy;
            draw_pixel(x, y);
        }
    }
}

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    draw_line(X1, Y1, X2, Y2);
    glFlush();
}

int main(int argc, char **argv) {
    std::cout << "Enter (X1, Y1, X2, Y2): ";
    std::cin >> X1 >> Y1 >> X2 >> Y2;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Bresenham's Line Drawing");
    myInit();
    glutDisplayFunc(myDisplay);
    glutMainLoop();

    return 0; // Add return statement to main
}
