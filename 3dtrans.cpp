#include <GL/glut.h>
#include <iostream>
#include <math.h>

using namespace std;

typedef float Matrix4[4][4];
Matrix4 theMatrix;
static GLfloat input[8][3] = {
    {40, 40, -50}, {90, 40, -50}, {90, 90, -50}, {40, 90, -50},
    {30, 30, 0}, {80, 30, 0}, {80, 80, 0}, {30, 80, 0}
};

GLfloat output[8][3];
int choice = 0, t = 0;
float tx = 0, ty = 0, tz = 0; // Translation
float sx = 1, sy = 1, sz = 1; // Scaling
float angle = 0; // Rotation angle

void setIdentityM(Matrix4 m) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            m[i][j] = (i == j) ? 1 : 0;
}

void multiplyM() {
    // Multiply the transformation matrix with the output
    for (int i = 0; i < 8; i++) {
        float x = output[i][0];
        float y = output[i][1];
        float z = output[i][2];

        output[i][0] = theMatrix[0][0] * x + theMatrix[0][1] * y + theMatrix[0][2] * z + theMatrix[0][3];
        output[i][1] = theMatrix[1][0] * x + theMatrix[1][1] * y + theMatrix[1][2] * z + theMatrix[1][3];
        output[i][2] = theMatrix[2][0] * x + theMatrix[2][1] * y + theMatrix[2][2] * z + theMatrix[2][3];
    }
}

void translate(int tx, int ty, int tz) {
    setIdentityM(theMatrix);
    theMatrix[0][3] = tx;
    theMatrix[1][3] = ty;
    theMatrix[2][3] = tz;
}

void scale(int sx, int sy, int sz) {
    setIdentityM(theMatrix);
    theMatrix[0][0] = sx;
    theMatrix[1][1] = sy;
    theMatrix[2][2] = sz;
}

void rotateX(float angle) {
    setIdentityM(theMatrix);
    float rad = angle * M_PI / 180.0;
    theMatrix[1][1] = cos(rad);
    theMatrix[1][2] = -sin(rad);
    theMatrix[2][1] = sin(rad);
    theMatrix[2][2] = cos(rad);
}

void rotateY(float angle) {
    setIdentityM(theMatrix);
    float rad = angle * M_PI / 180.0;
    theMatrix[0][0] = cos(rad);
    theMatrix[0][2] = sin(rad);
    theMatrix[2][0] = -sin(rad);
    theMatrix[2][2] = cos(rad);
}

void rotateZ(float angle) {
    setIdentityM(theMatrix);
    float rad = angle * M_PI / 180.0;
    theMatrix[0][0] = cos(rad);
    theMatrix[0][1] = -sin(rad);
    theMatrix[1][0] = sin(rad);
    theMatrix[1][1] = cos(rad);
}

void draw(GLfloat vertices[][3]) {
    glBegin(GL_QUADS);
    for (int i = 0; i < 8; i++) {
        glVertex3fv(vertices[i]);
    }
    glEnd();
}

void Axes() {
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0); // X-axis
    glVertex3f(-100, 0, 0);
    glVertex3f(100, 0, 0);
    glColor3f(0.0, 1.0, 0.0); // Y-axis
    glVertex3f(0, -100, 0);
    glVertex3f(0, 100, 0);
    glColor3f(0.0, 0.0, 1.0); // Z-axis
    glVertex3f(0, 0, -100);
    glVertex3f(0, 0, 100);
    glEnd();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glOrtho(-100, 100, -100, 100, -100, 100);
    glEnable(GL_DEPTH_TEST);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Axes();

    // Apply transformations based on user choice
    switch (choice) {
    case 1: // Translation
        translate(tx, ty, tz);
        break;
    case 2: // Scaling
        scale(sx, sy, sz);
        break;
    case 3: // Rotation
        switch (choiceRot) {
        case 1:
            rotateX(angle);
            break;
        case 2:
            rotateY(angle);
            break;
        case 3:
            rotateZ(angle);
            break;
        }
        break;
    }

    // Multiply transformations and draw
    multiplyM();
    draw(output);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1362, 750);
    glutInitWindowPosition(0,0);
    glutCreateWindow("3D Transformations");
    init();
    cout<<"Enter Your choice: \n 1. Translation \n 2. Scaling \n 3. Rotation \n";
    cin>>choice;
    case 1: // Translation
        cout<<"\nEnter tx,ty,tz: \n";
	cin>>tx>>ty>>tz;
        break;
    case 2: // Scaling
        cout<<"\nEnter sx,sy,sz: \n";
	cin>>sx>>sy>>sz;
        break;
    case 3: // Rotation
	cout<<"Enter your choice for Rotation about axis: \n 1. paralle to x axis:"<<"(y &z) \n 2.parallel to Y axis. (x& z) \n 3.parllel to Z-axis:"<<"(x& y)\n ==";
	cin>>choiceRot;
        switch (choiceRot) {
        case 1:
            cout<<"Enter Rotation angle: ";
	    cin>>angle;
            break;
        case 2:
            cout<<"Enter Rotation angle: ";
	    cin>>angle;
            break;
        case 3:
            cout<<"Enter Rotation angle: ";
	    cin>>angle;
            break;
	default:
		break;
        }

        break;
    }
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

