#ifndef WAVREADER_H
#define WAVREADER_H

#include <vector>
#include <fstream>
#include <cstdio>
#include <climits>
#include <stdint.h>
#include "BitsPerSampleEnum.h"

class WavReader
{

protected:
    
    FILE * Ffile;
    std::ifstream file;
    unsigned int ChunkSize, SubChunk1Size, SampleRate, ByteRate, SubChunk2Size;
    unsigned short AudioFormat, NumChannels, BlockAlign, BitsPerSample;
    const float _8_BIT_FLOAT,
    _16_BIT_FLOAT,
    _24_BIT_FLOAT,
    _32_BIT_FLOAT;
    char ChunkID[4],
    Format[4],
    SubChunk1ID[4],
    SubChunk2ID[4];

    std::vector<float> SoundData;
    
private:
    
    int UnsignedToSigned( int buffer );
    float IntToDigitalSignal( int AudioSample );

public:

    WavReader();
    ~WavReader();
    void open( const char * filename );
    void read();
    void close();
    std::vector<float>::const_iterator begin();
    std::vector<float>::const_iterator end();
    char * getChunkID();
    unsigned int * getChunkSize();
    char * getFormat();
    char * getSubChunk1ID();
    unsigned int * getSubChunk1Size();
    unsigned short * getAudioFormat();
    unsigned short * getNumChannels();
    unsigned int * getSampleRate();
    unsigned int * getByteRate();
    unsigned short * getBlockAlign();
    unsigned short * getBitsPerSample();
    char * getSubChunk2ID();
    unsigned int * getSubChunk2Size();
    void * getSoundDataBuffer(); 
    void setSoundDataBufferSize( std::vector<int>::size_type new_size );
    std::vector<float>& getSoundDataRef();
    std::vector<int>::iterator getSampleIterator;
    
    };

#endif // WAVREADER_Hx
