// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2002 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#define COPASI_MAIN

#include "copasi/copasi.h"
#include "copasi/utilities/CGlobals.h"
#include "copasi/optimization/COptMethod.h"
#include "copasi/optimization/CRealProblem.h"
#include "copasi/utilities/CCopasiException.h"
#include "copasi/core/CRootContainer.h"

C_INT32 TestOptimization(void);     //yohe: new

C_INT main(C_INT argc, char *argv[])
{
  cout << "Starting main program." << endl;

  CDataContainer::init();
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
  pdelete(CRootContainer::Root);

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
