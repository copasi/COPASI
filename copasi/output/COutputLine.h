/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/output/Attic/COutputLine.h,v $
   $Revision: 1.22 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/05/13 13:14:21 $
   End CVS Header */

/*****************************************************************************
 * PROGRAM NAME: COutputLine.h
 * PROGRAMMER: Wei Sun wsun@vt.edu
 * PURPOSE: Declare the COutputLine Class, each COutputLine object contains 
 *        all the CDatum object that can be output at the same line in a given
 *     time   
 *****************************************************************************/

#ifndef COPASI_COutputLine
#define COPASI_COutputLine

#include <iostream>
#include <fstream>

#include "CDatum.h"
#include "report/CCopasiContainer.h"
#include "utilities/CCopasiVector.h"

class CState;
class CSteadyStateTask;
class CReadConfig;
class CWriteConfig;
class CState;
class CModel;
class CSteadyStateTask;

class COutputLine : public CCopasiContainer
  {
  private:
    /**
     *  Datum can be output in the same line.
     * @supplierCardinality 0..*
     */
    CCopasiVectorS < CDatum > mLine;

  public:

    /**
     * Default constructor. 
     * @param const std::string & name (default: "NoName")
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    COutputLine(const std::string & name = "NoName",
                const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor. 
     * @param const COutputLineg & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    COutputLine(const COutputLine & src,
                const CCopasiContainer * pParent = NULL);

    /**
     *  Destructor. 
     */
    ~COutputLine();

    void init();

    void cleanup();

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
     *     for example: Interactive time course  
     *  @return mFail
     *  @see mFail
     */
    C_INT32 load(CReadConfig & configbuffer, std::string& searchName);

    /**
     *  Dummy method.
     */ 
    //    const std::string & getName() const;

    /**
     *  Complie the mpValue in each output line
     */ 
    //void compileOutputLine(COutputList &outputList);

    /**
     * print the titles of the steady-state data file
     */
    void sSOutputTitles(std::ostream &fout, C_INT16 SSSeparator, C_INT16 SSColWidth, C_INT16 SSQuotes);

    /**
     * print the mpValue of each Object in the steady-state data file
     */
    void sSOutputData(std::ostream &fout, C_INT16 SSSeparator, C_INT16 SSColWidth, C_INT16 SSQuotes);

    /**
     * print the titles of the time couse data file
     */
    void dynOutputTitles(std::ostream &fout, C_INT16 DynSeparator, C_INT16 DynColWidth, C_INT16 DynQuotes);

    /**
     * print the mpValue of Object in the time course data file
     */
    void dynOutputData(std::ostream &fout, C_INT16 DynSeparator, C_INT16 DynColWidth, C_INT16 DynQuotes);

    /**
     *  Sets the name of this line, (For example: Interactive time course)
     *  @param title constant reference to a string.
     */
    bool setName(std::string LineName);

    /**
     *  Assign the pointer to each datum object in the output line for time course
     */
    void compile(const std::string & name, CModel *model, CState *state);

    /**
     *  Assign the pointer to each datum object in the output line for steady State
     */
    void compile(const std::string & name, CModel *model, CSteadyStateTask *soln);
  };

#endif // COutputLine
