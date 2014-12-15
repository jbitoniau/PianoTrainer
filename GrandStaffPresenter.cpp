#include "GrandStaffPresenter.h"

#include <QGraphicsItemGroup>

GrandStaffPresenter::GrandStaffPresenter( GrandStaff* grandStaff, QGraphicsScene* graphicsScene )
	: GrandStaff::Listener(),
	  mGrandStaff(grandStaff),
	  mGraphicsScene(graphicsScene),
	  mTrebleStaffPresenter(0),
	  mBassStaffPresenter(0),
	  mNoteNameItem(0),
	  mTextItem(0)
{
	QGraphicsItemGroup* trebleGroup = new QGraphicsItemGroup();
	mGraphicsScene->addItem( trebleGroup );
	mTrebleStaffPresenter = new StaffPresenter( &grandStaff->getTrebleStaff(), trebleGroup );

	QGraphicsItemGroup* bassGroup = new QGraphicsItemGroup();
	bassGroup->setPos(0, 300 );
	mGraphicsScene->addItem( bassGroup );
	mBassStaffPresenter = new StaffPresenter( &grandStaff->getBassStaff(), bassGroup );

	mNoteNameItem = mGraphicsScene->addText( "..." );
	mNoteNameItem->setPos( 400, 0 );
	mNoteNameItem->setScale( 4 );

	mTextItem = mGraphicsScene->addText( "..." );
	mTextItem->setPos( 400, 40 );
	mTextItem->setScale( 4 );

	mGrandStaff->addListener(this);
}

void GrandStaffPresenter::setText( const QString& text )
{
	mTextItem->setPlainText(text); 
}

void GrandStaffPresenter::setNoteNameVisible( bool value )
{
	mNoteNameItem->setVisible(value); 
}

void GrandStaffPresenter::onNoteChanged( GrandStaff* grandStaff, const Note& note )
{
	std::string noteName = note.getName(true);
	mNoteNameItem->setPlainText( noteName.c_str() );
}

