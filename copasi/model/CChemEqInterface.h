/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CChemEqInterface.h,v $
   $Revision: 1.1.1.1 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2004/10/26 15:17:57 $
   End CVS Header */

#ifndef CCHEMEQINTERFACE_H
#define CCHEMEQINTERFACE_H

#include <string>
#include <vector>
#include <set>

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

    const std::vector<std::string> & getListOfNames(const std::string & role) const;
    const std::vector<C_FLOAT64> & getListOfMultiplicities(const std::string & role) const;

    //right now only modifiers can be added to the ChemEq without entering them into the CHemEq string
    void addModifier(const std::string & name);
    void clearModifiers();

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
    static bool isValidEq(const std::string & eq);

  private:
    static std::string writeElement(const std::string & name, C_FLOAT64 mult, bool expanded);
    static bool splitChemEq(const std::string & input,
                            std::string & left, std::string & right, std::string & mod);

    static bool setElements(std::vector<std::string> & names,
                            std::vector<C_FLOAT64> & mults,
                            const std::string & reaction,
                            const bool modif = false);

    static bool extractElement(const std::string & input,
                               std::string::size_type & pos,
                               std::string & name, C_FLOAT64 & mult);

    static bool extractModifier(const std::string & input,
                                std::string::size_type & pos,
                                std::string & name);

    static bool checkFirstLevel(const std::string & eq);
  };

#endif
