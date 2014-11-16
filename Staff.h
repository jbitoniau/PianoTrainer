#pragma once

#include "Note.h"

/*
	Clef

	Represents the general concept of clef in musical notation
	This object is the clef out of the staff context. It's basically
	just the clef symbol here.
	There only exist a handful of clefs: G/Sol, F/Fa, C/Do

	See http://en.wikipedia.org/wiki/Clef
*/
class Clef
{
public:
	Clef( const std::string& name, int indexInOctave );		// The index is just another way of naming the key. It doesn't carry any meaningful information
	
	const std::string&	getName() const				{ return mName; }
	const int			getIndexInOctave() const	{ return mIndexInOctave; };

	static const Clef GClef;
	static const Clef FClef;
	static const Clef CClef;

private:
	std::string mName;
	int			mIndexInOctave;
};

/*
	StaffClef

	Represents a clef in the context of a staff. 
	The clef symbol can be placed at different positions (i.e lines)
	on the staff.
	
	Here again there are well defined clefs in musical notation,
	each with a specific name and each accomodating a particular 
	tessitura.

	See:
	http://en.wikipedia.org/wiki/Clef
	http://en.wikipedia.org/wiki/Tessitura
*/
class StaffClef
{
public:
	StaffClef( const std::string& name, const Clef& clef, int clefNoteNumber, int staffYPosition );

	const std::string&	getName() const				{ return mName; }
	const Clef&			getClef() const				{ return mClef; }
	int					getClefNoteNumber() const	{ return mClefNoteNumber; }
	int					getStaffYPosition() const	{ return mStaffYPosition; }

	static const StaffClef TrebbleClef;
	static const StaffClef BassClef;
	static const StaffClef MezzoSopranoClef;
	static const StaffClef SopranoClef;

private:
	std::string			mName;
	Clef				mClef;
	int					mClefNoteNumber;
	int					mStaffYPosition;
};


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

private:
	static int		mIndexInOctaveToSopranoClefYPos_SharpMode[Note::mNumNoteNames];		
	static int		mIndexInOctaveToSopranoClefYPos_FlatMode[Note::mNumNoteNames];

	StaffClef		mStaffClef;
	Note			mNote;
};