/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/parameterFitting/CExperiment.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/09/16 19:08:34 $
   End CVS Header */

#include "copasi.h"
 #include "CExperiment.h"

const std::string CExperiment::TypeName[] =
  {
    "ignored",
    "independent",
    "dependent",
    ""
  };

const char* CExperiment::XMLType[] =
  {
    "ignored",
    "independent",
    "dependent",
    NULL
  };

CExperiment::CExperiment(const CCopasiContainer * pParent):
    CCopasiParameterGroup("Experiment", pParent),
    mpFileName(NULL),
    mpPosition(NULL),
    mpTaskType(NULL),
    mpSeperator(NULL),
    mpRowOriented(NULL),
    mpNameRow(NULL),
    mpNumRows(NULL),
    mpNumColumns(NULL),
    mpColumnType(NULL),
    mRowName(NULL),
    mDataIndependent(0),
    mDataDependent(0)
{initializeParameter();}

CExperiment::CExperiment(const CExperiment & src,
                         const CCopasiContainer * pParent):
    CCopasiParameterGroup(src, pParent),
    mpFileName(NULL),
    mpPosition(NULL),
    mpTaskType(NULL),
    mpSeperator(NULL),
    mpRowOriented(NULL),
    mpNameRow(NULL),
    mpNumRows(NULL),
    mpNumColumns(NULL),
    mpColumnType(NULL),
    mRowName(NULL),
    mDataIndependent(src.mDataIndependent),
    mDataDependent(src.mDataDependent)
{initializeParameter();}

CExperiment::CExperiment(const CCopasiParameterGroup & group,
                         const CCopasiContainer * pParent):
    CCopasiParameterGroup(group, pParent),
    mpFileName(NULL),
    mpPosition(NULL),
    mpTaskType(NULL),
    mpSeperator(NULL),
    mpRowOriented(NULL),
    mpNameRow(NULL),
    mpNumRows(NULL),
    mpNumColumns(NULL),
    mpColumnType(NULL),
    mRowName(NULL),
    mDataIndependent(0),
    mDataDependent(0)
{initializeParameter();}

CExperiment::~CExperiment() {}

void CExperiment::initializeParameter()
{
  if (!getParameter("File Name"))
    addParameter("File Name", CCopasiParameter::STRING, std::string(""));
  mpFileName = getValue("File Name").pSTRING;

  if (!getParameter("Position in File"))
    addParameter("Position in File", CCopasiParameter::UINT, (unsigned C_INT32) C_INVALID_INDEX);
  mpPosition = getValue("").pUINT;

  if (!getParameter("Experiment Type"))
    addParameter("Experiment Type", CCopasiParameter::UINT, (unsigned C_INT32) CCopasiTask::unset);
  mpTaskType = (CCopasiTask::Type *) getValue("Experiment Type").pUINT;

  if (!getParameter("Seperator"))
    addParameter("Seperator", CCopasiParameter::STRING, std::string("\t"));
  mpSeperator = getValue("Seperator").pSTRING;

  if (!getParameter("Data is Row Oriented"))
    addParameter("Data is Row Oriented", CCopasiParameter::BOOL, (bool) true);
  mpRowOriented = getValue("Data is Row Oriented").pBOOL;

  if (!getParameter("Row containing Names"))
    addParameter("Row containing Names", CCopasiParameter::UINT, (unsigned C_INT32) C_INVALID_INDEX);
  mpNameRow = getValue("Row containing Names").pUINT;

  if (!getParameter("Number of Rows"))
    addParameter("Number of Rows", CCopasiParameter::UINT, (unsigned C_INT32) 0);
  mpNumRows = getValue("Number of Rows").pUINT;

  if (!getParameter("Number of Columns"))
    addParameter("Number of Columns", CCopasiParameter::UINT, (unsigned C_INT32) 0);
  mpNumColumns = getValue("Number of Columns").pUINT;

  if (!getParameter("Column Role"))
    addGroup("Column Role");
  mpColumnType = getValue("Column Role").pGROUP;
}

const CCopasiTask::Type & CExperiment::getExperimentType() const
{return *mpTaskType;}

const CMatrix< C_FLOAT64 > & CExperiment::getIndependentData() const
  {return mDataIndependent;}

const CMatrix< C_FLOAT64 > & CExperiment::getDependentData() const
  {return mDataDependent;}

const CExperiment::Type & CExperiment::getColumnType(const unsigned C_INT32 & index) const
  {
    assert (index < mpColumnType->size());
    return * static_cast<CExperiment::Type *>((*mpColumnType)[index]->getValue().pVOID);
  }

bool CExperiment::setColumnType(const unsigned C_INT32 & index,
                                const CExperiment::Type & type)
{
  assert (index < mpColumnType->size());
  return (*mpColumnType)[index]->setValue((unsigned C_INT32) type);
}

const unsigned C_INT32 & CExperiment::getNumColumns() const
  {return *mpNumColumns;}

bool CExperiment::setNumColumns(const unsigned C_INT32 & cols)
{
  *mpNumColumns = cols;
  return true;
}

const unsigned C_INT32 & CExperiment::getNumRows() const
  {return *mpNumRows;}

bool CExperiment::setNumRows(const unsigned C_INT32 & rows)
{
  *mpNumRows = rows;
  return true;
}

const std::string & CExperiment::getSeperator() const
  {return *mpSeperator;}

bool CExperiment::setSeperator(const std::string & seperator)
{
  *mpSeperator = seperator;
  return true;
}

const bool & CExperiment::isRowOriented() const
  {return *mpRowOriented;}

bool CExperiment::setIsRowOriented(const bool & isRowOriented)
{
  *mpRowOriented = isRowOriented;
  return true;
}
