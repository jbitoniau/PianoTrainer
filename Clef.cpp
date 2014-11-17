#include "Clef.h"

Clef::Clef( const std::string& name, int indexInOctave )
	:	mName(name), 
		mIndexInOctave(indexInOctave)
{
}

const Clef Clef::GClef( "Clef de Sol", 7 );		// G-Clef
const Clef Clef::FClef( "Clef de Fa", 5 );		// F-Clef
const Clef Clef::CClef( "Clef de Ut", 0 );		// C-Clef
