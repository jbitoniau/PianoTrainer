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

	Staff*					mStaff;
	QGraphicsScene*			mGraphicsScene;
	QGraphicsPixmapItem*	mNoteItem;

	static const float		mStaffLineSpacing;
	static const float		mStaffWidth;
};