#pragma once

#include <string>
#include <deque>
#include <Note.h>
#include "BasicNoteGenerator.h"
/*
	Generator of note for our exercices.
	The generation is based on spaced repetition and Leithner Sytem.
	The idea is memorise errors and present them more often
	More info here: http://en.wikipedia.org/wiki/Leitner_system
*/
class LeitnerNoteGenerator : public BasicNoteGenerator
{
public:
	LeitnerNoteGenerator();

	Note		DrawNewtNote();
	bool		EvalAnswer(Note answer, int timeInMs, std::string& evalMessage);

private:
	void		GenerateBucket();
	void		PrintBucketState();

	int			mSessionSize;
	int			mSessionCurrentNumber;

	int			mSuccesSpeed;

	std::deque<Note> mWorkingBucket;
	std::deque<Note> mSuccessBucket;
};