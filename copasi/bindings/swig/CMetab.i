%{

#include "model/CMetab.h"

%}


class CMetab : public CModelEntity
{
  public:
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



    /**
     *
     */
    const C_FLOAT64 & getConcentration() const;

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

    /**
     *
     */
    const CCompartment * getCompartment() const;

    /**
     *
     */
    const CModel * getModel() const;

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
     * Retreive whether the metabolite dependent
     * @return bool dependent
     */
    bool isDependent() const;


};

