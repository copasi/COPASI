/*****************************************************************************
* PROGRAM NAME: COutput.cpp
* PROGRAMMER: Wei Sun	wsun@vt.edu
* PURPOSE: COutput Class Implemention
*****************************************************************************/

#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <time.h>

#include "copasi.h"
#include "COutput.h"
#include "utilities/utilities.h"
#include "model/model.h"

/**
 *  Default constructor. 
 */
COutput::COutput()
{
  Dyn = 0;
  DynTitles = 0;
  DynQuotes = 0;
  DynColWidth = 0;
  DynSeparator = 0;
  SS = 0;
  SSTitles = 0;
  SSQuotes = 0;
  SSColWidth = 0;
  SSSeparator = 0;
  SSStrategy = 0;
  Rep = 0;
  RepStruct = 0;
  RepStab = 0;
  RepMCA = 0;
  RepComments = 1;	//???? No such configure variable in *.GPS files

  mOutput = NULL;
}

void COutput::init()
{
  mOutput = new CCOutputLine;
}

void COutput::cleanup()
{
  if (mOutput) delete mOutput;
  mOutput = NULL;
}

/**
 *  Destructor. 
 */
COutput::~COutput()
{
  //	cleanup();
}

/**
 *	Reset output data file and reporting file configure variables
 */
void COutput::reset()
{
  Dyn = 0;
  DynTitles = 0;
  DynQuotes = 0;
  DynColWidth = 0;
  DynSeparator = 0;
  SS = 0;
  SSTitles = 0;
  SSQuotes = 0;
  SSColWidth = 0;
  SSSeparator = 0;
  SSStrategy = 0;
  Rep = 0;
  RepStruct = 0;
  RepStab = 0;
  RepMCA = 0;
  RepComments = 0;
}

/**
 *  Assignement operator. 
 *  Copies the contents from one COutput object to another.
 *  @param source reference to the recipient object.
 */
COutput& COutput::operator=(const COutput &source)
{
  mOutput = source.mOutput;

  return *this;
}

/**
 *  Return the pointer of the COutputLine that can be output at the same time. 
 *  @return mOutput
 *  @see mOutput
 */
CCOutputLine * COutput::getList() const
{
  return mOutput;
}

/**
 *  Add new OutputLine object to a list
 *  @param newLine constant reference to COutputLine .
 *  @see COutputLine Class
 */
void COutput::addLine(COutputLine &newLine)
{
  if (!mOutput) init();
  mOutput->add(newLine);
}

/**
 *  Saves the contents of the object to a CWriteConfig object.
 *  (Which usually has a file attached but may also have socket)
 *  @param pconfigbuffer reference to a CWriteConfig object.
 *  @return mFail
 *  @see mFail
 */
C_INT32 COutput::save(CWriteConfig & configbuffer)
{
  C_INT32 Fail = 0;

  writeDefaultVar(configbuffer);

  if ((Fail = mOutput->save(configbuffer)))
    return Fail;

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
C_INT32 COutput::load(CReadConfig & configbuffer)
{
  C_INT32 Fail = 0;

  readDefaultVar(configbuffer);
	
  string InteractiveTimeCourse = "Interactive time course";
  string TimeCourse = "Time-course output";
  string SteadyState = "Steady-state output";

  COutputLine newLine1;
  newLine1.load(configbuffer, InteractiveTimeCourse);
  addLine(newLine1);

  COutputLine newLine2;
  newLine2.load(configbuffer, TimeCourse);
  addLine(newLine2);

  COutputLine newLine3;
  newLine3.load(configbuffer, SteadyState);
  addLine(newLine3);

  return Fail;
}

/**
 *	print the titles of the steady-state data file
 */
void COutput::sSOutputTitles(ofstream &fout, string &SSName, C_INT16 SSSeparator, C_INT16 SSColWidth, C_INT16 SSQuotes) 
{
  string Name;

  for (unsigned C_INT32 i = 0; i < mOutput->size(); i++)
    {
      Name = (*mOutput)[i].getName();
      if (Name == SSName)
	(*mOutput)[i].sSOutputTitles(fout, SSSeparator, SSColWidth, SSQuotes);
    }

}

/**
 *	print mpValue of each Object in the steady-state data file
 */
void COutput::sSOutputData(ofstream &fout, string &SSName, C_INT16 SSSeparator, C_INT16 SSColWidth, C_INT16 SSQuotes) 
{
  string Name;

  for (unsigned C_INT32 i = 0; i < mOutput->size(); i++)
    {
      Name = (*mOutput)[i].getName();
      if (Name == SSName)
	(*mOutput)[i].sSOutputData(fout, SSSeparator, SSColWidth, SSQuotes);
    }
}

/**
 * print the titles of the time couse data file
 */
void COutput::dynOutputTitles(ofstream &fout, string &DynName, C_INT16 DynSeparator, C_INT16 DynColWidth, C_INT16 DynQuotes)
{
  string Name;

  for (unsigned C_INT32 i = 0; i < mOutput->size(); i++)
    {
      Name = (*mOutput)[i].getName();
      if (Name == DynName)
	(*mOutput)[i].dynOutputTitles(fout, DynSeparator, DynColWidth, DynQuotes);
    }

}

/**
 * print the mpValue of Object in the time course data file
 */
void COutput::dynOutputData(ofstream &fout, string &DynName, C_INT16 DynSeparator, C_INT16 DynColWidth, C_INT16 DynQuotes)
{
  string Name;

  for (unsigned C_INT32 i = 0; i < mOutput->size(); i++)
    {
      Name = (*mOutput)[i].getName();
      if (Name == DynName)
	(*mOutput)[i].dynOutputData(fout, DynSeparator, DynColWidth, DynQuotes);
    }

}

/**
 *	Assign the pointer to each datum object in the output
 */
void COutput::compile(string &name, CModel &model)
{

  for (unsigned C_INT32 i = 0; i < mOutput->size(); i++)
    {
      (*mOutput)[i].compile(name, model);
    }
}

/**
 *	Output the comments to the output reporting file
 */
void COutput::repComments(ofstream &fout)
{

  fout << Model.getComments() << endl;
}

/**
 *	Output the model title to the output reporting file
 */
void COutput::repTitle(ofstream &fout)
{

  fout << Model.getTitle() << endl << endl;
}

/**
 *	Print each line of the header in the reporting file
 */
void COutput::repHeaderLine(ofstream &fout, int width, string OutStr)
{
  int pre, suf, i;
  string Str = "*";

  pre = (width - OutStr.length()) / 2;
  suf = width - pre - OutStr.length();

  for (i = 0; i < pre; i++)
    Str += ' ';

  Str += OutStr;

  for (i = 0; i < suf; i++)
    Str += ' ';

  Str += "*";

  fout << Str << endl;
}



/**
 *	print the header of the reporting file
 */
void COutput::repHeader(ofstream &fout)
{
  string TimeStamp, TimeStr;
  int width, i;

  struct tm *newtime;
  time_t aclock;

  // Get time in seconds
  time( &aclock );
  // Convert time to struct tm form
  newtime = localtime( &aclock );
  TimeStr = asctime( newtime );
  TimeStamp = TimeStr.substr(0, TimeStr.length()-1);

  string VersionString = "Copasi Version " + Copasi.ProgramVersion.getVersion();

  width = (VersionString.length() > TimeStamp.length()) ? VersionString.length():TimeStamp.length();
  // width = max(width, ArchString.length());

  // write a full line with stars
  for (i = 0; i < width+4; i++)
    fout << "*";
  fout << endl;

  repHeaderLine(fout, width+2, VersionString);
  //repHeaderLine(fout, width, ArchString);
  repHeaderLine(fout, width+2, TimeStamp);

  for (i = 0; i < width+4; i++)
    fout << "*";
  fout << endl << endl;

}

/**
 *	print the parameters of the simulation
 */
void COutput::repParams(ofstream &fout)
{
  string StrOut;
  unsigned C_INT32 i, j;

  StrOut = "KINETIC PARAMETERS";
  fout << endl << StrOut << endl;

  // Set Float manipulators
  fout.setf(ios::scientific, ios::floatfield);
  fout.setf(ios::showpoint);
	
  for (i = 0; i < Model.getReactions().size(); i++)
    {
	  
      StrOut = Model.getReactions()[i].getName();
      fout << StrOut << " (";

      StrOut = Model.getReactions()[i].getFunction().getName();
      fout << StrOut << ")" << endl;

      for (j = 0; j < Model.getReactions()[i].getId2Parameters().size(); j++)
	{

	  fout << " " << Model.getReactions()[i].getId2Parameters()[j].getIdentifierName() << " =  ";
	  fout << setprecision(4) << Model.getReactions()[i].getId2Parameters()[j].getValue();
	  fout << endl;
		
	}
    }

  fout << endl << "COMPARTMENTS" << endl;

  for( i=0; i< Model.getCompartments()->size(); i++ )
    {
      fout << "V(" << (*Model.getCompartments())[i].getName() << ") =  ";
      fout << setprecision(4) << (*Model.getCompartments())[i].getVolume();
      fout << endl;
    }		

  fout << endl;
}

/**
 *	print the structural analysis
 */
void COutput::repStruct(ofstream &fout)
{
  unsigned C_INT32 i, j;
  // determine the kernel of the stoichiometry matrix
  //Model.getKernel();

  fout << endl << "STRUCTURAL ANALYSIS" << endl;

  if (Model.getDimension() > 0)
    {
      fout << endl << "Rank of the stoichiometry matrix: " << Model.getDimension() << endl;
    }

  fout << endl << "key for step (column) numbers: "<< endl;

  for (i = 0; i < Model.getReactions().size(); i++)
    {
      fout << setw(2) << i << " - ";
      fout << Model.getReactions()[i].getName();
      fout << endl;
    }

  fout << endl << "REDUCED STOICHIOMETRY MATRIX" << endl;

  for (i = 0; i < Model.getReactions().size(); i++)
    if (i)	fout << setw(4) << i;
    else fout << setw(16) << i;

  fout << endl;

  for (i = 0; i < Model.getReactions().size(); i++)
    {
      if (i) fout << setw(4) << "----";
      else fout << setw(15) << "----";
    }

  fout << "--" << endl;

  // Set Left Justification
  fout.setf(ios::left);

  for (i = 0; i < Model.getMetabolitesInd().size(); i++)
    {
      fout << setw(11) << Model.getMetabolitesInd()[i]->getName() << "|";

      for (j = 0; j < Model.getReactions().size(); j++)
		fout << setprecision(1) << setw(10) << Model.getRedStoi()[i][j];
      fout << endl;
    }

  fout << endl << endl << "INVERSE OF THE REDUCTION MATRIX" << endl;

  // Restore Justification
  fout.unsetf(ios::left);

  for (i = 0; i < Model.getMetabolitesInd().size(); i++)
    {
      if (i)	fout << setw(4) << i;
      else fout << setw(15) << i;
    }

  fout << endl;


  for (i = 0; i < Model.getMetabolitesInd().size(); i++)
    if (i) fout << setw(4) << "----";
    else fout << setw(15) << "----";

  fout << "--" << endl;

  // Set Left Justification
  fout.setf(ios::left);

  for (i = 0; i < Model.getMetabolitesInd().size(); i++)
    {
      fout << setw(11) << Model.getMetabolites()[i]->getName() << "|";

      //for (j = 0; j < Model.getMetabolitesInd().size(); j++)
      //		fout << setprecision(1) << setw(10) << Model.getRedStoi()[i][j];
      fout << endl;
    }

  fout << endl;

  if (Model.getMoieties()->size() > 0)
    {
      fout << endl << "CONSERVATION RELATIONSHIPS" << endl;
		
      for (i = 0; i < Model.getMoieties()->size(); i++)
	{
	  fout << (*Model.getMoieties())[i].getDescription() << " = " ;
	  fout << (*Model.getMoieties())[i].getNumber() << endl;

	}
    }
  fout << endl;
}

/**
 *	print the results of the stability analysis
 */
void COutput::repStability(ofstream &fout)
{
}

/**
 *	print the results of the MCA
 */
void COutput::repMCA(ofstream &fout)
{
}

/**
 *	print the titles of the time-course data file
 */
void COutput::dynOutputTitles(ofstream &fout, string &DynName)
{
  for (unsigned C_INT32 i = 0; i < mOutput->size(); i++)
    {
      (*mOutput)[i].dynOutputTitles(fout, DynSeparator, DynColWidth, DynQuotes);
    }

}

/**
 *	print a line of data (one time point) on the time-course data file
 */
void COutput::dynOutputData(ofstream &fout, string &DynName)
{
  for (unsigned C_INT32 i = 0; i < mOutput->size(); i++)
    {
      (*mOutput)[i].sSOutputData(fout, DynSeparator, DynColWidth, DynQuotes);
    }

}

/**
 *	print the titles of the steady-state data file
 */
void COutput::sSOutputTitles(ofstream &fout, string &SSName)
{

  for (unsigned C_INT32 i = 0; i < mOutput->size(); i++)
    {
      if (SSName == (*mOutput)[i].getName())
	(*mOutput)[i].sSOutputTitles(fout, SSSeparator, SSColWidth, SSQuotes);
    }
}

/**
 *	print a line of data (one iteration) on the steady-state data file
 */
void COutput::sSOutputData(ofstream &fout, string &SSName)
{
  for (unsigned C_INT32 i = 0; i < mOutput->size(); i++)
    {
      if (SSName == (*mOutput)[i].getName())
	(*mOutput)[i].sSOutputData(fout, SSSeparator, SSColWidth, SSQuotes);
    }
}

/*
 *	print the reporting data file
 */
void COutput::copasiRep(ofstream &fout)
{
  repHeader(fout);

  repTitle(fout);

  if (RepComments) repComments(fout);
  if (RepStruct) repStruct(fout);
#if 0
  if (RepStab) repStability(fout);
  if (RepMCA)	repMCA(fout);
#endif
  repParams(fout);

}

/*
 * print the steady state data file
 */
void COutput::copasiSS(ofstream &fout, int time)
{
  string SSName = "Steady-state output";

  if (!time)
  {
	if (SSTitles) sSOutputTitles(fout, SSName);
  }
  else sSOutputData(fout, SSName);
}

/*
 * print the time course dynamic data file
 */
void COutput::copasiDyn(ofstream &fout, int time)
{
  string DynName = "Time-course output";

  if (!time) 
  {
	  if (DynTitles) dynOutputTitles(fout, DynName);
  }
  else dynOutputData(fout, DynName);
}


/**
 *	Read config variables from input configburg buffer
 *  @param configbuffer: reference of the config buffer.
 */
C_INT32 COutput::readDefaultVar(CReadConfig &configbuffer)
{
  C_INT32	Fail = 0;

  if ((Fail = configbuffer.getVariable("Dynamics", "C_INT16",
				       (void *) &Dyn,
				       CReadConfig::LOOP)))
    return Fail;

  if ((Fail = configbuffer.getVariable("SteadyState", "C_INT16",
				       (void *) &SS,
				       CReadConfig::SEARCH)))
    return Fail;

  if ((Fail = configbuffer.getVariable("Report", "C_INT16",
				       (void *) &Rep,
				       CReadConfig::SEARCH)))
    return Fail;

  if ((Fail = configbuffer.getVariable("DynTitles", "C_INT16",
				       (void *) &DynTitles,
				       CReadConfig::SEARCH)))
    return Fail;

  if ((Fail = configbuffer.getVariable("SSTitles", "C_INT16",
				       (void *) &SSTitles,
				       CReadConfig::SEARCH)))
    return Fail;

  if ((Fail = configbuffer.getVariable("DynQuotes", "C_INT16",
				       (void *) &DynQuotes,
				       CReadConfig::SEARCH)))
    return Fail;

  if ((Fail = configbuffer.getVariable("SSQuotes", "C_INT16",
				       (void *) &SSQuotes,
				       CReadConfig::SEARCH)))
    return Fail;

  if ((Fail = configbuffer.getVariable("DynColWidth", "C_INT16",
				       (void *) &DynColWidth,
				       CReadConfig::SEARCH)))
    return Fail;

  if ((Fail = configbuffer.getVariable("SSColWidth", "C_INT16",
				       (void *) &SSColWidth,
				       CReadConfig::SEARCH)))
    return Fail;

  if ((Fail = configbuffer.getVariable("DynSeparator", "C_INT16",
				       (void *) &DynSeparator,
				       CReadConfig::SEARCH)))
    return Fail;

  if ((Fail = configbuffer.getVariable("SSSeparator", "C_INT16",
				       (void *) &SSSeparator,
				       CReadConfig::SEARCH)))
    return Fail;

  if ((Fail = configbuffer.getVariable("SSStrategy", "C_INT16",
				       (void *) &SSStrategy,
				       CReadConfig::SEARCH)))
    return Fail;

  try 
    {
      Fail = configbuffer.getVariable("RepComments", "C_INT16",
				      (void *) &RepComments,
				      CReadConfig::SEARCH);
    }
  
  catch (CCopasiException Exception)
    {
      if ((MCReadConfig + 1) == Exception.getMessage().getNumber())
	RepComments = 0;
      else
	throw Exception;
    }
  
  if ((Fail = configbuffer.getVariable("RepStructuralAnalysis", "C_INT16",
				       (void *) &RepStruct,
				       CReadConfig::LOOP)))
    return Fail;

  if ((Fail = configbuffer.getVariable("RepStabilityAnalysis", "C_INT16",
				       (void *) &RepStab,
				       CReadConfig::SEARCH)))
    return Fail;

  if ((Fail = configbuffer.getVariable("RepMCA", "C_INT16",
				       (void *) &RepMCA,
				       CReadConfig::SEARCH)))
    return Fail;


  // Note:: there is no variable controlling comments output
  //		  in current configure file
  return Fail;
}


/**
 *	Write output control variables from input configburg buffer
 *  @param configbuffer: reference of the config buffer.
 */
C_INT32 COutput::writeDefaultVar(CWriteConfig &configbuffer)
{
  C_INT32	Fail = 0;

  if ((Fail = configbuffer.setVariable("Dynamics", "C_INT16",
				       &Dyn)))
    return Fail;

  if ((Fail = configbuffer.setVariable("SteadyState", "C_INT16",
				       &SS)))
    return Fail;

  if ((Fail = configbuffer.setVariable("Report", "C_INT16",
				       &Rep)))
    return Fail;

  if ((Fail = configbuffer.setVariable("DynTitles", "C_INT16",
				       &DynTitles)))
    return Fail;

  if ((Fail = configbuffer.setVariable("SSTitles", "C_INT16",
				       &SSTitles)))
    return Fail;

  if ((Fail = configbuffer.setVariable("DynQuotes", "C_INT16",
				       &DynQuotes)))
    return Fail;

  if ((Fail = configbuffer.setVariable("SSQuotes", "C_INT16",
				       &SSQuotes)))
    return Fail;

  if ((Fail = configbuffer.setVariable("DynColWidth", "C_INT16",
				       &DynColWidth)))
    return Fail;

  if ((Fail = configbuffer.setVariable("SSColWidth", "C_INT16",
				       &SSColWidth)))
    return Fail;

  if ((Fail = configbuffer.setVariable("DynSeparator", "C_INT16",
				       &DynSeparator)))
    return Fail;

  if ((Fail = configbuffer.setVariable("SSSeparator", "C_INT16",
				       &SSSeparator)))
    return Fail;

  if ((Fail = configbuffer.setVariable("SSStrategy", "C_INT16",
				       &SSStrategy)))
    return Fail;

  if ((Fail = configbuffer.setVariable("RepComments", "C_INT16",
				       &RepComments)))
    return Fail;

  if ((Fail = configbuffer.setVariable("RepStructuralAnalysis", "C_INT16",
				       &RepStruct)))
    return Fail;

  if ((Fail = configbuffer.setVariable("RepStabilityAnalysis", "C_INT16",
				       &RepStab)))
    return Fail;

  if ((Fail = configbuffer.setVariable("RepMCA", "C_INT16",
				       &RepMCA)))
    return Fail;

  // Note:: there is no variable controlling comments output
  //		  in current configure file
  return Fail;
}

/**
 *	Assigns model in the Outputlist
 */
void COutput::setModel(const CModel &model)
{
  Model = model;
}

CCOutputLine::CCOutputLine() {}

CCOutputLine::~CCOutputLine() {}

C_INT16 CCOutputLine::isInsertAllowed(const COutputLine & src)
{return TRUE;}
