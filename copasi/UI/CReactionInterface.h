#ifndef CREACTIONINTERFACE_H
#define CREACTIONINTERFACE_H

#include <vector>
#include <string>
#include "copasi.h"
#include "model/CChemEq.h"
#include "model/CReaction.h"
#include "function/CFunction.h"

class CFunction;
class CModel;

/**
 * This class provides an interface between a reaction and the gui.
 */
class CReactionInterface
  {
  private:

    std::string emptyString;

    /**
     * This is the name that identifies the Reaction that is beeing edited (may become a key later)
     */
    std::string mReactionReferenceName;

    /**
     * The name of the reaction (which may change)
     */
    std::string mReactionName;

    /**
     * A copy of the chemical equation of the reaction
     */
    CChemEq mChemEq;

    /**
     * A pointer to the kinetic function of the reaction
     */
    const CFunction* mpFunction;

    /**
     * A copy of the function parameters
     */
    CFunctionParameters mParameters;

    /**
     * what metabolite for what function parameter
     */
    std::vector< std::vector< std::string > > mNameMap;

    /**
     * values of the kinetic parameters
     */
    std::vector< C_FLOAT64 > mValues;

    /**
     * is the reaction valid?
     */
    bool mValid;

  public:
    CReactionInterface();
    ~CReactionInterface();

    void setReactionName(const std::string & name) {mReactionName = name;};
    const std::string & getReactionName() const {return mReactionName;};

    void setChemEqString(const std::string & eq);
    std::string getChemEqString() const {return mChemEq.getChemicalEquationConverted();};
    bool isReversible() const {return mChemEq.getReversibility();};
    void setReversibility(bool rev);

    /**
     * This produces a list of metab names (from the chem eq) for use in
     * the combo boxes. The role must be given like a usage, e.g. "SUBSTRATE".
     */
    std::vector<std::string> getListOfMetabs(std::string role) const;

    /**
     * set the function.
     * "force" tells whether a remapping from scratch of the parameters is also
     * enforced when the function is the same as before
     */
    void setFunction(const std::string & fn, bool force = false);
    const std::string & getFunctionName() const
      {if (mpFunction) return mpFunction->getName(); else return emptyString;};

    std::vector< std::string > getListOfPossibleFunctions() const;

    C_INT32 size() const
    {if (mpFunction) return mpFunction->getParameters().size(); else return 0;};

    bool isVector(C_INT32 index) const
      {
        if (mpFunction) return (mpFunction->getParameters()[index]->getType() == CFunctionParameter::VFLOAT64);
        else return (false);
      }

    std::string getUsage(C_INT32 index) const
      {
        if (mpFunction) return mpFunction->getParameters()[index]->getUsage();
        else return emptyString;
      }

    std::string getParameterName(C_INT32 index) const
      {
        if (mpFunction) return mpFunction->getParameters()[index]->getName();
        else return emptyString;
      }

    void setMetab(C_INT32 index, std::string mn);
    void removeMetab(C_INT32 index, std::string mn);
    const std::vector< std::string > & getMetabs(C_INT32 index) const
    {return mNameMap[index];}

    void setValue(C_INT32 index, C_FLOAT64 value) {mValues[index] = value;}
    const C_FLOAT64 & getValue(C_INT32 index) const {return mValues[index];}

    void initFromReaction(const std::string & rn, const CModel & model);

    void writeBackToReaction(CModel & model) const;

    bool isValid() const {return mValid;}

    /**
     * is the mapping of this parameter locked?
     */
    bool isLocked(C_INT32 index) const;
    bool isLocked(std::string usage) const;

  private:

    /**
     * guesses how to connect metabs with paramters for a specific usage
     */
    void connectFromScratch(std::string role, bool pedantic);

    void clearFunction();
  };

#endif
