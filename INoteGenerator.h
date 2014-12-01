#pragma once

#include <Note.h>


/*
	INoteGenerator

	Interface for generating Notes. There are three methods to implement:
	setRange: where you can specify the range of the notes you would like to study
	drawNewNote: where your generator returns a note 
	evalAnswer: this makes your generator aware the user's answer so you can take it
	into account for the next notes to draw.
*/
class INoteGenerator
{
public:
	virtual ~INoteGenerator() {}

	virtual void setRange(Note minNote, Note maxNote) = 0;
	virtual Note drawNewNote() = 0;
	virtual bool evaluateAnswer(Note answer, int timeInMs, std::string& evalMessage) = 0;
};