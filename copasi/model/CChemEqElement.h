/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CChemEqElement.h,v $
   $Revision: 1.25 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/06/30 15:18:43 $
   End CVS Header */

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

template <class CType> class CCopasiVectorN;

/** @dia:pos 12.7837,97.0309 */
class CChemEqElement : public CCopasiContainer
  {
    //  Attributes

  private:
    /**
     *  The name of the metabolite the element
     */
    std::string mMetaboliteKey;

    /**
     *  The multiplizity of the metabolite
     */
    C_FLOAT64 mMultiplicity;

  public:
    /**
     *  Default constructor
     * @param const std::string & name (default: "NoName")
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CChemEqElement(const std::string & name = "Chem Eq Element",
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
     *  Add to the multiplicity of the element.
     *  @param "const C_FLOAT64" multiplicity (default = 1.0)
     */
    void addToMultiplicity(const C_FLOAT64 multiplicity = 1.0);

    /**
     *  Retrieves the multiplicity of the element.
     *  @return C_FLOAT64 multiplicity
     */
    C_FLOAT64 getMultiplicity() const;

    /**
     *  Set the metabolite of the element.
     *  @param CMetab * metabolite
     */ 
    //void setMetabolite(CMetab * metabolite);
    void setMetabolite(const std::string & key);

    /**
     *  Retrieves the metabolite of the element.
     *  @return "CMetab &" metabolite
     */
    const CMetab & getMetabolite() const;

    const std::string & getMetaboliteKey() const;

    /**
     *  Retrieves the metabolite name.
     *  @return "const string &" name
     */
    const std::string & getMetaboliteName() const;

    /**
     *  Write the element in the form mMultiplier * mMetaboliteName
     *  @return "string"
     */
    std::string writeElement() const;

    friend std::ostream & operator<<(std::ostream &os,
                                     const CChemEqElement & d);

  private:
    void initObjects();
  };

#endif // COPASI_CChemEqElement
