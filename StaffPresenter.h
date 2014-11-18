#pragma once

#include <QGraphicsScene>
#include "Staff.h"

class QGraphicsPixmapItem;

class StaffPresenter
{
public:
	StaffPresenter( Staff* staff, QGraphicsScene* graphicsScene );

	Staff*			getStaff() const { return mStaff; }
	QGraphicsScene*	getGraphicsScene() const { return mGraphicsScene; }

	void			update();

private:
	void			init();
	

	void			createStaffLineItems();
	void			createStaffKeyItem();
	void			createNoteItem();
	
	// Return the vertical position in the scene (i.e. QGraphicsItem's 
	// coordinate system)
	qreal			getSceneYFromStaffY( int y ) const;

	Staff*					mStaff;
	QGraphicsScene*			mGraphicsScene;
	QGraphicsPixmapItem*	mNoteItem;
	std::vector<QGraphicsLineItem*> mLedgerLines;

	QPixmap					mNotePixmap;
	QPixmap					mNoteSharpPixmap;
	QPixmap					mNoteFlatPixmap;

	static const float		mStaffLineSpacing;
	static const float		mStaffWidth;
	static const float		mNoteXPos;
	static const float		mLedgerLineWidth;
	static const QPen		mLinePen;
};