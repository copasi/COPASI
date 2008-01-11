// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CChemEqInterface.h,v $
//   $Revision: 1.19 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/01/11 15:12:28 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
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
    CModel * mpModel;

    std::vector< std::string > mSubstrateNames;
    std::vector< std::string > mProductNames;
    std::vector< std::string > mModifierNames;

    std::vector< C_FLOAT64 > mSubstrateMult;
    std::vector< C_FLOAT64 > mProductMult;
    std::vector< C_FLOAT64 > mModifierMult;

    std::vector< std::string > mSubstrateCompartments;
    std::vector< std::string > mProductCompartments;
    std::vector< std::string > mModifierCompartments;

    std::vector< std::string > mSubstrateDisplayNames;
    std::vector< std::string > mProductDisplayNames;
    std::vector< std::string > mModifierDisplayNames;

    bool mReversibility;

  private:
    CChemEqInterface();

  public:
    CChemEqInterface(CModel * pModel);

    ~CChemEqInterface();

    std::string getChemEqString(bool expanded) const;
    bool setChemEqString(const std::string & ces);

    bool loadFromChemEq(const CChemEq & ce);
    bool writeToChemEq(CChemEq & ce) const;

    const std::vector<C_FLOAT64> & getListOfMultiplicities(CFunctionParameter::Role role) const;
    const std::vector<std::string> & getListOfDisplayNames(CFunctionParameter::Role role) const;

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
    bool isMulticompartment() const;

    /**
     * convenience method. If the reaction is single compartment the
     * compartment is returned, else NULL.
     */
    const CCompartment * getCompartment() const;

    void reverse();

    unsigned C_INT32 getMolecularity(CFunctionParameter::Role role) const;

    std::set<std::string> listOfNonUniqueMetabNames() const;
    std::set< std::pair< std::string, std::string > > listOfNonExistingMetabNames() const;

    bool createNonExistingMetabs();

    //convenience methods:
    static std::string getChemEqString(CModel * model, const CReaction & rea, bool expanded);
    static void setChemEqFromString(CModel * model, CReaction & rea, const std::string & ces);
    static bool isValidEq(const std::string & eq);

  private:
    void buildDisplayNames();
    void completeCompartments();
    static std::string writeElement(const std::string & name, C_FLOAT64 mult, bool expanded);
  };

#endif
