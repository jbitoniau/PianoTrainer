#pragma once

class Staff
{
public:
	Staff();

	int		getSolKeyNote() const				{ return mSolKeyNote; }
	void	setSolKeyNote( int note );
	
private:
	int		mSolKeyNote;
};