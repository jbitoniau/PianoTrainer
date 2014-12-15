#include "GrandStaff.h"

GrandStaff::GrandStaff()
	: mTrebbleStaff( StaffClef::TrebbleClef ),
	  mBassStaff( StaffClef::BassClef),
	  mNote()
{
}

void GrandStaff::setNote( const Note& note ) 
{
	if ( mNote==note )
		return;
	mNote = note;
	
	if ( mNote.getNumber()>60 )
	{
		mTrebbleStaff.setNote( note );
		mBassStaff.setNote( Note::EmptyNote );
	}
	else
	{
		mTrebbleStaff.setNote( Note::EmptyNote );
		mBassStaff.setNote( note );
	}
	notifyListeners();	
}

void GrandStaff::addListener( Listener* listener )
{
	mListeners.push_back( listener );
}

void GrandStaff::notifyListeners()
{
	for ( std::size_t i=0; i<mListeners.size(); ++i )
		mListeners[i]->onNoteChanged( this, getNote() );
}

