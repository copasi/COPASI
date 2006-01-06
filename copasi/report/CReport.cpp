/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CReport.cpp,v $
   $Revision: 1.41.2.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/01/06 18:06:47 $
   End CVS Header */

#include "copasi.h"

#include "CReportDefinition.h"
#include "CReport.h"
#include "CCopasiContainer.h"
#include "CCopasiTimer.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "utilities/CDirEntry.h"

//////////////////////////////////////////////////
//
//class CReport
//
//////////////////////////////////////////////////
CReport::CReport(const CCopasiContainer * pParent):
    CCopasiContainer("Report", pParent, "Report"),
    mpOstream(NULL),
    mStreamOwner(false),
    mpReportDef(NULL),
    mTarget(""),
    mAppend(true),
    mFooterObjectList(),
    mBodyObjectList(),
    mHeaderObjectList(),
    mFooterActualizeList(),
    mBodyActualizeList(),
    mHeaderActualizeList()
{}

CReport::CReport(const CReport & src,
                 const CCopasiContainer * pParent):
    CCopasiContainer("Report", pParent, "Report"),
    mpOstream(src.mpOstream),
    mStreamOwner(false),
    mpReportDef(src.mpReportDef),
    mTarget(src.mTarget),
    mAppend(src.mAppend),
    mFooterObjectList(src.mFooterObjectList),
    mBodyObjectList(src.mBodyObjectList),
    mHeaderObjectList(src.mHeaderObjectList),
    mFooterActualizeList(src.mFooterActualizeList),
    mBodyActualizeList(src.mBodyActualizeList),
    mHeaderActualizeList(src.mHeaderActualizeList)
{}

CReport::~CReport()
{cleanup();}

void CReport::cleanup()
{
  mHeaderObjectList.clear();
  mBodyObjectList.clear();
  mFooterObjectList.clear();

  mHeaderActualizeList.clear();
  mBodyActualizeList.clear();
  mFooterActualizeList.clear();

  close();
}

CReportDefinition* CReport::getReportDefinition()
{return mpReportDef;}

void CReport::setReportDefinition(CReportDefinition* reportDef)
{mpReportDef = reportDef;}

const std::string& CReport::getTarget() const
  {return mTarget;}

void CReport::setTarget(std::string target)
{mTarget = target;}

bool CReport::append() const
  {return mAppend;}

void CReport::setAppend(bool append)
{mAppend = append;}

void CReport::printHeader()
{
  if (!mpOstream) return;

  std::vector< Actualize * >::iterator itA = mHeaderActualizeList.begin();
  std::vector< Actualize * >::iterator endA = mHeaderActualizeList.end();

  for (; itA != endA; ++itA) (**itA)();

  std::vector< CCopasiObject * >::iterator it = mHeaderObjectList.begin();
  std::vector< CCopasiObject * >::iterator end = mHeaderObjectList.end();

  if (it == end) return;

  for (; it != end; ++it) (*it)->print(mpOstream);

  (*mpOstream) << std::endl;
}

void CReport::printBody()
{
  if (!mpOstream) return;

  std::vector< Actualize * >::iterator itA = mBodyActualizeList.begin();
  std::vector< Actualize * >::iterator endA = mBodyActualizeList.end();

  for (; itA != endA; ++itA) (**itA)();

  std::vector< CCopasiObject * >::iterator it = mBodyObjectList.begin();
  std::vector< CCopasiObject * >::iterator end = mBodyObjectList.end();

  if (it == end) return;

  for (; it != end; ++it) (*it)->print(mpOstream);

  (*mpOstream) << std::endl;
}

void CReport::printFooter()
{
  if (!mpOstream) return;

  std::vector< Actualize * >::iterator itA = mFooterActualizeList.begin();
  std::vector< Actualize * >::iterator endA = mFooterActualizeList.end();

  for (; itA != endA; ++itA) (**itA)();

  std::vector< CCopasiObject * >::iterator it = mFooterObjectList.begin();
  std::vector< CCopasiObject * >::iterator end = mFooterObjectList.end();

  if (it == end) return;

  for (; it != end; ++it) (*it)->print(mpOstream);

  (*mpOstream) << std::endl;
}

void CReport::printEmptyLine()
{
  if (!mpOstream) return;
  (*mpOstream) << std::endl;
}

// Compile the List of Report Objects;
// Support Parellel

bool CReport::compile(std::vector< CCopasiContainer * > listOfContainer)
{
  bool success = true;

  mHeaderObjectList.clear();
  mBodyObjectList.clear();
  mFooterObjectList.clear();

  mHeaderActualizeList.clear();
  mBodyActualizeList.clear();
  mFooterActualizeList.clear();

  // check if there is a Report Definition Defined
  if (!mpReportDef) return false;

  listOfContainer.push_back(this);

  if (mpReportDef->isTable())
    if (!mpReportDef->preCompileTable(listOfContainer)) success = false;

  generateObjectsFromName(&listOfContainer, mHeaderObjectList, mHeaderActualizeList,
                          mpReportDef->getHeaderAddr());
  generateObjectsFromName(&listOfContainer, mBodyObjectList, mBodyActualizeList,
                          mpReportDef->getBodyAddr());
  generateObjectsFromName(&listOfContainer, mFooterObjectList, mFooterActualizeList,
                          mpReportDef->getFooterAddr());

  return success;
}

std::ostream * CReport::open(std::ostream * pOstream)
{
  if (mStreamOwner) pdelete(mpOstream);

  if (pOstream)
    {
      mpOstream = pOstream;
      mStreamOwner = false;
    }
  else if (mTarget != "")
    {
      if (CDirEntry::isRelativePath(mTarget) &&
          !CDirEntry::makePathAbsolute(mTarget, CCopasiDataModel::Global->getFileName()))
        mTarget = CDirEntry::fileName(mTarget);

      mpOstream = new std::ofstream;
      mStreamOwner = true;

      if (mAppend)
        ((std::ofstream *) mpOstream)->
        open(mTarget.c_str(), std::ios_base::out | std::ios_base::app);
      else
        ((std::ofstream *) mpOstream)->
        open(mTarget.c_str(), std::ios_base::out);

      if (!((std::ofstream *) mpOstream)->is_open()) pdelete(mpOstream);

      if (mpOstream) mpOstream->precision(mpReportDef->getPrecision());
    }

  return mpOstream;
}

void CReport::close()
{
  if (mStreamOwner) pdelete(mpOstream);

  mpOstream = NULL;
  mStreamOwner = false;
}

std::ostream * CReport::getStream() const {return mpOstream;}

/*void CReport::printBody(CReport * pReport)
{
  if (pReport)
    pReport->printBody();
}*/

// make to support parallel tasks
void CReport::generateObjectsFromName(const std::vector< CCopasiContainer * > * pListOfContainer,
                                      std::vector<CCopasiObject*> & objectList,
                                      std::vector< Actualize * > & actualizeList,
                                      const std::vector<CRegisteredObjectName>* nameVector)
{
  unsigned C_INT32 i;
  CCopasiObject* pSelected;

  for (i = 0; i < nameVector->size(); i++)
    {
      pSelected = CCopasiContainer::ObjectFromName(*pListOfContainer,
                  (*nameVector)[i]);

      if (pSelected)
        {
          objectList.push_back(pSelected);
          if (pSelected->getActualize())
            {
              if (dynamic_cast<CCopasiTimer *>(pSelected))
                dynamic_cast<CCopasiTimer *>(pSelected)->start();

              actualizeList.push_back(pSelected->getActualize());
            }
        }
    }
}
