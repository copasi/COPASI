/*****************************************************************************
 * PROGRAM NAME: COutputLine.cpp
 * PROGRAMMER: Wei Sun wsun@vt.edu
 * PURPOSE: COutputLine Class Implemention
 *****************************************************************************/

#include <iostream>
#include <fstream>
#include <iomanip>

#define  COPASI_TRACE_CONSTRUCTION

#include "copasi.h"
#include "utilities/readwrite.h"
#include "utilities/CCopasiVector.h"
#include "model/CCompartment.h"
#include "CDatum.h"
#include "COutputLine.h"
#include "steadystate/CSteadyStateTask.h"

/**
 *  Default constructor. 
 */
COutputLine::COutputLine(const std::string & name,
                         const CCopasiContainer * pParent):
    CCopasiContainer(name, pParent, "Output Line"),
    mLine("Data", this)
{}

COutputLine::COutputLine(const COutputLine & src,
                         const CCopasiContainer * pParent):
    CCopasiContainer(src, pParent),
    mLine(src.mLine, this)
{}

void COutputLine::init() {}

void COutputLine::cleanup()
{
  // if (mLine) delete mLine;
  // mLine = NULL;
  mLine.cleanup();
}

/**
 *  Destructor. 
 */
COutputLine::~COutputLine()
{
  // cleanup();
}

/**
 *  Return the pointer of the CDatum that can be output at the same line. 
 *  @return mLine
 *  @see mLine
 */
const CCopasiVectorS < CDatum > & COutputLine::getLine() const
  {
    return mLine;
  }

/**
 *  Sets the name of this line, (For example: Interactive time course)
 *  @param title constant reference to a string.
 */
bool COutputLine::setName(std::string LineName)
{
  return setObjectName(LineName);
}

/**
 *  Add new CDatum object to a line
 *  @param newDatum constant reference to CDatum.
 *  @see CDatum Class
     */
void COutputLine::addDatum(CDatum & newDatum)
{
  mLine.add(newDatum);
}
C_INT32 COutputLine::load(CReadConfig & C_UNUSED(configbuffer)) {return 0;}

/**
 *  Loads an object with data coming from a CReadConfig object.
 *  (CReadConfig object reads an input stream)
 *  @param pconfigbuffer reference to a CReadConfig object.
 *  @param searchName refernece to a the time of seach section,
 *     for example: Interactive time course  
 *  @return mFail
 *  @see mFail
 */
C_INT32 COutputLine::load(CReadConfig & configbuffer, std::string &searchName)
{
  C_INT32 Fail = 0;
  C_INT32 Size = 0;

  // Search string searchName from configure variable
  std::string tmp;
  if ((Fail = configbuffer.getVariable(searchName, "string",
                                       &tmp,
                                       CReadConfig::SEARCH)))
    return Fail;
  setObjectName(tmp);

  // now pout points the end of search string
  // Read the number of items in this section
  if ((Fail = configbuffer.getVariable("Items", "C_INT32",
                                       &Size, CReadConfig::NEXT)))
    return Fail;

  init();

  // Read objects and create the OutputLine
  for (int i = 0; i < Size; i++)
    {
      CDatum newItem;

      newItem.load(configbuffer);
      addDatum(newItem);
    }

  return Fail;
}

const std::string & COutputLine::getName() const {return getObjectName();}

/**
 *  Saves the contents of the object to a CWriteConfig object.
 *  (Which usually has a file attached but may also have socket)
 *  @param pconfigbuffer reference to a CWriteConfig object.
 *  @return mFail
 *  @see mFail
 */
C_INT32 COutputLine::save(CWriteConfig & configbuffer)
{
  C_INT32 Fail = 0;
  C_INT32 Size = 0;

  Size = mLine.size();
  std::string tmp = getObjectName();
  if ((Fail = configbuffer.setVariable(tmp, "string", NULL)))
    return Fail;

  if ((Fail = configbuffer.setVariable("Items", "C_INT32", &Size)))
    return Fail;

  // Output each datum in this line
  //Fail = mLine->save(configbuffer);

  mLine.save(configbuffer);

  return Fail;
}

/**
 * print the titles of the steady-state data file
 */
void COutputLine::sSOutputTitles(std::ostream &fout, C_INT16 SSSeparator, C_INT16 SSColWidth, C_INT16 SSQuotes)
{
  unsigned C_INT32 i;
  CDatum * item;
  std::string Title;

  // Set Left Justification
  fout.setf(std::ios::left);

  for (i = 0; i < mLine.size(); i++)
    {
      if (i)
        {
          switch (SSSeparator)
            {
            case 9:
              fout << "\t";
              break;

            case 32:
              fout << " ";
              break;

            case 44:
              fout << ",";
              break;
            }
        }

      item = mLine[i];

      if (item->getTitle().length() > (unsigned C_INT32) SSColWidth)
        Title = item->getTitle().substr(0, SSColWidth);
      else
        Title = item->getTitle();

      if (SSQuotes)
        fout << "\"" << std::setw(SSColWidth) << Title << "\"";
      else
        fout << std::setw(SSColWidth) << Title;
    }

  fout.unsetf(std::ios::left);
  fout << std::endl;
}

/**
 * print the mpValue of each Object in the steady-state data file
 */
void COutputLine::sSOutputData(std::ostream &fout, C_INT16 SSSeparator,
                               C_INT16 SSColWidth, C_INT16 C_UNUSED(SSQuotes))
{
  unsigned C_INT32 i;
  C_INT32 Type;
  C_INT16 *Value1;
  C_INT32 *Value2;
  C_FLOAT32 *Value3;
  C_FLOAT64 *Value4;
  CDatum *datum;

  // Set Left Justification
  fout.setf(std::ios::left);
  // Set Float manipulators
  fout.setf(std::ios::scientific, std::ios::floatfield);
  fout.setf(std::ios::showpoint);

  for (i = 0; i < mLine.size(); i++)
    {
      if (i)
        {
          switch (SSSeparator)
            {
            case 9:
              fout << "\t";
              break;

            case 32:
              fout << " ";
              break;

            case 44:
              fout << ",";
              break;
            }
        }

      datum = mLine[i];
      // before outputing value of user defined function, need to
      // calculate first

      if (datum->getObjectType(datum->getObject()) == D_UFUNC)
        datum->calcFunc();

      Type = mLine[i]->getType();

      switch (Type)
        {
        case 1:
          // Type is C_INT16
          Value1 = (C_INT16 *)mLine[i]->getValue();

          if (!Value1)
            fout << std::setprecision(SSColWidth - 8) << std::setw(SSColWidth) << 0;  //?? Sign std::setw(SSColWidth-1)
          else
            fout << std::setprecision(SSColWidth - 8) << std::setw(SSColWidth) << *Value1; //?? Sign

          break;

        case 2:
          // Type is C_INT32
          Value2 = (C_INT32 *)mLine[i]->getValue();

          if (!Value2)
            fout << std::setprecision(SSColWidth - 8) << std::setw(SSColWidth) << 0;
          else
            fout << std::setprecision(SSColWidth - 8) << std::setw(SSColWidth) << *Value2;

          break;

        case 3:
          // Type is C_FLOAT32
          Value3 = (C_FLOAT32 *)mLine[i]->getValue();

          if (!Value3)
            fout << std::setprecision(SSColWidth - 8) << std::setw(SSColWidth) << 0;
          else
            fout << std::setprecision(SSColWidth - 8) << std::setw(SSColWidth) << *Value3;

          break;

        case 4:
          // Type is C_FLOAT64
          Value4 = (C_FLOAT64 *)mLine[i]->getValue();

          if (!Value4)
            fout << std::setprecision(SSColWidth - 8) << std::setw(SSColWidth) << 0;
          else
            fout << std::setprecision(SSColWidth - 8) << std::setw(SSColWidth) << *Value4;

          break;
        }
    }

  fout.unsetf(std::ios::left);
  fout << std::endl;
}

/**
 * print the titles of the time course data file
 */
void COutputLine::dynOutputTitles(std::ostream &fout, C_INT16 DynSeparator, C_INT16 DynColWidth, C_INT16 DynQuotes)
{
  unsigned C_INT32 i;
  CDatum * item;
  std::string Title;

  // Set Left Justification
  fout.setf(std::ios::left);

  for (i = 0; i < mLine.size(); i++)
    {
      if (i)
        {
          switch (DynSeparator)
            {
            case 9:
              fout << "\t";
              break;

            case 32:
              fout << " ";
              break;

            case 44:
              fout << ",";
              break;
            }
        }

      item = mLine[i];

      if (item->getTitle().length() > (unsigned C_INT16) DynColWidth)
        Title = item->getTitle().substr(0, DynColWidth);
      else
        Title = item->getTitle();

      if (DynQuotes)
        fout << "\"" << std::setw(DynColWidth) << Title << "\"";
      else
        fout << std::setw(DynColWidth) << Title;
    }

  fout.unsetf(std::ios::left);
  fout << std::endl;
}

/**
 * print the mpValue of each Object in the time course data file
 */
void COutputLine::dynOutputData(std::ostream &fout, C_INT16 DynSeparator,
                                C_INT16 DynColWidth, C_INT16 C_UNUSED(DynQuotes))
{
  unsigned C_INT32 i;
  C_INT32 Type;
  C_INT16 *Value1;
  C_INT32 *Value2;
  C_FLOAT32 *Value3;
  C_FLOAT64 *Value4;
  CDatum *datum;

  // Set Left Justification
  fout.setf(std::ios::left);
  // Set Float manipulators
  fout.setf(std::ios::scientific, std::ios::floatfield);
  fout.setf(std::ios::showpoint);

  for (i = 0; i < mLine.size(); i++)
    {
      if (i)
        {
          switch (DynSeparator)
            {
            case 9:
              fout << "\t";
              break;

            case 32:
              fout << " ";
              break;

            case 44:
              fout << ",";
              break;
            }
        }

      datum = mLine[i];
      // before outputing value of user defined function, need to
      // calculate first

      if (datum->getObjectType(datum->getObject()) == D_UFUNC)
        datum->calcFunc();

      Type = mLine[i]->getType();

      switch (Type)
        {
        case 1:
          // Type is C_INT16
          Value1 = (C_INT16 *)mLine[i]->getValue();

          if (!Value1)
            fout << std::setprecision(DynColWidth - 8) << std::setw(DynColWidth) << 0;
          else
            fout << std::setprecision(DynColWidth - 8) << std::setw(DynColWidth) << *Value1;

          break;

        case 2:
          // Type is C_INT32
          Value2 = (C_INT32 *)mLine[i]->getValue();

          if (!Value2)
            fout << std::setprecision(DynColWidth - 8) << std::setw(DynColWidth) << 0;
          else
            fout << std::setprecision(DynColWidth - 8) << std::setw(DynColWidth) << *Value2;

          break;

        case 3:
          // Type is C_FLOAT32
          Value3 = (C_FLOAT32 *)mLine[i]->getValue();

          if (!Value3)
            fout << std::setprecision(DynColWidth - 8) << std::setw(DynColWidth) << 0;
          else
            fout << std::setprecision(DynColWidth - 8) << std::setw(DynColWidth) << *Value3;

          break;

        case 4:
          // Type is C_FLOAT64
          Value4 = (C_FLOAT64 *)mLine[i]->getValue();

          if (!Value4)
            fout << std::setprecision(DynColWidth - 8) << std::setw(DynColWidth) << 0;
          else
            fout << std::setprecision(DynColWidth - 8) << std::setw(DynColWidth) << *Value4;

          break;
        }
    }

  fout.unsetf(std::ios::left);
  fout << std::endl;
}

/**
 *  Assign the pointer to each datum object in the output line for time course
 */
void COutputLine::compile(const std::string & name, CModel *model, CState *state)
{
  if (!getObjectName().compare(name))
    {// ???? Maybe it isnot necessary after finish whole module

      for (unsigned C_INT32 i = 0; i < mLine.size(); i++)
        {
          mLine[i]->compileDatum(model, state, NULL);
        }
    }
}

/**
 *  Assign the pointer to each datum object in the output line for steady state
 */
void COutputLine::compile(const std::string & name, CModel * model,
                          CSteadyStateTask * soln)
{
  if (!getObjectName().compare(name))
    {// ???? Maybe it isnot necessary after finish whole module

      for (unsigned C_INT32 i = 0; i < mLine.size(); i++)
        {
          mLine[i]->compileDatum(model, soln->getState(), soln);
        }
    }
}

#ifdef XXXX
COutputLine::CCDatum::CCDatum() {}
COutputLine::CCDatum::~CCDatum() {}

C_INT16 COutputLine::CCDatum::isInsertAllowed(const CDatum & src)
{return TRUE;}

#endif // XXXX
