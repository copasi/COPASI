/*****************************************************************************
* PROGRAM NAME: COutput.h
* PROGRAMMER: Wei Sun	wsun@vt.edu
* PURPOSE: Declare the COutput Class, each COutput object contains 
*	       all the COutputLine objects that can be output at the same time			
*****************************************************************************/

#ifndef COPASI_COutput
#define COPASI_COutput

#include <iostream>
#include "COutputLine.h"
#include "trajectory/trajectory.h"


class COutputLine;

class COutput
{
 private:
  /**
   *  Datum lines can be output in the same time.
   * @supplierCardinality 0..*
   */
  CCopasiVectorS < COutputLine > mOutput;

  /**
   *  The type of output trigger
   *  The types of trigger event are: {TIME_INT, TIME_POINT, TIME_END}
   */
  C_INT16 mTriggerType;

  /**
   *	1 if time-course is to be calculated
   */
  C_INT16		Dyn;				

  /**
   *	1 if titles are to be output 
   */
  C_INT16		DynTitles;			

  /**
   *	1 if titles are to be put in quotes in the Dyn File 
   */
  C_INT16		DynQuotes;			

  /**
   *	width of the columns in the Dyn file 
   */
  C_INT16		DynColWidth;	

  /**
   *	character to separate columns in Dyn file 
   */
  C_INT16		DynSeparator;	

  /**
   *	1 if steady state is to be calculated 
   */
  C_INT16		SS;					 

  /**
   *	1 if titles are to be output in the SS file 
   */
  C_INT16		SSTitles;			

  /**
   *	1 if titles are to be put in quotes in the SS file 
   */
  C_INT16		SSQuotes;			 

  /**
   *	width of the columns in the SS file 
   */
  C_INT16		SSColWidth;			

  /**
   *	character to separate columns in SS file 
   */
  C_INT16		SSSeparator;		

  /**
   *	0-normal 1-Integr.only 2-Newton only 3-back.integr.only 
   */
  C_INT16		SSStrategy;			 

  /**
   *	1 if report is to be written 
   */
  C_INT16		Rep;				
	
  /**
   *	1 if report is to include structural analysis 
   */
  C_INT16		RepStruct;			 

  /**
   *	1 if report is to include stability analysis 
   */
  C_INT16		RepStab;			

  /**
   *	1 if report is to include MCA 
   */
  C_INT16		RepMCA;				 

  /**
   *	1 if report is to include the comment 
   */
  C_INT16		RepComments;		 

  /**
   *	Concentration Unit
   */
  string		ConcUnit;

  /**
   *	Time Unit
   */
  string		TimeUnit;

  /**
   * Pointer to a ss_solution when each 
   **/
  CSS_Solution  *mSolution;

  /**
   * the mathematical model 
   * :TODO: this should be removed SH
   */
  // CModel 		Model;			

  /**
   *	Reset output data file and reporting file configure variable
   */
  void reset();

  /**
   *	Print each line of the header in the reporting file
   */
  void repHeaderLine(ofstream &fout, int width, string OutStr);

  int CheckEquilibrium();

 public:

  /**
   *  Default constructor. 
   */
  COutput();

  /**
   *  Destructor. 
   */
  ~COutput();

  void init();

  void cleanup();

  /**
   *  Assignement operator. 
   *  Copies the contents from one COutput object to another.
   *  @param source reference to the recipient object.
   */
  COutput& operator=(const COutput &source);

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
  C_INT32 save(CWriteConfig & configbuffer);

  /**
   *  Loads an object with data coming from a CReadConfig object.
   *  (CReadConfig object reads an input stream)
   *  @param pconfigbuffer reference to a CReadConfig object.
   *  @param searchName refernece to a the time of seach section,
   *		   for example: Interactive time course		
   *  @return mFail
   *  @see mFail
   */
  C_INT32 load(CReadConfig & configbuffer);

  /**
   *  Dummy method.
   */	
  string getName() const {return "";}

  /**
   * print the titles of the steady-state data file
   */
  void sSOutputTitles(ofstream &fout, string &SSName, C_INT16 SSSeparator, C_INT16 SSColWidth, C_INT16 SSQuotes);

  /**
   * print the mpValue of Object in the steady-state data file
   */
  void sSOutputData(ofstream &fout, string &SSName, C_INT16 SSSeparator, C_INT16 SSColWidth, C_INT16 SSQuotes, C_INT32 ss_solution);

  /**
   * print the titles of the time couse data file
   */
  void dynOutputTitles(ofstream &fout, string &DynName, C_INT16 DynSeparator, C_INT16 DynColWidth, C_INT16 DynQuotes);

  /**
   * print the mpValue of Object in the time course data file
   */
  void dynOutputData(ofstream &fout, string &DynName, C_INT16 DynSeparator, C_INT16 DynColWidth, C_INT16 DynQuotes);

  /**
   * print the header of the reporting file
   */
  void repHeader(ofstream &fout);

  /**
   *	Output the comments to the output reporting file
   */
  void repComments(ofstream &fout);

  /**
   *	print the parameters of the simulation
   */
  void repParams(ofstream &fout);
	
  /**
   *	print the structural analysis
   */		
  void repStruct(ofstream &fout); 
	
  /**
   *	print the results of the stability analysis
   */
  void repStability(ofstream &fout); 
	
  /**
   *	print the results of the MCA
   */
  void repMCA(ofstream &fout); 

  /**
   *	print the titles of the time-course data file
   */
  void dynOutputTitles(ofstream &fout, string &DynName); 
	
  /**
   *	print a line of data (one time point) on the time-course data file
   */
  void dynOutputData(ofstream &fout, string &DynName); 
	
  /**
   *	print the titles of the steady-state data file
   */
  void sSOutputTitles(ofstream &fout, string &SSName); 
	
  /**
   *	print a line of data (one iteration) on the steady-state data file
   */
  void sSOutputData(ofstream &fout, string &SSName, C_INT32 ss_solution); 

  /**
   *	Output the model title to the output reporting file
   */
  void repTitle(ofstream &fout);

  /**
   *	Assign the pointer to each datum object for time course
   */
  void compile(const string & name, CModel *model, CTrajectory *traj);

  /**
   *	Assign the pointer to each datum object for steady state
   */
  void compile(const string & name, CModel *model, CSS_Solution *soln);

  /*
   * print the time course dynamic data file
   */		
  void copasiDyn(ofstream &fout, int time);

  /*
   * print the steady state data file
   */		
  void copasiSS(ofstream &fout, C_INT32 ss_solution);

  /*
   * print the reporting data file
   */
  void copasiRep(ofstream &fout);

  /**
   *	Write output control variables from input configburg buffer
   *  @param configbuffer: reference of the config buffer.
   */
  C_INT32 writeDefaultVar(CWriteConfig &configbuffer);

  /**
   *	Read output control variables from input configburg buffer
   *  @param configbuffer: reference of the config buffer.
   */
  C_INT32 readDefaultVar(CReadConfig &configbuffer);

  /**
   * print the results of the steady-state simulation
   */
  void repSS(ofstream &fout);


};

#endif //COutput.h
