#ifndef SOUNDENGINECLASS_H
    #define	SOUNDENGINECLASS_H

    #include <jack/jack.h>
    #include "easylogging.h"

class SoundEngineClass
{

protected:

    jack_client_t * client;
    jack_status_t status;
    jack_nframes_t SampleRate; //uint32_t

    const char ** ports;
    
public:
    
    jack_port_t * LeftChannelOutputPort, * RightChannelOutputPort;

public:
    
    SoundEngineClass( );
    SoundEngineClass( const SoundEngineClass& orig );
    virtual ~SoundEngineClass( );
    jack_client_t * getClient( );
    int OpenClient( jack_client_t * clientptr, const char * name );
    int ActivateClient( );
    void setLeftChannelOutputPort( const char * PortName );
    void setRightChannelOutputPort( const char * PortName );
    int ConnectPorts( );
    void setErrorCallback( void(*Callback)(const char *) );
    void setProcessCallback( JackProcessCallback Callback, void * pointer );
    void setSampleRateCallback( JackSampleRateCallback Callback, void * pointer );
    
};

#endif	/* SOUNDENGINECLASS_H */

