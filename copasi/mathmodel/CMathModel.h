/**
 *  CMathModel class.
 *  The class CMathModel is a mathematical representation of a chemical
 *  model (class CModel
 *
 *  Created for Copasi by Stefan Hoops 2003
 */

#ifndef COPASI_CMathModel
#define COPASI_CMathModel

#include <map>
#include <string>
#include <vector>

#include "model/CReaction.h"

class CModel;
class CMathConstantCompartment;
class CMathVariableMetab;
class CMathConstantMetab;
class CMathVariableVolume;
class CMathVariableTime;
class CMathSymbol;
class CMathConstantParameter;
class CMathConstantReference;
class CMathEq;
class CMathNode;
class CMathNodeFunction;
class CMathNodeOperation;

/** @dia:pos 97.0405,-33.6536 */
class CMathModel
  {
    // Attributes
  private:
    /**
     *
     */
    const CModel * mpModel;

    /**
     *
     */
    /** @dia:route 4,14; h,36.0092,8.45635,44.0627,-29.1536,97.0405 */
    std::map< std::string, CMathConstantCompartment * > mCompartmentList;

    /**
     *
     */
    /** @dia:route 22,2; h,97.0405,-25.9536,94.1261,19.8639,89.2166 */
    std::map< std::string, CMathVariableMetab * > mMetabList;

    /**
     *
     */
    /** @dia:route 9,16; h,32.7356,21.502,44.9189,-28.3536,97.0405 */
    std::map< std::string, CMathConstantMetab * > mFixedMetabList;

    /**
     *
     */
    /** @dia:route 20,2; h,97.0405,-26.7536,93.2281,10.1749,84.0686 */
    std::map< std::string, CMathVariableVolume * > mVolumeList;

    /**
     *
     */
    /** @dia:route 24,2; h,97.0405,-25.1536,95.0241,35.5887,83.9366 */
    CMathVariableTime * mpTime; // done

    /**
     *
     */
    /** @dia:route 12,2; h,97.0405,-29.9536,-6.00072,-25.6956,-12.6802 */
    std::map< std::string, CMathSymbol * > mFunctionList;

    /**
     *
     */
    /** @dia:route 4,18; h,36.0356,33.3698,45.8713,-27.5536,97.0405 */
    std::map< std::string, CMathConstantParameter * > mConstantsList;

    /**
     *
     */
    std::vector< CMathEq * > mEqList;

    /**
     *
     */
    CMathConstantReference * mpConversionFactor;

    // Operations
  public:
    /**
     *
     */
    CMathModel();

    /**
     *
     */
    CMathModel(const CMathModel & src);

    /**
     *
     */
    ~CMathModel();

    /**
     *
     */
    bool setModel(const CModel * pModel);

    /**
     *
     */
    const CModel * getModel() const;

    /**
     *
     */
    bool compile();

    /**
     *
     */
    std::map< std::string, CMathConstantCompartment * > & getCompartmentList();

    /**
     *
     */
    std::map< std::string, CMathVariableMetab * > & getMetabList();

    /**
     *
     */
    std::map< std::string, CMathConstantMetab * > & getFixedMetabList();

    /**
     *
     */
    std::map< std::string, CMathVariableVolume * > & getVolumeList();

    /**
     *
     */
    CMathVariableTime * getTime();

    /**
     *
     */
    std::map< std::string, CMathSymbol * > & getFunctionList();

    /**
     *
     */
    std::map< std::string, CMathConstantParameter * > & getConstantsList();

    /**
     *
     */
    std::vector< CMathEq * > & getEqList();

  private:
    /**
     *
     */
    bool buildCompartmentList();

    /**
     *
     */
    bool buildMetabList();

    /**
     *
     */
    bool buildFixedMetabList();

    /**
     *
     */
    bool buildVolumeList();

    /**
     *
     */
    bool buildTime();

    /**
     *
     */
    bool buildFunctionList();

    /**
     *
     */
    bool buildConstantsList();

    /**
     *
     */
    bool compileCompartmentList();

    /**
     *
     */
    bool compileMetabList();

    /**
     *
     */
    bool compileFixedMetabList();

    /**
     *
     */
    template < class SymbolList > bool clearList(SymbolList & list);

    /**
     *
     */
    bool clearEqList();

    /**
     *
     */
    bool buildEqList();

    /**
     *
     */
    CMathNode * createScalingFactor(const CReaction * pReaction);

    /**
     * Create a node presenting the kinetic function for a reaction
     * including it list of parameters.
     * @param const CReaction * pReaction
     * @return CMathNodeFunction * pFunction
     */
    static CMathNodeFunction * createFunction(const CReaction * pReaction);

    /**
     *
     */
    static CMathNodeOperation * createComponent(const CChemEqElement * pElement,
        CMathNode * pScalingFactor,
        CMathNodeFunction * pFunction);

    /**
     *
     */
    static bool addParameterSymbols(const CCopasiVector< CReaction::CId2Param > & parameters);

    /**
     *
     */
    static bool deleteParameterSymbols(const CCopasiVector< CReaction::CId2Param > & parameters);
  };

#endif // COPASI_CMathModel
