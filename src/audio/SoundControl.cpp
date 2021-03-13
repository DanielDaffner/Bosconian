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
    asteroidHit = wavLoader.loadWAV("../App_Data/audio/asteroidHit.wav");
//    enemyShipHit = wavLoader.loadWAV("../../App_Data/audio/enemyShipHit.wav");
    formationAttack = wavLoader.loadWAV("../App_Data/audio/formationAttack.wav");
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
    background = wavLoader.loadWAV("../App_Data/audio/background.wav");
    background2 = wavLoader.loadWAV("../App_Data/audio/background2.wav");
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
}

void SoundControl::loopSound(Sound sound) {
    std::cout << "LOOP" << std::endl;
    alSourcei(sound.source, AL_LOOPING, AL_TRUE);
    alSourcePlay(sound.source);
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
        case BACKGROUND:
            playSound(*background);
            std::cout << "background" << std::endl;
            break;
            case BACKGROUND2:
            playSound(*background2);
            std::cout << "background2" << std::endl;
            break;
        default:
            break;
    }
}


void SoundControl::loop(SoundNames name) {

    //play
    switch (name) {

        case SHOOT:
            loopSound(*shoot);
            std::cout << "shoot" << std::endl;
            break;
        case CANNONHIT:
            loopSound(*cannonHit);
            std::cout << "cannonHit" << std::endl;
            break;
        case BLAST:
            loopSound(*blast);
            std::cout << "blast" << std::endl;
            break;
        case ASTEROIDHIT:
            loopSound(*asteroidHit);
            std::cout << "asteroidHit" << std::endl;
            break;
        case ENEMYSHIPHIT:
            loopSound(*enemyShipHit);
            std::cout << "enemyShipHit" << std::endl;
            break;
        case FORMATIONATTACK:
            loopSound(*formationAttack);
            std::cout << "formationAttack" << std::endl;
            break;
        case EXTENDINGSOUND:
            loopSound(*extendingSound);
            std::cout << "extendingSound" << std::endl;
            break;
        case NEXTLEVEL:
            loopSound(*nextLevel);
            std::cout << "nextLevel" << std::endl;
            break;
        case ALIVE:
            loopSound(*alive);
            std::cout << "alive" << std::endl;
            break;
        case BATTLESTATION:
            loopSound(*battleStation);
            std::cout << "battleStation" << std::endl;
            break;
        case BLASTOFF:
            loopSound(*blastOff);
            std::cout << "blastOff" << std::endl;
            break;
        case CONTOTIONRED:
            loopSound(*conditionRed);
            std::cout << "conditionRed" << std::endl;
            break;
        case SPYSHIPSIGHTED:
            loopSound(*spyShipSighted);
            std::cout << "spyShipSighted" << std::endl;
            break;
        case MINEEXPLOSION:
            loopSound(*mineExplosion);
            std::cout << "mineExplosion" << std::endl;
            break;
        case BASEEXPLOSION:
            loopSound(*baseExplosion);
            std::cout << "baseExplosion" << std::endl;
            break;
        case BASEARMHIT:
            loopSound(*baseArmHit);
            std::cout << "baseArmHit" << std::endl;
            break;
        case BACKGROUND:
            loopSound(*background);
            std::cout << "background" << std::endl;
            break;
        case BACKGROUND2:
            loopSound(*background2);
            std::cout << "background2" << std::endl;
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
        case BACKGROUND:
            stopSound(*background);
            std::cout << "background" << std::endl;
            break;
        case BACKGROUND2:
            stopSound(*background2);
            std::cout << "background2" << std::endl;
            break;
        default:
            break;
    }


}

void SoundControl::normalizeVolume(){
    //sounds
    //change to float * (100/Volume)

    alSourcef(blast->source, AL_GAIN,0.05f);

//    alSourcef(cannonHit->source, AL_GAIN,0.1f);
//
//    alSourcef(blast->source, AL_GAIN,0.1f);
//
    alSourcef(asteroidHit->source, AL_GAIN,0.1f);
//
//    alSourcef(enemyShipHit->source, AL_GAIN,0.1f);
//
    alSourcef(formationAttack->source, AL_GAIN,0.1f);
//
//    alSourcef(extendingSound->source, AL_GAIN,0.1f);
//
//    alSourcef(nextLevel->source, AL_GAIN,0.1f);
//
    alSourcef(mineExplosion->source, AL_GAIN,1.0f);
//
    alSourcef(baseExplosion->source, AL_GAIN,1.0f);
//
    alSourcef(baseArmHit->source, AL_GAIN,0.7f);

    alSourcef(background->source, AL_GAIN,0.1f);

    alSourcef(background2->source, AL_GAIN,0.1f);
//
//    alSourcef(alive->source, AL_GAIN,0.1f);
//
//    alSourcef(battleStation->source, AL_GAIN,0.1f);
//
//    alSourcef(blastOff->source, AL_GAIN,0.1f);
//
//    alSourcef(conditionRed->source, AL_GAIN,0.1f);
//
//    alSourcef(spyShipSighted->source, AL_GAIN,0.1f);

}
