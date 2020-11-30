#include <iostream>
#include "libs/glfw-3.3.2/include/GLFW/glfw3.h"
#include <gl/gl.h>

int main() {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1280, 960, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glMatrixMode( GL_PROJECTION ); // Stack für Projektionsmatrix als
        // aktiven Matrixstack setzen
        glLoadIdentity();              // Identitätsmatrix auf den Stack laden

        // Eine orthogonale Projektionsmatrix zum Stack
        // dazu multiplizieren.
        glOrtho( 0, 800, 600, 0, -1, 1 );
        
        glBegin( GL_TRIANGLES ); // Wir wollen ein Dreieck zeichnen
        glColor3f(1,0,0);      // Ab jetzt werden alle gezeichneten Punkte rot
        glVertex3f(400,100,0); // Der erste Eckpunkt ist mittig und 100 Pixel
        // vom oberen Rand entfernt

        glColor3f(0,1,0);      // Ab jetzt werden alle gezeichneten Punkte grün
        glVertex3f(750,500,0); // Der zweite Eckpunkt ist 50 Pixel vom rechten
        // und 100 Pixel vom unteren Rand entfernt

        glColor3f(0,0,1);      // Ab jetzt werden alle gezeichneten Punkte blau
        glVertex3f(50,500,0);  // Der dritte Eckpunkt ist 50 Pixel vom linken
        // und 100 Pixel vom unteren Rand entfernt
        glEnd();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        printf("do_it");
        _sleep(1000);
    }

    glfwTerminate();
    return 0;
}
