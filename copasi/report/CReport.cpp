/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CReport.cpp,v $
   $Revision: 1.41.2.3 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/01/27 13:49:55 $
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
    mFooterRefreshList(),
    mBodyRefreshList(),
    mHeaderRefreshList()
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
    mFooterRefreshList(src.mFooterRefreshList),
    mBodyRefreshList(src.mBodyRefreshList),
    mHeaderRefreshList(src.mHeaderRefreshList)
{}

CReport::~CReport()
{cleanup();}

void CReport::cleanup()
{
  mHeaderObjectList.clear();
  mBodyObjectList.clear();
  mFooterObjectList.clear();

  mHeaderRefreshList.clear();
  mBodyRefreshList.clear();
  mFooterRefreshList.clear();

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

  std::vector< Refresh * >::iterator itA = mHeaderRefreshList.begin();
  std::vector< Refresh * >::iterator endA = mHeaderRefreshList.end();

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

  std::vector< Refresh * >::iterator itA = mBodyRefreshList.begin();
  std::vector< Refresh * >::iterator endA = mBodyRefreshList.end();

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

  std::vector< Refresh * >::iterator itA = mFooterRefreshList.begin();
  std::vector< Refresh * >::iterator endA = mFooterRefreshList.end();

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

  mHeaderRefreshList.clear();
  mBodyRefreshList.clear();
  mFooterRefreshList.clear();

  // check if there is a Report Definition Defined
  if (!mpReportDef) return false;

  listOfContainer.push_back(this);

  if (mpReportDef->isTable())
    if (!mpReportDef->preCompileTable(listOfContainer)) success = false;

  generateObjectsFromName(&listOfContainer, mHeaderObjectList, mHeaderRefreshList,
                          mpReportDef->getHeaderAddr());
  generateObjectsFromName(&listOfContainer, mBodyObjectList, mBodyRefreshList,
                          mpReportDef->getBodyAddr());
  generateObjectsFromName(&listOfContainer, mFooterObjectList, mFooterRefreshList,
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
                                      std::vector< Refresh * > & refreshList,
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
          if (pSelected->getRefresh())
            {
              if (dynamic_cast<CCopasiTimer *>(pSelected))
                dynamic_cast<CCopasiTimer *>(pSelected)->start();

              refreshList.push_back(pSelected->getRefresh());
            }
        }
    }
}
