#include <vector>

#include "WavReader.h"
#include "easylogging.h"

WavReader::WavReader( ) :
    _8_BIT_FLOAT(255.0),
    _16_BIT_FLOAT(65535.0),
    _24_BIT_FLOAT(8388607.0),
    _32_BIT_FLOAT(4294967295.0)
    {}

WavReader::~WavReader( ){ }



void WavReader::open( const char * filename )
{
    file.open( filename, std::fstream::binary );
}

void WavReader::read( )
{
    file.read( this->getChunkID( ), 4 );

    file.read( ( char* ) this->getChunkSize( ), 4 );

    file.read( this->getFormat( ), 4 );

    file.read( this->getSubChunk1ID( ), 4 );

    file.read( ( char* ) this->getSubChunk1Size( ), 4 );

    file.read( ( char* ) this->getAudioFormat( ), 2 );

    file.read( ( char* ) this->getNumChannels( ), 2 );

    file.read( ( char* ) this->getSampleRate( ), 4 );

    file.read( ( char* ) this->getByteRate( ), 4 );

    file.read( ( char* ) this->getBlockAlign( ), 2 );

    file.read( ( char* ) this->getBitsPerSample( ), 2 );

    file.read( ( char* ) this->getSubChunk2ID( ), 4 );

    file.read( ( char* ) this->getSubChunk2Size( ), 4 );

    int buffer;
    
    int number_of_bytes = 2; //Read the README For more information about this line.
    
    float AudioSampleBuffer;
    
    for( int i = 0; i < *this->getSubChunk2Size() / *this->getNumChannels(); i++)
    {
        file.read( ( char * ) &buffer, number_of_bytes );

        // Determine the padding byte
        unsigned char padding_byte = 0;

        if( ( ( char* ) &buffer )[number_of_bytes - 1] & 128 )
        {
            padding_byte = 255;
        }

        // Pad the data
        for( int i = number_of_bytes; i < sizeof (buffer ); i++ )
        {
            ( ( char* ) &buffer )[i] = padding_byte;
        }
        
        AudioSampleBuffer = this->IntToDigitalSignal( buffer );
        
        SoundData.push_back( AudioSampleBuffer );
        
    }
    
}

float WavReader::IntToDigitalSignal( int AudioSample )
{  
    switch( BitsPerSample )
    {
        case 8:
            return AudioSample / _8_BIT_FLOAT;
            break;
            
        case 16:
            return AudioSample / _16_BIT_FLOAT;
            break;
            
        case 24:
            return AudioSample / _24_BIT_FLOAT;
            break;
            
        case 32:
            return AudioSample / _32_BIT_FLOAT;
            
        default:
            FATAL( "INVALID BITS PER SAMPLE VALUE, CORRUPTED WAV?" );
            exit(1);
    }
     
}

void WavReader::close( )
{
    file.close( );
}

char * WavReader::getChunkID( )
{
    return ChunkID;
}

unsigned int * WavReader::getChunkSize( )
{
    return &ChunkSize;
}

char * WavReader::getFormat( )
{
    return Format;
}

char * WavReader::getSubChunk1ID( )
{
    return SubChunk1ID;
}

unsigned int * WavReader::getSubChunk1Size( )
{
    return &SubChunk1Size;
}

unsigned short * WavReader::getAudioFormat( )
{
    return &AudioFormat;
}

unsigned short * WavReader::getNumChannels( )
{
    return &NumChannels;
}

unsigned int * WavReader::getSampleRate( )
{
    return &SampleRate;
}

unsigned int * WavReader::getByteRate( )
{
    return &ByteRate;
}

unsigned short * WavReader::getBlockAlign( )
{
    return &BlockAlign;
}

unsigned short * WavReader::getBitsPerSample( )
{
    return &BitsPerSample;
}

char * WavReader::getSubChunk2ID( )
{
    return SubChunk2ID;
}

unsigned int * WavReader::getSubChunk2Size( )
{
    return &SubChunk2Size;
}

void * WavReader::getSoundDataBuffer( )
{
    try
    {
        if( SoundData.size( ) < 1 )
        {
            throw "You must set a buffer size via 'setSoundDataBufferSize' before calling the SoundDataBuffer.";
        }

        return SoundData.data( );
    }
    catch( const char * msg )
    {
        FATAL( "Exception raised:" << msg );
    }
}

std::vector<float> & WavReader::getSoundDataRef( )
{
    return SoundData;
}

std::vector<float>::const_iterator WavReader::begin()
{
    return SoundData.begin();
}

std::vector<float>::const_iterator WavReader::end()
{
    return SoundData.end();
}

void WavReader::setSoundDataBufferSize( std::vector<int>::size_type new_size )
{
    SoundData.resize( new_size );
}
