#include "StaffPresenter.h"

//#include <QGraphicsLineItem>
#include <QImage>
#include <QGraphicsPixmapItem>

const float StaffPresenter::mStaffLineSpacing = 40;
const float StaffPresenter::mStaffWidth = 400;

StaffPresenter::StaffPresenter( Staff* staff, QGraphicsScene* graphicsScene )
	: mStaff(staff),
	  mGraphicsScene(graphicsScene)
{
	init();
	update();
}

void StaffPresenter::init()
{
	for ( int i=0; i<5; ++i )
	{
		qreal y = static_cast<qreal>(i) * mStaffLineSpacing;
		mGraphicsScene->addLine( 0, y, mStaffWidth, y );
	}

	{
		QImage image( "GClef.png" );
		int imageWidth = image.width();
		int imageHeight = image.height();
		qreal desiredHeight = 200.0;
		qreal scaleFactor =  desiredHeight / static_cast<qreal>(imageHeight);
		QPixmap pixmap = QPixmap::fromImage(image);
		QGraphicsPixmapItem* pixmapItem = mGraphicsScene->addPixmap( pixmap );
		pixmapItem->setScale( scaleFactor );
		pixmapItem->setPos( 0, (-desiredHeight/2) + mStaffLineSpacing * 3 );
	}
	
	{
		QImage image( "Note.png" );
		int imageWidth = image.width();
		int imageHeight = image.height();
		qreal desiredHeight = 40.0;
		qreal scaleFactor =  desiredHeight / static_cast<qreal>(imageHeight);
		QPixmap pixmap = QPixmap::fromImage(image);
		mNoteItem = mGraphicsScene->addPixmap( pixmap );
		mNoteItem->setScale( scaleFactor );
		mNoteItem->setVisible(false);
	}
}

void StaffPresenter::update()
{
	int solNoteKey = mStaff->getSolKeyNote();

	if ( solNoteKey!=999 )
	{
		mNoteItem->setVisible(true);
		mNoteItem->setPos( 200, (( -mNoteItem->pixmap().height() *mNoteItem->scale()) /2) + mStaffLineSpacing * 3 );
	}
	else
	{
		mNoteItem->setVisible(false);
	}
}
