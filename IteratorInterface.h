#include <vector>

#ifndef ITERATORINTERFACE_H
#define ITERATORINTERFACE_H

class IteratorInterface
{

public:

	virtual ~IteratorInterface(){}
	virtual jack_default_audio_sample_t current() = 0;
	virtual int key() = 0;
	virtual void next() = 0;
    virtual void next( int Position ) = 0;	
    virtual void rewind() = 0; 
};

#endif
