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
	

	// To represent a note vertically on the staff, we assign a number
	// to each of its line and interline starting from the bottom. 
	// This is the staff coordinate system.
	// The bottom vertical position is 0 (Mi on a Sol key staff), 
	// then the interline above is 1 (Fa), 
	// then the line above is 2 (Sol), etc...
	// When the note lies on the "regular" lines/interlines of the staff
	// its vertical position is therefore between 0 and 8 (both included)
	// It is be negative or greater than 8 when the note lies outside 
	// regular staff lines/interlines. 
	// Ledger lines are required (when position is >9 or <-1) 
	// see http://en.wikipedia.org/wiki/Ledger_line
	/*int				getStaffYCoordinate( const Note& note, bool useSharpPosition ) const;		
	//static int		getStaffYCoordinate( const Note& note, Staff::Key staffKey, bool useSharpPosition );		
	static int		getStaffYCoordinate( const Note& note, const Note& staffKeyNote, bool useSharpPosition );		
		// Return the number of the note lying at the 0th line of the staff
	int				getStaffY0NoteNumber() const;*/

	// Return the vertical position in the scene (i.e. QGraphicsItem's 
	// coordinate system)
	qreal			getSceneYFromStaffY( int y ) const;

	Staff*					mStaff;
	QGraphicsScene*			mGraphicsScene;
	QGraphicsPixmapItem*	mNoteItem;
	QGraphicsLineItem*		mNoteLedgerLineItem;

	static const float		mStaffLineSpacing;
	static const float		mStaffWidth;
	
	// Note name to note Soprano staff (Ut 1st line) Y position when using sharp mode
	// In this key, there's a simple match between the note name (do, ré, mi, ...) and
	// its position in the staff:
	//	C (Do) is at 0th position, 0th line,
	//	D (Ré) is at 1st position, 0th interline,
	//	E (Mi) is at 2nd position, 1st line,
	//	etc...
	// The position depends on whether we want the note to be presented 
	// with a sharp or with a flat.
	/*static int				mIndexInOctaveToSopranoKeyYPos_SharpMode[Note::mNumNoteNames];		
	static int				mIndexInOctaveToSopranoKeyYPos_FlatMode[Note::mNumNoteNames];*/
};