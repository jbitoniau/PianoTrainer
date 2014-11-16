#include "Staff.h"

/*
	Clef
*/
Clef::Clef( const std::string& name, int indexInOctave )
	:	mName(name), 
		mIndexInOctave(indexInOctave)
{
}

const Clef Clef::GClef( "Clef de Sol", 7 );		// G-Clef
const Clef Clef::FClef( "Clef de Fa", 5 );		// F-Clef
const Clef Clef::CClef( "Clef de Ut", 0 );		// C-Clef

/*
	StaffClef
*/
StaffClef::StaffClef( const std::string& name, const Clef& clef, int clefNoteNumber, int staffYPosition )
	:	mName(name), 
		mClef(clef),
		mClefNoteNumber(clefNoteNumber),
		mStaffYPosition(staffYPosition)
{
}

const StaffClef StaffClef::TrebbleClef( "Clef de Sol 2eme", Clef::GClef, 67, 2 );
const StaffClef StaffClef::BassClef( "Clef de Fa 4eme", Clef::FClef, 53, 6 );
const StaffClef StaffClef::MezzoSopranoClef( "Clef d'Ut 2eme", Clef::CClef, 60, 2 );
const StaffClef StaffClef::SopranoClef( "Clef d'Ut 1ere", Clef::CClef, 60, 0 );

/*
	Staff
*/
int	 Staff::mIndexInOctaveToSopranoClefYPos_SharpMode[12] =	{ 0, 0, 1, 1, 2, 3, 3, 4, 4, 5, 5, 6 }; 
int	 Staff::mIndexInOctaveToSopranoClefYPos_FlatMode[12] =	{ 0, 1, 1, 2, 2, 3, 4, 4, 5, 5, 6, 6 };

Staff::Staff( const StaffClef& staffClef )
	: mStaffClef(staffClef),
	  mNote(Note::EmptyNote)
{
}

void Staff::setNote( const Note& note ) 
{
	mNote = note;
}

int Staff::getStaffYPositionFromNote( int noteNumber, bool sharpMode, const StaffClef& staffClef )
{
	int index = 0;

/*	int staffClefNoteNumber = staffClef.getClefNoteNumber();
	int sopranoStaffClefNoteNumber = StaffClef::SopranoClef.getClefNoteNumber();
	int deltaClef = staffClefNoteNumber - sopranoStaffClefNoteNumber;
	index += deltaClef;*/

	int indexInOctave = Note::getIndexInOctave( noteNumber );
	index += indexInOctave;

	index = index % Note::mNumNoteNames;

	// Consider that the note is in the 4th octave and displayed on a staff in Soprano key (C4)
	int y = 0;
	if ( sharpMode )
		y = mIndexInOctaveToSopranoClefYPos_SharpMode[index];
	else
		y = mIndexInOctaveToSopranoClefYPos_FlatMode[index];
	

/*	// Shift to note's octave
	int noteOctaveNumber = Note::getOctaveNumber( noteNumber );
	int yPosOctave = noteOctaveNumber * 11;
	int y = yPosOctave * 11 + yPosInOctave

	// Now shift the position to the right octave
	int noteOctaveNumber = Note::getOctaveNumber( noteNumber );
	int sopranoStaffClefNoteNumber = StaffClef::SopranoClef.getClefNoteNumber();
	int sopranoOctaveNumber = Note::getOctaveNumber( sopranoStaffClefNoteNumber );
	int deltaOctave = noteOctaveNumber - sopranoOctaveNumber;
	
	y += deltaOctave * 11;
*/

	return y;
}


