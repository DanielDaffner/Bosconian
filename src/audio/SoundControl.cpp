//
// Created by Daniel on 07.03.2021.
//

#include "../../include/audio/SoundControl.h"
#include <thread>
#include "../../include/utility.h"


SoundControl::SoundControl(){
    initDeviceAndContext();
    loadAudioFiles();
}

void SoundControl::errorLog(char* msg){
    // error msg
    std::cout << msg << std::endl ;
    system("PAUSE");
}

void SoundControl::loadAudioFiles(){

    //loadWaveFiles
//    shoot = wavLoader.loadWAV("../../App_Data/audio/shoot.wav");
//    cannonHit = wavLoader.loadWAV("../../App_Data/audio/cannonHit.wav");
    blast = wavLoader.loadWAV("../App_Data/audio/Blast.wav");
//    asteroidHit = wavLoader.loadWAV("../../App_Data/audio/asteroidHit.wav");
//    enemyShipHit = wavLoader.loadWAV("../../App_Data/audio/enemyShipHit.wav");
//    formationAttack = wavLoader.loadWAV("../../App_Data/audio/formationAttack.wav");
//    extendingSound = wavLoader.loadWAV("../../App_Data/audio/extendingSound.wav");
//    nextLevel = wavLoader.loadWAV("../../App_Data/audio/nextLevel.wav");
//    alive = wavLoader.loadWAV("../../App_Data/audio/alive.wav");
//    battleStation = wavLoader.loadWAV("../../App_Data/audio/battleStation.wav");
//    blastOff = wavLoader.loadWAV("../../App_Data/audio/blastOff.wav");
//    conditionRed = wavLoader.loadWAV("../../App_Data/audio/conditionRed.wav");
//    spyShipSighted = wavLoader.loadWAV("../../App_Data/audio/spyShipSighted.wav");
}

void SoundControl::initDeviceAndContext() {
    device = alcOpenDevice(NULL);
    if(!device){
        errorLog("no sound device");
        return;
    }

    context = alcCreateContext(device, NULL);
    alcMakeContextCurrent(context);
    if(!context){
        errorLog("no sound context");
        return;
    }
}

void playInThread(Sound sound){

    ALuint source;
    ALuint buffer;

    alGenBuffers(1,&buffer);
    alGenSources(1, &source);

    if(sound.bitsPerSample==8){
        if(sound.channels==1)
            sound.format = AL_FORMAT_MONO8;
        else if ( sound.channels==2)
            sound.format = AL_FORMAT_STEREO8;
    }
    else if (sound.bitsPerSample == 16)
    {
        if(sound.channels==1)
            sound.format = AL_FORMAT_MONO16;
        else if (sound.channels==2)
            sound.format = AL_FORMAT_STEREO16;
    }

    alBufferData(buffer, sound.format, sound.data, sound.size, sound.frequency);
    alSourcei(source, AL_BUFFER, buffer);
    std::cout << "PLAY" << std::endl;
    alSourcePlay(source);
    _sleep(5000);
    std::cout << "END" << std::endl;


}

void SoundControl::playSound(Sound sound) {
    //play
    //std::thread worker (playInThread, sound);
    playInThread(sound);
}

void SoundControl::play(SoundNames name) {
    //play
    switch (name) {

        case SHOOT:
            playSound(*shoot);
            break;
        case CANNONHIT:
            playSound(*cannonHit);
            break;
        case BLAST:
            playSound(*blast);
            break;
        case ASTEROIDHIT:
            playSound(*asteroidHit);
            break;
        case ENEMYSHIPHIT:
            playSound(*enemyShipHit);
            break;
        case FORMATIONATTACK:
            playSound(*formationAttack);
            break;
        case EXTENDINGSOUND:
            playSound(*extendingSound);
            break;
        case NEXTLEVEL:
            playSound(*nextLevel);
            break;
        case ALIVE:
            playSound(*alive);
            break;
        case BATTLESTATION:
            playSound(*battleStation);
            break;
        case BLASTOFF:
            playSound(*blastOff);
            break;
        case CONTOTIONRED:
            playSound(*conditionRed);
            break;
        case SPYSHIPSIGHTED:
            playSound(*spyShipSighted);
            break;

        default:
            break;
    }
}

