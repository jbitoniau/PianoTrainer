//#include 
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>

#include <StaffPresenter.h>

int main( int argc, char** argv )
{
	QApplication app(argc, argv);

	QGraphicsScene*	scene = new QGraphicsScene();
	QGraphicsView* view = new QGraphicsView( scene, NULL );
	
	Staff staff;
	staff.setSolKeyNote( 12 );
	StaffPresenter presenter( &staff, scene );

	view->show();
	
	int ret = app.exec();
	
	return ret ;
}