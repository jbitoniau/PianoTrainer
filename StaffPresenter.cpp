#include "StaffPresenter.h"

#include <QImage>
#include <QGraphicsPixmapItem>
#include <cmath>

const float StaffPresenter::mStaffLineSpacing = 40;
const float StaffPresenter::mStaffWidth = 400;
const float StaffPresenter::mNoteXPos = 200;
const float StaffPresenter::mLedgerLineWidth = 70;	
const QPen StaffPresenter::mLinePen( Qt::black,  2 );

StaffPresenter::StaffPresenter( Staff* staff, QGraphicsScene* graphicsScene )
	: mStaff(staff),
	  mGraphicsScene(graphicsScene),
	  mNoteItem(NULL),
	  mLedgerLines(),
	  mNoteNameItem(NULL),
	  mTextItem(NULL),
	  mNotePixmap(),
	  mNoteSharpPixmap(),
	  mNoteFlatPixmap()	  
{
	init();
	update();

	staff->addListener(this);
}

void StaffPresenter::onNoteChanged( Staff* staff, const Note& note )
{
	update();
}

void StaffPresenter::createStaffLineItems()
{
	for ( int i=0; i<5; ++i )
	{
		qreal y = getSceneYFromStaffY(i*2);
		mGraphicsScene->addLine( 0, y, mStaffWidth, y, mLinePen );
	}
}

void StaffPresenter::createStaffKeyItem()
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
			return;		//throw new std::exception("Unsupported staff key");
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

void StaffPresenter::createNoteItem()
{
	int imageWidth = mNotePixmap.width();
	int imageHeight = mNotePixmap.height();
	qreal desiredHeight = 40.0;
	qreal scaleFactor =  desiredHeight / static_cast<qreal>(imageHeight);

	mNoteItem = mGraphicsScene->addPixmap( mNotePixmap );
	mNoteItem->setScale( scaleFactor );
	mNoteItem->setVisible(false);
}

void StaffPresenter::createNoteNameItem()
{
	mNoteNameItem = mGraphicsScene->addText( "..." );
	mNoteNameItem->setPos( mStaffWidth, -5 * mStaffLineSpacing / 2 );
	mNoteNameItem->setScale( 4 );
}

void StaffPresenter::init()
{
	mNotePixmap = QPixmap( "Note.png" );
	mNoteSharpPixmap = QPixmap( "NoteSharp.png" );
	mNoteFlatPixmap = QPixmap( "NoteFlat.png" );

	createStaffLineItems();
	createStaffKeyItem();
	createNoteItem();
	createNoteNameItem();

	mTextItem = mGraphicsScene->addText( "" );
	mTextItem->setPos( mStaffWidth, -8 * mStaffLineSpacing / 2 );
	mTextItem->setScale( 4 );
}

void StaffPresenter::update()
{
	const Note& note = mStaff->getNote();
	std::string noteName = note.getName(true);
	
	mNoteNameItem->setPlainText( noteName.c_str() );

	for ( size_t i=0; i<mLedgerLines.size(); ++i )
		mGraphicsScene->removeItem( mLedgerLines[i] );
	mLedgerLines.clear();

	if ( note==Note::EmptyNote )
	{
		mNoteItem->setVisible(false);
		return;
	}
	mNoteItem->setVisible(true);

	bool useSharpMode = false;		// This could be randomize

	int staffY = mStaff->getStaffYPositionFromNote( note.getNumber(), useSharpMode );
	bool isSharpOrFlat = Note::isSharpOrFlat( note.getNumber() );
	
	QPixmap pixmap = mNotePixmap;
	if ( isSharpOrFlat )
	{
		if ( useSharpMode )
			pixmap = mNoteSharpPixmap;
		else
			pixmap = mNoteFlatPixmap;
	}
	mNoteItem->setPixmap( pixmap );

	int x0 = (-mNoteItem->pixmap().width() * mNoteItem->scale()) / 2;
	int x = x0 + mNoteXPos;

	int y0 = (-mNoteItem->pixmap().height() * mNoteItem->scale()) / 2;
	int yOffset = staffY * (mStaffLineSpacing/2);
	int y = y0 - yOffset;
	mNoteItem->setVisible(true);
	mNoteItem->setPos( x,  y );

	const float mLedgerLineHalfWidth = mLedgerLineWidth / 2.f;
	if ( staffY<0 )
	{
		int numLedgerLinesBelow = static_cast<int>( fabs( static_cast<double>(staffY)/-2.0 ) ) ;
		for ( int i=0; i<numLedgerLinesBelow; ++i )
		{
			float y = ( static_cast<float>(i) + 1 ) * mStaffLineSpacing;
			QGraphicsLineItem* line = mGraphicsScene->addLine( mNoteXPos-mLedgerLineHalfWidth, y, mNoteXPos+mLedgerLineHalfWidth, y, mLinePen );
			mLedgerLines.push_back( line );
		}
	}
	else if ( staffY>8 )
	{
		int numLedgerLinesAbove = (staffY - 8) / 2;
		for ( int i=0; i<numLedgerLinesAbove; ++i )
		{
			float y = -1.0 * (5.f + static_cast<float>(i)) * mStaffLineSpacing;
			QGraphicsLineItem* line = mGraphicsScene->addLine( mNoteXPos-mLedgerLineHalfWidth, y, mNoteXPos+mLedgerLineHalfWidth, y, mLinePen );
			mLedgerLines.push_back( line );
		}
	}
}

qreal StaffPresenter::getSceneYFromStaffY( int staffY ) const
{
	qreal y = -1 * static_cast<qreal>(staffY) * (mStaffLineSpacing/2);
	return y;
}

void StaffPresenter::setText( const QString& text )
{
	mTextItem->setPlainText(text); 
}

void StaffPresenter::setNoteNameVisible( bool value )
{
	mNoteNameItem->setVisible(value); 
}
