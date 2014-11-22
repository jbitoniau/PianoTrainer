#include "NoteProvider.h"

void NoteProvider::addListener( Listener* listener )
{
	mListeners.push_back( listener );
}

void NoteProvider::notifyListeners( const Note& note )
{
	for ( std::size_t i=0; i<mListeners.size(); ++i )
		mListeners[i]->onNoteReceived( this, note );
}

