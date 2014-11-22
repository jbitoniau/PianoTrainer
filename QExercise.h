#pragma once

#include <fstream>
#include <QTime>
#include <QTimer>
#include "StaffPresenter.h"
#include "NoteProvider.h"

class QExercise :	public QObject,
					public NoteProvider::Listener
{
	Q_OBJECT

public:
	QExercise( StaffPresenter* presenter, NoteProvider* noteProvider, QObject* parent );

public slots:
	void			start();
	void			stop();

private slots:
	void			timerTimeout();

private:
	virtual void	onNoteReceived( NoteProvider* noteProvider, const Note& note );
	
	enum State
	{
		Stopped,
		CountDown,
		WaitForAnswer,
		CheckAnswer
	};

	void			nextState();
	void			startCountDown();
	void			updateCountDown();
	void			startWaitForAnswer();
	void			startCheckAnswer();

	StaffPresenter*	mPresenter;
	NoteProvider*   mNoteProvider;
	QTimer*			mTimer;
	QTime			mTime;

	State			mState;
	int				mCounter;

	Note			mNoteToFind;
	Note			mNoteAnswered;
	int				mAnswerTimeInMs;		

	bool			mIgnoreOctaveNumberInAnswer;
	bool			mChooseOnlyPlainNotes;
	std::fstream 	mLog;
};

