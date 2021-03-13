//
// Created by Daniel on 07.03.2021.
//

#include "../../include/audio/SoundControl.h"
#include <thread>
#include "../../include/utility.h"


SoundControl::SoundControl(){
    initDeviceAndContext();
    loadAudioFiles();
    normalizeVolume();
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
    blast = wavLoader.loadWAV("../App_Data/audio/blast.wav");
//    asteroidHit = wavLoader.loadWAV("../../App_Data/audio/asteroidHit.wav");
//    enemyShipHit = wavLoader.loadWAV("../../App_Data/audio/enemyShipHit.wav");
//    formationAttack = wavLoader.loadWAV("../../App_Data/audio/formationAttack.wav");
//    extendingSound = wavLoader.loadWAV("../../App_Data/audio/extendingSound.wav");
//    nextLevel = wavLoader.loadWAV("../../App_Data/audio/nextLevel.wav");
    mineExplosion = wavLoader.loadWAV("../App_Data/audio/mineExplosion.wav");
    baseExplosion = wavLoader.loadWAV("../App_Data/audio/baseExplosion.wav");
    baseArmHit = wavLoader.loadWAV("../App_Data/audio/baseArmHit.wav");
    alive = wavLoader.loadWAV("../App_Data/audio/alive.wav");
    battleStation = wavLoader.loadWAV("../App_Data/audio/battleStation.wav");
    blastOff = wavLoader.loadWAV("../App_Data/audio/blastOff.wav");
    conditionRed = wavLoader.loadWAV("../App_Data/audio/conditionRed.wav");
    spyShipSighted = wavLoader.loadWAV("../App_Data/audio/spyShipSighted.wav");
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



void SoundControl::playSound(Sound sound) {
    std::cout << "PLAY" << std::endl;

    alSourcePlay(sound.source);

    //alSourcei(sound.source, AL_LOOPING, AL_FALSE);
}

void SoundControl::play(SoundNames name) {

    //play
    switch (name) {

        case SHOOT:
            playSound(*shoot);
            std::cout << "shoot" << std::endl;
            break;
        case CANNONHIT:
            playSound(*cannonHit);
            std::cout << "cannonHit" << std::endl;
            break;
        case BLAST:
            playSound(*blast);
            std::cout << "blast" << std::endl;
            break;
        case ASTEROIDHIT:
            playSound(*asteroidHit);
            std::cout << "asteroidHit" << std::endl;
            break;
        case ENEMYSHIPHIT:
            playSound(*enemyShipHit);
            std::cout << "enemyShipHit" << std::endl;
            break;
        case FORMATIONATTACK:
            playSound(*formationAttack);
            std::cout << "formationAttack" << std::endl;
            break;
        case EXTENDINGSOUND:
            playSound(*extendingSound);
            std::cout << "extendingSound" << std::endl;
            break;
        case NEXTLEVEL:
            playSound(*nextLevel);
            std::cout << "nextLevel" << std::endl;
            break;
        case ALIVE:
            playSound(*alive);
            std::cout << "alive" << std::endl;
            break;
        case BATTLESTATION:
            playSound(*battleStation);
            std::cout << "battleStation" << std::endl;
            break;
        case BLASTOFF:
            playSound(*blastOff);
            std::cout << "blastOff" << std::endl;
            break;
        case CONTOTIONRED:
            playSound(*conditionRed);
            std::cout << "conditionRed" << std::endl;
            break;
        case SPYSHIPSIGHTED:
            playSound(*spyShipSighted);
            std::cout << "spyShipSighted" << std::endl;
            break;
        case MINEEXPLOSION:
            playSound(*mineExplosion);
            std::cout << "mineExplosion" << std::endl;
            break;
        case BASEEXPLOSION:
            playSound(*baseExplosion);
            std::cout << "baseExplosion" << std::endl;
            break;
        case BASEARMHIT:
            playSound(*baseArmHit);
            std::cout << "baseArmHit" << std::endl;
            break;
        default:
            break;
    }
}

void SoundControl::stopSound(Sound sound) {
    std::cout << "STOP" << std::endl;
    alSourceStop(sound.source);
    std::cout << "STOPPED" << std::endl;
    //alSourcei(sound.source, AL_LOOPING, AL_FALSE);
}

void SoundControl::stop(SoundNames name) {
    //play
    switch (name) {

        case SHOOT:
            stopSound(*shoot);
            break;
        case CANNONHIT:
            stopSound(*cannonHit);
            break;
        case BLAST:
            stopSound(*blast);
            break;
        case ASTEROIDHIT:
            stopSound(*asteroidHit);
            break;
        case ENEMYSHIPHIT:
            stopSound(*enemyShipHit);
            break;
        case FORMATIONATTACK:
            stopSound(*formationAttack);
            break;
        case EXTENDINGSOUND:
            stopSound(*extendingSound);
            break;
        case NEXTLEVEL:
            stopSound(*nextLevel);
            break;
        case ALIVE:
            stopSound(*alive);
            break;
        case BATTLESTATION:
            stopSound(*battleStation);
            break;
        case BLASTOFF:
            stopSound(*blastOff);
            break;
        case CONTOTIONRED:
            stopSound(*conditionRed);
            break;
        case SPYSHIPSIGHTED:
            stopSound(*spyShipSighted);
            break;

        default:
            break;
    }


}

void SoundControl::normalizeVolume(){
    //sounds
    //change to float * (100/Volume)

    alSourcef(blast->source, AL_GAIN,0.1f);

//    alSourcei(cannonHit->source, AL_GAIN,0.1f);
//
//    alSourcei(blast->source, AL_GAIN,0.1f);
//
//    alSourcei(asteroidHit->source, AL_GAIN,0.1f);
//
//    alSourcei(enemyShipHit->source, AL_GAIN,0.1f);
//
//    alSourcei(formationAttack->source, AL_GAIN,0.1f);
//
//    alSourcei(extendingSound->source, AL_GAIN,0.1f);
//
//    alSourcei(nextLevel->source, AL_GAIN,0.1f);
//
    alSourcef(mineExplosion->source, AL_GAIN,1.0f);
//
//    alSourcei(baseExplosion->source, AL_GAIN,0.1f);
//
    alSourcei(baseArmHit->source, AL_GAIN,0.1f);
//
//    alSourcei(alive->source, AL_GAIN,0.1f);
//
//    alSourcei(battleStation->source, AL_GAIN,0.1f);
//
//    alSourcei(blastOff->source, AL_GAIN,0.1f);
//
//    alSourcei(conditionRed->source, AL_GAIN,0.1f);
//
//    alSourcei(spyShipSighted->source, AL_GAIN,0.1f);

}
