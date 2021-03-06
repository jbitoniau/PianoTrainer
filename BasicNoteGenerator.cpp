#include "BasicNoteGenerator.h"

#include <assert.h>
#include <time.h>
#include <Note.h>


BasicNoteGenerator::BasicNoteGenerator()
{
	mMinNote = 60;
	mMaxNote = 60;

	mNoteToFind = -1;
	mNoteHasBeenAnswered = true;
	mChooseOnlyPlainNotes = true;

	srand((unsigned int)time(NULL));
}

BasicNoteGenerator::BasicNoteGenerator(int minNote, int maxNote)
{
	setRange(minNote, maxNote);
}

void BasicNoteGenerator::setRange(Note minNote, Note maxNote)
{
	mMinNote = minNote;
	mMaxNote = maxNote;
}

Note BasicNoteGenerator::drawNewNote()
{
	assert( mNoteHasBeenAnswered );
	mNoteHasBeenAnswered = false;

	int range = mMaxNote.getNumber() - mMinNote.getNumber() + 1;		// +1 to include max note number
	int resultNoteNumber = -1;

	while (resultNoteNumber == -1)
	{
		resultNoteNumber = (rand() % range) + mMinNote.getNumber();
		if (mChooseOnlyPlainNotes)
			if (Note::isSharpOrFlat(resultNoteNumber))
				resultNoteNumber = -1;
	}
	mNoteToFind = Note(resultNoteNumber);
	return mNoteToFind;
}


bool BasicNoteGenerator::evaluateAnswer(Note noteAnswered, int timeInMs, std::string& evalMessage)
{
	mNoteHasBeenAnswered = true;

	if (mNoteToFind == noteAnswered)
	{
		evalMessage = "OK!";
		return false;
	}
	else
	{
		evalMessage = "WRONG!";
		return false;
	}
}
