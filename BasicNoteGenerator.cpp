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
	SetRange(minNote, maxNote);
}

void BasicNoteGenerator::SetRange(Note minNote, Note maxNote)
{
	mMinNote = minNote;
	mMaxNote = maxNote;
}

Note BasicNoteGenerator::DrawNewtNote()
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
	return Note(resultNoteNumber);
}


bool BasicNoteGenerator::EvalAnswer(Note noteAnswered, int timeInMs, std::string& evalMessage)
{
	mNoteHasBeenAnswered = true;

	if (mNoteToFind == noteAnswered)
	{
		evalMessage = "TRUE !!";
		return false;
	}
	else
	{
		evalMessage = "WRONG !!";
		return false;
	}
}
