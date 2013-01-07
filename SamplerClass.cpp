#include "SamplerClass.h"
#include <iterator>

SamplerClass::SamplerClass(){}

SamplerClass::~SamplerClass(){}

SamplerClass::SamplerClass( WavReader * WavFile ) 
{
    SoundFile = WavFile;
}

//Iterator methods begin.

void SamplerClass::setSampleIterator( const_iterator_t NewIterator )
{
    SampleIterator = NewIterator;
}

jack_default_audio_sample_t SamplerClass::current()
{
    return *SampleIterator;
}

const_iterator_t SamplerClass::CurrentIterator()
{
    return SampleIterator;
}

int SamplerClass::key()
{
    return std::distance( SoundFile->begin(), SampleIterator );
}

void SamplerClass::next()
{
    SampleIterator++;
}

void SamplerClass::next( int Offset )
{
    SampleIterator = SampleIterator + Offset;
}

void SamplerClass::rewind()
{
    SampleIterator--;
}

//Iterator methods end.

bool SamplerClass::isAtEnd()
{
    if( this->CurrentIterator() < SoundFile->end() )
    {
        return false;
    }

    return true;
}

WavReader * SamplerClass::getSoundFile( )
{
    return SoundFile;
}

int SamplerClass::Process( jack_nframes_t nframes, void * arg )
{
    SamplerClass * SamplerPtr = ( SamplerClass * ) arg;

    jack_default_audio_sample_t * LeftChannel, * RightChannel;

    LeftChannel = ( jack_default_audio_sample_t * ) jack_port_get_buffer( SamplerPtr->LeftChannelOutputPort, nframes );
    RightChannel = ( jack_default_audio_sample_t * ) jack_port_get_buffer( SamplerPtr->RightChannelOutputPort, nframes );

    for( unsigned int i = 0; i < nframes; i++ )
    {
        LeftChannel[i] = SamplerPtr->current();

        SamplerPtr->next();

        RightChannel[i] = SamplerPtr->current();

        SamplerPtr->next();
    }

    return 0;
}

int SamplerClass::SampleRate( jack_nframes_t nframes, void* arg )
{
    INFO( "The current Jack2 sample rate is " << nframes );

    return 0;
}
