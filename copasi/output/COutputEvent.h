/*****************************************************************************
* PROGRAM NAME: COutputEvent.h
* PROGRAMMER: Wei Sun	wsun@vt.edu
* PURPOSE: Handle Output Event 
*****************************************************************************/

#ifndef COPASI_COutputEvent
#define COPASI_COutputEvent

#include <iostream>

#include "output/output.h"
#include "steadystate/CSS_Solution.h"
#include "trajectory/CTrajectory.h"

class COutput;
class COutputList;
class CSS_Solution;

class COutputEvent
{
 private:
	 int mTime;
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
	 */
	COutputEvent(CTrajectory &tra, int time);

	/**
	 * User defined constructor. 
	 * @param tra refers to the CSS_solution object.
	 * @param time refers to the output interval
	 * time = 0, header
	 * time = 1, any time of simulation exceution
	 * time = 2, the final result
	 */
	COutputEvent(CSS_Solution &ss, int time);

	/**
	 * Deconstructor
	 */
	~COutputEvent();

	/**
	 *	Clean Up
	 */
	void cleanup();

	/**
	 * Copy output at the specified time 
	 * @param tra refers to the CTrajectory object.
	 */
	void print(CTrajectory &tra, COutputList list, ofstream &fout);

	/**
	 * Copy output at the specified time 
	 * @param tra refers to the CSS_solution object.
	 */
	void print(CSS_Solution &ss, COutputList list, ofstream &fout);
};

#endif // COutputEvent
