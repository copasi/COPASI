#ifndef CCHEMEQINTERFACE_H
#define CCHEMEQINTERFACE_H

#include <string>
#include <vector>
#include <set>

#include "copasi.h"

class CChemEq;
class CModel;
class CReaction;

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

    const std::vector<std::string> & getListOfNames(const std::string & role) const;
    const std::vector<C_FLOAT64> & getListOfMultiplicities(const std::string & role) const;

    bool getReversibility() const {return mReversibility;};
    void setReversibility(bool rev) {mReversibility = rev;};

    void reverse();

    C_INT32 getMolecularity(const std::string & role) const;

    std::set<std::string> listOfNonUniqueMetabNames(const CModel * model) const;
    std::set<std::string> listOfNonExistingMetabNames(const CModel * model) const;

    bool createNonExistingMetabs(CModel * model) const;

    //convenience methods:
    static std::string getChemEqString(const CModel * model, const CReaction & rea, bool expanded);
    static void setChemEqFromString(const CModel * model, CReaction & rea, const std::string & ces);

  private:
    static std::string writeElement(const std::string & name, C_FLOAT64 mult, bool expanded);
    static bool splitChemEq(const std::string & input,
                            std::string & left, std::string & right, std::string & mod);

    static void setElements(std::vector<std::string> & names,
                            std::vector<C_FLOAT64> & mults,
                            const std::string & reaction,
                            const bool modif = false);

    static void extractElement(const std::string & input,
                               std::string::size_type & pos,
                               std::string & name, C_FLOAT64 & mult);

    static void extractModifier(const std::string & input,
                                std::string::size_type & pos,
                                std::string & name);
  };

#endif
