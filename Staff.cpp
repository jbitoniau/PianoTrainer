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
	if ( mNote==note )
		return;
	mNote = note;
	notifyListeners();	
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
	// Get properties of the staff clef 
	int staffClefNoteNumber = staffClef.getClefNoteNumber();
	int staffClefIndexInOctave = Note::getIndexInOctave( staffClefNoteNumber );
	int staffClefOctaveNumber = Note::getOctaveNumber( staffClefNoteNumber );
	int staffClefYPos = staffClef.getStaffYPosition();

	// Get properties of the note to display
	int noteIndexInOctave = Note::getIndexInOctave( noteNumber );
	int noteOctaveNumber = Note::getOctaveNumber( noteNumber );
	
	// For now, we consider that the staff key is displayed on the first line (Staff key Y-Pos=0). 
	// First we get the Y Pos of the C-note (Do) that is just below (or identical) to the staff key note.
	// It is usually a just a few Y-Pos below.
	// We use sharp mode in the calculation here. This works because all standard staff keys (treble, bass, etc...) 
	// are "plain" notes (i.e. non sharp or flat). We could therefore use either the SharpMode or FlatMode 
	// version here as it would return the same thing.
	int y = -mIndexInOctaveToSopranoClefYPos_SharpMode[staffClefIndexInOctave];		
	
	// Then we shift the Y Pos to take into consideration the octave of the note. 
	int octaveYPosShift = (noteOctaveNumber-staffClefOctaveNumber) * 7;			// 7 is the number of note names in an octave, i.e. the number of Y Pos to move from one octave to the next
	y += octaveYPosShift;

	// Then we shift the Y Pos to take into consideration the note in its octave.
	if ( sharpMode )
		y += mIndexInOctaveToSopranoClefYPos_SharpMode[noteIndexInOctave];
	else
		y += mIndexInOctaveToSopranoClefYPos_FlatMode[noteIndexInOctave];	

	// Finally shift everything to the line on which the key is displayed on the staff 
	y += staffClefYPos;	
	
	return y;
}

void Staff::addListener( Listener* listener )
{
	mListeners.push_back( listener );
}

void Staff::notifyListeners()
{
	for ( std::size_t i=0; i<mListeners.size(); ++i )
		mListeners[i]->onNoteChanged( this, getNote() );
}

