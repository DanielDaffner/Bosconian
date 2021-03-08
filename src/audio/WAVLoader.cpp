//
// Created by Daniel on 07.03.2021.
//

#include <iostream>
#include <cstdlib>
#include "../../include/audio/WAVLoader.h"

void errorLog (char* msg){
    // error msg
    std::cout << msg << std::endl ;
    system("PAUSE");
}

Sound* WAVLoader::loadWAV(char *url) {

    FILE *fp = NULL;
    fp = fopen(url,"rb");
    char type[4];
    uint32_t size, chunkSize;
    short formatType, channels;
    uint32_t sampleRate, avgBytesPerSec;
    short bytesPerSample, bitsPerSample;
    uint32_t dataSize;

    fread(type, sizeof(char),4,fp);
    if(type[0]!='R' || type[1]!='I' || type[2]!='F' || type[3]!='F'){
        errorLog("!RIFF");
        return NULL;}

    fread (&size, sizeof (uint32_t),1,fp);
    fread (type, sizeof (char),4,fp);
    if(type[0]!='W' || type[1]!='A' || type[2]!='V' || type[3]!='E'){
        errorLog("!WAVE");
        return NULL;}

    fread (type, sizeof (char),4,fp);
    if(type[0]!='f' || type[1]!='m' || type[2]!='t' || type[3]!=' '){
        errorLog("!fmt");
        return NULL;}

    // wave info
    fread(&chunkSize, sizeof(uint32_t),1,fp);
    fread(&formatType, sizeof(short),1,fp);
    fread(&channels, sizeof(short),1,fp);
    fread(&sampleRate, sizeof(uint32_t),1,fp);
    fread(&avgBytesPerSec, sizeof(uint32_t),1,fp);
    fread(&bytesPerSample, sizeof(short),1,fp);
    fread(&bitsPerSample, sizeof(short),1,fp);

    //sound data
    fread (type, sizeof (char),4,fp);
    if(type[0]!='d' || type[1]!='a' || type[2]!='t' || type[3]!='a'){
        errorLog("Missing DATA");
        return NULL;}

    fread(&dataSize, sizeof(uint32_t),1,fp);

    //read data
    unsigned char* buf = new unsigned char[dataSize];
    fread(buf, sizeof(char),dataSize,fp);

    ALuint source;
    ALuint buffer;

    alGenBuffers(1,&buffer);
    alGenSources(1, &source);

    if(bitsPerSample==8){
        if(channels==1)
            formatType = AL_FORMAT_MONO8;
        else if ( channels==2)
            formatType = AL_FORMAT_STEREO8;
    }
    else if (bitsPerSample == 16)
    {
        if(channels==1)
            formatType = AL_FORMAT_MONO16;
        else if (channels==2)
            formatType = AL_FORMAT_STEREO16;
    }

    alBufferData(buffer, formatType, buf, size, sampleRate);
    alSourcei(source, AL_BUFFER, buffer);
    //alSourcei(source, AL_LOOPING, AL_TRUE);
    alSourcef(source,AL_GAIN,0.3f);
    Sound* result = new Sound(source);

    return result;

}