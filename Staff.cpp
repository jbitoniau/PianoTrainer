#include "Staff.h"

// Index in octave to note Y Pos in Soprano (Ut 1st line) when using sharp mode
// In this key, there's a simple match between the note name (do, ré, mi, ...) and
// its position in the staff:
//	C (Do) is at 0th position, 0th line,
//	D (Ré) is at 1st position, 0th interline,
//	E (Mi) is at 2nd position, 1st line,
//	etc...
// The position depends on whether we want the note to be presented 
// with a sharp or with a flat.
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

// To represent a note vertically on the staff, we assign a number
// to each of its line and interline starting from the bottom. 
// This is the staff coordinate system.
// The bottom vertical position is 0 (Mi on a Sol key staff), 
// then the interline above is 1 (Fa), 
// then the line above is 2 (Sol), etc...
// When the note lies on the "regular" lines/interlines of the staff
// its vertical position is therefore between 0 and 8 (both included)
// It is be negative or greater than 8 when the note lies outside 
// regular staff lines/interlines. 
// Ledger lines are required (when position is >9 or <-1) 
// see http://en.wikipedia.org/wiki/Ledger_line
int Staff::getStaffYPositionFromNote( int noteNumber, bool sharpMode, const StaffClef& staffClef )
{
	int index = 0;
	
	int staffClefNoteNumber = staffClef.getClefNoteNumber();
	
	int staffClefIndexInOctave = Note::getIndexInOctave( staffClefNoteNumber );
	int staffClefOctaveNumber = Note::getOctaveNumber( staffClefNoteNumber );
	int staffClefYPos = staffClef.getStaffYPosition();

	int noteIndexInOctave = Note::getIndexInOctave( noteNumber );
	int noteOctaveNumber = Note::getOctaveNumber( noteNumber );
	int y = 0;
	
	// Use sharp mode here! This works because all staff keys are "regular" notes, i.e. non sharp or flat
	y = -mIndexInOctaveToSopranoClefYPos_SharpMode[staffClefIndexInOctave];	// YPos for Do in same octave as StaffKey
	
	int octaveYPosShift = (noteOctaveNumber-staffClefOctaveNumber) * 7;			// 7 is the number of note names in an octave... i.e. the number of Y pos
	y += octaveYPosShift;

	y += mIndexInOctaveToSopranoClefYPos_SharpMode[noteIndexInOctave];

	y += staffClefYPos;	// Finally shift everything to the line on which the key is
	
	return y;
}


