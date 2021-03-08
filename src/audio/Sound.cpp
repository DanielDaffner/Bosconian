//
// Created by Daniel on 07.03.2021.
//

#include "../../include/audio/Sound.h"

Sound::Sound(unsigned char* data,int size, ALuint freq, ALenum form,short bps, short chan) {

     frequency=freq;
     format=form;
     bitsPerSample=bps;
     channels=chan;

}