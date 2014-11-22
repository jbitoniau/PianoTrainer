#pragma once

#include <QGraphicsScene>
#include "Staff.h"

class QGraphicsPixmapItem;

class StaffPresenter : public Staff::Listener
{
public:
	StaffPresenter( Staff* staff, QGraphicsScene* graphicsScene );

	Staff*			getStaff() const { return mStaff; }
	QGraphicsScene*	getGraphicsScene() const { return mGraphicsScene; }

	void			update();

private:
	void			onNoteChanged( Staff* staff, const Note& note );
	
	void			init();
	void			createStaffLineItems();
	void			createStaffKeyItem();
	void			createNoteItem();
	void			createNoteNameItem();
	
	// Return the vertical position in the scene (i.e. QGraphicsItem's coordinate system)
	qreal			getSceneYFromStaffY( int y ) const;

	Staff*					mStaff;
	QGraphicsScene*			mGraphicsScene;
	QGraphicsPixmapItem*	mNoteItem;
	std::vector<QGraphicsLineItem*> mLedgerLines;
	QGraphicsTextItem*		mNoteNameItem;
	
	QPixmap					mNotePixmap;
	QPixmap					mNoteSharpPixmap;
	QPixmap					mNoteFlatPixmap;

	static const float		mStaffLineSpacing;
	static const float		mStaffWidth;
	static const float		mNoteXPos;
	static const float		mLedgerLineWidth;
	static const QPen		mLinePen;
};