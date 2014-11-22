#pragma once

#include <QTimer>

class NoteProvider;

class QNoteProviderUpdater : public QObject
{
	Q_OBJECT

public:
	QNoteProviderUpdater( NoteProvider* noteProvider, int intervalInMs, QObject* parent );
	void			start();
	void			stop();

protected slots:
	void			timerTimeout();

private:
	NoteProvider*	mNoteProvider;
	QTimer*			mTimer;
};

