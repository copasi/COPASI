/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CReport.cpp,v $
   $Revision: 1.33 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/04/19 08:57:46 $
   End CVS Header */

#include "copasi.h"
#include "CReportDefinition.h"
#include "CReportBody.h"
#include "CReport.h"
#include "CCopasiContainer.h"

const std::vector< CCopasiContainer * > CReport::EmptyList;

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
    mAppend(true)
    //,mKey(CKeyFactory::add("Report", this))
{}

CReport::CReport(const CReport & src,
                 const CCopasiContainer * pParent):
    CCopasiContainer("Report", pParent, "Report"),
    mpOstream(src.mpOstream),
    mStreamOwner(false),
    mpReportDef(src.mpReportDef),
    mTarget(src.mTarget),
    mAppend(src.mAppend)
    //,mKey(CKeyFactory::add("Report", this))
{}

CReport::~CReport()
{cleanup();}

void CReport::cleanup()
{
  headerObjectList.clear();
  bodyObjectList.clear();
  footerObjectList.clear();

  close();
  //  CKeyFactory::remove(mKey);
  // mpReportDef pointer shall be dealt outside, where it is created
  //  pdelete(mpReportDef);
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

  std::vector< CCopasiObject * >::iterator it = headerObjectList.begin();
  std::vector< CCopasiObject * >::iterator end = headerObjectList.end();

  if (it == end) return;

  for (; it != end; ++it) (*it)->print(mpOstream);

  (*mpOstream) << std::endl;
}

void CReport::printBody()
{
  if (!mpOstream) return;

  std::vector< CCopasiObject * >::iterator it = bodyObjectList.begin();
  std::vector< CCopasiObject * >::iterator end = bodyObjectList.end();

  if (it == end) return;

  for (; it != end; ++it) (*it)->print(mpOstream);

  (*mpOstream) << std::endl;
}

void CReport::printFooter()
{
  if (!mpOstream) return;

  std::vector< CCopasiObject * >::iterator it = footerObjectList.begin();
  std::vector< CCopasiObject * >::iterator end = footerObjectList.end();

  if (it == end) return;

  for (; it != end; ++it) (*it)->print(mpOstream);

  (*mpOstream) << std::endl;
}

// Compile the List of Report Objects;
// Support Parellel

bool CReport::compile(const std::vector< CCopasiContainer * > listOfContainer)
{
  headerObjectList.clear();
  bodyObjectList.clear();
  footerObjectList.clear();

  // check if there is a Report Definition Defined
  if (!mpReportDef) return false;

  const_cast<std::vector< CCopasiContainer * > *>(&listOfContainer)->
  push_back(this);

  if (mpReportDef->getTitle())
    generateObjectsFromName(&listOfContainer, headerObjectList,
                            mpReportDef->getHeaderAddr());
  generateObjectsFromName(&listOfContainer, bodyObjectList,
                          mpReportDef->getBodyAddr());
  generateObjectsFromName(&listOfContainer, footerObjectList,
                          mpReportDef->getFooterAddr());

  const_cast<std::vector< CCopasiContainer * > *>(&listOfContainer)->
  pop_back();

  return true;
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
      mpOstream = new std::ofstream;
      mStreamOwner = true;

      if (mAppend)
        ((std::ofstream *) mpOstream)->
        open(mTarget.c_str(), std::ios_base::out | std::ios_base::app);
      else
        ((std::ofstream *) mpOstream)->
        open(mTarget.c_str(), std::ios_base::out);

      if (!((std::ofstream *) mpOstream)->is_open()) pdelete(mpOstream);
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

void CReport::printBody(CReport * pReport)
{
  if (pReport)
    pReport->printBody();
}

// make to support parallel tasks
void CReport::generateObjectsFromName(const std::vector< CCopasiContainer * > * pListOfContainer,
                                      std::vector<CCopasiObject*> & objectList,
                                      std::vector<CCopasiObjectName>* nameVector)
{
  unsigned C_INT32 i;
  CCopasiObject* pSelected;

  for (i = 0; i < nameVector->size(); i++)
    {
      pSelected = CCopasiContainer::ObjectFromName(*pListOfContainer,
                  (*nameVector)[i]);

      if (pSelected)
        {
          if (pSelected->isStaticString() &&
              pSelected->getObjectParent() != this)
            add(pSelected);

          objectList.push_back(pSelected);
        }
    }
}
