/****************************************************************************
**  $ CopasiUI/Observer.h                 Modified on : 8th March, 2002
**  $ Author  : Ankur Gupta
**  
**  This file is a HEADER for Observer a part of OBSERVER DESIGN PATTERN.
**   
**
**********************************************************************/
#ifndef OBSERVER_H
#define OBSERVER_H


/***********************************************************************
** This class is the one that listens to the subject and is derived by the
** view class .
***********************************************************************/
class Subject;
class Observer{


public:
	   virtual ~Observer();// destructor
	   virtual void update(Subject* theChangedSubject,int status)=0; //this is the abstract class. that is informed whenever the data changes by the subject class.
protected:
	   Observer();// constructor

};

#endif

