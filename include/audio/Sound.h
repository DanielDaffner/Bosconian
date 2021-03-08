//
// Created by Daniel on 07.03.2021.
//

#ifndef BOSCONIAN_SOUND_H
#define BOSCONIAN_SOUND_H


#include <AL/al.h>
#include <cstdint>

class Sound {
public:
    unsigned char* data;
    int size;
    ALuint source;
    ALuint buffer;
    ALuint frequency;
    ALenum format;
    short bitsPerSample;
    short channels;

    Sound(unsigned char* data,int size, ALuint freq, ALenum form,short bitsPerSample, short chan);
};


#endif //BOSCONIAN_SOUND_H
