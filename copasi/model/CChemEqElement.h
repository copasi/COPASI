/**
 *  CChemEqElement class.
 *  Describing an element of a chemical equation Stefan Hoops 2001
 *
 *  Created for Copasi by Stefan Hoops 2001
 */

#ifndef COPASI_CChemEqElement
#define COPASI_CChemEqElement

#include <string>

#include "utilities/CCopasiVector.h"
#include "CMetab.h"

/** @dia:pos 12.8337,93.7809 */
class CChemEqElement : public CCopasiContainer
  {
    //  Attributes

  private:
    /**
     *  The name of the metabolite the element
     */
    std::string mMetaboliteName;

    /**
     *  The name of the compartment the element is located in
     */ 
    //std::string mCompartmentName;

    /**
     *  The multiplizity of the metabolite
     */
    C_FLOAT64 mMultiplicity;

    /**
     *  A pointer to the metabolite
     */
    /** @dia:route 2,105; h,45.5713,93.7809,123.645,92.0961,117.263 */
    CMetab * mpMetabolite;

    // Operations

  public:
    /**
     *  Default constructor
     * @param const std::string & name (default: "NoName")
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CChemEqElement(const std::string & name = "NoName",
                   const CCopasiContainer * pParent = NULL);

    /**
     *  Copy constructor
     *  @param "const CChemEqElement &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CChemEqElement(const CChemEqElement & src,
                   const CCopasiContainer * pParent = NULL);

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
    const CMetab & getMetabolite() const;

    /**
     *  Retrieves the address of the metabolite of the element.
     *  @return "CMetab *" metabolite
     */ 
    //CMetab * getMetaboliteAddr() const;

    /**
     *  Set the name of the element.
     *  @param "const string &" name
     */
    void setMetaboliteName(const std::string & metabolitName);

    /**
     *  Retrieves the name of the element.
     *  @return "const string &" name
     */
    const std::string & getMetaboliteName() const;

    /**
     *  Set the name of the element.
     *  @param "const string &" name
     */ 
    //void setCompartmentName(const std::string & compartmentName);

    /**
     *  Retrieves the name of the element.
     *  @return "const string &" name
     */ 
    //const std::string & getCompartmentName() const;

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
    void compile(const CCopasiVectorN < CCompartment > & compartments);
    /**
     *  Write the element in the form mMultiplier * mMetaboliteName
     *  @return "string"
     */
    std::string writeElement() const;

    friend std::ostream & operator<<(std::ostream &os, const CChemEqElement & d)
    {
      //os << "CChemEqElement: [" << d.mCompartmentName << "]  " << d.mMultiplicity <<
      //" * " << d.mMetaboliteName << std::endl;
      os << "CChemEqElement: " << d.mMultiplicity << " * " << d.mMetaboliteName << std::endl;

      if (d.mpMetabolite)
        os << "      mpMetabolite " << d.mpMetabolite->getName() << std::endl;
      else
        os << "      mpMetabolite == 0 " << std::endl;

      return os;
    }
  };

#endif // COPASI_CChemEqElement
