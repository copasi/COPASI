/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/output/Attic/COutput.cpp,v $
   $Revision: 1.58 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/05/24 14:18:15 $
   End CVS Header */

/*****************************************************************************
 * PROGRAM NAME: COutput.cpp
 * PROGRAMMER: Wei Sun wsun@vt.edu
 * PURPOSE: COutput Class Implemention
 *****************************************************************************/

#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <time.h>

#define  COPASI_TRACE_CONSTRUCTION

#include "copasi.h"
#include "COutput.h"
#include "CUDFunction.h"
#include "CUDFunctionDB.h"
#include "utilities/readwrite.h"
#include "utilities/CCopasiVector.h"
#include "utilities/CCopasiException.h" 
//#include "model/model.h"
#include "utilities/CGlobals.h"
#include "steadystate/CSteadyStateTask.h"
#include "steadystate/CEigen.h"

/**
 *  Default constructor. 
 */
COutput::COutput(const std::string & name,
                 const CCopasiContainer * pParent):
    CCopasiContainer(name, pParent, "Output"),
    mOutputLines("Output Lines", this),
    mTriggerType(),
    Dyn(0),
    DynTitles(0),
    DynQuotes(0),
    DynColWidth(0),
    DynSeparator(0),
    SS(0),
    SSTitles(0),
    SSQuotes(0),
    SSColWidth(0),
    SSSeparator(0),
    SSStrategy(0),
    Rep(0),
    RepStruct(0),
    RepStab(0),
    RepMCA(0),
    RepComments(1),
    ConcUnit(),
    TimeUnit(),
    mSolution(NULL)
{}

COutput::COutput(const COutput & src,
                 const CCopasiContainer * pParent):
    CCopasiContainer(src, pParent),
    mOutputLines(src.mOutputLines, this),
    mTriggerType(src.mTriggerType),
    Dyn(src.Dyn),
    DynTitles(src.DynTitles),
    DynQuotes(src.DynQuotes),
    DynColWidth(src.DynColWidth),
    DynSeparator(src.DynSeparator),
    SS(src.SS),
    SSTitles(src.SSTitles),
    SSQuotes(src.SSQuotes),
    SSColWidth(src.SSColWidth),
    SSSeparator(src.SSSeparator),
    SSStrategy(src.SSStrategy),
    Rep(src.Rep),
    RepStruct(src.RepStruct),
    RepStab(src.RepStab),
    RepMCA(src.RepMCA),
    RepComments(src.RepComments),
    ConcUnit(src.ConcUnit),
    TimeUnit(src.TimeUnit),
    mSolution(src.mSolution)
{}

void COutput::init()
{
  //  mOutput = new CCOutputLine;
}

void COutput::cleanup()
{
  //  if (mOutput) delete mOutput;
  //  mOutput = NULL;
  mOutputLines.cleanup();
  // mSolution->cleanup();
}

/**
 *  Destructor. 
 */
COutput::~COutput()
{
  // cleanup();
}

/**
 * Reset output data file and reporting file configure variables
 */
void COutput::resetConfiguration()
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

void COutput::setDynConfiguration(C_INT16 pDyn,
                                  C_INT16 pDynTitles,
                                  C_INT16 pDynQuotes,
                                  C_INT16 pDynColWidth,
                                  C_INT16 pDynSeparator)
{
  Dyn = pDyn;
  DynTitles = pDynTitles;
  DynQuotes = pDynQuotes;
  DynColWidth = pDynColWidth;
  DynSeparator = pDynSeparator;
}

/**
 *  Return the pointer of the COutputLine that can be output at the same time. 
 *  @return mOutput
 *  @see mOutput
 */
const CCopasiVectorS < COutputLine > & COutput::getList() const
  {
    return mOutputLines;
  }

/**
 *  Add new OutputLine object to a list
 *  @param newLine constant reference to COutputLine .
 *  @see COutputLine Class
 */
void COutput::addLine(COutputLine &newLine)
{
  // if (!mOutput) init();
  mOutputLines.add(newLine);
}

COutputLine * COutput::findOrCreateOutputLine(std::string nameOfLine)
{
  C_INT32 i;
  C_INT32 imax = mOutputLines.size();

  for (i = 0; i < imax; i++)
    {
      if (nameOfLine == mOutputLines[i]->getObjectName())
        return mOutputLines[i];
    }
  COutputLine * pLine = new COutputLine(nameOfLine);
  mOutputLines.add(pLine);
  return pLine;
}

void COutput::addDatum(std::string nameOfLine,
                       std::string title,
                       C_INT32 typeOfOutput,
                       std::string IName,
                       std::string JName)
{
  COutputLine* pLine = findOrCreateOutputLine(nameOfLine);

  CDatum Datum(title, NULL, typeOfOutput, "");
  Datum.createObjectString("not known", IName, JName, typeOfOutput);
  pLine->addDatum(Datum);
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

  mOutputLines.save(configbuffer);

  return Fail;
}

/**
 *  Loads an object with data coming from a CReadConfig object.
 *  (CReadConfig object reads an input stream)
 *  @param pconfigbuffer reference to a CReadConfig object.
 *  @param searchName refernece to a the time of seach section,
 *     for example: Interactive time course  
 *  @return mFail
 *  @see mFail
 */
C_INT32 COutput::load(CReadConfig & configbuffer)
{
  C_INT32 Fail = 0;

  readDefaultVar(configbuffer);

  std::string InteractiveTimeCourse = "Interactive time course";
  std::string TimeCourse = "Time-course output";
  std::string SteadyState = "Steady-state output";

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

//const std::string & COutput::getName() const {return getObjectName();}

/**
 * print the titles of the steady-state data file
 */
void COutput::sSOutputTitles(std::ostream &fout, std::string &SSName, C_INT16 SSSeparator, C_INT16 SSColWidth, C_INT16 SSQuotes) const
  {
    std::string Name;

    for (unsigned C_INT32 i = 0; i < mOutputLines.size(); i++)
      {
        Name = mOutputLines[i]->getObjectName();

        if (Name == SSName)
          mOutputLines[i]->sSOutputTitles(fout, SSSeparator, SSColWidth, SSQuotes);
      }
  }

/**
 * print mpValue of each Object in the steady-state data file
 */
void COutput::sSOutputData(std::ostream &fout, std::string &SSName, C_INT16 SSSeparator, C_INT16 SSColWidth, C_INT16 SSQuotes) const
  {
    std::string Name;

    for (unsigned C_INT32 i = 0; i < mOutputLines.size(); i++)
      {
        Name = mOutputLines[i]->getObjectName();

        if (Name == SSName)
          mOutputLines[i]->sSOutputData(fout, SSSeparator, SSColWidth, SSQuotes);
      }
  }

/**
 * print the titles of the time couse data file
 */
void COutput::dynOutputTitles(std::ostream &fout, std::string &DynName, C_INT16 DynSeparator, C_INT16 DynColWidth, C_INT16 DynQuotes) const
  {
    std::string Name;

    for (unsigned C_INT32 i = 0; i < mOutputLines.size(); i++)
      {
        Name = mOutputLines[i]->getObjectName();

        if (Name == DynName)
          mOutputLines[i]->dynOutputTitles(fout, DynSeparator, DynColWidth, DynQuotes);
      }
  }

/**
 * print the mpValue of Object in the time course data file
 */
void COutput::dynOutputData(std::ostream &fout, std::string &DynName, C_INT16 DynSeparator, C_INT16 DynColWidth, C_INT16 DynQuotes) const
  {
    std::string Name;

    for (unsigned C_INT32 i = 0; i < mOutputLines.size(); i++)
      {
        Name = mOutputLines[i]->getObjectName();

        if (Name == DynName)
          mOutputLines[i]->dynOutputData(fout, DynSeparator, DynColWidth, DynQuotes);
      }
  }

/**
 * Assign the pointer to each datum object for time course
 */
void COutput::compile(const std::string & name, CModel *model, CState *state)
{
  for (unsigned C_INT32 i = 0; i < mOutputLines.size(); i++)
    {
      mOutputLines[i]->compile(name, model, state);
    }
}

/**
 * Assign the pointer to each datum object for steady state
 */
void COutput::compile(const std::string & name, CModel *model, CSteadyStateTask *soln)
{
  for (unsigned C_INT32 i = 0; i < mOutputLines.size(); i++)
    {
      mOutputLines[i]->compile(name, model, soln);
    }

  mSolution = soln;
}

/**
 * Output the comments to the output reporting file
 */
void COutput::repComments(std::ostream &fout) const
  {
    fout << Copasi->pModel->getComments() << std::endl;
  }

/**
 * Output the model title to the output reporting file
 */
void COutput::repTitle(std::ostream &fout) const
  {
    fout << Copasi->pModel->getTitle() << std::endl << std::endl;
  }

/**
 * Print each line of the header in the reporting file
 */
void COutput::repHeaderLine(std::ostream &fout, int width, std::string OutStr) const
  {
    int pre, suf, i;
    std::string Str = "*";

    pre = (width - OutStr.length()) / 2;
    suf = width - pre - OutStr.length();

    for (i = 0; i < pre; i++)
      Str += ' ';

    Str += OutStr;

    for (i = 0; i < suf; i++)
      Str += ' ';

    Str += "*";

    fout << Str << std::endl;
  }

/**
 * print the header of the reporting file
 */
void COutput::repHeader(std::ostream &fout) const
  {
    std::string TimeStamp, TimeStr;
    int width, i;

    struct tm *newtime;
    time_t aclock;

    // Get time in seconds
    time(&aclock);
    // Convert time to struct tm form
    newtime = localtime(&aclock);
    TimeStr = asctime(newtime);
    TimeStamp = TimeStr.substr(0, TimeStr.length() - 1);

    std::string VersionString = "Copasi Version " + Copasi->ProgramVersion.getVersion();
    width = (VersionString.length() > TimeStamp.length()) ? VersionString.length() : TimeStamp.length();
    // width = max(width, ArchString.length());

    // write a full line with stars

    for (i = 0; i < width + 4; i++)
      fout << "*";

    fout << std::endl;

    repHeaderLine(fout, width + 2, VersionString);

    //repHeaderLine(fout, width, ArchString);
    repHeaderLine(fout, width + 2, TimeStamp);

    for (i = 0; i < width + 4; i++)
      fout << "*";

    fout << std::endl << std::endl;
  }

/**
 * print the parameters of the simulation
 */
void COutput::repParams(std::ostream &fout) const
  {
    std::string StrOut;
    unsigned C_INT32 i, j;
    CModel *model = Copasi->pModel;

    StrOut = "KINETIC PARAMETERS";
    fout << std::endl << StrOut << std::endl;

    // Set Float manipulators
    fout.setf(std::ios::scientific, std::ios::floatfield);
    fout.setf(std::ios::showpoint);

    for (i = 0; i < model->getReactions().size(); i++)
      {
        StrOut = model->getReactions()[i]->getObjectName();
        fout << StrOut << " (";

        StrOut = model->getReactions()[i]->getFunction().getObjectName();
        fout << StrOut << ")" << std::endl;

        for (j = 0; j < model->getReactions()[i]->getParameters().size(); j++)
          {
            fout << " " << model->getReactions()[i]->getParameters().getName(j) << " =  ";
            fout << std::setprecision(4) << model->getReactions()[i]->getParameters().getValue(j);
            fout << std::endl;
          }
      }

    fout << std::endl << "COMPARTMENTS" << std::endl;

    for (i = 0; i < model->getCompartments().size(); i++)
      {
        fout << "V(" << model->getCompartments()[i]->getObjectName() << ") =  ";
        fout << std::setprecision(4) << model->getCompartments()[i]->getVolume();
        fout << std::endl;
      }

    fout << std::endl;
  }

/**
 * print the structural analysis
 */
void COutput::repStruct(std::ostream &fout) const
  {
    unsigned C_INT32 i, j;
    CModel *model = Copasi->pModel;

    // determine the kernel of the stoichiometry matrix
    //model.getKernel();

    fout << std::endl << "STRUCTURAL ANALYSIS" << std::endl;

    if (model->getDimension() > 0)
      {
        fout << std::endl << "Rank of the stoichiometry matrix: " << model->getDimension() << std::endl;
      }

    fout << std::endl << "key for step (column) numbers: " << std::endl;

    for (i = 0; i < model->getReactions().size(); i++)
      {
        fout << std::setw(2) << i << " - ";
        fout << model->getReactions()[i]->getObjectName();
        fout << std::endl;
      }

    fout << std::endl << "REDUCED STOICHIOMETRY MATRIX" << std::endl;

    for (i = 0; i < model->getReactions().size(); i++)
      if (i)
        fout << std::setw(4) << i;
      else
        fout << std::setw(16) << i;

    fout << std::endl;

    for (i = 0; i < model->getReactions().size(); i++)
      {
        if (i)
          fout << std::setw(4) << "----";
        else
          fout << std::setw(15) << "----";
      }

    fout << "--" << std::endl;

    // Set Left Justification
    fout.setf(std::ios::left);

    for (i = 0; i < model->getMetabolitesInd().size(); i++)
      {
        fout << std::setw(11) << model->getMetabolitesInd()[i]->getObjectName() << "|";

        for (j = 0; j < model->getReactions().size(); j++)
          {
            fout << std::setprecision(1);

            if (j)
              // Set Left Justification
              fout.setf(std::ios::left);
            else
              fout.setf(std::ios::right);

            fout << std::setw(4) << model->getRedStoi()[i][j];
          }

        fout << std::endl;
        // Restore Justification
        fout.unsetf(std::ios::right);
        fout.setf(std::ios::left);
      }

    fout << std::endl << "INVERSE OF THE REDUCTION MATRIX" << std::endl;

    fout << std::endl;

    // Restore Justification
    fout.unsetf(std::ios::left);

    for (i = 0; i < model->getIntMetab(); i++)
      {
        if (i)
          fout << std::setw(4) << i;
        else
          fout << std::setw(16) << i;
      }

    fout << std::endl;

    for (i = 0; i < model->getIntMetab(); i++)
      if (i)
        fout << std::setw(4) << "----";
      else
        fout << std::setw(15) << "----";

    fout << "--" << std::endl;

    // Set Left Justification
    fout.setf(std::ios::left);

    // Create a arry to store name from
    std::vector < std::string > inverse;

    for (i = 0; i < model->getMetabolitesInd().size(); i++)
      inverse.push_back(model->getMetabolitesInd()[i]->getObjectName());

    for (j = 0; j < model->getDepMetab(); j++)
      inverse.push_back(model->getMetabolitesDep()[j]->getObjectName());

    const CModel::CLinkMatrixView & Inverse = model->getL();

    for (i = 0; i < model->getIntMetab(); i++)
      {
        fout << std::setw(11) << inverse[i] << "|";

        for (j = 0; j < model->getIntMetab(); j++)
          {
            if (j)
              // Set Left Justification
              fout.setf(std::ios::left);
            else
              fout.setf(std::ios::right);

            fout << std::setprecision(1) << std::setw(4) << Inverse(i, j);

            //fout << std::setprecision(1) << std::setw(4) << model->getML()[i][j];
          }

        fout << std::endl;
        // Restore Justification
        fout.unsetf(std::ios::right);
        fout.setf(std::ios::left);
      }

    fout << std::endl;

    if (model->getMoieties().size() > 0)
      {
        fout << std::endl << "CONSERVATION RELATIONSHIPS" << std::endl;

        fout.setf(std::ios::fixed)

;
        for (i = 0; i < model->getMoieties().size(); i++)
          {
            fout << model->getMoieties()[i]->getDescription(model) << " = ";
            fout << model->getMoieties()[i]->getNumber() << std::endl;
          }

        fout.unsetf(std::ios::fixed)

;
      }

    fout << std::endl;
  }

/**
 * print the results of the steady-state simulation
 */
void COutput::repSS(std::ostream &fout) const
  {
    unsigned C_INT32 i;
    double rate;
    CModel *model = Copasi->pModel;

    fout << *mSolution;

    fout.unsetf(std::ios::left);
    fout.setf(std::ios::right);

    // Output concentrations

    for (i = 0; i < model->getTotMetab(); i++)
      {
        if (model->getMetabolites()[i]->getStatus() == 0) // METAB_FIXED == 0
          rate = 0.0;
        else
          rate = model->getMetabolites()[i]->getRate();

        // Output Concentration
        fout << "[" << std::setw(10) << model->getMetabolites()[i]->getObjectName();

        fout << "] = ";

        fout << std::setprecision(6) << model->getMetabolites()[i]->getConcentration();

        fout << " " << ConcUnit << ", ";

        // Output Transition time of the metabolite
        fout << "tt = " << std::setprecision(6) << model->getMetabolites()[i]->getTransitionTime();

        fout << " " << TimeUnit << " " << ", ";

        // Output rate
        fout << "rate = " << std::setprecision(3) << rate;

        fout << " " << ConcUnit << "/" << TimeUnit;

        if (model->getMetabolites()[i]->getConcentration() < 0.0)
          fout << " BOGUS!";

        fout << std::endl;
      }

    // output fluxes
    for (i = 0; i < model->getTotSteps(); i++)
      {
        fout << "J(" << model->getReactions()[i]->getObjectName() << ") = ";
        fout << std::setprecision(6) << model->getReactions()[i]->getFlux();
        fout << " " << ConcUnit << "/" << TimeUnit << std::endl;
      }

    // output user-defined functions
    /*   unsigned C_INT32 size = Copasi->pUDFunctionDB->getFunctions().size();

       CUDFunction pFunct;

       if (size > 0)
         {
           fout << std::endl;

           for (i = 0; i < size; i++)
             {
               // calculate the flux of this step
               fout << Copasi->pUDFunctionDB->getFunctions()[i]->getObjectName();
               fout << " =";
               fout << std::setprecision(6) << Copasi->pUDFunctionDB->getFunctions()[i]->getValue();
               fout << std::endl;
             }
         }*/
  }

/**
 * print the results of the stability analysis
 */
void COutput::repStability(std::ostream &fout) const
  {
    unsigned C_INT32 i, imax;
    unsigned C_INT32 j, jmax;

    const CMatrix< C_FLOAT64 > & Jacobian = mSolution->getJacobian();
    CModel *model = Copasi->pModel;

    fout << *mSolution->getEigenValues();

    // Set Float manipulators
    fout.setf(std::ios::scientific, std::ios::floatfield);
    fout.setf(std::ios::showpoint);
    fout.width(10);

    // Output Jacobian Matrix
    fout << std::endl << "Jacobian matrix" << std::endl;
    fout << std::setprecision(6);

    imax = jmax = model->getIntMetab();
    for (i = 0; i < imax; i++)
      {
        for (j = 0; j < jmax; j++)
          fout << Jacobian[i][j] << "  ";

        fout << std::endl;
      }

    // Output Eigenvalus of the Jacibian Matrix
    fout << std::endl << "Eigenvalues of the Jacobian matrix" << std::endl;

    for (i = 0; i < model->getIntMetab(); i++)
      {
        if (mSolution->getEigenValues()->getEigen_i()[i] == 0.0)
          fout << std::setprecision(6) << mSolution->getEigenValues()->getEigen_r()[i];
        else
          {
            fout << std::setprecision(6) << mSolution->getEigenValues()->getEigen_r()[i];
            fout << " + " << std::setprecision(6) << mSolution->getEigenValues()->getEigen_i()[i];
          }

        fout << std::endl;
      }

    fout << std::endl;
  }

/**
 * print the results of the MCA
 */
void COutput::repMCA(std::ostream & C_UNUSED(fout)) const
  {
#if 0

    if (mSolution->getSolution != SS_FOUND)
      return;
    else
      {
        fout << std::endl << "METABOLIC CONTROL ANALYSIS" << std::endl;
        // Output elasticties

        if (mSolution->)
          else
          }

#endif
  }

/**
 * print the titles of the time-course data file
 */
void COutput::dynOutputTitles(std::ostream &fout, std::string & C_UNUSED(DynName)) const
  {
    for (unsigned C_INT32 i = 0; i < mOutputLines.size(); i++)
      {
        mOutputLines[i]->dynOutputTitles(fout, DynSeparator, DynColWidth, DynQuotes);
      }
  }

/**
 * print a line of data (one time point) on the time-course data file
 */
void COutput::dynOutputData(std::ostream &fout, std::string & C_UNUSED(DynName)) const
  {
    for (unsigned C_INT32 i = 0; i < mOutputLines.size(); i++)
      {
        mOutputLines[i]->dynOutputData(fout, DynSeparator, DynColWidth, DynQuotes);
      }
  }

/**
 * print the titles of the steady-state data file
 */
void COutput::sSOutputTitles(std::ostream &fout, std::string &SSName) const
  {
    for (unsigned C_INT32 i = 0; i < mOutputLines.size(); i++)
      {
        if (SSName == mOutputLines[i]->getObjectName())
          mOutputLines[i]->sSOutputTitles(fout, SSSeparator, SSColWidth, SSQuotes);
      }
  }

/**
 * print a line of data (one iteration) on the steady-state data file
 */
void COutput::sSOutputData(std::ostream &fout, std::string &SSName) const
  {
    for (unsigned C_INT32 i = 0; i < mOutputLines.size(); i++)
      {
        if (SSName == mOutputLines[i]->getObjectName())
          mOutputLines[i]->sSOutputData(fout, SSSeparator, SSColWidth, SSQuotes);
      }
  }

/*
 * print the reporting data file
 */
void COutput::copasiRep(std::ostream &fout) const
  {
    repHeader(fout);

    repTitle(fout);

    if (RepComments)
      repComments(fout);

    if (RepStruct)
      repStruct(fout);

    repParams(fout);

    repSS(fout);

    if (RepStab)
      repStability(fout);

#if 0

    if (RepMCA)
      repMCA(fout);

#endif
  }

/*
 * print the steady state data file
 */
void COutput::copasiSS(std::ostream &fout) const
  {
    std::string SSName = "Steady-state output";

    if (SS)
      {
        repSS(fout);
        repStability(fout);
        if (SSTitles)
          {
            sSOutputTitles(fout, SSName);
            sSOutputData(fout, SSName);
          }
      }
  }

/*
 * print the time course dynamic data file
 */
void COutput::copasiDyn(std::ostream &fout, int time) const
  {
    std::string DynName = "Time-course output";

    if (Dyn)
      {
        if (!time)
          {
            if (DynTitles)
              dynOutputTitles(fout, DynName, DynSeparator, DynColWidth, DynQuotes);
          }
        else
          dynOutputData(fout, DynName, DynSeparator, DynColWidth, DynQuotes);
      }
  }

/**
 * Read config variables from input configburg buffer
 *  @param configbuffer: reference of the config buffer.
 */
C_INT32 COutput::readDefaultVar(CReadConfig &configbuffer)
{
  C_INT32 Fail = 0;

  if ((Fail = configbuffer.getVariable("TimeUnit", "string",
                                       (void *) & TimeUnit,
                                       CReadConfig::LOOP)))
    return Fail;

  if ((Fail = configbuffer.getVariable("ConcentrationUnit", "string",
                                       (void *) & ConcUnit,
                                       CReadConfig::SEARCH)))
    return Fail;

  if ((Fail = configbuffer.getVariable("Dynamics", "C_INT16",
                                       (void *) & Dyn,
                                       CReadConfig::SEARCH)))
    return Fail;

  if ((Fail = configbuffer.getVariable("SteadyState", "C_INT16",
                                       (void *) & SS,
                                       CReadConfig::SEARCH)))
    return Fail;

  if ((Fail = configbuffer.getVariable("Report", "C_INT16",
                                       (void *) & Rep,
                                       CReadConfig::SEARCH)))
    return Fail;

  if ((Fail = configbuffer.getVariable("DynTitles", "C_INT16",
                                       (void *) & DynTitles,
                                       CReadConfig::SEARCH)))
    return Fail;

  if ((Fail = configbuffer.getVariable("SSTitles", "C_INT16",
                                       (void *) & SSTitles,
                                       CReadConfig::SEARCH)))
    return Fail;

  if ((Fail = configbuffer.getVariable("DynQuotes", "C_INT16",
                                       (void *) & DynQuotes,
                                       CReadConfig::SEARCH)))
    return Fail;

  if ((Fail = configbuffer.getVariable("SSQuotes", "C_INT16",
                                       (void *) & SSQuotes,
                                       CReadConfig::SEARCH)))
    return Fail;

  if ((Fail = configbuffer.getVariable("DynColWidth", "C_INT16",
                                       (void *) & DynColWidth,
                                       CReadConfig::SEARCH)))
    return Fail;

  if ((Fail = configbuffer.getVariable("SSColWidth", "C_INT16",
                                       (void *) & SSColWidth,
                                       CReadConfig::SEARCH)))
    return Fail;

  if ((Fail = configbuffer.getVariable("DynSeparator", "C_INT16",
                                       (void *) & DynSeparator,
                                       CReadConfig::SEARCH)))
    return Fail;

  if ((Fail = configbuffer.getVariable("SSSeparator", "C_INT16",
                                       (void *) & SSSeparator,
                                       CReadConfig::SEARCH)))
    return Fail;

  if ((Fail = configbuffer.getVariable("SSStrategy", "C_INT16",
                                       (void *) & SSStrategy,
                                       CReadConfig::SEARCH)))
    return Fail;

  try
    {
      Fail = configbuffer.getVariable("RepComments", "C_INT16",
                                      (void *) & RepComments,
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
                                       (void *) & RepStruct,
                                       CReadConfig::LOOP)))
    return Fail;

  if ((Fail = configbuffer.getVariable("RepStabilityAnalysis", "C_INT16",
                                       (void *) & RepStab,
                                       CReadConfig::SEARCH)))
    return Fail;

  if ((Fail = configbuffer.getVariable("RepMCA", "C_INT16",
                                       (void *) & RepMCA,
                                       CReadConfig::SEARCH)))
    return Fail;

  // Note:: there is no variable controlling comments output
  //    in current configure file
  return Fail;
}

/**
 * Write output control variables from input configburg buffer
 *  @param configbuffer: reference of the config buffer.
 */
C_INT32 COutput::writeDefaultVar(CWriteConfig &configbuffer)
{
  C_INT32 Fail = 0;

  if ((Fail = configbuffer.setVariable("TimeUnit", "string",
                                       &TimeUnit)))
    return Fail;

  if ((Fail = configbuffer.setVariable("ConcentrationUnit", "string",
                                       &ConcUnit)))
    return Fail;

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
  //    in current configure file
  return Fail;
}
#ifdef XXXX
int COutput::CheckEquilibrium()
{
  unsigned C_INT32 i;
  double hr, tmp;
  int Equilibrium;

  // find the highest concentration rate

  for (i = 0, hr = 0.0; i < Copasi->Model->getTotSteps(); i++)
    if ((tmp = fabs(Copasi->Model->getReactions()[i]->getFlux())) > hr)
      hr = tmp;

  // true if in chemical equilibrium
  if (hr < mSolution->getSSRes())
    Equilibrium = 1;
  else
    Equilibrium = 0;

  return 0;
}
#endif // XXXX
