#pragma once

#include <Note.h>


/*
	INoteGenerator

	Interface for generating Notes. THere are three methods  to implement:
	SetRange: where you can specify the range of note you would like to study
	DrawNewtNote: where you generator decide which Note to 
	EvalAnswer, which evalutes your answer so it could influence or not the next draw.
*/
class INoteGenerator
{
public:
	virtual ~INoteGenerator() {}

	virtual void SetRange(Note minNote, Note maxNote) = 0;
	virtual Note DrawNewtNote() = 0;
	virtual bool EvalAnswer(Note answer, int timeInMs, std::string& evalMessage) = 0;
};