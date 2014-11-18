#pragma once

#include "NoteProvider.h"

class NoteProviderMidi : public NoteProvider
{
public:
	virtual ~NoteProviderMidi();	

	virtual Note getNote();
};