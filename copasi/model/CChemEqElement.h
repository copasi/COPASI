/**
 *  CChemEqElement class.
 *  Describing an element of a chemical equation Stefan Hoops 2001
 *
 *  Created for Copasi by Stefan Hoops 2001
 */

#ifndef COPASI_CChemEqElement
#define COPASI_CChemEqElement

#include <string>

#include "CMetab.h"

class CChemEqElement
  {
    //  Attributes

  private:
    /**
     *  The name of the metabolite the element
     */
    string mMetaboliteName;

    /**
     *  The name of the compartment the element is located in
     */
    string mCompartmentName;

    /**
     *  The multiplizity of the metabolite
     */
    C_FLOAT64 mMultiplicity;

    /**
     *  A pointer to the metabolite
     */
    CMetab * mpMetabolite;

    // Operations

  public:
    /**
     *  Default constructor
     */
    CChemEqElement();

    /**
     *  Copy constructor
     *  @param "const CChemEqElement &" src
     */
    CChemEqElement(const CChemEqElement & src);

    /**
     *  Destructor
     */
    ~CChemEqElement();

    /**
     *  cleanup
     */
    void cleanup();

    /**
     *  Set the multiplicity of the element.
     *  @param "const C_FLOAT64" multiplicity
     */
    void setMultiplicity(const C_FLOAT64 multiplicity);

    /**
     *  Retrieves the multiplicity of the element.
     *  @return C_FLOAT64 multiplicity
     */
    C_FLOAT64 getMultiplicity() const;

    /**
     *  Set the metabolite of the element.
     *  @param "const CMetab &" metabolite
     */
    void setMetabolite(CMetab & metabolite);

    /**
     *  Retrieves the metabolite of the element.
     *  @return "CMetab &" metabolite
     */
    CMetab & getMetabolite() const;

    /**
     *  Set the name of the element.
     *  @param "const string &" name
     */
    void setMetaboliteName(const string & metabolitName);

    /**
     *  Retrieves the name of the element.
     *  @return "const string &" name
     */
    const string & getMetaboliteName() const;

    /**
     *  Set the name of the element.
     *  @param "const string &" name
     */
    void setCompartmentName(const string & compartmentName);

    /**
     *  Retrieves the name of the element.
     *  @return "const string &" name
     */
    const string & getCompartmentName() const;

    /**
     *  Add to the multiplicity of the element.
     *  @param "const C_FLOAT64" multiplicity (default = 0.0)
     */
    void addToMultiplicity(const C_FLOAT64 multiplicity = 1.0);

    /**
     *  Compile the ChemEqElement, i.e., the pointer to the metabolite
     *  is assigned.
     *  @param "vector < CMetab * > &" metabolites
     */
    void compile(CCopasiVectorN < CCompartment > & metabolites);
    /**
     *  Write the element in the form mMultiplier * mMetaboliteName
     *  @return "string"
     */
    string writeElement() const;

    friend ostream & operator<<(ostream &os, const CChemEqElement & d)
    {
      os << "CChemEqElement: [" << d.mCompartmentName << "]  " << d.mMultiplicity <<
      " * " << d.mMetaboliteName << endl;

      if (d.mpMetabolite)
        os << "      mpMetabolite " << d.mpMetabolite->getName() << endl;
      else
        os << "      mpMetabolite == 0 " << endl;

      return os;
    }
  };

#endif // COPASI_CChemEqElement
