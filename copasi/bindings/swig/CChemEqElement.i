%{

#include "model/CChemEqElement.h"

%}

class CChemEqElement : public CCopasiContainer
{
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
    void setMetabolite(const std::string & key);

    /**
     *  Retrieves the metabolite of the element.
     *  @return "CMetab *" metabolite
     */
    const CMetab * getMetabolite() const;

    const std::string & getMetaboliteKey() const;

    /**
     *  Write the element in the form mMultiplier * mMetaboliteName
     *  @return "string"
     */
    std::string writeElement() const;

};


