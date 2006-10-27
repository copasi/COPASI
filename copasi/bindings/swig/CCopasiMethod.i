%{

#include "utilities/CCopasiMethod.h"  

%}

#ifndef COPASI_DEBUG

%nodefaultctor
%nodefaultdtor

#endif /* !COPASI_DEBUG */


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
      Newton,
      deterministic,
      LSODAR,
      stochastic,
      hybrid,
      hybridLSODA,
      tauLeap,
      mcaMethodReder,
      scanMethod,
      lyapWolf,
      tssMethod,
      sensMethod,
#ifdef COPASI_SSA
      ssaMethod,
#endif // COPASI_SSA
#ifdef COPASI_EXTREMECURRENTS
      extremeCurrents,
#endif
      EFMAlgorithm
    };

    /**
     * String literals for the GUI to display sub type names of methods known
     * to COPASI.
     */
    static const std::string SubTypeName[];

    /**
     * Convert a SubTypeName to the matching enum value.
     * Returns CCopasiMethod::unset if no match is found.
     * @param (const std::string & subTypeName)
     * @return CCopasiMethod::SubType type
     */
    static
    CCopasiMethod::SubType TypeNameToEnum(const std::string & subTypeName);

#ifdef COPASI_DEBUG

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

#endif /* COPASI_DEBUG */

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

    /**
     * Check if the method is suitable for this problem
     * @return bool suitability of the method
     */
    virtual bool isValidProblem(const CCopasiProblem * pProblem);

};

#ifndef COPASI_DEBUG

%clearnodefaultctor
%clearnodefaultdtor

#endif /* !COPASI_DEBUG */


