
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
    mAppend(true),
    ostream(NULL)
    //,mKey(CKeyFactory::add("Report", this))
{}

CReport::~CReport()
{cleanup();}

void CReport::cleanup()
{
  // Please Dont clear the objectList, as all pointers are also referred swh else
  int i;
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
  // for loop print out mpReportDef->getHeader()
  int i;
  for (i = 0; i < headerObjectList.size(); i++)
    headerObjectList[i]->print(*ostream);
}

void CReport::printBody()
{
  // for loop print out mpReportDef->getBody()
  int i;
  for (i = 0; i < bodyObjectList.size(); i++)
    bodyObjectList[i]->print(*ostream);
}

void CReport::printFooter()
{
  // for loop print out mpReportDef->getFooter()
  int i;
  for (i = 0; i < footerObjectList.size(); i++)
    footerObjectList[i]->print(*ostream);
}

// Compile the List of Report Objects;
// Support Parellel

void CReport::compile(const std::vector< CCopasiContainer * > * pListOfContainer)
{
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
  int i;
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
      int containerIndex;
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

void CReport::getObjectFromName(
  const std::vector< CCopasiContainer * > * pListOfContainer,
  CCopasiObject* pObject,
  const CCopasiObjectName& objName)
{
  // if no specified container list
  if (!pListOfContainer)
    {
      pObject = NULL;
      pObject =
        (CCopasiObject*)CCopasiContainer::Root->getObject(objName);
    }
  else
    {
      CCopasiContainer* pCopasiObject;
      int containerIndex;
      //favor to search the list of container first
      pObject = NULL;
      for (containerIndex = 0; containerIndex < pListOfContainer->size(); containerIndex++)
        {
          pCopasiObject = (*pListOfContainer)[containerIndex];
          pObject =
            (CCopasiObject*)pCopasiObject->getObject(objName);
        }
      // if not find search the root
      if (!pObject)
        pObject =
          (CCopasiObject*)CCopasiContainer::Root->getObject(objName);
      // has been deleted all where
    }
}
