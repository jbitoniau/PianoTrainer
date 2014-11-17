#include "StaffPresenter.h"

//#include <QGraphicsLineItem>
#include <QImage>
#include <QGraphicsPixmapItem>

const float StaffPresenter::mStaffLineSpacing = 40;
const float StaffPresenter::mStaffWidth = 400;
/*
int	 StaffPresenter::mIndexInOctaveToSopranoKeyYPos_SharpMode[12] =	{ 0, 0, 1, 1, 2, 3, 3, 4, 4, 5, 5, 6 }; 
int	 StaffPresenter::mIndexInOctaveToSopranoKeyYPos_FlatMode[12] =	{ 0, 1, 1, 2, 2, 3, 4, 4, 5, 5, 6, 6 };
*/
StaffPresenter::StaffPresenter( Staff* staff, QGraphicsScene* graphicsScene )
	: mStaff(staff),
	  mGraphicsScene(graphicsScene),
	  mNoteItem(NULL),
	  mNoteLedgerLineItem(NULL)
{
	init();
	update();
}

void StaffPresenter::createKeyItem()
{
	int clefIndexInOctave = mStaff->getStaffClef().getClef().getIndexInOctave();
	
	QString resourceName;
	switch ( clefIndexInOctave )
	{
		case 7 : resourceName="GClef.png";
			break;
		case 5 : resourceName="FClef.png";
			break;
		default:
			throw new std::exception("Unsupported staff key");
	}
	
	QImage image(resourceName);
	int imageWidth = image.width();
	int imageHeight = image.height();

	QPixmap pixmap = QPixmap::fromImage(image);
	QGraphicsPixmapItem* pixmapItem = mGraphicsScene->addPixmap( pixmap );
	
	qreal desiredHeight = 200.0;
	qreal scaleFactor =  desiredHeight / static_cast<qreal>(imageHeight);
	pixmapItem->setScale( scaleFactor );

	int staffY = mStaff->getStaffClef().getStaffYPosition();
	qreal y=getSceneYFromStaffY(staffY);
	pixmapItem->setPos( 0, (-desiredHeight/2) + y );
}


void StaffPresenter::init()
{
	// Create the staff lines
	for ( int i=0; i<5; ++i )
	{
		qreal y = getSceneYFromStaffY(i*2);
		if ( y==0 )
			mGraphicsScene->addLine( 0, y, mStaffWidth*2, y );
		else
			mGraphicsScene->addLine( 0, y, mStaffWidth, y );
	}

	createKeyItem();
	
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

		QPen pen( Qt::red,  4 );
		mNoteLedgerLineItem = mGraphicsScene->addLine( 0, 0, 10, 10, pen );
	}
}

void StaffPresenter::update()
{
	const Note& note = mStaff->getNote();
	if ( note==Note::EmptyNote )
	{
		mNoteItem->setVisible(false);
		return;
	}
	mNoteItem->setVisible(true);

	int staffY = mStaff->getStaffYPositionFromNote( note.getNumber(), true );
	
	int y0 = (-mNoteItem->pixmap().height() * mNoteItem->scale()) / 2;
	int yOffset = staffY * (mStaffLineSpacing/2);
	int y = y0 - yOffset;
	mNoteItem->setVisible(true);
	mNoteItem->setPos( 200,  y );

	mNoteLedgerLineItem->setLine( 0, -yOffset, 100, -yOffset );
}

qreal StaffPresenter::getSceneYFromStaffY( int staffY ) const
{
	qreal y = -1 * static_cast<qreal>(staffY) * (mStaffLineSpacing/2);
	return y;
}
/*
//int	getStaffYCoordinate( const Note& note ) const
int	StaffPresenter::getStaffYCoordinate( const Note& note, bool useSharpPosition ) const		
{
	if ( note==Note::EmptyNote )
		throw new std::exception("Invalid parameter");

	int noteNumber = note.getNumber();
	int staffY0NoteNumber = getStaffY0NoteNumber();
	int y = noteNumber - staffY0NoteNumber;
	return y;
}

int	StaffPresenter::getStaffYCoordinate( const Note& note, const Note& staffKeyNote, bool useSharpPosition )	
{
	if ( note==Note::EmptyNote )
		throw new std::exception("Invalid parameter");
	
	int indexInOctave = note.getIndexInOctave();
	int octaveNumber = note.getOctaveNumber();

	int sopranoStaffYPos = 0;
	if ( useSharpPosition )
		sopranoStaffYPos = mIndexInOctaveToSopranoKeyYPos_SharpMode[indexInOctave];
	else
		sopranoStaffYPos = mIndexInOctaveToSopranoKeyYPos_FlatMode[indexInOctave];
}*/


// http://en.wikipedia.org/wiki/Clef#Individual_clefs
/*
int StaffPresenter::getStaffY0NoteNumber() const
{
	switch( mStaff->getKey() )
	{
		case Staff::Treble:	return 64;			// Mi4 E4
		case Staff::Bass:	return 43;			// Sol2 G2
	}
	throw new std::exception("Unsupported staff key");
}*/