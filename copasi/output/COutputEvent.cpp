/*****************************************************************************
 * PROGRAM NAME: COutputEvent.cpp
 * PROGRAMMER: Wei Sun wsun@vt.edu
 * PURPOSE: COutputEvent Class Implemention
 *****************************************************************************/
#define  COPASI_TRACE_CONSTRUCTION

#include "copasi.h"
#include "output.h" 
// #include "COutputEvent.h"

/**
 * Default constructor. 
 */
COutputEvent::COutputEvent()
{
  mTime = 0;
}

/**
 * User defined constructor. 
 *  @param time refers to the output interval
 * time = 0, header
 * time = 1, any time of simulation exceution
 *  time = 2, the final result
 */
COutputEvent::COutputEvent(int time)
{
  mTime = time;
}

/**
 * User defined constructor. 
 *  @param time refers to the output interval
 */
COutputEvent::COutputEvent(CSS_Solution & C_UNUSED(ss))
{
  //mTime = time;
  mTime = 0;    // wsun steady state just output one line data
}

/**
 * Print output at the specified time 
 * @param time refers to the output interval
 * @param list refer to the while output list of this model
 */
void COutputEvent::print(COutputList list, ofstream &fout)
{
  list.copasiDyn(fout, mTime);
}

/**
 * Print output at the specified time 
 * @param time refers to the output interval
 * @param list refer to the while output list of this model
 */
void COutputEvent::print(CSS_Solution &ss, COutputList list, ofstream &fout)
{
  list.copasiSS(fout, ss.getSolution());
}

/**
 * Clean Up
 */

void COutputEvent::cleanup()
{}

/**
 * Deconstructor
 */
COutputEvent::~COutputEvent()
{
  cleanup();
}
