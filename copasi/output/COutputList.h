/*****************************************************************************
 * PROGRAM NAME: COutputList.h
 * PROGRAMMER: Wei Sun wsun@vt.edu
 * PURPOSE: Declare the COutputList Class, COutputList decides how to output 
 *          data file and reporting file, it is the main control of Copasi 
 *          output module
 *****************************************************************************/

#ifndef COPASI_COutputList
#define COPASI_COutputList

#include <iostream>

#include "copasi.h"
#include "utilities/utilities.h"
#include "output/output.h"
#include "model/model.h"

class CState;

class COutputList
  {
  private:

    /**
     * @supplierCardinality 0..* 
     */
    CCopasiVectorS < COutput > mList;

  public:

    /**
     * Default constructor. 
     */
    COutputList();

    /**
     * Deconstructor
     */
    ~COutputList();

    /**
     * User defined constructor. 
     * Read config variables from input configburg buffer
     *  @param configbuffer: reference of the config buffer.
     */
    COutputList(CReadConfig &configbuffer);

    /**
     *  Return the pointer of the COutputLine that can be output at the same time. 
     *  @return mList
     *  @see mList
     */
    const CCopasiVectorS < COutput > & getList() const;

    /**
     *  Add new OutputLine object to a list
     *  @param newLine constant reference to COutputLine .
     *  @see COutputLine Class
     */
    void addOutput(COutput &newOutput);

    /**
     *  Saves the contents of the object to a CWriteConfig object.
     *  (Which usually has a file attached but may also have socket)
     *  @param pconfigbuffer reference to a CWriteConfig object.
     *  @return mFail
     *  @see mFail
     */
    C_INT32 save(CWriteConfig & configbuffer);

    /**
     *  Loads an object with data coming from a CReadConfig object.
     *  (CReadConfig object reads an input stream)
     *  @param pconfigbuffer reference to a CReadConfig object.
     *  @return mFail
     *  @see mFail
     */
    C_INT32 load(CReadConfig & configbuffer);

    void init();

    void cleanup();

    /*
     * print the time course dynamic data file
     */
    void copasiDyn(ofstream &fout, int time);

    /*
     * print the steady state data file
     */
    void copasiSS(ofstream &fout);

    /*
     * print the reporting data file
     */
    void copasiRep(ofstream &fout);

    /**
     * Assign the pointer to each datum object for time couse
     */
    void compile(const string & name, CModel * model, CState *state);

    /**
     * Assign the pointer to each datum object for steady state
     */
    void compile(const string & name, CModel *model, CSteadyStateTask *soln);
  };

#endif //COutputList
