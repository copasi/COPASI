// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CCopasiMethod.i,v $ 
//   $Revision: 1.7 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2008/04/21 10:27:08 $ 
// End CVS Header 

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

%{

#include "utilities/CCopasiMethod.h"  

%}


class CCopasiMethod : public CCopasiParameterGroup
{
  public:
    /**
     * Enumeration of the sub types of methods known to COPASI.
     */
    enum SubType
    {
      unset = 0,
      RandomSearch,
      RandomSearchMaster,
      SimulatedAnnealing,
      GeneticAlgorithm,
      EvolutionaryProgram,
      SteepestDescent,
      HybridGASA,
      GeneticAlgorithmSR,
      HookeJeeves,
      LevenbergMarquardt,
      NelderMead,
      SRES,
      Statistics,
      ParticleSwarm,
      Praxis,
      TruncatedNewton,
      Newton,
      deterministic,
      LSODAR,
      stochastic,
      hybrid,
      hybridLSODA,
#ifdef COPASI_TSSA
      tssILDM,
      tssCSP,
#endif // COPASI_TSSA
      tauLeap,
      mcaMethodReder,
      scanMethod,
      lyapWolf,
#ifdef COPASI_TSS
      tssMethod,
#endif // COPASI_TSS
      sensMethod,
#ifdef COPASI_SSA
      ssaMethod,
#endif // COPASI_SSA
#ifdef COPASI_EXTREMECURRENTS
      extremeCurrents,
#endif
      EFMAlgorithm,
      Householder
    };

    /**
     * Convert a SubTypeName to the matching enum value.
     * Returns CCopasiMethod::unset if no match is found.
     * @param (const std::string & subTypeName)
     * @return CCopasiMethod::SubType type
     */
    static
    CCopasiMethod::SubType TypeNameToEnum(const std::string & subTypeName);


    /**
     * Copy constructor
     * @param const CCopasiMethodr & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CCopasiMethod(const CCopasiMethod & src,
                  const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    virtual ~CCopasiMethod();


    /**
     * Retrieve the type of the method
     * @return  const string & type
     */
    const CCopasiTask::Type & getType() const;

    /**
     * Retrieve the sub type of the method
     * @return CCopasiMethod::SubType & subType
     */
    const CCopasiMethod::SubType & getSubType() const;

%extend{
  static const std::string& getSubTypeName(const int& subType)
  {
    return CCopasiMethod::SubTypeName[subType];
  }
}

};


