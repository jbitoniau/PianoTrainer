#pragma once

#include <string>

/*
	Note

	Represents note in musical notation
	Only support its pitch for now ( http://en.wikipedia.org/wiki/Pitch_(music) )
	Value could be added later (http://en.wikipedia.org/wiki/Note_value)
	http://www.sengpielaudio.com/calculator-notenames.htm
*/
class Note
{
public:
	static const Note&	EmptyNote;

	Note();
	Note( int number );

	bool operator==( const Note& otherNote ) const;
	bool operator!=( const Note& otherNote ) const;

	// Return the MIDI number of the note. In this numbering scheme,
	// Middle C is defined as number 60. This means that on a regular 
	// piano the lowest possible note, A0, is number 21 and the 
	// highest, C8 is 108.
	int					getNumber() const			{ return mNumber; }

	// Return the octave number. The numbering considers Middle-C is at 4th octave
	// The method will therefore return 4 for note number 60.
	int					getOctaveNumber() const		{ return getOctaveNumber( getNumber() ); }
	static int			getOctaveNumber( int noteNumber );

	// Return the 0-based index of the note in its octave.
	// For example: it will return 0 for Middle-C/60, 6 for F# and 11 for B
	int					getIndexInOctave() const	{ return getIndexInOctave( getNumber() ); }
	static int			getIndexInOctave( int noteNumber );

	std::string			getName( bool sharpMode ) const	 { return getName( getNumber(), sharpMode ); }
	static std::string	getName( int noteNumber, bool sharpMode );

	bool				isSharpOrFlat() const		{ return isSharpOrFlat(getNumber()); }
	static bool			isSharpOrFlat( int noteNumber );
	
	double				getFrequency() const		{ return getFrequency( getNumber() ); }
	static double		getFrequency( int noteNumber );

	std::string			toString() const;
	
	static const int	mNumNoteNames = 12;
	
private:
	int					mNumber;
	static char*		mNoteNames_SharpMode[mNumNoteNames];		
	static char*		mNoteNames_FlatMode[mNumNoteNames];	
	static bool			mIsSharpOrFlatNote[mNumNoteNames];
};