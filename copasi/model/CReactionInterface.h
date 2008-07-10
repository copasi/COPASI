// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CReactionInterface.h,v $
//   $Revision: 1.19 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/07/10 19:57:59 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CREACTIONINTERFACE_H
#define CREACTIONINTERFACE_H

#include <vector>
#include <string>
#include "copasi.h"
//#include "model/CChemEq.h"
#include "model/CReaction.h"
#include "model/CChemEqInterface.h"
#include "function/CFunction.h"

//class CFunction;
class CModel;

/**
 * This class provides an interface for dealing with reactions.
 * For representing the parameter mappings it uses object names.
 * A CReactionInterface allows editing a reaction while trying to
 * keep everything consistent.
 *
 * Note: Many of the methods need to be provided with a model.
 * While handling of the metabolites is completely independent of the
 * model (they are handled by name, and they don't need to exist),
 * the mapping of Compartments and global parameters is done with
 * the entities that exist in the model. This may seem inconsistent,
 * but the idea is that metabolites can be created from the gui by entering
 * them into the reaction equation. Compartments and global parameters
 * can only be chosen from the list of existing objects.
 */
class CReactionInterface
  {
  private:
    CModel * mpModel;

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
     * values of the kinetic parameters
     */
    std::vector<bool> mIsLocal;

  private:
    CReactionInterface();

  public:
    CReactionInterface(CModel * pModel);

    ~CReactionInterface();

    void setReactionName(const std::string & name) {mReactionName = name;};
    const std::string & getReactionName() const {return mReactionName;};

    /**
     * set a new chemical equation.
     * newFunction suggests a new kinetic function which is only used if adequate.
     */
    void setChemEqString(const std::string & eq, const std::string & newFunction);

    std::string getChemEqString() const {return mChemEqI.getChemEqString(false);};

    const CChemEqInterface & getChemEqInterface() const {return mChemEqI;};

    bool isReversible() const {return mChemEqI.getReversibility();};

    /**
     * this method tries to find out if the REACTION involves several compartments
     * It only takes into account the metabs that
     * actually exist in the model. A non existing metabolite is assumed
     * not to be in a different compartment
     */
    bool isMulticompartment() const;

    /**
     * set the reversibility.
     * newFunction suggests a new kinetic function which is only used if adequate.
     */
    void setReversibility(bool rev, const std::string & newFunction);

    /**
     * reverse the reaction and set the reversibility.
     * newFunction suggests a new kinetic function which is only used if adequate.
     */
    void reverse(bool rev, const std::string & newFunction);

    /**
     * This produces a list of metab names (from the chem eq) for use in
     * the combo boxes. The role must be given like a usage, e.g. "SUBSTRATE".
     */
    const std::vector<std::string> & getListOfMetabs(CFunctionParameter::Role role) const;

    /**
     * set the function. an empty mapping is created
     */
    void setFunctionWithEmptyMapping(const std::string & fn);

    /**
     * set the function.
     * a new mapping is created that tries to preserve as much information as
     * possible from the old mapping. Then a default mapping is set from
     * the chemical equation and the model (if possible).
     */
    void setFunctionAndDoMapping(const std::string & fn);

    const std::string & getFunctionName() const
      {if (mpFunction) return mpFunction->getObjectName(); else return emptyString;};

    const std::string & getFunctionDescription() const
    {if (mpFunction) return mpFunction->getInfix(); else return emptyString;};

    const CFunction * getFunction() const
    {return mpFunction;}

    std::vector< std::string > getListOfPossibleFunctions() const;

    //query information about the function variables

    C_INT32 size() const
      {if (mpFunction) return mpParameters->size(); else return 0;};

    bool isVector(unsigned C_INT32 index) const
      {
        if (mpFunction) return ((*mpParameters)[index]->getType() == CFunctionParameter::VFLOAT64);
        else return (false);
      }

    CFunctionParameter::Role getUsage(unsigned C_INT32 index) const
      {
        if (mpFunction) return (*mpParameters)[index]->getUsage();
        else return CFunctionParameter::VARIABLE;
      }

    std::string getParameterName(unsigned C_INT32 index) const
      {
        if (mpFunction) return (*mpParameters)[index]->getObjectName();
        else return emptyString;
      }

    // set/get the mapping

    void setMapping(unsigned C_INT32 index, std::string mn);

    void removeMapping(unsigned C_INT32 index, std::string mn);

    const std::vector< std::string > & getMappings(unsigned C_INT32 index) const
    {return mNameMap[index];}

    const std::string & getMapping(unsigned C_INT32 index) const
      {
        assert(!isVector(index));
        return mNameMap[index][0];
      }

    void setLocalValue(unsigned C_INT32 index, C_FLOAT64 value)
    {
      mValues[index] = value;
      mIsLocal[index] = true;
    }

    void setLocal(unsigned C_INT32 index)
    {
      mIsLocal[index] = true;
    }

    const C_FLOAT64 & getLocalValue(unsigned C_INT32 index) const {return mValues[index];}

    bool isLocalValue(unsigned C_INT32 index) const {return mIsLocal[index];};

    /**
     *  associate the function parameter referenced by "index" with the global
     *  parameter named pn. Only valid if the role for this function parameter is "PARAMETER".
     *  returns success
     */
    //bool setGlobalParameter(unsigned C_INT32 index, std::string pn);

    //const std::string & getGlobalParameter(unsigned C_INT32 index) const;

    //bool setCompartment(unsigned C_INT32 index, std::string pn);

    //const std::string & getCompartment(unsigned C_INT32 index) const;

    void initFromReaction(const std::string & key);

    /**
     * writes the information back to a CReaction.
     * createMetabolites() and createOtherObjects() should be called before.
     */
    bool writeBackToReaction(CReaction * rea);

    /**
     * create all metabolites that are needed by the reaction but do
     * not exist in the model yet.
     */
    bool createMetabolites();

    /**
     * create all other objects that are needed by the reaction but do
     * not exist in the model yet.
     */
    bool createOtherObjects() const;

    bool isValid() const;

    /**
     * Is the mapping of this parameter locked?
     * The bahaviour of this method is different for different roles:
     * SUBSTRATE, PRODUCT: according to the chemical equation
     * MODIFIER: always unlocked
     * TIME: always locked
     * VOLUME, PARAMETER: according to the model
     *
     * The idea is that in the reaction GUI new species can be entered
     * in the chemical equation that are then created automatically.
     * Compartments and global parameters can only be chosen from those
     * existing in the model.
     */
    bool isLocked(unsigned C_INT32 index) const;
    bool isLocked(CFunctionParameter::Role usage) const;

#ifdef COPASI_DEBUG
    void printDebug() const;
#endif // COPASI_DEBUG

  private:

    /**
     * initialize mapping (resize vectors and set names to "unknown").
     * Also initializes mpParameters but doesn't delete the old mpParameters.
     */
    void initMapping();

    /**
     * create new mapping, try to keep as much information from the current
     * mapping. Calls initMapping().
     */
    void copyMapping();

    /**
     * guesses how to connect metabs with parameters for a specific usage
     */
    void connectFromScratch(CFunctionParameter::Role role);

    /**
     * tries to determine the mapping for PARAMETER, VOLUME, TIME
     * only if the current mapping is "unknown".
     * Is typically called after initMapping() and copyMapping()
     */
    void connectNonMetabolites();

    /**
     * updates the modifiers in the chemical equation according to
     * the parameter mapping
     */
    void updateModifiersInChemEq();

    void clearFunction();

    /**
     * checks if newFunction is an valid function for the reaction.
     * If it is not or if newFunction="" another function is chosen.
     */
    void findAndSetFunction(const std::string & newFunction);

    /**
     * returns a list of metabolites (from the chemical equation). Species can occur
     * several times according to theit multiplicity
     */
    std::vector<std::string> getExpandedMetabList(CFunctionParameter::Role role) const;

    bool loadMappingAndValues(const CReaction & rea);
  };

#endif
