#include "Clef.h"

Clef::Clef( const std::string& name, int indexInOctave )
	:	mName(name), 
		mIndexInOctave(indexInOctave)
{
}

bool Clef::operator==( const Clef& other ) const
{
	return	mIndexInOctave==other.mIndexInOctave;	// Equality operator doesn't care about the name given to the clef only its actual properties
}

bool Clef::operator!=( const Clef& other ) const
{
	return !operator==(other);
}

const Clef Clef::GClef( "Clef de Sol", 7 );		// G-Clef
const Clef Clef::FClef( "Clef de Fa", 5 );		// F-Clef
const Clef Clef::CClef( "Clef de Ut", 0 );		// C-Clef
