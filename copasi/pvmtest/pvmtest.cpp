/* Begin CVS Header
  $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/pvmtest/pvmtest.cpp,v $
  $Revision: 1.6 $
  $Name:  $
  $Author: gauges $
  $Date: 2009/02/18 20:54:47 $
  End CVS Header */

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#define COPASI_MAIN

#include "copasi.h"
#include "utilities/CGlobals.h"
#include "optimization/COptMethod.h"
#include "optimization/CRealProblem.h"
#include "utilities/CCopasiException.h"
#include "report/CCopasiRootContainer.h"

C_INT32 TestOptimization(void);     //yohe: new

C_INT main(C_INT argc, char *argv[])
{
  cout << "Starting main program." << endl;

  CCopasiContainer::init();
  Copasi = new CGlobals;

  Copasi->setArguments(argc, argv);

  try
    {
      TestOptimization();
    }

  catch (CCopasiException Exception)
    {
      cout << Exception.getMessage().getText() << endl;
    }

  pdelete(Copasi);
  pdelete(CCopasiRootContainer::Root);

  cout << "Leaving main program." << endl;
  return 0;
} // end of main

C_INT32 TestOptimization(void)
{
  int i, num_params;
  cout << "TestOptimization() begins --- " << endl;
  COptMethod * CRand = COptMethod::createMethod();

  CRealProblem *CReal = new CRealProblem();
  CRand->setProblem(CReal);

  // set parameter numbers....
  /**** hard coded num of params ***/
  num_params = 10;
  CReal->setParameterNum(num_params);

  // set the individual parameters

  CRand->setValue(0, 100000);

  for (i = 0; i < num_params; i++)
    {
      CReal->setParameterMin(i, -5);
      CReal->setParameterMax(i, 2);
    }

  CRand->optimise();
  cout << "result---best values";
  for (i = 0; i < num_params; i++)
    {
      cout << CReal->getBestValue(i);
      cout << "\n";
    }

  pdelete(CRand);
  return 0;
}
