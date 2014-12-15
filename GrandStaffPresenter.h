#pragma once

#include "GrandStaff.h"
#include "StaffPresenter.h"

class GrandStaffPresenter : public GrandStaff::Listener
{
public:
	GrandStaffPresenter( GrandStaff* staff, QGraphicsScene* graphicsScene );

	GrandStaff*		getGrandStaff() const { return mGrandStaff; }

	StaffPresenter*	getTrebleStaffPresenter() const { return mTrebleStaffPresenter; }
	StaffPresenter*	getBassStaffPresenter() const { return mBassStaffPresenter; }
	
	void			setText( const QString& text );
	void			setNoteNameVisible( bool value );

/*	Staff*			getStaff() const { return mStaff; }
	QGraphicsScene*	getGraphicsScene() const { return mGraphicsScene; }

	void			update();

	void			setText( const QString& text );
	void			setNoteNameVisible( bool value );
*/

private:
	void			onNoteChanged( GrandStaff* grandStaff, const Note& note );
/*	
	void			init();
	void			createStaffLineItems();
	void			createStaffKeyItem();
	void			createNoteItem();
	void			createNoteNameItem();
	
	// Return the vertical position in the scene (i.e. QGraphicsItem's coordinate system)
	qreal			getSceneYFromStaffY( int y ) const;

	*/
	GrandStaff*				mGrandStaff;
	QGraphicsScene*			mGraphicsScene;
	StaffPresenter*			mTrebleStaffPresenter;
	StaffPresenter*			mBassStaffPresenter;

	QGraphicsTextItem*		mNoteNameItem;
	QGraphicsTextItem*		mTextItem;
};