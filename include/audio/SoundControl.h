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
    Sound* mineExplosion;
    Sound* baseExplosion;
    Sound* baseArmHit;
    Sound* background;
    Sound* background2;
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
        SPYSHIPSIGHTED = 13,
        MINEEXPLOSION = 14,
        BASEEXPLOSION = 15,
        BASEARMHIT = 16,
        BACKGROUND = 17,
        BACKGROUND2 = 18
    };

    //methods
    SoundControl();
    void errorLog(char* msg);
    void playSound(Sound sound);
    void initDeviceAndContext();
    void loadAudioFiles();
    void play(SoundNames name);
    void stop(SoundNames name);
    void stopSound(Sound sound);
    void normalizeVolume();
    void loopSound(Sound sound);
    void loop(SoundNames name);
};


#endif //BOSCONIAN_SOUNDCONTROL_H
