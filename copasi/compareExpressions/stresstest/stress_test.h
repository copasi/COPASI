// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/stresstest/stress_test.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/10/09 06:29:42 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef STRESS_TEST_H__
#define STRESS_TEST_H__

#include <string>
#include <vector>

class CNormalFraction;
class Model;

// This test reads all models from the biomodels database and normalizes all
// mathematical expressions it finds in there.
// Later on, it will do the same for the functions in COPASIs function database
// and compare the expressions from the model to those in the function database
// in order to find out if they are the same.
class stress_test
  {
  public:
    /**
     * Constructor.
     */
    stress_test();

    /**
     * Destructor.
     */
    virtual ~stress_test();

    /**
     * Goes through the list of files, loads each file and normalizes the
     * mathematical expressions in the contained model.
     */
    void run(const std::vector<std::string>& filenames);

  protected:
    /**
     * Loads an sbml model from the given file and
     * normalized all mathematical expressions in the SBML model.
     */
    void normalizeMath(const std::string& filename);

    /**
     * Normalizes all expressions but the function definitions in the given
     * model.
     */
    void normalizeExpressions(const Model* pModel);

    /**
     * Normalizes the function definitions in the given model.
     */
    void normalizeFunctionDefinitions(const Model* pModel);

    /**
     * Normalizes COPASIs function database.
     */
    void normalizeFunctionDB();

  protected:
    std::vector<CNormalFraction*> mNormalizedExpressions;
    std::vector<CNormalFraction*> mNormalizedFunctionDefinitions;
    std::vector<CNormalFraction*> mNormalizedCOPASIFunctionDefinitions;
  };

#endif // STRESS_TEST_H__
