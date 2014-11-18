#pragma once

#include "Note.h"

class NoteProvider
{
public:
	virtual Note getNote() = 0;
};