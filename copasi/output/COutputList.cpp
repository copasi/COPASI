/*****************************************************************************
* PROGRAM NAME: COutputList.cpp
* PROGRAMMER: Wei Sun	wsun@vt.edu
* PURPOSE: COutputList Class Implemention
*****************************************************************************/

#include <fstream>
#include <iostream>
#include <string>

#include "copasi.h"
#include "COutputList.h"

/**
 *	Default constructor.
 */
COutputList::COutputList()
{
  mList = NULL;
}

COutputList::~COutputList()
{
}

/**
 *	User defined constructor.
 *	Read config variables from input configburg buffer
 *  @param configbuffer: reference of the config buffer.
 */
COutputList::COutputList(CReadConfig &configbuffer)
{
  init();
}


void COutputList::init()
{
  mList = new CCOutput;
}

void COutputList::cleanup()
{
  if (mList) delete mList;
  mList = NULL;
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

  mList->save(configbuffer);

  return Fail;
}

/**
 *  Loads an object with data coming from a CReadConfig object.
 *  (CReadConfig object reads an input stream)
 *  @param pconfigbuffer reference to a CReadConfig object.
 *  @param searchName refernece to a the time of seach section,
 *		   for example: Interactive time course
 *  @return mFail
 *  @see mFail
 */
C_INT32 COutputList::load(CReadConfig & configbuffer)
{
  C_INT32 Fail = 0;
  COutput output;

  output.load(configbuffer);
  output.setModel(Model);
  addOutput(output);

  return Fail;
}

/**
 *  Return the pointer of the COutputLine that can be output at the same time.
 *  @return mList
 *  @see mList
 */
CCOutput * COutputList::getList() const
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
  if (!mList) init();
  mList->add(newOutput);
}

/**
 *	Assigns model in the Outputlist
 */
void COutputList::setModel(const CModel &model)
{
  Model = model;
  // Temporarily use, need consideration???
  for (unsigned C_INT32 i = 0; i < mList->size(); i++)
    {
      (*mList)[i].setModel(model);
    }

}

/*
 *	print the reporting data file
 */
void COutputList::copasiRep(ofstream &fout)
{
  for (unsigned C_INT32 i = 0; i < mList->size(); i++)
    {
      (*mList)[i].copasiRep(fout);
    }
}

/*
 * print the steady state data file
 */
void COutputList::copasiSS(ofstream &fout, int time)
{
  for (unsigned C_INT32 i = 0; i < mList->size(); i++)
    {
      (*mList)[i].copasiSS(fout, time);
    }
}

/*
 * print the time course dynamic data file
 */
void COutputList::copasiDyn(ofstream &fout, int time)
{
  for (unsigned C_INT32 i = 0; i < mList->size(); i++)
    {
      (*mList)[i].copasiDyn(fout, time);
    }
}

void COutputList::compile(string &name)
{

  for (unsigned C_INT32 i = 0; i < mList->size(); i++)
    {
      (*mList)[i].compile(name, Model);
    }

}

CCOutput::CCOutput() {}

CCOutput::~CCOutput() {}

C_INT16 CCOutput::isInsertAllowed(const COutput & src)
{return TRUE;}
