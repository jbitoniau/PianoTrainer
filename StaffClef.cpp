#include "StaffClef.h"

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
