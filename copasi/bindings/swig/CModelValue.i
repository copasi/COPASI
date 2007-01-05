%{

#include "model/CModelValue.h"

%}

%nodefaultctor CModelEntity;
%nodefaultdtor CModelEntity;

class CModelEntity : public CCopasiContainer
{
  public:
    /**
     *  The valid states for metabolites
     */
    enum Status
    {
      FIXED = 0,          //the entity is constant (for metabs even if they are part of a reaction)
      ASSIGNMENT,         //the entity is changed by an assignment rule
      REACTIONS,          //applies only for metabs, the metab concentration is changed by reactions
      //      DEPENDENT, //applies only for metabs, the metab concentration is determined by conservation rules
      //      UNUSED,
      ODE,                //the entity is changed by an ordinary differential equation
      TIME
    };

    /**
     * String representation of the states
     */
    static const std::string StatusName[];


    /**
     *  Retrieve the key
     * @return std::string key
     */
    virtual const std::string & getKey() const;

    /**
     *
     */
    const CModelEntity::Status & getStatus() const;

    /**
     * Calculate the value or the rate depending whether we have an ASIGNMENT or ODE
     */
    virtual void calculate();

    bool isFixed();

    /**
     * Retreive the value
     */
    const C_FLOAT64 & getValue() const;

    /**
     * Retreive the initial value
     */
    const C_FLOAT64 & getInitialValue() const;

    /**
     * Return rate of production of this entity
     */
    const C_FLOAT64 & getRate() const;

    /**
     * Set the status
     * @param const CModelEntity::Status & status
     */
    virtual void setStatus(const CModelEntity::Status & status);

    /**
     * Set the initial value
     * @param const C_FLOAT64 & initialValue
     */
    virtual void setInitialValue(const C_FLOAT64 & initialValue);

    /**
     * Sets the SBMLId.
     */
    void setSBMLId(const std::string& id);

    /**
     * Returns a reference to the SBML Id.
     */
    const std::string& getSBMLId() const;


    /**
     * Set the expression for non FIXED model values
     * @param const std::string & expression
     * @return bool success
     */
    bool setExpression(const std::string & expression);

    /**
     * Retrieve the expression for non FIXED model values.
     * @return std::string expression
     */
    std::string getExpression() const;

    /**
     * Set the expression for ODE or REACTION model values
     * @param const std::string & expression
     * @return bool success
     */
    bool setInitialExpression(const std::string & expression);

    /**
     * Retrieve the expression for ODE or REACTION model values.
     * @return std::string expression
     */
    std::string getInitialExpression() const;

    /**
     * Set whether the model entity is used during simulation
     * @param const bool & used
     */
    void setUsed(const bool & used);

    /**
     * Retreive whether the model value is used during simulation
     * @return const bool & used
     */
    const bool & isUsed() const;

    /**
     * Set whether the model entity is used once prior to simulation
     * @param const bool & used
     */
    void setUsedOnce(const bool & usedOnce);

    /**
     * Retreive whether the model value is used once prior to simulation
     * @return const bool & usedOnce
     */
    const bool & isUsedOnce() const;

};




class CModelValue : public CModelEntity
{
  public:

    /**
     * Default constructor
     * @param const std::string & name (default: "NoName")
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CModelValue(const std::string & name = "NoName",
                const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor
     * @param const CModelValue & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CModelValue(const CModelValue & src,
                const CCopasiContainer * pParent = NULL);

    /**
     *  Destructor.
     */
    ~CModelValue();
};


