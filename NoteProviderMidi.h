#pragma once

#include "NoteProvider.h"

class RtMidiIn;

class NoteProviderMidi : public NoteProvider
{
public:
	NoteProviderMidi();
	virtual ~NoteProviderMidi();	

	virtual void update();

	bool IsAvailable();

private:
	RtMidiIn* mMidiIn;
};