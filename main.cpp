#include <iostream>
#include "include/controller/Controller.h"
#include "include/view/View.h"
#include <chrono>
#include <fstream>
#include "libs/openal-soft/include/AL/al.h"
#include "libs/openal-soft/include/AL/alc.h"

bool isBigEndian(){
    int a = 1;
    return !((char*)&a)[0];
}

int convertToInt(char* buffer, int len){
    int a=0;
    if(!isBigEndian()) {
        for (int i = 0; i < len; i++) {
            ((char *) &a)[i] = buffer[i];
        }
    }
    else {
        for (int i=0;i<len;i++) {
            ((char*)&a) [3-1]=buffer[i];
        }
    }
    return a;
}

char* loadWAV(const char* fn, int& chan, int& samplerate, int& bps, int& size){
    char buffer[4];
    std::ifstream in( fn, std::ios::binary);
    in.read(buffer,4);
    if(strncmp(buffer,"RIFF",4)!=0) {
        std::cout << "this is not a valid WAVE file" << std::endl;
        std::cout << buffer[0] << buffer[1] << buffer[2] << buffer[3] << std::endl;
        //return NULL;
    }
    in.read(buffer,4);
    in.read(buffer,4);  //WAVE
    in.read(buffer,4);  //fmt
    in.read(buffer,4);  //16
    in.read(buffer,2);  //1
    in.read(buffer,2);
    chan=convertToInt(buffer,2);
    in.read(buffer,4);
    samplerate=convertToInt(buffer,4);
    in.read(buffer,4);
    in.read(buffer,2);
    in.read(buffer,2);
    bps=convertToInt(buffer,2);
    in.read(buffer,4);  //data
    in.read(buffer,4);
    size=convertToInt(buffer,4);
    std::cout << size << std::endl;
    char* data= new char[size];

    in.read(data,size);

    return data;

}

int test(){
    //test
    if (isBigEndian()){
        std::cout << "big endian" << std::endl;

    }
    else {
        std::cout << "little endian" << std::endl;
    }

    // start
    int channel,sampleRate,bps,size;

    char* data=loadWAV("test.wav", channel, sampleRate,bps,size);
    ALCdevice* device=alcOpenDevice(NULL);
    if(device==NULL)
    {
        std::cout << "cannot open sound card" << std::endl;
        return 0;
    }
    ALCcontext* context=alcCreateContext(device, NULL);
    if(context=NULL){
        std::cout << "cannot open context" << std::endl;
        return 0;
    }
    alcMakeContextCurrent(context);

    unsigned int bufferid,format;
    alGenBuffers(1, &bufferid);
    if(channel==1)
    {
        if(bps==8)
        {
            AL_FORMAT_MONO8;
        }
        else{
            format=AL_FORMAT_MONO16;
        }

    }
    else{
        if(bps==8){
            format=AL_FORMAT_STEREO8;
        }
        else{
            format=AL_FORMAT_STEREO16;
        }
    }

    alBufferData(bufferid, format, data, size,sampleRate);

    unsigned int sourceid;
    alGenSources(1,&sourceid);
    alSourcei(sourceid,AL_BUFFER,bufferid);
    alSourcePlay(sourceid);
    _sleep(5000);

    alDeleteSources(1,&sourceid);
    alDeleteBuffers(1,&bufferid);

    alcDestroyContext(context);
    alcCloseDevice(device);

    delete[] data;

    return 0;
}

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
    controller->onStart();
    test();
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
        sleeptime = 8 - (int)(elapsed_seconds.count()*1000);
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

