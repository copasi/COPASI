%{

#include "model/CMetab.h"

%}


class CMetab : public CModelEntity
{
  public:
    /**
     * Converts the concentration to number
     * @param const C_FLOAT64 & concentration
     * @param const CCompartment & compartment
     * @param const CModel & model
     * @return C_FLOAT64 number
     */
    static C_FLOAT64 convertToNumber(const C_FLOAT64 & concentration,
                                     const CCompartment & compartment,
                                     const CModel & model);

    /**
     * Converts the number to concentration
     * @param const C_FLOAT64 & number
     * @param const CCompartment & compartment
     * @param const CModel & model
     * @return C_FLOAT64 concentration
     */
    static C_FLOAT64 convertToConcentration(const C_FLOAT64 & number,
                                            const CCompartment & compartment,
                                            const CModel & model);

    /**
     * Default constructor
     * @param const std::string & name (default: "NoName")
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CMetab(const std::string & name = "NoName",
           const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor
     * @param const CMetab & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CMetab(const CMetab & src,
           const CCopasiContainer * pParent = NULL);

    /**
     *  Destructor.
     */
    ~CMetab();

    virtual std::string getObjectDisplayName(bool regular = true, bool richtext = false) const;

    void initCompartment(const CCompartment * pCompartment = NULL);

    /**
     * Sets the parent of the metabolite;
     * @param const CCopasiContainer * pParent
     * @return bool success
     */
    virtual bool setObjectParent(const CCopasiContainer * pParent);

    /**
     *
     */
    virtual void setStatus(const CModelEntity::Status & status);

    /**
     *
     */
    void setConcentration(const C_FLOAT64 concentration);

    /**
     *
     */
    const C_FLOAT64 & getConcentration() const;

    /**
     *
     */
    virtual void setValue(const C_FLOAT64 & value);

    /**
     *
     */
    void setInitialConcentration(const C_FLOAT64 & initialConcentration);

    /**
     *
     */
    const C_FLOAT64 & getInitialConcentration() const;

    /**
     *
     */
    virtual void setInitialValue(const C_FLOAT64 & initialValue);

    void refreshInitialConcentration();

    void refreshConcentration();

    /**
     *
     */
    const CCompartment * getCompartment() const;

    /**
     *
     */
    const CModel * getModel() const;

    /**
     *  Set transition time
     *  @param "const C_FLOAT64 &" transitionTime
     */
    void setTransitionTime(const C_FLOAT64 & transitionTime);

    /**
     *  Retrieves the transition time
     *  @return "const C_FLOAT64 &" transitionTime
     */
    const C_FLOAT64 & getTransitionTime() const;

    /**
     * Return rate of production of this metaboLite
     */
    C_FLOAT64 getConcentrationRate() const;

    /**
     * Calculate the conctration rate.
     */
    void refreshConcentrationRate();

    /**
     * Calculate the conctration rate.
     */
    void refreshRate();

    /**
     * Set whether the metabolite is dependent, i.e., calculated
     * by a moiety
     * @param const CMoiety * pMoiety
     */
    void setDependentOn(const CMoiety * pMoiety);

    /**
     * Retreive whether the metabolite dependent
     * @return bool dependent
     */
    bool isDependent() const;

    /**
     * Add a moiety to the list
     * @param CMoiety * pMoiety
     */
    void addMoiety(CMoiety * pMoiety);

    /**
     * Clear the list of moieties
     */
    void clearMoieties();

};

