#pragma once

#include <QGraphicsScene>
#include "Staff.h"

class QGraphicsPixmapItem;
class QGraphicsItemGroup;

class StaffPresenter : public Staff::Listener
{
public:
	StaffPresenter( Staff* staff, QGraphicsItemGroup* group );

	Staff*				getStaff() const		{ return mStaff; }
	QGraphicsItemGroup*	getItemGroup() const	{ return mGroup; }

	void				update();

private:
	void				onNoteChanged( Staff* staff, const Note& note );
	
	void				init();
	void				createStaffLineItems();
	void				createStaffKeyItem();
	void				createNoteItem();
	
	// Return the vertical position in the scene (i.e. QGraphicsItem's coordinate system)
	qreal				getSceneYFromStaffY( int y ) const;

	Staff*					mStaff;

	QGraphicsItemGroup*		mGroup;
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