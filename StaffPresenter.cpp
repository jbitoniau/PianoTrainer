#include "StaffPresenter.h"

//#include <QGraphicsLineItem>
#include <QImage>
#include <QGraphicsPixmapItem>

StaffPresenter::StaffPresenter( Staff* staff, QGraphicsScene* graphicsScene )
	: mStaff(staff),
	  mGraphicsScene(graphicsScene)
{
	init();
}

void StaffPresenter::init()
{
	qreal verticalSpacing = 40;
	qreal width = 400;
	for ( int i=0; i<5; ++i )
	{
		qreal y = static_cast<qreal>(i) * verticalSpacing;
		mGraphicsScene->addLine( 0, y, width, y );
	}

	QImage image( "GClef.png" );
	int imageWidth = image.width();
	int imageHeight = image.height();

	qreal desiredHeight = 200.0;
	qreal scaleFactor =  desiredHeight / static_cast<qreal>(imageHeight);
	QPixmap pixmap = QPixmap::fromImage(image);
	QGraphicsPixmapItem* pixmapItem = mGraphicsScene->addPixmap( pixmap );
	pixmapItem->setScale( scaleFactor );

	pixmapItem->setPos( 0, (-desiredHeight/2) + verticalSpacing * 3 );
}

void StaffPresenter::update()
{

}
