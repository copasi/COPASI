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

class CCOutputLine: public CCopasiVector < COutputLine >
{
 public:
  CCOutputLine();
  ~CCOutputLine();
 private:
  C_INT16 IsInsertAllowed(const COutputLine & src);
};


class COutput
{
 private:
  /**
   *  Datum lines can be output in the same time.
   */
  CCOutputLine * mOutput;

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
   * the mathematical model
   */
  CModel		Model;			

  /**
   *	Reset output data file and reporting file configure variable
   */
  void Reset();

  /**
   *	Print each line of the header in the reporting file
   */
  void Rep_Header_Line(ofstream &fout, int width, string OutStr);

 public:

  /**
   *  Default constructor. 
   */
  COutput();

  /**
   *  Destructor. 
   */
  ~COutput();

  void Init();

  void Delete();

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
  CCOutputLine * GetList() const;

  /**
   *  Add new OutputLine object to a list
   *  @param newLine constant reference to COutputLine .
   *  @see COutputLine Class
   */
  void AddLine(COutputLine &newLine);

  /**
   *  Return the trigger event type of the COutput.
   *  @return mTriggerType
   *  @see mTRiggerType
   */
  C_INT16 GetTriggerType() const;

#if 0
  /**
   *  Set the type of trigger output event
   *  @param triggerType constant reference to a integer type.
   *  @see mTriggerType
   */
  void SetList(const C_INT16 triggerType);
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
  void SS_OutputTitles(ofstream &fout, string &SSName, C_INT16 SSSeparator, C_INT16 SSColWidth, C_INT16 SSQuotes);

  /**
   * print the mpValue of Object in the steady-state data file
   */
  void SS_OutputData(ofstream &fout, string &SSName, C_INT16 SSSeparator, C_INT16 SSColWidth, C_INT16 SSQuotes);

  /**
   * print the titles of the time couse data file
   */
  void Dyn_OutputTitles(ofstream &fout, string &DynName, C_INT16 DynSeparator, C_INT16 DynColWidth, C_INT16 DynQuotes);

  /**
   * print the mpValue of Object in the time course data file
   */
  void Dyn_OutputData(ofstream &fout, string &DynName, C_INT16 DynSeparator, C_INT16 DynColWidth, C_INT16 DynQuotes);

  /**
   * print the header of the reporting file
   */
  void Rep_Header(ofstream &fout);

  /**
   *	Output the comments to the output reporting file
   */
  void Rep_Comments(ofstream &fout);

  /**
   *	print the parameters of the simulation
   */
  void Rep_Params(ofstream &fout);
	
  /**
   *	print the structural analysis
   */		
  void Rep_Struct(ofstream &fout); 
	
  /**
   *	print the results of the stability analysis
   */
  void Rep_Stability(ofstream &fout); 
	
  /**
   *	print the results of the MCA
   */
  void Rep_MCA(ofstream &fout); 

  /**
   *	print the titles of the time-course data file
   */
  void Dyn_OutputTitles(ofstream &fout, string &DynName); 
	
  /**
   *	print a line of data (one time point) on the time-course data file
   */
  void Dyn_OutputData(ofstream &fout, string &DynName); 
	
  /**
   *	print the titles of the steady-state data file
   */
  void SS_OutputTitles(ofstream &fout, string &SSName); 
	
  /**
   *	print a line of data (one iteration) on the steady-state data file
   */
  void SS_OutputData(ofstream &fout, string &SSName); 

  /**
   *	Output the model title to the output reporting file
   */
  void Rep_Title(ofstream &fout);

  /**
   *	Assign the pointer to each datum object in the list
   */
  void Compile(string &name, CModel &model);

  /*
   * print the time course dynamic data file
   */		
  void CCopasi_Dyn(ofstream &fout, int time);

  /*
   * print the steady state data file
   */		
  void CCopasi_SS(ofstream &fout, int time);

  /*
   * print the reporting data file
   */
  void CCopasi_Rep(ofstream &fout);

  /**
   *	Assigns model in the Outputlist
   */
  void setModel(const CModel &model);

  /**
   *	Write output control variables from input configburg buffer
   *  @param configbuffer: reference of the config buffer.
   */
  C_INT32 WriteDefaultVar(CWriteConfig &configbuffer);

  /**
   *	Read output control variables from input configburg buffer
   *  @param configbuffer: reference of the config buffer.
   */
  C_INT32 ReadDefaultVar(CReadConfig &configbuffer);

};

#endif //COutput.h
