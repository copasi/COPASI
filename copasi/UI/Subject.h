/****************************************************************************
**  $ CopasiUI/Subject.h                 Modified on : 8th March, 2002
**  $ Author  : Ankur Gupta
**  
**  This file is a HEADER for Subject a part of OBSERVER DESIGN PATTERN.
**   
**
*****************************************************************************/


#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include "Observer.h"



/*******************************************************************
** This is the class declaration
**
********************************************************************/
class Subject{
public:

	    virtual ~Subject();// destructor
		virtual void attach(Observer *);//this method is used to attach the number of observing observing me.
		virtual void detach(Observer *);// this method is used to detach the obeserv from the list..
		virtual void notify(int);// this method is used to notify all the observer about any change in my state
protected:
	    Subject();// constructor
private:
	    std::vector<Observer*> _observers; // this vector is used to store the number of observers in my list
	   
			   
		
};

#endif
