#include "NoteProviderKeyboard.h"

#include <QKeyEvent>

#include "StaffPresenter.h" //!!!!!!

NoteProviderKeyboard::NoteProviderKeyboard( QWidget* parent, Qt::WindowFlags flags )
	: QWidget( parent, flags ),
	  mIndexNoteInOctave(0),
	  mOctaveIndex(4),

	  mStaffPresenter(0)
{
}

NoteProviderKeyboard::~NoteProviderKeyboard()
{
}

Note NoteProviderKeyboard::getNote()
{
	int noteNumber = (mOctaveIndex+1) * 12 + mIndexNoteInOctave;
	return Note(noteNumber);
}

void NoteProviderKeyboard::keyPressEvent( QKeyEvent* event )
{
	int key = event->key();
	if ( key>=Qt::Key_0 && key<=Qt::Key_9 )
	{
		mOctaveIndex = key - Qt::Key_0;
	}
	else 
	{
		int n = -1;
		if ( event->modifiers().testFlag(Qt::ShiftModifier) ) 
		{
			switch ( key )
			{
				case Qt::Key_D : n = 1; break;
				case Qt::Key_R : n = 3; break;
				case Qt::Key_M : n = 4; break;
				case Qt::Key_F : n = 6; break;
				case Qt::Key_S : n = 8; break;
				case Qt::Key_L : n = 10; break;
				case Qt::Key_I : n = 11; break;
			}
		}
		else
		{
			switch ( key )
			{
				case Qt::Key_D : n = 0; break;
				case Qt::Key_R : n = 2; break;
				case Qt::Key_M : n = 4; break;
				case Qt::Key_F : n = 5; break;
				case Qt::Key_S : n = 7; break;
				case Qt::Key_L : n = 9; break;
				case Qt::Key_I : n = 11; break;
			}
		}
		if ( n!=-1 )
			mIndexNoteInOctave = n;

		//!!!
		if ( n!=-1 && mStaffPresenter )
		{
			Note note = getNote();
			mStaffPresenter->getStaff()->setNote(note);
			mStaffPresenter->update();
		}
	}		
}

void NoteProviderKeyboard::keyReleaseEvent( QKeyEvent* event )
{
}
