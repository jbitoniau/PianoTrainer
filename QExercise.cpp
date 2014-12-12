#include "QExercise.h"
#include "LeitnerNoteGenerator.h"

#include <assert.h>
#include <cstdlib>
#include <time.h>
#include <QDateTime>

QExercise::QExercise( GrandStaffPresenter* presenter, NoteProvider* noteProvider, QObject* parent )
	:	QObject(parent),
		NoteProvider::Listener(),
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
		mIgnoreOctaveNumberInAnswer(true)
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

	//mNoteGenerator.reset( new LeitnerNoteGenerator() );
	mNoteGenerator.reset( new BasicNoteGenerator() );
	mNoteGenerator->setRange(60, 70);	// 41,??						// !!!!!!!!!!!!!!!!!

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
	mPresenter->getTrebleStaffPresenter()->setText("...");
	mPresenter->getTrebleStaffPresenter()->getStaff()->setNote( Note() );	
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
		mPresenter->getTrebleStaffPresenter()->setText("GO!");
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

	mPresenter->getTrebleStaffPresenter()->setNoteNameVisible(false);

	

	mNoteToFind = mNoteGenerator->drawNewNote();
	mPresenter->getTrebleStaffPresenter()->getStaff()->setNote( mNoteToFind );
	mTime.start();
}

void QExercise::startCheckAnswer()
{
	mState = CheckAnswer;
	
	mAnswerTimeInMs = mTime.elapsed();

	mPresenter->getTrebleStaffPresenter()->setNoteNameVisible(true);

	std::string evalMessage = "";

	if ( mIgnoreOctaveNumberInAnswer )
	{
		mNoteAnswered = Note(mNoteToFind.getOctaveNumber(), mNoteAnswered.getIndexInOctave() );
	}

	bool success = mNoteGenerator->evaluateAnswer(mNoteAnswered, mAnswerTimeInMs, evalMessage);
	mPresenter->getTrebleStaffPresenter()->setText( evalMessage.c_str() );

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
	