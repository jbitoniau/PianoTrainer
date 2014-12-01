#include "LeitnerNoteGenerator.h"

#include <assert.h>
#include <time.h>
#include <Note.h>
#include <iostream>
#include <algorithm>

LeitnerNoteGenerator::LeitnerNoteGenerator() 
	: BasicNoteGenerator()
{

	mSessionSize = 7;
	mSessionCurrentNumber = 0;
	mSuccesSpeed = 1500;
}


void LeitnerNoteGenerator::generateBucket()
{
	if (mSessionCurrentNumber != 0 && mSessionCurrentNumber % 2 == 0)
	{
		mWorkingBucket.clear();
		mSuccessBucket.clear();
		mSuccesSpeed -= 100;
		std::cout << "New Speed:" << mSuccesSpeed << "\n";
	}


	for (int i = 0; i < mSessionSize; ++i)
	{
		int proposedNoteNumber = -1;
		while (proposedNoteNumber == -1)
		{
			proposedNoteNumber = (rand() % 12) + mMinNote.getNumber() + 12*(mSessionCurrentNumber%2);

			if (mChooseOnlyPlainNotes)
				if (Note::isSharpOrFlat(proposedNoteNumber))
					proposedNoteNumber = -1;

			if (std::find(mWorkingBucket.begin(), mWorkingBucket.end(), Note(proposedNoteNumber)) != mWorkingBucket.end())
			{
				proposedNoteNumber = -1;
			}
		}
		mWorkingBucket.push_back(Note(proposedNoteNumber));
	}

	mSessionCurrentNumber += 1;
	mNoteHasBeenAnswered = true;
	printBucketState();
}

Note LeitnerNoteGenerator::drawNewNote()
{
	assert(mNoteHasBeenAnswered);
	mNoteHasBeenAnswered = false;

	if (!mSuccessBucket.empty() && (rand() % 4 == 0))
	{
		std::cout << "From Success List\n";

		// Taking randomly in the first half
		int successPos = (rand() % ( std::max(1, (int)mSuccessBucket.size() / 2) ));
		mNoteToFind = mSuccessBucket.at(successPos);
		mSuccessBucket.erase(mSuccessBucket.begin() + successPos);
		return mNoteToFind;
	}

	if (!mWorkingBucket.empty())
	{
		mNoteToFind =  mWorkingBucket.front();
		mWorkingBucket.pop_front();

		return mNoteToFind;
	}
	else
	{
		generateBucket();
		return drawNewNote();
	}
}


bool LeitnerNoteGenerator::evaluateAnswer(Note noteAnswered, int timeInMs, std::string& evaltMessage)
{
	mNoteHasBeenAnswered = true;

	bool bNoteCorrect = noteAnswered == mNoteToFind;

	if (bNoteCorrect && timeInMs < mSuccesSpeed)
	{
		mSuccessBucket.push_back(mNoteToFind);
		evaltMessage = "OK";
	}
	else
	{
		evaltMessage = bNoteCorrect ? "FASTER!!" : "WRONG!!!";

		std::deque<Note>::iterator  answerInSuccess = std::find(mSuccessBucket.begin(), mSuccessBucket.end(), noteAnswered);
		if (mSuccessBucket.end() != answerInSuccess)
		{

			mWorkingBucket.push_back(noteAnswered);
			mSuccessBucket.erase(answerInSuccess);
		}

		mWorkingBucket.push_back(mNoteToFind);
	}
	printBucketState();


	return bNoteCorrect;
}

void LeitnerNoteGenerator::printBucketState()
{
	std::cout << "Working: ";
	for (std::deque<Note>::iterator itr = mWorkingBucket.begin(); itr != mWorkingBucket.end(); itr++)
		std::cout << itr->getName(true) + " ";
	std::cout << "\n";

	std::cout << "Success: ";
	for (std::deque<Note>::iterator itr = mSuccessBucket.begin(); itr != mSuccessBucket.end(); itr++)
		std::cout << itr->getName(true) + " ";
	std::cout << "\n";
}
