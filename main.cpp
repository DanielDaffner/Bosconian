#include <iostream>
#include "include/controller/Controller.h"
#include "include/view/View.h"
#include <chrono>


int main() {

    //init controller

    Controller *controller = new Controller();
    controller->init();
    controller->view->createMainWindow();
    while (!glfwWindowShouldClose(controller->view->window )) {
    /* Loop until the user closes the window */
    while (!controller->inGame && !glfwWindowShouldClose(controller->view->window )) {
        /* Render here */
        controller->updateMainWindow();
        /* Swap front and back buffers */
        glfwSwapBuffers(controller->view->window);

        /* Poll for and process events */
        glfwPollEvents();
        _sleep(17);
    }

    //controller->view->createMainWindow();
    auto start = std::chrono::system_clock::now();
    auto end = std::chrono::system_clock::now();
    int sleeptime = 0;
    while (controller->inGame && !glfwWindowShouldClose(controller->view->window )) {
        /* Render here */
        start = std::chrono::system_clock::now();

        controller->updateGameWindow();
        /* Swap front and back buffers */
        glfwSwapBuffers(controller->view->window);
        /* Poll for and process events */
        glfwPollEvents();

        end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        sleeptime = 17 - (int)(elapsed_seconds.count()*1000);
//        printf("time %d\n",sleeptime);
        if(sleeptime < 0) {
            sleeptime = 0;
            printf("givememoretime\n");
        }
        start = std::chrono::system_clock::now();
        _sleep(sleeptime);
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
//        printf("actual %f\n", (elapsed_seconds.count()*1000));
    }

}
    glfwTerminate();
    return 0;


}

