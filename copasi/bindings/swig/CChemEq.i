// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

%{

#include "model/CChemEq.h"

%}

class CChemEq : public CCopasiContainer
{
  public:
    enum MetaboliteRole
    {
      PRODUCT = 0,
      SUBSTRATE,
      MODIFIER,
      NOROLE
    };

    /**
     * Default constructor
     * @param const std::string & name (default: "NoName")
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CChemEq(const std::string & name = "NoName",
            const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor
     * @param "const CChemEq &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CChemEq(const CChemEq & src,
            const CCopasiContainer * pParent = NULL);

    /**
     *  Destructor
     */
    ~CChemEq();


    void setReversibility(bool revers);
    bool getReversibility() const;

    bool addMetabolite(const std::string & key, const C_FLOAT64 mult, const MetaboliteRole role);

    /**
     *  Retrieves the vector of substrates and their multiplicity
     *  in the chemical reaction.
     *  @return "vector < CChemEqElement * > &" substrates
     */
    const CCopasiVector < CChemEqElement > & getSubstrates() const;

    /**
     *  Retrieves the vector of products and their multiplicity
     *  in the chemical reaction.
     *  @return "vector < CChemEqElement * > &" products
     */
    const CCopasiVector < CChemEqElement > & getProducts() const;

    /**
     *  Retrieves the vector of Modifiers and their multiplicity
     */
    const CCopasiVector < CChemEqElement > & getModifiers() const;

    /**
     *  Retrieves the vector of metabolites and their total balance
     *  in the chemical reaction.
     *  @return "vector < CChemEqElement * > &" balances
     */
    const CCopasiVector < CChemEqElement > & getBalances() const;

    /**
     * Returns the number of comparments the chemical equation is associated
     * with.
     */
    unsigned C_INT32 getCompartmentNumber() const;

    /**
     *  get the largest (smallest) compartment that the reaction touches.
     */
    const CCompartment & getLargestCompartment() const;

    %extend
    {
        CChemEqElement* getSubstrate(unsigned C_INT32 index)
        {
          return self->getSubstrates()[index];
        }

        CChemEqElement* getProduct(unsigned C_INT32 index)
        {
          return self->getProducts()[index];
        }

        CChemEqElement* getModifier(unsigned C_INT32 index)
        {
          return self->getModifiers()[index];
        }

        CChemEqElement const* getBalance(unsigned C_INT32 index)
        {
          return self->getBalances()[index];
        }
    }


};


