/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sensitivities/CSensProblem.cpp,v $
   $Revision: 1.7 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/06/23 12:43:23 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <string>

#include "copasi.h"
#include "CSensProblem.h"
//#include "model/CModel.h"
//#include "model/CState.h"
#include "CopasiDataModel/CCopasiDataModel.h"

bool CSensItem::isSingleObject() const
  {
    return mIsSingleObject;
  }

const CCopasiObjectName & CSensItem::getSingleObjectCN() const
  {
    return mSingleObjectCN;
  }

std::string CSensItem::getSingleObjectDisplayName() const
  {
    return "";
  }

const CObjectLists::ListType & CSensItem::getListType() const
  {
    return mListType;
  }

std::string CSensItem::getListTypeDisplayName() const
  {
    return "";
  }

//************************ CSensProblem ***************************

const std::string CSensProblem::SubTaskName[] =
  {
    "Not Set",
    "Steady State",
    "Time Series",
    "Lyapunov Exponents",
  };

const char * CSensProblem::XMLSubTask[] =
  {
    "NotSet",
    "SteadyState",
    "TimeSeries",
    "LyapunovExponents",
  };

/**
 *  Default constructor.
 *  @param "CModel *" pModel
 */
CSensProblem::CSensProblem(const CCopasiContainer * pParent):
    CCopasiProblem(CCopasiTask::steadyState, pParent)
{
  //addParameter("JacobianRequested", CCopasiParameter::BOOL, true);
  //addParameter("StabilityAnalysisRequested", CCopasiParameter::BOOL, true);
  CONSTRUCTOR_TRACE;
}

/**
 *  Copy constructor.
 *  @param "const CSensProblem &" src
 */
CSensProblem::CSensProblem(const CSensProblem & src,
                           const CCopasiContainer * pParent):
    CCopasiProblem(src, pParent)
{CONSTRUCTOR_TRACE;}

/**
 *  Destructor.
 */
CSensProblem::~CSensProblem()
{DESTRUCTOR_TRACE;}

/**
 *   set the problem's SubTaskType:
 */
void
CSensProblem::setSubTaskType(const CSensProblem::SubTaskType & type)
{mSubTaskType = type;}

/**
 *   get the problem's SubTaskType:
 **/
const CSensProblem::SubTaskType &
CSensProblem::getSubTaskType() const {return mSubTaskType;}
