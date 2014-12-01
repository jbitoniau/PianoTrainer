#pragma once

#include <vector>
#include "Note.h"

class NoteProvider
{
public:
	virtual ~NoteProvider() {}
	virtual void update() = 0;

	
	class Listener
	{
	public:
		virtual ~Listener() {}
		virtual void onNoteReceived( NoteProvider* noteProvider, const Note& note ) {}
	};

	void	addListener( Listener* listener );

protected:
	void	notifyListeners( const Note& note );

private:
	std::vector<Listener*> mListeners;
};