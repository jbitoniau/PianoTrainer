#include <iostream>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QBoxLayout>
#include <QPushButton>

#include "Note.h"
#include "StaffPresenter.h"
#include "NoteProviderKeyboard.h"
#include "QNoteProviderUpdater.h"
#include "QExercise.h"

void testNotes();

int main( int argc, char** argv )
{
	testNotes();

	QApplication app(argc, argv);
	
	// Create the model
	Staff staff( StaffClef::TrebbleClef );
	
	// Create the user interface
	NoteProviderKeyboard* mainWidget = new NoteProviderKeyboard();		
	QVBoxLayout* mainLayout = new QVBoxLayout( mainWidget );
	QGraphicsScene*	scene = new QGraphicsScene();
	QGraphicsView* view = new QGraphicsView( scene, mainWidget );
	mainLayout->addWidget( view );
	QPushButton* button = new QPushButton( "Start", mainWidget );
	mainLayout->addWidget( button );

	// Create the model presenter	
	StaffPresenter staffPresenter( &staff, scene );

	// Create the note provider and its updater
	NoteProvider* noteProvider = mainWidget;
	QNoteProviderUpdater* providerUpdater = new QNoteProviderUpdater( noteProvider, 100, mainWidget );

	// Create the exercise
	QExercise* exercise = new QExercise( &staffPresenter, noteProvider, mainWidget );

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