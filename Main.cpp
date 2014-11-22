#include <iostream>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QBoxLayout>
#include <QPushButton>

#include "Note.h"
#include "StaffPresenter.h"
#include "NoteProviderKeyboard.h"

int main( int argc, char** argv )
{
	QApplication app(argc, argv);

	
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
	
	NoteProviderKeyboard* mainWidget = new NoteProviderKeyboard();		
	QVBoxLayout* mainLayout = new QVBoxLayout( mainWidget );

	QGraphicsScene*	scene = new QGraphicsScene();
	QGraphicsView* view = new QGraphicsView( scene, mainWidget );
	mainLayout->addWidget( view );

	QPushButton* button = new QPushButton( "Start", mainWidget );
	mainLayout->addWidget( button );

	//Staff staff( StaffClef::SopranoClef );
	Staff staff( StaffClef::TrebbleClef );
	//Staff staff( StaffClef::BassClef );
	//staff.setNote( middleC );
	//staff.setNote( Note(48) );
	
	StaffPresenter presenter( &staff, scene );

	mainWidget->show();
	mainWidget->resize( 800, 600 );

	mainWidget->setStuff( &presenter );
		
	int ret = app.exec();
	
	return ret ;
}