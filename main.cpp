#include <iostream>
#include "include/controller/Controller.h"
#include "include/view/View.h"

int main() {
    Controller *controller = new Controller();
    controller->init();
    controller->view->createWindow(1280,960);
    //needed ?
    //glViewport(0,0,width,height);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(controller->view->window))
    {
        /* Render here */
        controller->update();
        /* Swap front and back buffers */
        glfwSwapBuffers(controller->view->window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

