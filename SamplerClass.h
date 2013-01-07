#ifndef SAMPLERCLASS_H
    #define	SAMPLERCLASS_H
    
    #include "SoundEngineClass.h"
    #include "easylogging.h"
    #include "WavReader.h"
    #include <jack/jack.h>
    #include "IteratorInterface.h"

typedef std::vector<float>::const_iterator const_iterator_t;

class SamplerClass : public SoundEngineClass, public IteratorInterface
{

protected:

    WavReader * SoundFile;
    jack_default_audio_sample_t * buffer;
    const_iterator_t SampleIterator; 
    
public:
    
    SamplerClass();
    SamplerClass( WavReader * WavFile );
    virtual ~SamplerClass( );
    void setSampleIterator( const_iterator_t NewIterator );
    jack_default_audio_sample_t current();
    const_iterator_t CurrentIterator();
    int key();
    void next();
    void next( int Offset );
    void rewind();
    bool isAtEnd();   
    static int Process( jack_nframes_t nframes, void * arg );
    static int SampleRate( jack_nframes_t nframes, void* arg );
    WavReader * getSoundFile();
};

#endif	/* SAMPLERCLASS_H */
