/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/output/Attic/COutputList.cpp,v $
   $Revision: 1.22 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/16 16:25:54 $
   End CVS Header */

/*****************************************************************************
 * PROGRAM NAME: COutputList.cpp
 * PROGRAMMER: Wei Sun wsun@vt.edu
 * PURPOSE: COutputList Class Implemention
 *****************************************************************************/

#include <fstream>
#include <iostream>
#include <string>

#define  COPASI_TRACE_CONSTRUCTION

#include "copasi.h"
#include "COutputList.h"
#include "COutput.h"
#include "utilities/CReadConfig.h"

/**
 * Default constructor.
 */
COutputList::COutputList()
{
  //  mList = NULL;
}

COutputList::~COutputList()
{}

/**
 * User defined constructor.
 * Read config variables from input configburg buffer
 *  @param configbuffer: reference of the config buffer.
 */
COutputList::COutputList(CReadConfig & C_UNUSED(configbuffer))
{
  init();
}

void COutputList::init()
{
  //  mList = new CCOutput;
}

void COutputList::cleanup()
{
  //  if (mList) delete mList;
  //  mList = NULL;
  mList.cleanup();
}

/**
 *  Saves the contents of the object to a CWriteConfig object.
 *  (Which usually has a file attached but may also have socket)
 *  @param pconfigbuffer reference to a CWriteConfig object.
 *  @return mFail
 *  @see mFail
 */
C_INT32 COutputList::save(CWriteConfig & configbuffer)
{
  C_INT32 Fail = 0;

  mList.save(configbuffer);

  return Fail;
}

/**
 *  Loads an object with data coming from a CReadConfig object.
 *  (CReadConfig object reads an input stream)
 *  @param pconfigbuffer reference to a CReadConfig object.
 *  @param model refernce to the input configbuffer
 *  @return mFail
 *  @see mFail
 */
C_INT32 COutputList::load(CReadConfig & configbuffer)
{
  C_INT32 Fail = 0;
  COutput output;

  // We need to load
  // ReportFile=MassAction.txt
  // DynamicsFile=simresults.dyn
  // SSFile=simresults.ss
  configbuffer.getVariable("ReportFile", "string", &mReportFile,
                           CReadConfig::LOOP);
  configbuffer.getVariable("DynamicsFile", "string", &mTrajectoryFile);
  configbuffer.getVariable("SSFile", "string", &mSteadyStateFile);

  output.load(configbuffer);
  /* :TODO: We must not set the model here! */
  //output.setModel(model);
  addOutput(output);

  return Fail;
}

/**
 *  Return the pointer of the COutputLine that can be output at the same time.
 *  @return mList
 *  @see mList
 */
const CCopasiVectorS < COutput > & COutputList::getList() const
  {
    return mList;
  }

/**
 *  Add new OutputLine object to a list
 *  @param newLine constant reference to COutputLine .
 *  @see COutputLine Class
 */
void COutputList::addOutput(COutput &newOutput)
{
  //  if (!mList) init();
  mList.add(newOutput);
}

/*
 * print the reporting data file
 */
void COutputList::copasiRep(std::ostream &fout) const
  {
    for (unsigned C_INT32 i = 0; i < mList.size(); i++)
      {
        mList[i]->copasiRep(fout);
      }
  }

/*
 * print the steady state data file
 */
void COutputList::copasiSS(std::ostream &fout) const
  {
    for (unsigned C_INT32 i = 0; i < mList.size(); i++)
      {
        mList[i]->copasiSS(fout);
      }
  }

/*
 * print the time course dynamic data file
 */
void COutputList::copasiDyn(std::ostream &fout, int time) const
  {
    for (unsigned C_INT32 i = 0; i < mList.size(); i++)
      {
        mList[i]->copasiDyn(fout, time);
      }
  }

/**
 * Assign the mpvalue in CDatum for each type
 */
void COutputList::compile(const std::string & name, CModel *model, CState *state)
{
  for (unsigned C_INT32 i = 0; i < mList.size(); i++)
    {
      mList[i]->compile(name, model, state);
    }
}

/**
 * Assign the pointer to each datum object for steady state
 */
void COutputList::compile(const std::string & name, CModel *model,
                          CSteadyStateTask *soln)
{
  for (unsigned C_INT32 i = 0; i < mList.size(); i++)
    {
      mList[i]->compile(name, model, soln);
    }
}

const std::string & COutputList::getReportFile() const
  {return mReportFile;}

const std::string & COutputList::getTrajectoryFile() const
  {return mTrajectoryFile;}

const std::string & COutputList::getSteadyStateFile() const
  {return mSteadyStateFile;}
