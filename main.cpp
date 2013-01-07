#include "easylogging.h"
#include "WavReader.h"
#include "SoundEngineClass.h"
#include "SamplerClass.h"
#include <unistd.h>
#include <cstdlib>

jack_client_t * client;

void error( const char * msg )
{
    FATAL( "Message: " << msg );
}

int main( int argc, char** argv )
{
    if( argc != 3 )
    {
        printf( "%s", "Usage arguments: -play somefile.wav\n" );
        
        return 1;
    }
    
    DEBUG( "InitDummy" );   

    jack_set_error_function( error );
    
    WavReader WavFile;
   
    WavFile.open( argv[2] );

    WavFile.read( );
    
    WavFile.close( );

    WavReader * WavFilePtr = &WavFile;

    SamplerClass Sampler( WavFilePtr );

    SamplerClass * SamplerPtr = &Sampler;

    SoundEngineClass * PolySampler = SamplerPtr;
    
    Sampler.setSampleIterator( SamplerPtr->getSoundFile()->begin() /*- 1000000*/ );
    
    PolySampler->OpenClient( client, "Wav Sampler" );

    PolySampler->setProcessCallback( SamplerPtr->Process, SamplerPtr );

    PolySampler->setSampleRateCallback( SamplerPtr->SampleRate, SamplerPtr );

    PolySampler->setLeftChannelOutputPort( "DAW_LEFT_CHANNEL" );

    PolySampler->setRightChannelOutputPort( "DAW_RIGHT_CHANNEL" );

    PolySampler->ActivateClient( );

    PolySampler->ConnectPorts( );

    INFO( "Bits per sample " << *WavFile.getBitsPerSample( ) );

    STATUS( "Now Playing - " << argv[2] );
	
	INFO( "WavFile Sample Rate is: " << *WavFile.getSampleRate() );	

    while( !SamplerPtr->isAtEnd() )
    {
        sleep( 1 );
    }
   
    return 0;

}
