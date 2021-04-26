// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi/copasi.h"

#include "CReportDefinition.h"
#include "CReport.h"
#include "copasi/core/CDataTimer.h"

#include "copasi/core/CDataContainer.h"
#include "copasi/core/CRootContainer.h"

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/utilities/CCopasiMessage.h"
#include "copasi/utilities/CDirEntry.h"
#include "copasi/utilities/utility.h"
#include "copasi/commandline/CLocaleString.h"

//////////////////////////////////////////////////
//
//class CReport
//
//////////////////////////////////////////////////
CReport::CReport():
  COutputInterface(),
  mpDataModel(NULL),
  mpOstream(NULL),
  mStreamOwner(false),
  mpReportDef(NULL),
  mTarget(""),
  mAppend(true),
  mConfirmOverwrite(true),
  mFooterObjectList(),
  mBodyObjectList(),
  mHeaderObjectList(),
  mpHeader(NULL),
  mpBody(NULL),
  mpFooter(NULL),
  mState(Invalid)
{}

CReport::CReport(const CReport & src):
  COutputInterface(src),
  mpDataModel(src.mpDataModel),
  mpOstream(src.mpOstream),
  mStreamOwner(false),
  mpReportDef(src.mpReportDef),
  mTarget(src.mTarget),
  mAppend(src.mAppend),
  mConfirmOverwrite(src.mConfirmOverwrite),
  mFooterObjectList(src.mFooterObjectList),
  mBodyObjectList(src.mBodyObjectList),
  mHeaderObjectList(src.mHeaderObjectList),
  mpHeader(src.mpHeader),
  mpBody(src.mpBody),
  mpFooter(src.mpFooter),
  mState(Invalid)
{}

CReport::~CReport()
{cleanup();}

void CReport::cleanup()
{
  mHeaderObjectList.clear();
  mBodyObjectList.clear();
  mFooterObjectList.clear();

  finish();
  close();
}

const CReportDefinition* CReport::getReportDefinition() const
{
  return mpReportDef;
}

void CReport::setReportDefinition(const CReportDefinition* reportDef)
{
  mpReportDef = reportDef;
}

const std::string & CReport::getTarget() const
{
  return mTarget;
}

void CReport::setTarget(const std::string & target)
{
  mTarget = target;
}

const bool & CReport::append() const
{
  return mAppend;
}

void CReport::setAppend(const bool & append)
{
  mAppend = append;
}

const bool & CReport::confirmOverwrite() const
{
  return mConfirmOverwrite;
}

void CReport::setConfirmOverwrite(const bool & confirmOverwrite)
{
  mConfirmOverwrite = confirmOverwrite;
}

void CReport::output(const Activity & activity)
{
  switch (activity)
    {
      case COutputInterface::BEFORE:
        printHeader();
        break;

      case COutputInterface::DURING:
        printBody();
        break;

      case COutputInterface::AFTER:
        printFooter();
        break;
    }
}

void CReport::separate(const Activity & /* activity */)
{
  if (!mpOstream) return;

  (*mpOstream) << std::endl;
}

void CReport::finish()
{
  mState = FooterFooter;

  printFooter();

  pdelete(mpHeader);
  pdelete(mpBody);
  pdelete(mpFooter);

  mState = Invalid;
}

void CReport::close()
{
  if (mStreamOwner) pdelete(mpOstream);

  mpOstream = NULL;
  mStreamOwner = false;
}

void CReport::printHeader()
{
  if (!mpOstream) return;

  if (mpHeader)
    switch (mState)
      {
        case Compiled:
          mpHeader->printHeader();
          mState = HeaderHeader;
          return;

        case HeaderHeader:
          mpHeader->printBody();
          mState = HeaderBody;
          return;

        case HeaderBody:
          mpHeader->printBody();
          return;

        case HeaderFooter:
          mpHeader->printFooter();
          return;

        default:
          return;
      }

  if (mState == HeaderFooter) return;

  mState = HeaderFooter;

  std::vector< CObjectInterface * >::iterator it = mHeaderObjectList.begin();
  std::vector< CObjectInterface * >::iterator end = mHeaderObjectList.end();

  if (it == end) return;

  for (; it != end; ++it)(*it)->print(mpOstream);

  (*mpOstream) << std::endl;
}

void CReport::printBody()
{
  if (!mpOstream) return;

  // Close the header part
  if (mState < HeaderFooter)
    {
      mState = HeaderFooter;

      if (mpHeader) mpHeader->printFooter();
    }

  if (mpBody)
    switch (mState)
      {
        case HeaderFooter:
          mpBody->printHeader();
          mState = BodyHeader;
          return;

        case BodyHeader:
          mpBody->printBody();
          mState = BodyBody;
          return;

        case BodyBody:
          mpBody->printBody();
          return;

        case BodyFooter:
          mpBody->printFooter();
          return;

        default:
          return;
      }

  if (mState == BodyFooter) return;

  mState = BodyBody;

  std::vector< CObjectInterface * >::iterator it = mBodyObjectList.begin();
  std::vector< CObjectInterface * >::iterator end = mBodyObjectList.end();

  if (it == end) return;

  for (; it != end; ++it)
    {
      (*it)->print(mpOstream);
    }

  (*mpOstream) << std::endl;
}

void CReport::printFooter()
{
  if (!mpOstream) return;

  // Close the body part
  if (mState < BodyFooter)
    {
      mState = BodyFooter;

      if (mpBody) mpBody->printFooter();
    }

  if (mpFooter)
    switch (mState)
      {
        case BodyFooter:
          mpFooter->printHeader();
          mState = FooterHeader;
          return;

        case FooterHeader:
          mpFooter->printBody();
          mState = FooterBody;
          return;

        case FooterBody:
          mpFooter->printBody();
          return;

        case FooterFooter:
          mpFooter->printFooter();
          return;

        default:
          return;
      }

  if (mState != FooterFooter) return;

  std::vector< CObjectInterface * >::iterator it = mFooterObjectList.begin();
  std::vector< CObjectInterface * >::iterator end = mFooterObjectList.end();

  if (it == end) return;

  for (; it != end; ++it)(*it)->print(mpOstream);

  (*mpOstream) << std::endl;
}

// Compile the List of Report Objects;
// Support Parallel

bool CReport::compile(CObjectInterface::ContainerList listOfContainer)
{
  bool success = true;
  COutputInterface::mObjects.clear();

  // check if there is a Report Definition Defined
  if (!mpReportDef) return false;

  if (mpReportDef->isTable())
    if (!const_cast< CReportDefinition * >(mpReportDef)->preCompileTable(listOfContainer)) success = false;

  generateObjectsFromName(listOfContainer, mHeaderObjectList, mpHeader,
                          mpReportDef->getHeaderAddr());

  if (mpHeader)
    success &= compileChildReport(mpHeader, listOfContainer);

  generateObjectsFromName(listOfContainer, mBodyObjectList, mpBody,
                          mpReportDef->getBodyAddr());

  if (mpBody)
    success &= compileChildReport(mpBody, listOfContainer);

  generateObjectsFromName(listOfContainer, mFooterObjectList, mpFooter,
                          mpReportDef->getFooterAddr());

  if (mpFooter)
    success &= compileChildReport(mpFooter, listOfContainer);

  mState = Compiled;

  return success;
}

std::ostream * CReport::open(const CDataModel * pDataModel,
                             std::ostream * pOstream)
{
  mpDataModel = pDataModel;
  assert(mpDataModel != NULL);

  // If an ostream is given and it is the currently assigned one
  // we do nothing.
  if (pOstream != NULL &&
      pOstream == mpOstream)
    return mpOstream;

  if (mStreamOwner)
    pdelete(mpOstream);

  mpOstream = pOstream;

  if (pOstream)
    {
      mStreamOwner = false;
    }
  else if (mTarget != "" && mpReportDef != NULL)
    {
      if (CDirEntry::isRelativePath(mTarget) &&
          !CDirEntry::makePathAbsolute(mTarget, mpDataModel->getReferenceDirectory()))
        mTarget = CDirEntry::fileName(mTarget);

      mpOstream = new std::ofstream;
      mStreamOwner = true;

      if (mAppend)
        {
          ((std::ofstream *) mpOstream)->
          open(CLocaleString::fromUtf8(mTarget).c_str(), std::ios_base::out | std::ios_base::app);
        }
      else
        {
          ((std::ofstream *) mpOstream)->
          open(CLocaleString::fromUtf8(mTarget).c_str(), std::ios_base::out);
        }

      if (!((std::ofstream *) mpOstream)->is_open())
        {
          CCopasiMessage(CCopasiMessage::ERROR, MCDirEntry + 3, mTarget.c_str());
          pdelete(mpOstream);
        }

      if (mpOstream)
        {
          mpOstream->precision(mpReportDef->getPrecision());
        }
    }

  return mpOstream;
}

std::ostream * CReport::getStream() const {return mpOstream;}

// make to support parallel tasks
void CReport::generateObjectsFromName(const CObjectInterface::ContainerList & listOfContainer,
                                      std::vector< CObjectInterface * > & objectList,
                                      CReport *& pReport,
                                      const std::vector<CRegisteredCommonName>* nameVector)
{
  objectList.clear();

  unsigned C_INT32 i;
  CObjectInterface * pObjectInterface;
  CReportDefinition * pReportDefinition;

  for (i = 0; i < nameVector->size(); i++)
    {
      pObjectInterface = CObjectInterface::GetObjectFromCN(listOfContainer, (*nameVector)[i]);

      if (pObjectInterface == NULL)
        {
          CCopasiMessage(CCopasiMessage::WARNING, MCCopasiTask + 6, (*nameVector)[i].c_str());
          continue;
        }

      if (!i && (pReportDefinition = dynamic_cast< CReportDefinition * >(pObjectInterface)) != NULL)
        {
          pReport = new CReport();
          pReport->setReportDefinition(pReportDefinition);

          return;
        }

      mObjects.insert(pObjectInterface);
      objectList.push_back(pObjectInterface);
    }
}

bool CReport::compileChildReport(CReport * pReport, CObjectInterface::ContainerList listOfContainer)
{
  pReport->open(mpDataModel, mpOstream);
  bool success = pReport->compile(listOfContainer);

  const CObjectInterface::ObjectSet & Objects = pReport->COutputInterface::getObjects();
  CObjectInterface::ObjectSet::const_iterator it = Objects.begin();
  CObjectInterface::ObjectSet::const_iterator end = Objects.end();

  for (; it != end; ++it)
    COutputInterface::mObjects.insert(*it);

  return success;
}
