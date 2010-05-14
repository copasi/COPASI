// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/crosssection/CCrossSectionMethod.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2010/05/14 22:20:54 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CCrossSectionMethod.h"

CCrossSectionMethod *
CCrossSectionMethod::createCrossSectionMethod(CCopasiMethod::SubType subType)
{
  CCrossSectionMethod * pMethod = NULL;

  switch (subType)
    {
      case unset:
      case crossSectionMethod:
        pMethod = new CCrossSectionMethod(subType);
        break;

      default:
        fatalError();
    }

  return pMethod;
}

/**
 *  Default constructor.
 */
CCrossSectionMethod::CCrossSectionMethod(CCopasiMethod::SubType subType,
    const CCopasiContainer * pParent):
    CCopasiMethod(CCopasiTask::crosssection, subType, pParent)
    //mpProblem(NULL)
{

  CONSTRUCTOR_TRACE;
}

/**
 *  Copy constructor.
 *  @param "const CCrossSectionMethod &" src
 */
CCrossSectionMethod::CCrossSectionMethod(const CCrossSectionMethod & src,
    const CCopasiContainer * pParent):
    CCopasiMethod(src, pParent)
    //mpProblem(src.mpProblem)
{CONSTRUCTOR_TRACE;}

/**
 *  Destructor.
 */
CCrossSectionMethod::~CCrossSectionMethod()
{DESTRUCTOR_TRACE;}
