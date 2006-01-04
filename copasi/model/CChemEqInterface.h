/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CChemEqInterface.h,v $
   $Revision: 1.11.2.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/01/04 15:20:45 $
   End CVS Header */

#ifndef CCHEMEQINTERFACE_H
#define CCHEMEQINTERFACE_H

#include <string>
#include <vector>
#include <set>

#include "function/CFunctionParameter.h"

class CChemEq;
class CModel;
class CReaction;

/** @dia:pos 21.8,-18.2 */
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

    //right now only modifiers can be added to the ChemEq without entering them into the CHemEq string
    void addModifier(const std::string & name);
    void clearModifiers();

    bool getReversibility() const {return mReversibility;};
    void setReversibility(bool rev) {mReversibility = rev;};

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
