/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CReport.cpp,v $
   $Revision: 1.26 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/11/12 22:12:48 $
   End CVS Header */

#include "copasi.h"
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
    ostream(NULL),
    mpReportDef(NULL),
    mTarget(""),
    mAppend(true)
    //,mKey(CKeyFactory::add("Report", this))
{}

CReport::~CReport()
{cleanup();}

void CReport::cleanup()
{
  // Please Dont clear the objectList, as all pointers are also referred swh else
  unsigned C_INT32 i;
  for (i = 0; i < headerObjectList.size(); i++)
    headerObjectList[i] = NULL;

  for (i = 0; i < bodyObjectList.size(); i++)
    bodyObjectList[i] = NULL;

  for (i = 0; i < footerObjectList.size(); i++)
    footerObjectList[i] = NULL;

  headerObjectList.clear();
  bodyObjectList.clear();
  footerObjectList.clear();
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
  // check if there is a target defined,
  if (!ostream)
    return;
  // for loop print out mpReportDef->getHeader()
  unsigned C_INT32 i;
  for (i = 0; i < headerObjectList.size(); i++)
    headerObjectList[i]->print(ostream);
}

void CReport::printBody()
{
  // check if there is a target defined,
  if (!ostream)
    return;
  // for loop print out mpReportDef->getBody()
  unsigned C_INT32 i;
  for (i = 0; i < bodyObjectList.size(); i++)
    bodyObjectList[i]->print(ostream);
}

void CReport::printFooter()
{
  // check if there is a target defined,
  if (!ostream)
    return;
  // for loop print out mpReportDef->getFooter()
  unsigned C_INT32 i;
  for (i = 0; i < footerObjectList.size(); i++)
    footerObjectList[i]->print(ostream);
}

// Compile the List of Report Objects;
// Support Parellel

void CReport::compile(const std::vector< CCopasiContainer * > * pListOfContainer)
{
  // check if there is a Report Definition Defined
  if (!mpReportDef)
    return;
  generateObjectsFromName(pListOfContainer, headerObjectList, mpReportDef->getHeaderAddr());
  generateObjectsFromName(pListOfContainer, bodyObjectList, mpReportDef->getBodyAddr());
  generateObjectsFromName(pListOfContainer, footerObjectList, mpReportDef->getFooterAddr());
}

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

  // if no specified container list
  if (!pListOfContainer)
    for (i = 0; i < nameVector->size(); i++)
      {
        pSelected = NULL;
        pSelected =
          (CCopasiObject*)CCopasiContainer::Root->getObject((*(nameVector))[i]);
        if (pSelected)
          objectList.push_back(pSelected);
      }
  else
    {
      CCopasiContainer* pCopasiObject;
      unsigned C_INT32 containerIndex;
      for (i = 0; i < nameVector->size(); i++)
        {
          //favor to search the list of container first
          pSelected = NULL;
          for (containerIndex = 0; containerIndex < pListOfContainer->size(); containerIndex++)
            {
              pCopasiObject = (*pListOfContainer)[containerIndex];
              pSelected =
                (CCopasiObject*)pCopasiObject->getObject((*(nameVector))[i]);
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
                (CCopasiObject*)CCopasiContainer::Root->getObject((*(nameVector))[i]);
              // has been deleted all where
              if (pSelected)
                objectList.push_back(pSelected);
            }
        }
    }
}
