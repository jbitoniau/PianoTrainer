#include "QExercise.h"

#include <assert.h>

QExercise::QExercise( StaffPresenter* presenter, NoteProvider* noteProvider, QObject* parent )
	:	QObject(parent),
		mPresenter(presenter),
		mNoteProvider(noteProvider),
		mTimer(NULL),
		mState(Stopped),
		mCounter(0),
		mNoteToFind(),
		mNoteAnswered()
{
	mNoteProvider->addListener(this);

	mTimer = new QTimer(this);
	mTimer->setInterval( 1000 );	
	bool ret = connect( mTimer, SIGNAL(timeout()), this, SLOT(timerTimeout()) );
	assert( ret );
}

void QExercise::start()
{
	if ( mState!=Stopped )
		return;
	nextState();
}

void QExercise::stop()
{
	if ( mState==Stopped )
		return;
	// Clear text and stuff
	mTimer->stop();
	mState = Stopped;
}

void QExercise::nextState()
{
	if ( mState==Stopped )
		startCountDown();
	else if ( mState==CountDown )
		startWaitForAnswer();
	else if ( mState==WaitForAnswer )
		startCheckAnswer();
	else if ( mState==CheckAnswer )
		startCountDown();
}

void QExercise::startCountDown()
{
	mState = CountDown;
	mTimer->start();
}

void QExercise::updateCountDown()
{
	mCounter++;
	if ( mCounter<=3 )
	{	
		// setText 3...2..1..
	}
	else
	{
		//setText("GO!");
		mTimer->stop();
		nextState();
	}
}

void QExercise::startWaitForAnswer()
{
	// If was there's been an aswer before
	// calculate answer time
	// store info with note and stuff
	mState = WaitForAnswer;
	mNoteToFind = Note( 60 );
	//mNoteDisplayedTime = currentTime;
}

void QExercise::startCheckAnswer()
{
	mState = WaitForAnswer;
	
	bool success = false;
	if ( mIgnoreOctaveNumberInAnswer )
	{
	}
	else
	{
		if ( mNoteAnswered==mNoteToFind )
			success = true;
	}

	if ( success )
	{
		// setText OK
	}
	else
	{
		// setText WRONG!
	}

	nextState();
}

void QExercise::timerTimeout()
{
	if ( mState!=CountDown )
		return;
	updateCountDown();	
}

void QExercise::onNoteReceived( NoteProvider* noteProvider, const Note& note )
{
	if ( mState!=WaitForAnswer )
		return;
	mNoteAnswered = note;
	nextState();
}
	