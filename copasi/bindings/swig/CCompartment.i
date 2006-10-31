%{

#include "model/CCompartment.h"  
  
%}


class CCompartment : public CModelEntity
{
  public:
    /**
     * Default constructor.
     * @param const std::string & name (default: "NoName")
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CCompartment(const std::string & name = "NoName",
                 const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor.
     * @param "const CCompartment &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CCompartment(const CCompartment & src,
                 const CCopasiContainer * pParent = NULL);

    /**
     *  Destructor.
     *  The destructor does nothing.
     */
    ~CCompartment();

    /**
     *
     */
    CCopasiVectorNS < CMetab > & getMetabolites();

    /**
     *  Adds a metabolite to the compartment. Only the concentration is taken from
     *  the metabolite, the number of particles is calculated according to the
     *  volume of the compartment
     *  @param const CMetab & metabolite;
     *  @return bool success
     */
    bool createMetabolite(const CMetab & metabolite);

    /**
     *  Adds a metabolite to the compartment. Only the concentration is taken from
     *  the metabolite, the number of particles is calculated according to the
     *  volume of the compartment
     *  @param CMetab * metabolite;
     *  @return bool success
     */
    bool addMetabolite(CMetab * metabolite);

    bool removeMetabolite(CMetab *metabolite);

    /**
     *  Sets the initial volume of this compartment.
     *  @param volume the volume of the compartment.
     *  @return bool success
     *  @see mVolume
     */
    virtual void setInitialValue(const C_FLOAT64 & initialValue);

    /**
     *  Sets the volume of this compartment.
     *  @param const C_FLOAT64 & volume
     *  @return bool success
     *  @see mVolume
     */
    virtual void setValue(const C_FLOAT64 & value);

};



