/*****************************************************************************
* PROGRAM NAME: COutputList.h
* PROGRAMMER: Wei Sun	wsun@vt.edu
* PURPOSE: Declare the COutputList Class, COutputList decides how to output 
*          data file and reporting file, it is the main control of Copasi 
*          output module
*****************************************************************************/

#ifndef COPASI_COutputList
#define COPASI_COutputList

#include <iostream>

#include "copasi.h"
#include "utilities/CCopasiVector.h"
#include "COutput.h"
#include "model/CModel.h"

class CCOutput: public CCopasiVector < COutput >
{
 public:
  CCOutput();
  ~CCOutput();
 private:
  C_INT16 IsInsertAllowed(const COutput & src);
};

class COutputList
{
 private:

  CCOutput *mList;

  CModel Model;			// Temperorary use for testing 

 public:

  /**
   *	Default constructor. 
   */
  COutputList();

  /**
   *	Deconstructor
   */
  ~COutputList();

  /**
   *	User defined constructor. 
   *	Read config variables from input configburg buffer
   *  @param configbuffer: reference of the config buffer.
   */
  COutputList(CReadConfig &configbuffer);

  /**
   *  Return the pointer of the COutputLine that can be output at the same time. 
   *  @return mList
   *  @see mList
   */
  CCOutput * GetList() const;

  /**
   *  Add new OutputLine object to a list
   *  @param newLine constant reference to COutputLine .
   *  @see COutputLine Class
   */
  void AddOutput(COutput &newOutput);

  /**
   *  Saves the contents of the object to a CWriteConfig object.
   *  (Which usually has a file attached but may also have socket)
   *  @param pconfigbuffer reference to a CWriteConfig object.
   *  @return mFail
   *  @see mFail
   */
  C_INT32 Save(CWriteConfig & configbuffer);

  /**
   *  Loads an object with data coming from a CReadConfig object.
   *  (CReadConfig object reads an input stream)
   *  @param pconfigbuffer reference to a CReadConfig object.
   *  @param searchName refernece to a the time of seach section,
   *		   for example: Interactive time course		
   *  @return mFail
   *  @see mFail
   */
  C_INT32 Load(CReadConfig & configbuffer);

  void Init();

  void Delete();

  /*
   * print the time course dynamic data file
   */		
  void CCopasi_Dyn(ofstream &fout);

  /*
   * print the steady state data file
   */		
  void CCopasi_SS(ofstream &fout);

  /*
   * print the reporting data file
   */
  void CCopasi_Rep(ofstream &fout);

  /**
   *	Assigns model in the Outputlist
   */
  void setModel(const CModel &model);

  /**
   *	Assign the pointer to each datum object in the output
   */
  void Compile(string &name);

};

#endif	//COutputList
