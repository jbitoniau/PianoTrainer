#include "QExercise.h"

#include <assert.h>
#include <cstdlib>
#include <time.h>
#include <QDateTime>

QExercise::QExercise( StaffPresenter* presenter, NoteProvider* noteProvider, QObject* parent )
	:	QObject(parent),
		mPresenter(presenter),
		mNoteProvider(noteProvider),
		mTimer(NULL),
		mTime(),
		mState(Stopped),
		mCounter(0),
		mNoteCount(0),
		mNoteToFind(),
		mNoteAnswered(),
		mAnswerTimeInMs(0),
		mIgnoreOctaveNumberInAnswer(true),
		mChooseOnlyPlainNotes(true)
{
	mNoteProvider->addListener(this);

	mTimer = new QTimer(this);
	mTimer->setInterval( 200 );	
	bool ret = connect( mTimer, SIGNAL(timeout()), this, SLOT(timerTimeout()) );
	assert( ret );
}

void QExercise::start()
{
	if ( mState!=Stopped )
		return;

	mNoteCount = 0;
	mLog.open ("Results.csv", std::fstream::in | std::fstream::out | std::fstream::app);
	assert( mLog.is_open() );
	mLog << "#DateTime;Count;NoteToFindNum;NoteToFindName;AnsweredNoteNum;AnsweredNoteName;AnswerTimeInMs;OK" << std::endl;

	nextState();
}

void QExercise::stop()
{
	if ( mState==Stopped )
		return;
	
	mLog.close();
	mNoteCount = 0;

	// Clear text and stuff
	mPresenter->setText("...");
	mPresenter->getStaff()->setNote( Note() );	
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
	mCounter = 0;
	mTimer->start();
}

void QExercise::updateCountDown()
{
	mCounter++;
	if ( mCounter<=3 )
	{	
	//	QString text = QString("%1").arg( mCounter );
	//	mPresenter->setText( text );
	}
	else
	{
		mPresenter->setText("GO!");
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

	mPresenter->setNoteNameVisible(false);

	int minNoteNumber = 60;
	int maxNoteNumber = 60;	
	if ( mPresenter->getStaff()->getStaffClef()==StaffClef::TrebbleClef )
	{
		minNoteNumber = 60;
		maxNoteNumber = 79;
	}
	else if ( mPresenter->getStaff()->getStaffClef()==StaffClef::BassClef )
	{
		minNoteNumber = 41;
		maxNoteNumber = 60;
	}
	int noteNumber = -1;
	int range = maxNoteNumber - minNoteNumber + 1;		// +1 to include max note number
	srand(time(NULL));
	while ( noteNumber==-1 )
	{
		noteNumber = (rand() % range) + minNoteNumber;
		if ( mChooseOnlyPlainNotes )
			if ( Note::isSharpOrFlat(noteNumber) )
				noteNumber=-1;
	}
	mNoteToFind = Note( noteNumber );
	mPresenter->getStaff()->setNote( mNoteToFind );
	mTime.start();
}

void QExercise::startCheckAnswer()
{
	mState = CheckAnswer;
	
	mAnswerTimeInMs = mTime.elapsed();

	mPresenter->setNoteNameVisible(true);

	bool success = false;
	if ( mIgnoreOctaveNumberInAnswer )
	{
		if ( mNoteToFind.getIndexInOctave()==mNoteAnswered.getIndexInOctave() )
			success=true;
	}
	else
	{
		if ( mNoteAnswered==mNoteToFind )
			success = true;
	}

	if ( success )
		mPresenter->setText("OK!");
	else
		mPresenter->setText("WRONG!");

	mNoteCount++;

	//mPresenter->getStaff()->setNote( Note() );
	QString dateTime = QDateTime::currentDateTime().toString();
	QByteArray dateTimeData = dateTime.toUtf8();
	mLog << dateTimeData.constData() << ";";
	mLog << mNoteCount << ";";
	mLog << mNoteToFind.getNumber() << ";";
	mLog << mNoteToFind.getName(true) << ";";
	mLog << mNoteAnswered.getNumber() << ";";
	mLog << mNoteAnswered.getName(true) << ";";
	mLog << mAnswerTimeInMs << ";";
	mLog << success << ";";
	mLog << std::endl;

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
	