#pragma once

#include <QGraphicsScene>
#include "Staff.h"

class StaffPresenter
{
public:
	StaffPresenter( Staff* staff, QGraphicsScene* graphicsScene );

private:
	void			init();
	void			update();

	Staff*			mStaff;
	QGraphicsScene*	mGraphicsScene;
};