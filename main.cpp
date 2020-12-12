#include <iostream>
#include "include/controller/Controller.h"
#include "include/view/View.h"



int main() {

    //init controller

    Controller *controller = new Controller();
    controller->init();
    controller->view->createMainWindow();
    while (!glfwWindowShouldClose(controller->view->window )) {

    /* Loop until the user closes the window */
    while (!controller->inGame) {
        /* Render here */
        controller->updateMainWindow();
        /* Swap front and back buffers */
        glfwSwapBuffers(controller->view->window);

        /* Poll for and process events */
        glfwPollEvents();
        _sleep(3);
    }

        controller->view->createMainWindow();

    while (!inGame) {
        /* Render here */
        controller->updateGameWindow();
        /* Swap front and back buffers */
        glfwSwapBuffers(controller->view->window);

        /* Poll for and process events */
        glfwPollEvents();
        _sleep(3);
    }

}
    glfwTerminate();
    return 0;


}

