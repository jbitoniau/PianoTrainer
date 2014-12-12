#pragma once

#include "Staff.h"

/*
	GrandStaff
*/
class GrandStaff
{
public:
	GrandStaff();

	const Staff&	getTrebleStaff() const			{ return mTrebbleStaff; }
	Staff&			getTrebleStaff()				{ return mTrebbleStaff; }
	const Staff&	getBassStaff() const			{ return mBassStaff; }
	Staff&			getBassStaff()					{ return mBassStaff; }

	void			setNote( const Note& note );

	class Listener
	{
	public:
		virtual ~Listener() {}
		virtual void onNoteChanged( Staff* staff, const Note& note ) {}
	};
	void			addListener( Listener* listener );

private:
	void			notifyListeners();

	Staff			mTrebbleStaff;
	Staff			mBassStaff;
	std::vector<Listener*> mListeners;
};
