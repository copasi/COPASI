/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/output/Attic/COutput.h,v $
   $Revision: 1.26 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/06/22 16:11:47 $
   End CVS Header */

/*****************************************************************************
 * PROGRAM NAME: COutput.h
 * PROGRAMMER: Wei Sun wsun@vt.edu
 * PURPOSE: Declare the COutput Class, each COutput object contains 
 *        all the COutputLine objects that can be output at the same time   
 *****************************************************************************/

#ifndef COPASI_COutput
#define COPASI_COutput

#include <iostream>
#include "COutputLine.h" 
//#include "report/CCopasiContainer.h"

class CSteadyStateTask;
class CCopasiContainer;

class COutput : public CCopasiContainer
  {
  private:
    /**
     *  Datum lines can be output in the same time.
     * @supplierCardinality 0..*
     */
    CCopasiVectorS < COutputLine > mOutputLines;

    /**
     *  The type of output trigger
     *  The types of trigger event are: {TIME_INT, TIME_POINT, TIME_END}
     */
    C_INT16 mTriggerType;

    /**
     * 1 if time-course is to be calculated
     */
    C_INT16 Dyn;

    /**
     * 1 if titles are to be output 
     */
    C_INT16 DynTitles;

    /**
     * 1 if titles are to be put in quotes in the Dyn File 
     */
    C_INT16 DynQuotes;

    /**
     * width of the columns in the Dyn file 
     */
    C_INT16 DynColWidth;

    /**
     * character to separate columns in Dyn file 
     */
    C_INT16 DynSeparator;

    /**
     * 1 if steady state is to be calculated 
     */
    C_INT16 SS;

    /**
     * 1 if titles are to be output in the SS file 
     */
    C_INT16 SSTitles;

    /**
     * 1 if titles are to be put in quotes in the SS file 
     */
    C_INT16 SSQuotes;

    /**
     * width of the columns in the SS file 
     */
    C_INT16 SSColWidth;

    /**
     * character to separate columns in SS file 
     */
    C_INT16 SSSeparator;

    /**
     * 0-normal 1-Integr.only 2-Newton only 3-back.integr.only 
     */
    C_INT16 SSStrategy;

    /**
     * 1 if report is to be written 
     */
    C_INT16 Rep;

    /**
     * 1 if report is to include structural analysis 
     */
    C_INT16 RepStruct;

    /**
     * 1 if report is to include stability analysis 
     */
    C_INT16 RepStab;

    /**
     * 1 if report is to include MCA 
     */
    C_INT16 RepMCA;

    /**
     * 1 if report is to include the comment 
     */
    C_INT16 RepComments;

    /**
     * Concentration Unit
     */
    std::string ConcUnit;

    /**
     * Time Unit
     */
    std::string TimeUnit;

    /**
     * Pointer to a ss_solution when each 
     **/
    CSteadyStateTask *mSolution;

    /**
     * Print each line of the header in the reporting file
     */
    void repHeaderLine(std::ostream &fout, int width, std::string OutStr) const;

    int CheckEquilibrium();

    COutputLine * findOrCreateOutputLine(std::string nameOfLine);

  public:

    /**
     * Reset output data file and reporting file configure variable
     */
    void resetConfiguration();

    void setDynConfiguration(C_INT16 Dyn = 1,
                             C_INT16 DynTitles = 0,
                             C_INT16 DynQuotes = 0,
                             C_INT16 DynColWidth = 12,
                             C_INT16 DynSeparator = 32);

    void noDynConfiguration() {setDynConfiguration(0);}

    /**
     * Default constructor. 
     * @param const std::string & name (default: "NoName")
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    COutput(const std::string & name = "NoName",
            const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor. 
     * @param const COutput & src,
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    COutput(const COutput & src,
            const CCopasiContainer * pParent = NULL);

    /**
     *  Destructor. 
     */
    ~COutput();

    void init();

    void cleanup();

    /**
     *  Return the pointer of the COutputLine that can be output at the same time. 
     *  @return mList
     *  @see mList
     */
    const CCopasiVectorS < COutputLine > & getList() const;

    /**
     *  Add new OutputLine object to a list
     *  @param newLine constant reference to COutputLine .
     *  @see COutputLine Class
     */
    void addLine(COutputLine &newLine);

    /**
     *  Add new output datum object to a the output line
     *  with the given name.
     */
    void addDatum(std::string nameOfLine,
                  std::string title,
                  C_INT32 typeOfOutput,
                  std::string IName = "",
                  std::string JName = "");

    /**
     *  Return the trigger event type of the COutput.
     *  @return mTriggerType
     *  @see mTRiggerType
     */
    C_INT16 getTriggerType() const;

#if 0
    /**
     *  Set the type of trigger output event
     *  @param triggerType constant reference to a integer type.
     *  @see mTriggerType
     */
    void setList(const C_INT16 triggerType);
#endif

    /**
     *  Saves the contents of the object to a CWriteConfig object.
     *  (Which usually has a file attached but may also have socket)
     *  @param pconfigbuffer reference to a CWriteConfig object.
     *  @return mFail
     *  @see mFail
     */ 
    //    C_INT32 save(CWriteConfig & configbuffer);

    /**
     *  Loads an object with data coming from a CReadConfig object.
     *  (CReadConfig object reads an input stream)
     *  @param pconfigbuffer reference to a CReadConfig object.
     *  @param searchName refernece to a the time of seach section,
     *     for example: Interactive time course  
     *  @return mFail
     *  @see mFail
     */
    C_INT32 load(CReadConfig & configbuffer);

    /**
     *  Dummy method.
     */ 
    //    const std::string & getName() const;

    /**
     * print the titles of the steady-state data file
     */
    void sSOutputTitles(std::ostream &fout, std::string &SSName, C_INT16 SSSeparator, C_INT16 SSColWidth, C_INT16 SSQuotes) const;

    /**
     * print the mpValue of Object in the steady-state data file
     */
    void sSOutputData(std::ostream &fout, std::string &SSName, C_INT16 SSSeparator, C_INT16 SSColWidth, C_INT16 SSQuotes) const;

    /**
     * print the titles of the time couse data file
     */
    void dynOutputTitles(std::ostream &fout, std::string &DynName, C_INT16 DynSeparator, C_INT16 DynColWidth, C_INT16 DynQuotes) const;

    /**
     * print the mpValue of Object in the time course data file
     */
    void dynOutputData(std::ostream &fout, std::string &DynName, C_INT16 DynSeparator, C_INT16 DynColWidth, C_INT16 DynQuotes) const;

    /**
     * print the header of the reporting file
     */
    void repHeader(std::ostream &fout) const;

    /**
     * Output the comments to the output reporting file
     */
    void repComments(std::ostream &fout) const;

    /**
     * print the parameters of the simulation
     */
    void repParams(std::ostream &fout) const;

    /**
     * print the structural analysis
     */
    void repStruct(std::ostream &fout) const;

    /**
     * print the results of the stability analysis
     */
    void repStability(std::ostream &fout) const;

    /**
     * print the results of the MCA
     */
    void repMCA(std::ostream &fout) const;

    /**
     * print the titles of the time-course data file
     */
    void dynOutputTitles(std::ostream &fout, std::string &DynName) const;

    /**
     * print a line of data (one time point) on the time-course data file
     */
    void dynOutputData(std::ostream &fout, std::string &DynName) const;

    /**
     * print the titles of the steady-state data file
     */
    void sSOutputTitles(std::ostream &fout, std::string &SSName) const;

    /**
     * print a line of data (one iteration) on the steady-state data file
     */
    void sSOutputData(std::ostream &fout, std::string &SSName) const;

    /**
     * Output the model title to the output reporting file
     */
    void repTitle(std::ostream &fout) const;

    /**
     * Assign the pointer to each datum object for time course
     */
    void compile(const std::string & name, CModel *model, CState *state);

    /**
     * Assign the pointer to each datum object for steady state
     */
    void compile(const std::string & name, CModel *model, CSteadyStateTask *soln);

    /*
     * print the time course dynamic data file
     */
    void copasiDyn(std::ostream &fout, int time) const;

    /*
     * print the steady state data file
     */
    void copasiSS(std::ostream &fout) const;

    /*
     * print the reporting data file
     */
    void copasiRep(std::ostream &fout)const;

    /**
     * Write output control variables from input configburg buffer
     *  @param configbuffer: reference of the config buffer.
     */
    C_INT32 writeDefaultVar(CWriteConfig &configbuffer);

    /**
     * Read output control variables from input configburg buffer
     *  @param configbuffer: reference of the config buffer.
     */
    C_INT32 readDefaultVar(CReadConfig &configbuffer);

    /**
     * print the results of the steady-state simulation
     */
    void repSS(std::ostream &fout) const;
  };

#endif //COutput.h
