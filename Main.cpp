//#include 
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QBoxLayout>
#include <QPushButton>

#include <StaffPresenter.h>

int main( int argc, char** argv )
{
	QApplication app(argc, argv);

	
	QWidget* mainWidget = new QWidget();
	QVBoxLayout* mainLayout = new QVBoxLayout( mainWidget );

	QGraphicsScene*	scene = new QGraphicsScene();
	QGraphicsView* view = new QGraphicsView( scene, mainWidget );
	mainLayout->addWidget( view );

	QPushButton* button = new QPushButton( "Start", mainWidget );
	mainLayout->addWidget( button );

	Staff staff;
	staff.setSolKeyNote( 12 );
	StaffPresenter presenter( &staff, scene );

	mainWidget->show();
	mainWidget->resize( 800, 600 );
		
	int ret = app.exec();
	
	return ret ;
}