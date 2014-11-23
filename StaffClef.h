#pragma once

#include "Clef.h"

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

	bool operator==( const StaffClef& other ) const;
	bool operator!=( const StaffClef& other ) const;

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