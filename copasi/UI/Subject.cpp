/****************************************************************************
**  $ CopasiUI/Subject.cpp                 Modified on : 8th March, 2002
**  $ Author  : Ankur Gupta
**  
**  This file is a cpp for Subject a part of OBSERVER DESIGN PATTERN.
**   
**
**********************************************************************/
#include "Subject.h"

/**
* This method attaches the observer in the observers list...to keep track of how many
* of them are observing the changes done in the data model
*/
void Subject::attach(Observer* o)
{
   // append it in the observer list... 
	  _observers.push_back(o);
	
}

/**This method removes the observer from the observer's list
*/
void Subject::detach(Observer* o)
{
   // detach from the observer list...
   int length=_observers.size();
   int i=0;
   for(i=0;i<length;i++)
	  if( _observers[i]==o)
		  break;
	  
    Observer** Target;
 
   if(i!= length)
	  {
	     Target = _observers.begin() + i;
        	   _observers.erase(Target, Target + 1);
   }

     

}

/**This method is used to notify all the observer's of the change in the value
* along with the change in the status..ie.wht is changed...
*/
void Subject::notify(int status)
{

   int length=_observers.size();
   for(int i=0;i<length;i++)
	   _observers[i]->update(this,status);


}

Subject::Subject(){}
Subject::~Subject(){}