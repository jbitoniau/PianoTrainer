#pragma once

#include <QGraphicsScene>
#include "Staff.h"

class QGraphicsPixmapItem;

class StaffPresenter
{
public:
	StaffPresenter( Staff* staff, QGraphicsScene* graphicsScene );
	
private:
	void			init();
	void			update();

	void			createKeyItem();
	
	// Return the vertical position in the scene (i.e. QGraphicsItem's 
	// coordinate system)
	qreal			getSceneYFromStaffY( int y ) const;

	Staff*					mStaff;
	QGraphicsScene*			mGraphicsScene;
	QGraphicsPixmapItem*	mNoteItem;
	QGraphicsLineItem*		mNoteLedgerLineItem;

	static const float		mStaffLineSpacing;
	static const float		mStaffWidth;
	static const float		mNoteXPos;
};