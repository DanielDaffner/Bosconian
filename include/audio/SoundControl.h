//
// Created by Daniel on 07.03.2021.
//

#ifndef BOSCONIAN_SOUNDCONTROL_H
#define BOSCONIAN_SOUNDCONTROL_H
#include "AL/al.h"
#include "AL/alc.h"
#include "WAVLoader.h"
#include <iostream>
#include "Sound.h"


class SoundControl {
public:

    //wavloader
    WAVLoader wavLoader;
    // device & context
    ALCdevice *device;
    ALCcontext *context;
    //sounds
    Sound* shoot;
    Sound* cannonHit;
    Sound* blast;
    Sound* asteroidHit;
    Sound* enemyShipHit;
    Sound* formationAttack;
    Sound* extendingSound;
    Sound* nextLevel;

    //Speech
    Sound* alive;
    Sound* battleStation;
    Sound* blastOff;
    Sound* conditionRed;
    Sound* spyShipSighted;

    //enum
    enum SoundNames {
        SHOOT = 1,
        CANNONHIT = 2,
        BLAST = 3,
        ASTEROIDHIT = 4,
        ENEMYSHIPHIT = 5,
        FORMATIONATTACK = 6,
        EXTENDINGSOUND = 7,
        NEXTLEVEL = 8,
        ALIVE = 9,
        BATTLESTATION = 10,
        BLASTOFF = 11,
        CONTOTIONRED = 12,
        SPYSHIPSIGHTED = 13
    };

    //methods
    SoundControl();
    void errorLog(char* msg);
    void playSound(Sound sound);
    void initDeviceAndContext();
    void loadAudioFiles();
    void play(SoundNames name);



};


#endif //BOSCONIAN_SOUNDCONTROL_H
