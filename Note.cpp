#include "Note.h"

#include <sstream>
#include <cmath>
//#include <exception>

const Note&	Note::EmptyNote(-1);


const char* Note::mNoteNames_SharpMode[mNumSemitones] = 
//	 { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" };
	 { "Do", "Do#", "Re", "Re#", "Mi", "Fa", "Fa#", "Sol", "Sol#", "La", "La#", "Si" };	
	//  0     1      2      3     4      5     6      7      8       9      10    11
const char* Note::mNoteNames_FlatMode[mNumSemitones] = 
     { "Do", "Re-b", "Re", "Mi-b", "Mi", "Fa", "Sol-b", "Sol", "La-b", "La", "Si-b", "Si" };		// Flat character should be \u266D

bool  Note::mIsSharpOrFlatNote[mNumSemitones] = 
	{ false, true, false, true, false, false, true, false, true, false, true, false };


Note::Note() 
	: mNumber( EmptyNote.getNumber() )
{
}

Note::Note( int number ) 
	: mNumber(number)
{
}

Note::Note(int octave, int getIndexInOctave)
{
	mNumber = (octave + 1)* mNumSemitones + getIndexInOctave;
}


bool Note::operator==( const Note& other ) const
{
	return mNumber==other.mNumber;
}

bool Note::operator!=( const Note& other ) const
{
	return !operator==(other);
}
	
int	Note::getOctaveNumber( int noteNumber )
{
	if ( noteNumber<0 )
		return -1;
		//throw new std::exception( std::string("Can't get octave from Empty Note") );
	int octaveNumber = (noteNumber / mNumSemitones) - 1;
	return octaveNumber;
}

int Note::getIndexInOctave( int noteNumber )
{
	if ( noteNumber<0 )
		//throw new std::exception( std::string("Empty Note has no index in octave") );
		return -1;
	int indexInOctave = noteNumber % mNumSemitones;
	return indexInOctave;
}

std::string	Note::getName( int noteNumber, bool sharpMode )
{
	if ( noteNumber<0 )
		return "";

	int octaveNumber = getOctaveNumber(noteNumber);
	int indexInOctave = getIndexInOctave(noteNumber);
	
	std::string noteName;
	if ( sharpMode )
		noteName = mNoteNames_SharpMode[indexInOctave];
	else
		noteName = mNoteNames_FlatMode[indexInOctave];

	std::stringstream stream;
	stream << noteName << " " << octaveNumber;
	return stream.str();
}

bool Note::isSharpOrFlat( int noteNumber )
{
	int indexInOctave = getIndexInOctave(noteNumber);
	return mIsSharpOrFlatNote[indexInOctave];
}


// See http://en.wikipedia.org/wiki/MIDI_Tuning_Standard
double Note::getFrequency( int noteNumber )
{
	if ( noteNumber<0 )
		return 0.0;
	double frequency = pow( 2.0, (static_cast<double>(noteNumber)-69.0)/12.0 ) * 440.0;
	return frequency;
}

std::string Note::toString() const
{
	std::stringstream stream;
	stream << "Note number: " << getNumber() << " ";
	stream << "name: " << getName(true) << " ";
	if ( getName(true)!=getName(false) )
		stream << "(or " << getName(false) << ") ";
	stream << "frequency: " << getFrequency() << " ";
	stream << std::endl;
	return stream.str();
}
