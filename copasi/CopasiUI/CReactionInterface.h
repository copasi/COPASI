/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CReactionInterface.h,v $
   $Revision: 1.12 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/04/19 08:28:41 $
   End CVS Header */

#ifndef CREACTIONINTERFACE_H
#define CREACTIONINTERFACE_H

#include <vector>
#include <string>
#include "copasi.h" 
//#include "model/CChemEq.h"
#include "model/CReaction.h"
#include "model/CChemEqInterface.h"
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
     * This is the key that identifies the Reaction that is beeing edited
     */
    std::string mReactionReferenceKey;

    /**
     * The name of the reaction (which may change)
     */
    std::string mReactionName;

    /**
     * A copy of the chemical equation of the reaction
     */ 
    //CChemEq *mpChemEq;
    CChemEqInterface mChemEqI;

    /**
     * A pointer to the kinetic function of the reaction
     */
    const CFunction* mpFunction;

    /**
     * A copy of the function parameters
     */
    CFunctionParameters * mpParameters;

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

    /**
     * set a new chemical equation.
     * newFunction suggests a new kinetic function which is only used if adequate.
     */
    void setChemEqString(const std::string & eq, const std::string & newFunction = "");
    std::string getChemEqString() const {return mChemEqI.getChemEqString(false);};

    bool isReversible() const {return mChemEqI.getReversibility();};

    /**
     * set the reversibility.
     * newFunction suggests a new kinetic function which is only used if adequate.
     */
    void setReversibility(bool rev, const std::string & newFunction = "");

    /**
     * reverse the reaction and set the reversibility.
     * newFunction suggests a new kinetic function which is only used if adequate.
     */
    void reverse(bool rev, const std::string & newFunction = "");

    /**
     * This produces a list of metab names (from the chem eq) for use in
     * the combo boxes. The role must be given like a usage, e.g. "SUBSTRATE".
     */
    const std::vector<std::string> & getListOfMetabs(std::string role) const;

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
    {if (mpFunction) return mpParameters->size(); else return 0;};

    bool isVector(unsigned C_INT32 index) const
      {
        if (mpFunction) return ((*mpParameters)[index]->getType() == CFunctionParameter::VFLOAT64);
        else return (false);
      }

    std::string getUsage(unsigned C_INT32 index) const
      {
        if (mpFunction) return (*mpParameters)[index]->getUsage();
        else return emptyString;
      }

    std::string getParameterName(unsigned C_INT32 index) const
      {
        if (mpFunction) return (*mpParameters)[index]->getName();
        else return emptyString;
      }

    void setMetab(unsigned C_INT32 index, std::string mn);
    void removeMetab(unsigned C_INT32 index, std::string mn);
    const std::vector< std::string > & getMetabs(unsigned C_INT32 index) const
    {return mNameMap[index];}

    void setValue(unsigned C_INT32 index, C_FLOAT64 value) {mValues[index] = value;}
    const C_FLOAT64 & getValue(unsigned C_INT32 index) const {return mValues[index];}

    void initFromReaction(const CModel & model, const std::string & key);

    void writeBackToReaction(CModel & model) const;

    bool createMetabolites(CModel & model) const;

    bool isValid() const {return mValid;}

    /**
     * is the mapping of this parameter locked?
     */
    bool isLocked(unsigned C_INT32 index) const;
    bool isLocked(std::string usage) const;

  private:

    /**
     * guesses how to connect metabs with parameters for a specific usage
     */
    void connectFromScratch(std::string role, bool pedantic);

    void clearFunction();

    /**
     * checks if newFunction is an valid function for the reaction.
     * If it is not or if newFunction="" another function is chosen.
     */
    void findAndSetFunction(const std::string & newFunction = "");

    /**
     * returns a list of metabolites (from the chemical equation). Species´ can occur
     * several times according to theit multiplicity
     */
    std::vector<std::string> getExpandedMetabList(const std::string & role) const;

    void loadNameMap(const CModel & model, const CReaction & rea);
  };

#endif
