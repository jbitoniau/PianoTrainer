#pragma once

#include <INoteGenerator.h>

/*
	Basic generator of notes for our exercices.
	Purely random
*/

class BasicNoteGenerator : public INoteGenerator
{
public:
	BasicNoteGenerator();
	BasicNoteGenerator(int minNote, int maxNote);

	virtual void	setRange(Note minNote, Note maxNote);
	virtual Note	drawNewNote();
	virtual bool	evaluateAnswer(Note answer, int timeInMs, std::string& evalMessage);

protected:
	Note			mMinNote;
	Note			mMaxNote;

	Note			mNoteToFind;
	bool			mNoteHasBeenAnswered;

	bool			mChooseOnlyPlainNotes;
};