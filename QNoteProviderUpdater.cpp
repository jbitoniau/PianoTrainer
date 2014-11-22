#include "QNoteProviderUpdater.h"

#include <assert.h>
#include "NoteProvider.h"

QNoteProviderUpdater::QNoteProviderUpdater( NoteProvider* noteProvider, int intervalInMs, QObject* parent )
	:	QObject(parent),
		mNoteProvider(noteProvider),
		mTimer(NULL)
{
	mTimer = new QTimer(this);
	mTimer->setInterval( intervalInMs );	
	bool ret = connect( mTimer, SIGNAL(timeout()), this, SLOT(timerTimeout()) );
	assert( ret );
	start();
}

void QNoteProviderUpdater::start()
{
	mTimer->start();
}

void QNoteProviderUpdater::stop()
{
	mTimer->stop();
}

void QNoteProviderUpdater::timerTimeout()
{
	mNoteProvider->update();
}

