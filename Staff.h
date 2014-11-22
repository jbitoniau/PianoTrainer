#pragma once

#include <vector>
#include "Note.h"
#include "StaffClef.h"

/*
	Staff

	Represents a staff (or stave) in musical notation.
	A staff is container for notes.

	The Staff is always made up of five lines and four
	interlines. Notes that don't fit on these are placed
	on ledger lines.
	
	The staff is constructed with a staff clef that 
	determines on which line/interline each note should 
	be placed.
	
	For now, the Staff only contains a single note and 
	no key signature
	
	TODO: Explain staff-Y-position coordinate system!

	See:
	http://en.wikipedia.org/wiki/Staff_(music)
	http://en.wikipedia.org/wiki/Key_signature
	http://en.wikipedia.org/wiki/Ledger_line
*/
class Staff
{
public:
	Staff( const StaffClef& staffClef );

	StaffClef		getStaffClef() const			{ return mStaffClef; }

	const Note&		getNote() const					{ return mNote; }
	void			setNote( const Note& note );

	int				getStaffYPositionFromNote( int noteNumber, bool sharpMode ) const		{ return getStaffYPositionFromNote(noteNumber, sharpMode, getStaffClef()); }
	static int		getStaffYPositionFromNote( int noteNumber, bool sharpMode, const StaffClef& staffClef );

	class Listener
	{
	public:
		virtual ~Listener() {}
		virtual void onNoteChanged( Staff* staff, const Note& note ) {}
	};
	void			addListener( Listener* listener );

private:
	static int		mIndexInOctaveToSopranoClefYPos_SharpMode[Note::mNumSemitones];		
	static int		mIndexInOctaveToSopranoClefYPos_FlatMode[Note::mNumSemitones];

	void			notifyListeners();

	StaffClef		mStaffClef;
	Note			mNote;
	std::vector<Listener*> mListeners;
};
