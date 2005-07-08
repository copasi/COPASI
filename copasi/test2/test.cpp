/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/test2/test.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/07/08 09:11:24 $
   End CVS Header */

// Main
//
// (C) Stefan Hoops 2002
//

#include <stdlib.h>
#include <sstream>
#include <string>
#include <iostream>

#define COPASI_MAIN
#define COPASI_TRACE_CONSTRUCTION

#include "copasi.h" 
//#include "CopasiDataModel/CCopasiDataModel.h"
//#include "utilities/CCopasiMessage.h"
//#include "utilities/CCopasiException.h"
//#include "utilities/CCopasiTask.h"
//#include "utilities/CCopasiProblem.h"
//#include "commandline/COptionParser.h"
//#include "commandline/COptions.h"
//#include "function/CFunctionDB.h"
//#include "function/CEvaluationTree.h"

#include "utilities/CopasiTime.h" 
//#include "randomGenerator/CRandom.h"
//#include "report/CKeyFactory.h"

#include "function/CFunction.h"

int main(int argc, char *argv[])
{
  std::cout << "CFunction test program" << std::endl;

  CFunction * func0 = new CFunction("abc", NULL);

  func0->setInfix("2*A*B");
  func0->compile();

  CFunctionParameters & fp = func0->getVariables();

  std::cout << "This function has " << fp.size() << " variables." << std::endl;

  //now we create the data structure to call the function

  CCallParameters<C_FLOAT64>* cp = new CCallParameters<C_FLOAT64>(fp.size());

  //some float variables
  C_FLOAT64 f_a = 2.0;
  C_FLOAT64 f_b = 3.0;

  (*cp)[0].value = &f_a;
  (*cp)[1].value = &f_b;

  std::cout << "" << func0->calcValue(*cp) << std::endl;

  return 0;
}
