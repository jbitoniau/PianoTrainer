#pragma once

#include "NoteProvider.h"

class NoteProviderKeyboard : public NoteProvider
{
public:
	virtual ~NoteProviderKeyboard();	

	virtual Note getNote();
};