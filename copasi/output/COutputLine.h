/*****************************************************************************
* PROGRAM NAME: COutputLine.h
* PROGRAMMER: Wei Sun	wsun@vt.edu
* PURPOSE: Declare the COutputLine Class, each COutputLine object contains 
*	       all the CDatum object that can be output at the same line in a given
*		   time			
*****************************************************************************/

#ifndef COPASI_COutputLine
#define COPASI_COutputLine

#include <iostream>
#include <fstream>

#include "CDatum.h"
#include "utilities/CCopasiVector.h"

class COutputLine
{
 private:
#ifdef XXXX
  class CCDatum: public CCopasiVector < CDatum >
    {
    public:
      CCDatum();
      ~CCDatum();
			
    private:
      C_INT16 isInsertAllowed(const CDatum & src);
    };
#endif // XXXX
  /**
   *  Datum can be output in the same line.
   */
  CCopasiVectorS < CDatum > mLine;

  /**
   *  Note: Temperaly use it 
   *	The name of outputline from configuration file, 
   *  such as "Interactive time course"
   */
  string mName;
	
 public:

  /**
   *  Default constructor. 
   */
  COutputLine();


  /**
   *  Destructor. 
   */
  ~COutputLine();

  void init();

  void cleanup();

  /**
   *  Assignement operator. 
   *  Copies the contents from one COutputLine object to another.
   *  @param source reference to the recipient object.
   */
  COutputLine& operator=(const COutputLine &source);

  /**
   *  Return the pointer of the CDatum that can be output at the same line. 
   *  @return mLine
   *  @see mLine
   */
  const CCopasiVectorS < CDatum > & getLine() const;

  /**
   *  Add new data object to a line
   *  @param newDatum constant reference to CDatum.
   *  @see CDatum Class
   */
  void addDatum(CDatum & newDatum);

  /**
   *  Saves the contents of the object to a CWriteConfig object.
   *  (Which usually has a file attached but may also have socket)
   *  @param pconfigbuffer reference to a CWriteConfig object.
   *  @return mFail
   *  @see mFail
   */
  C_INT32 save(CWriteConfig & configbuffer);

  C_INT32 load(CReadConfig & configbuffer);
  /**
   *  Loads an object with data coming from a CReadConfig object.
   *  (CReadConfig object reads an input stream)
   *  @param pconfigbuffer reference to a CReadConfig object.
   *  @param searchName refernece to a the time of seach section,
   *		   for example: Interactive time course		
   *  @return mFail
   *  @see mFail
   */
  C_INT32 load(CReadConfig & configbuffer, string& searchName);

  /**
   *  Dummy method.
   */	
  string getName() const {return mName;}

  /**
   *  Complie the mpValue in each output line
   */
  //void compileOutputLine(COutputList &outputList);

  /**
   * print the titles of the steady-state data file
   */
  void sSOutputTitles(ofstream &fout, C_INT16 SSSeparator, C_INT16 SSColWidth, C_INT16 SSQuotes);

  /**
   * print the mpValue of each Object in the steady-state data file
   */
  void sSOutputData(ofstream &fout, C_INT16 SSSeparator, C_INT16 SSColWidth, C_INT16 SSQuotes);

  /**
   * print the titles of the time couse data file
   */
  void dynOutputTitles(ofstream &fout, C_INT16 DynSeparator, C_INT16 DynColWidth, C_INT16 DynQuotes);

  /**
   * print the mpValue of Object in the time course data file
   */
  void dynOutputData(ofstream &fout, C_INT16 DynSeparator, C_INT16 DynColWidth, C_INT16 DynQuotes);

  /**
   *  Sets the name of this line, (For example: Interactive time course)
   *  @param title constant reference to a string.
   */
  void setName(string LineName);

  /**
   *	Assign the pointer to each datum object in the output line
   */
  void compile(string &name, CModel &model);
};

#endif // COutputLine
