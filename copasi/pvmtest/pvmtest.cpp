// Main
//
// (C) Pedro Mendes 2000
//

// #include <iostream>
// #include <fstream>
// #include <string>
// #include <strstream>
// #include <vector>
// #include <iomanip>
// #include <algorithm>

#define COPASI_MAIN

#include "copasi.h"
#include "utilities/CGlobals.h"
#include "optimization/COptMethod.h"
#include "optimization/CRealProblem.h"

C_INT32 TestOptimization(void);     //yohe: new

int main(int argc, char *argv[])
{
  cout << "Starting main program." << endl;
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

  delete Copasi;
  cout << "Leaving main program." << endl;
  return 0;
}

C_INT32 TestOptimization(void)
{
  int i;
  cout << "TestOptimization() begins --- " << endl;
  COptMethod * CRand = COptMethod::createMethod();

  CRealProblem *CReal = new CRealProblem();
  CRand->setProblem(CReal);
  //CRandom *testRand = new CRandom(2);
  //CRandom *rand;
  //CRandom::Type t;
  //t=CRandom::r250;
  //rand = CRandom::createGenerator(t,2);

  // set parameter numbers....
  CReal->setParameterNum(5);

  // set the individual parameters

  CRand->setValue(0, 100000);

  for (i = 0; i < 5; i++)
    {
      CReal->setParameterMin(i, -5);
      CReal->setParameterMax(i, 2);
    }

  CRand->optimise();
  cout << "result---best values";
  for (i = 0; i < 5; i++)
    {
      cout << CReal->getBestValue(i);
      cout << "\n";
    }

  pdelete(CRand);
  return 0;
}
