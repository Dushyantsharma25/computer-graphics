#include <iostream>
#include <GL/glut.h>
#include <cmath>
#include <cstdlib> // For rand()
#include <ctime>   // For time()

float ballX = 0.0f;          // Ball's X position
float ballY = 0.0f;          // Ball's Y position
float ballRadius = 20.0f;    // Ball radius
float ballSpeedX = 2.0f;     // Slower speed of the ball in X direction
float ballSpeedY = 2.0f;     // Slower speed of the ball in Y direction
float rectX = 0.0f;          // Rectangle's X position
const float rectWidth = 100.0f; // Width of the rectangle
const float rectHeight = 20.0f; // Height of the rectangle
const float moveSpeed = 30.0f;   // Speed of rectangle movement
int score = 0;               // Player's score

// Function to set a random direction for the ball
void setRandomBallDirection() {
    ballSpeedX = (rand() % 2 == 0 ? 2.0f : -2.0f) * (1 + (rand() % 3)); // Random speed and direction
    ballSpeedY = (rand() % 2 == 0 ? 2.0f : -2.0f) * (1 + (rand() % 3)); // Random speed and direction
}

// Initialization function
void myInit() {
    glClearColor(1.0, 1.0, 1.0, 0.0); // Set background color to white
    glColor3f(1.0f, 0.0f, 0.0f);      // Set ball color to red
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-600.0, 600.0, -340.0, 340.0); // Set up the coordinate system
}

// Keyboard function to handle user input
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'a': // Move left
            rectX -= moveSpeed;
            if (rectX < -600 + rectWidth / 2) rectX = -600 + rectWidth / 2; // Keep inside left wall
            break;
        case 'd': // Move right
            rectX += moveSpeed;
            if (rectX > 600 - rectWidth / 2) rectX = 600 - rectWidth / 2; // Keep inside right wall
            break;
    }
    glutPostRedisplay(); // Request to redraw
}

// Timer function for updating the ball's position
void update(int value) {
    ballX += ballSpeedX;
    ballY += ballSpeedY;

    // Check for wall collisions
    if (ballX + ballRadius >= 600 || ballX - ballRadius <= -600) {
        ballSpeedX = -ballSpeedX; // Reverse direction
    }
    if (ballY + ballRadius >= 340) {
        ballSpeedY = -ballSpeedY; // Reverse direction
    }

    // Check if the ball is caught by the rectangle
    if (ballY - ballRadius <= -300 && ballX >= rectX - rectWidth / 2 && ballX <= rectX + rectWidth / 2) {
        score++;
        std::cout << "Score: " << score << std::endl;
        ballX = 0.0f; // Reset ball position
        ballY = 0.0f;
        setRandomBallDirection(); // Set random direction and speed for the ball
    }

    // Check for ground collision
    if (ballY - ballRadius <= -340) {
        std::cout << "Game Over! Final Score: " << score << std::endl;
        exit(0); // End the game
    }

    glutPostRedisplay(); // Request to redraw
    glutTimerFunc(16, update, 0); // Call update again after a short delay
}

// Display function
void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT); // Clear the screen

    // Draw the ball
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(ballX, ballY);
    for (int i = 0; i <= 20; i++) {
        float angle = 2.0f * 3.14159f * float(i) / float(20); // Circle
        float x = ballRadius * cosf(angle);
        float y = ballRadius * sinf(angle);
        glVertex2f(ballX + x, ballY + y);
    }
    glEnd();

    // Draw the rectangle
    glBegin(GL_QUADS);
    glVertex2f(rectX - rectWidth / 2, -300 - rectHeight / 2);
    glVertex2f(rectX + rectWidth / 2, -300 - rectHeight / 2);
    glVertex2f(rectX + rectWidth / 2, -300 + rectHeight / 2);
    glVertex2f(rectX - rectWidth / 2, -300 + rectHeight / 2);
    glEnd();

    glutSwapBuffers(); // Swap the buffers
}

// Main function
int main(int argc, char** argv) {
    srand(static_cast<unsigned int>(time(0))); // Seed for random number generation

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(1100, 600); // Set window size
    glutInitWindowPosition(100, 100); // Set window position
    glutCreateWindow("Catch the Ball Game"); // Create window

    glutKeyboardFunc(keyboard); // Register keyboard function
    myInit(); // Call initialization
    glutDisplayFunc(myDisplay); // Register display function
    glutTimerFunc(0, update, 0); // Start the timer
    glutMainLoop(); // Enter the GLUT event loop
    return 0;
}
