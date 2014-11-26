#pragma once

#include "NoteProvider.h"

class NoteProviderMidi : public NoteProvider
{
public:
	NoteProviderMidi();
	virtual ~NoteProviderMidi();	

	virtual void update();
};