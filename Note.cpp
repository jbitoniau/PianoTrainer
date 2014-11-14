#include "Note.h"

#include <sstream>
#include <cmath>

char* Note::mNoteNames[mNumNoteNames] = 
//	 { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" };
	 { "Do", "Do#", "Ré", "Ré#", "Mi", "Fa", "Fa#", "Sol", "Sol#", "La", "La#", "Si" };


Note::Note( int number ) 
	: mNumber(number)
{
}

std::string	Note::getName( const Note& note )
{
	int noteNumber = note.getNumber();
	if ( noteNumber<0 )
		return "invalid";

	int octaveNumber = (noteNumber / mNumNoteNames) - 1;
	int noteNumberInOctave = noteNumber % mNumNoteNames;
	
	std::stringstream stream;
	stream << mNoteNames[noteNumberInOctave] << " " << octaveNumber;
	return stream.str();
}

// See http://en.wikipedia.org/wiki/MIDI_Tuning_Standard
double Note::getFrequency( const Note& note )
{
	double noteNumber = static_cast<double>(note.getNumber());
	if ( noteNumber<0.0 )
		return 0.0;
	
	double frequency = pow( 2.0, (noteNumber-69.0)/12.0 ) * 440.0;
	return frequency;
}

std::string Note::toString() const
{
	std::stringstream stream;
	stream << "Note number: " << getNumber() << " ";
	stream << "name: " << getName() << " ";
	stream << "frequency: " << getFrequency() << " ";
	stream << std::endl;
	return stream.str();
}