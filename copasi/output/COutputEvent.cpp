/*****************************************************************************
* PROGRAM NAME: COutputEvent.cpp
* PROGRAMMER: Wei Sun	wsun@vt.edu
* PURPOSE: COutputEvent Class Implemention
*****************************************************************************/
#include "copasi.h"
#include "output.h"
// #include "COutputEvent.h"

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
 */
COutputEvent::COutputEvent(CTrajectory &tra, int time)
{
	mTime = time;
}

/**
 *	User defined constructor. 
 *  @param tra refers to the CSS_solution object.
 *  @param time refers to the output interval
 */
COutputEvent::COutputEvent(CSS_Solution &ss)
{
	//mTime = time;
	mTime = 0;				// wsun steady state just output one line data
}

/**
 * Print output at the specified time 
 * @param tra refers to the CTrajectory object.
 * @param time refers to the output interval
 * @param list refer to the while output list of this model
 */
void COutputEvent::print(CTrajectory &tra, COutputList list, ofstream &fout)
{

	list.copasiDyn(fout, mTime);
}

/**
 * Print output at the specified time 
 * @param tra refers to the CSS_solution object.
 * @param time refers to the output interval
 * @param list refer to the while output list of this model
 */
void COutputEvent::print(CSS_Solution &ss, COutputList list, ofstream &fout)
{
	list.copasiSS(fout);
}


/**
 * Clean Up
 */

void COutputEvent::cleanup()
{
}

/**
 * Deconstructor
 */
COutputEvent::~COutputEvent()
{
	cleanup();
}

