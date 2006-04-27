/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CChemEqInterface.h,v $
   $Revision: 1.15 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/04/27 01:29:21 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CCHEMEQINTERFACE_H
#define CCHEMEQINTERFACE_H

#include <string>
#include <vector>
#include <set>

#include "function/CFunctionParameter.h"

class CChemEq;
class CModel;
class CReaction;
class CCompartment;

/**
 * This class describes a chemical equation based on metabolite names
 * It supports parsing and generating string representations.
 * Note that this class handles only metab names without caring about whether
 * these metabs exist in the model. There is however a method to create
 * the missing metabs.
 */
class CChemEqInterface
  {
  private:
    std::vector< std::string > mSubstrateNames;
    std::vector< std::string > mProductNames;
    std::vector< std::string > mModifierNames;

    std::vector< C_FLOAT64 > mSubstrateMult;
    std::vector< C_FLOAT64 > mProductMult;
    std::vector< C_FLOAT64 > mModifierMult;

    bool mReversibility;

  public:
    CChemEqInterface();

    ~CChemEqInterface();

    std::string getChemEqString(bool expanded) const;
    bool setChemEqString(const std::string & ces);

    bool loadFromChemEq(const CModel * model, const CChemEq & ce);
    bool writeToChemEq(const CModel * model, CChemEq & ce) const;

    const std::vector<std::string> & getListOfNames(CFunctionParameter::Role role) const;
    const std::vector<C_FLOAT64> & getListOfMultiplicities(CFunctionParameter::Role role) const;

    /**
     * add a modifier to the chemical equation. It is only added if it is not alreay in there.
     */
    void addModifier(const std::string & name);
    void clearModifiers();

    bool getReversibility() const {return mReversibility;};
    void setReversibility(bool rev) {mReversibility = rev;};

    /**
     * this method tries to find out if the chemical equation involves several compartments
     * in a given model. It only takes into account the metabs that
     * actually exist in the model. A non existing metabolite is assumed
     * not to be in a different compartment
     */
    bool isMulticompartment(const CModel * model) const;

    /**
     * convenience method. If the reaction is single compartment the
     * compartment is returned, else NULL.
     */
    const CCompartment * getCompartment(const CModel * model) const;

    void reverse();

    C_INT32 getMolecularity(CFunctionParameter::Role role) const;

    std::set<std::string> listOfNonUniqueMetabNames(const CModel * model) const;
    std::set<std::string> listOfNonExistingMetabNames(const CModel * model) const;

    bool createNonExistingMetabs(CModel * model) const;

    //convenience methods:
    static std::string getChemEqString(const CModel * model, const CReaction & rea, bool expanded);
    static void setChemEqFromString(const CModel * model, CReaction & rea, const std::string & ces);
    static bool isValidEq(const std::string & eq);

  private:
    static std::string writeElement(const std::string & name, C_FLOAT64 mult, bool expanded);
  };

#endif
