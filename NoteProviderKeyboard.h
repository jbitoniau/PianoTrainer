#pragma once

#include <QWidget>
#include "NoteProvider.h"

class StaffPresenter;

class NoteProviderKeyboard : public QWidget,
							 public NoteProvider
{
	Q_OBJECT

public:
	NoteProviderKeyboard( QWidget* parent=NULL, Qt::WindowFlags flags=0 );
	virtual ~NoteProviderKeyboard();	

	virtual void update();
	
protected:
	virtual void keyPressEvent( QKeyEvent* event );
	virtual void keyReleaseEvent( QKeyEvent* event );

private:
	Note	getNote() const;
	int		mIndexNoteInOctave;
	int		mOctaveIndex;
	bool	mNoteReady;
};