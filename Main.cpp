#include <iostream>
#include <assert.h>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QBoxLayout>
#include <QPushButton>

#include "Note.h"
#include "StaffPresenter.h"
#include "NoteProviderKeyboard.h"
#include "NoteProviderMidi.h"
#include "QNoteProviderUpdater.h"
#include "QExercise.h"

void testNotes();

int main( int argc, char** argv )
{
	testNotes();

	QApplication app(argc, argv);
	
	// Create the model
	//Staff staff( StaffClef::TrebbleClef );
	Staff staff( StaffClef::BassClef );
	
	// Create the user interface
	NoteProviderKeyboard* mainWidget = new NoteProviderKeyboard();		
	QVBoxLayout* mainLayout = new QVBoxLayout( mainWidget );
	QGraphicsScene*	scene = new QGraphicsScene();
	QGraphicsView* view = new QGraphicsView( scene, mainWidget );
	mainLayout->addWidget( view );
	QPushButton* startButton = new QPushButton( "Start", mainWidget );
	mainLayout->addWidget( startButton );
	QPushButton* stopButton = new QPushButton( "Stop", mainWidget );
	mainLayout->addWidget( stopButton );

	// Create the model presenter	
	StaffPresenter staffPresenter( &staff, scene );

	// Create the note providers and its updater
	NoteProvider* noteProviderKeyboard = mainWidget;
	NoteProviderMidi* noteProviderMidi = new NoteProviderMidi();
	QNoteProviderUpdater* providerUpdaterKeyboard = new QNoteProviderUpdater(noteProviderKeyboard, 10, mainWidget);
	QNoteProviderUpdater* providerUpdaterMIDI = new QNoteProviderUpdater(noteProviderMidi, 5, mainWidget);
	NoteProvider* noteProvider = NULL;

	if (noteProviderMidi->IsAvailable())
		noteProvider = noteProviderMidi;
	else
		noteProvider = noteProviderKeyboard;

	// Create the exercise
	QExercise* exercise = new QExercise(&staffPresenter, noteProvider, mainWidget);

	bool r = startButton->connect( startButton, SIGNAL( pressed() ), exercise, SLOT( start() ) );
	assert(r);
	r = stopButton->connect( stopButton, SIGNAL( pressed() ), exercise, SLOT( stop() ) );
	assert(r);

	// Start the app
	mainWidget->show();
	mainWidget->resize( 800, 600 );
	int ret = app.exec();
	
	return ret ;
}


void testNotes()
{
	Note middleC(60);
	std::cout << middleC.toString();
	
	Note la440(69);
	std::cout << la440.toString();
	
	Note c0(12);
	std::cout << c0.toString();
	
	Note dsharp4(63);
	std::cout << dsharp4.toString();

	Note a0(21);
	std::cout << a0.toString();
	
	Note e3(52);
	std::cout << e3.toString();
	
	Note c8(108);
	std::cout << c8.toString();
}
