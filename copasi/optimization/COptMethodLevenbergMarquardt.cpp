/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptMethodLevenbergMarquardt.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/04/03 18:51:14 $
   End CVS Header */

#include "copasi.h"

#include "COptMethod.h"

COptMethodLevenbergMarquardt::COptMethodLevenbergMarquardt(const CCopasiContainer * pParent):
    COptMethod(CCopasiTask::optimization, CCopasiMethod::GeneticAlgorithm, pParent)
{
  // addParameter("Number of Generations", CCopasiParameter::UINT, (unsigned C_INT32) 200);

  initObjects();
}

COptMethodLevenbergMarquardt::COptMethodLevenbergMarquardt(const COptMethodLevenbergMarquardt & src,
    const CCopasiContainer * pParent):
    COptMethod(src, pParent)
{initObjects();}

COptMethodLevenbergMarquardt::~COptMethodLevenbergMarquardt()
{cleanup();}

bool COptMethodLevenbergMarquardt::optimise()
{return true;}

void COptMethodLevenbergMarquardt::initObjects()
{
  // addObjectReference("Current Generation", mGeneration, CCopasiObject::ValueInt);
}
