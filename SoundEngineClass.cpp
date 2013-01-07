#include "SoundEngineClass.h"
#include "stdlib.h"
#include <limits>

SoundEngineClass::SoundEngineClass( ){ }

SoundEngineClass::SoundEngineClass( const SoundEngineClass& orig ){ }

SoundEngineClass::~SoundEngineClass( )
{
    jack_deactivate( client );
    jack_port_unregister( client, LeftChannelOutputPort );
    jack_port_unregister( client, RightChannelOutputPort );
    jack_client_close( client );
}

jack_client_t * SoundEngineClass::getClient( )
    {
        return client;
    }

    int SoundEngineClass::OpenClient( jack_client_t * clientptr, const char * name )
    {
        if( ( clientptr = jack_client_open( name, JackNullOption, &status ) ) == 0 )
        {
            FATAL( "Jack Server not running?" );

            return 1;
        }

        STATUS( "Jack client " << name << " successfully opened.   " );

        client = clientptr;

        return 0;
    }

    int SoundEngineClass::ActivateClient( )
    {
        if( jack_activate( client ) )
        {
            ERROR( "Cannot activate client." );

            return 1;
        }

        return 0;

    }

    void SoundEngineClass::setLeftChannelOutputPort( const char * PortName )
    {
        LeftChannelOutputPort = jack_port_register( client, PortName, JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0 );
    }

    void SoundEngineClass::setRightChannelOutputPort( const char * PortName )
    {
        RightChannelOutputPort = jack_port_register( client, PortName, JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0 );
    }

    int SoundEngineClass::ConnectPorts( )
    {
        if( ( ports = jack_get_ports( client, NULL, NULL, JackPortIsPhysical | JackPortIsInput ) ) == NULL )
        {
            FATAL( "Cannot find any physical playback ports" );

            exit( 1 );
        }

        if( ports[0] != NULL )
        {
            if( jack_connect( client, jack_port_name( LeftChannelOutputPort ), ports[0] ) )
            {
                ERROR( "Cannot connect " << jack_port_name( LeftChannelOutputPort ) << " to " << ports[0] );
            }

            if( jack_connect( client, jack_port_name( RightChannelOutputPort ), ports[1] ) )
            {
                ERROR( "Cannot connect " << jack_port_name( RightChannelOutputPort ) << " to " << ports[1] );
            }
        }
        
        return 0;
    }
    
    //Experimental function.
    void SoundEngineClass::setErrorCallback( void(*Callback)(const char *) )
    {
        jack_set_error_function( Callback );
    }

    void SoundEngineClass::setProcessCallback( JackProcessCallback Callback, void * pointer )
    {
        long long sigwut = 0;
        jack_set_process_callback( client, Callback, pointer );
    }

    void SoundEngineClass::setSampleRateCallback( JackSampleRateCallback Callback, void * pointer )
    {
        jack_set_sample_rate_callback( client, Callback, pointer );
    }