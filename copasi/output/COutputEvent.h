/*****************************************************************************
* PROGRAM NAME: COutputEvent.h
* PROGRAMMER: Wei Sun	wsun@vt.edu
* PURPOSE: Handle Output Event 
*****************************************************************************/

#ifndef COPASI_COutputEvent
#define COPASI_COutputEvent

#include <iostream>

#include "trajectory/CTrajectory.h"
#include "steadystate/CSS_Solution.h"
#include "COutput.h"
#include "COutputList.h"

class CSS_Solution;

class COutputEvent
{
 private:
	 int mTime;
	 COutput *mInteractiveTime;
	 COutput *mTimeCourse;
	 COutput *mSteadyState;
 public:  	
	/**
	 * Default constructor. 
	 */
	COutputEvent();

	/**
	 * User defined constructor. 
	 * @param tra refers to the CTrajectory object.
	 * @param time refers to the output interval
	 * time = 0, header
	 * time = 1, any time of simulation exceution
	 * time = 2, the final result
	 * @param list refer to the while output list of this model
	 */
	COutputEvent(CTrajectory &tra, int time, COutputList *list, ofstream &fout);

	/**
	 * User defined constructor. 
	 * @param tra refers to the CSS_solution object.
	 * @param time refers to the output interval
	 * time = 0, header
	 * time = 1, any time of simulation exceution
	 * time = 2, the final result
     *  @param list refer to the while output list of this model
	 */
	COutputEvent(CSS_Solution &ss, int time, COutputList *list, ofstream &fout);

	/**
	 * Deconstructor
	 */
	~COutputEvent();

	/**
	 *	Clean Up
	 */
	void cleanup();

	/**
	 *	
	 */
	void print();

	/**
	 * Copy output at the specified time 
	 * @param tra refers to the CTrajectory object.
	 */
	void copy(CTrajectory &tra, COutputList *list, ofstream &fout);

	/**
	 * Copy output at the specified time 
	 * @param tra refers to the CSS_solution object.
	 */
	void copy(CSS_Solution &ss, COutputList *list, ofstream &fout);
};

#endif //COutputEvent
