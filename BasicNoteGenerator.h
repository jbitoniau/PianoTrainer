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

	virtual void	SetRange(Note minNote, Note maxNote);
	virtual Note	DrawNewtNote();
	virtual bool	EvalAnswer(Note answer, int timeInMs, std::string& evalMessage);

protected:
	Note			mMinNote;
	Note			mMaxNote;

	Note			mNoteToFind;
	bool			mNoteHasBeenAnswered;

	bool			mChooseOnlyPlainNotes;
};