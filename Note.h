#pragma once

#include <string>


// http://www.sengpielaudio.com/calculator-notenames.htm
class Note
{
public:
	Note( int number );

	// Return the MIDI number of the note. In this numbering scheme,
	// Middle C is defined as number 60. This means that on a regular 
	// piano the lowest possible note, A0, is number 21 and the 
	// highest, C8 is 108.
	int					getNumber() const	{ return mNumber; }

	std::string			getName() const		{ return getName(*this); }
	static std::string	getName( const Note& note );

	double				getFrequency() const		 { return getFrequency(*this); }
	static double		getFrequency( const Note& note );

	std::string			toString() const;

private:
	int					mNumber;
	static const int	mNumNoteNames = 12;
	static char*		mNoteNames[mNumNoteNames];
};