%{

#include "model/CMoiety.h"  
  
%}

#ifndef COPASI_DEBUG

%nodefaultctor
%nodefaultdtor

#endif /* !COPASI_DEBUG */


class CMoiety : public CCopasiContainer
{
  public:

#ifdef COPASI_DEBUG
    /**
     * Default constructor
     * @param const std::string & name (default: "NoName")
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CMoiety(const std::string & name = "NoName",
            const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor
     * @param "const CMoiety &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CMoiety(const CMoiety & src,
            const CCopasiContainer * pParent = NULL);

    /**
     *  Destructor
     */
    ~CMoiety();
#endif /*COPASI_DEBUG */

    /**
     * Add a metabolite to a moiety
     * @param C_FLOAT64 value
     * @param CMetab * metabolite
     */
    void add(C_FLOAT64 value, CMetab * metabolite);

    /**
     *
     */
    void setInitialValue();

    /**
     * get the string representation of the moiety using the CMetabNameInterface
     */
    std::string getDescription(const CModel* model) const;

    /**
     * Retrieve and refresh the dependent number;
     * @return const C_FLOAT64 & dependentNumber
     */
    const C_FLOAT64 & dependentNumber();

    /**
     * Retrieve the dependent number;
     * @return const C_FLOAT64 & dependentNumber
     */
    const C_FLOAT64 & getDependentNumber() const;

    /**
     * Retrieve the dependent rate;
     * @return const C_FLOAT64 & dependentRate
     */
    const C_FLOAT64 & getDependentRate() const;

    /**
     *
     */
    C_FLOAT64 getNumber() const;

    /**
     *  Returns a string with the name of this compartment.
     *  @return std::string key
     */
    virtual const std::string & getKey() const; //By G

    /**
     * Refreshes the value of the dependent number
     */
    void refreshDependentNumber();

    /**
     * Refreshes the value of the dependent rate
     */
    void refreshDependentRate();


};

#ifndef COPASI_DEBUG

%clearnodefaultctor
%clearnodefaultdtor

#endif /* !COPASI_DEBUG */


