#pragma once

#include <string>

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

	static const Clef	GClef;
	static const Clef	FClef;
	static const Clef	CClef;

private:
	std::string mName;
	int			mIndexInOctave;
};