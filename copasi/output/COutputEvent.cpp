/*****************************************************************************
* PROGRAM NAME: COutputEvent.cpp
* PROGRAMMER: Wei Sun	wsun@vt.edu
* PURPOSE: COutputEvent Class Implemention
*****************************************************************************/
#include "copasi.h"
#include "COutputEvent.h"

/**
 *	Default constructor. 
 */
COutputEvent::COutputEvent()
{
	mTime = 0;
}

/**
 *	User defined constructor. 
 *  @param tra refers to the CTrajectory object.
 *  @param time refers to the output interval
 *	time = 0, header
 *	time = 1, any time of simulation exceution
 *  time = 2, the final result
 *  @param list refer to the while output list of this model
 */
COutputEvent::COutputEvent(CTrajectory &tra, int time, COutputList *list, ofstream &fout)
{
	// Note: just for Interactive time course and Time-course output

	mInteractiveTime = new COutput;

	mTimeCourse = new COutput;

	mTime = time;
	copy(tra, list, fout);
}

/**
 *	User defined constructor. 
 *  @param tra refers to the CSS_solution object.
 *  @param time refers to the output interval
 *	time = 0, header
 *	time = 1, any time of simulation exceution
 *  time = 2, the final result
 *  @param list refer to the while output list of this model
 */
COutputEvent::COutputEvent(CSS_Solution &ss, int time, COutputList *list, ofstream &fout)
{
	// Just for steady state 
	mSteadyState = new COutput;

	mTime = time;
	copy(ss, list, fout);
}

/**
 * Copy output at the specified time 
 * @param tra refers to the CTrajectory object.
 * @param time refers to the output interval
 * @param list refer to the while output list of this model
 */
void COutputEvent::copy(CTrajectory &tra, COutputList *list, ofstream &fout)
{

	list->copasiDyn(fout, mTime);
}

/**
 * Copy output at the specified time 
 * @param tra refers to the CSS_solution object.
 * @param time refers to the output interval
 * @param list refer to the while output list of this model
 */
void COutputEvent::copy(CSS_Solution &ss, COutputList *list, ofstream &fout)
{
	list->copasiSS(fout, mTime);
}


/**
 * Clean Up
 */

void COutputEvent::cleanup()
{
	if (mInteractiveTime)
		delete mInteractiveTime;
	mInteractiveTime = NULL;

	if (mTimeCourse)
		delete mTimeCourse;
	mTimeCourse = NULL;

	if (mSteadyState)
		delete mSteadyState;
	mSteadyState = NULL;

}

/**
 * Deconstructor
 */
COutputEvent::~COutputEvent()
{
	cleanup();
}

