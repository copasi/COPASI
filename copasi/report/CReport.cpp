
#include "CReportDefinition.h"
#include "CReportBody.h"
#include "CReport.h"
#include "CCopasiContainer.h"

//////////////////////////////////////////////////
//
//class CReport
//
//////////////////////////////////////////////////
CReport::CReport():
    CCopasiObject("Report", NULL, "Report", CCopasiObject::Container),
    mpReportDef(NULL),
    mAppend(true)
    //,mKey(CKeyFactory::add("Report", this))
{}

CReport::~CReport()
{cleanup();}

void CReport::cleanup()
{
  // Please Dont clear the objectList, as all pointers are also referred swh else
  int i;
  for (i = 0; i < objectList.size(); i++)
    {
      objectList[i] = NULL;
    }

  objectList.clear();
  //  CKeyFactory::remove(mKey);
  // mpReportDef pointer shall be dealt outside, where it is created
  //  pdelete(mpReportDef);
}

CReportDefinition* CReport::getReportDefinition()
{return mpReportDef;}

void CReport::setReportDefinition(CReportDefinition* reportDef)
{mpReportDef = reportDef;}

const std::string& CReport::getTarget()
{return mTarget;}

void CReport::setTarget(std::string target)
{mTarget = target;}

bool CReport::append()
{return mAppend;}

void CReport::setAppend(bool append)
{mAppend = append;}

void CReport::printHeader()
{
  // for loop print out mpReportDef->getHeader()
}

void CReport::printBody()
{
  // for loop print out mpReportDef->getBody()
}

void CReport::printFooter()
{
  // for loop print out mpReportDef->getFooter()
}

// Compile the List of Report Objects;
// Support Parellel

void CReport::compile(const std::vector< CCopasiContainer * > * pListOfContainer)
{
  int i;
  CCopasiObject* pSelected;

  // if no specified container list
  if (!pListOfContainer)
    for (i = 0; i < mpReportDef->getBodyAddr()->size(); i++)
      {
        pSelected = NULL;
        pSelected =
          (CCopasiObject*)CCopasiContainer::Root->getObject((*(mpReportDef->getBodyAddr()))[i]);
        if (pSelected)
          objectList.push_back(pSelected);
      }
  else
    {
      CCopasiContainer* pCopasiObject;
      int containerIndex;
      for (i = 0; i < mpReportDef->getBodyAddr()->size(); i++)
        {
          //favor to search the list of container first
          pSelected = NULL;
          for (containerIndex = 0; containerIndex < pListOfContainer->size(); containerIndex++)
            {
              pCopasiObject = (*pListOfContainer)[containerIndex];
              pSelected =
                (CCopasiObject*)pCopasiObject->getObject((*(mpReportDef->getBodyAddr()))[i]);
              if (pSelected)
                {
                  objectList.push_back(pSelected);
                  break;
                }
            }
          // if not find search the root
          if (!pSelected)
            {
              pSelected =
                (CCopasiObject*)CCopasiContainer::Root->getObject((*(mpReportDef->getBodyAddr()))[i]);
              // has been deleted all where
              if (pSelected)
                objectList.push_back(pSelected);
            }
        }
    }
}

void CReport::printBody(CReport * pReport)
{
  if (pReport)
    pReport->printBody();
}
