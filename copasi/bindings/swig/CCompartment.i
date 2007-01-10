// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

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

    bool removeMetabolite(CMetab *metabolite);

    /**
     *  Sets the initial volume of this compartment.
     *  @param volume the volume of the compartment.
     *  @return bool success
     *  @see mVolume
     */
    virtual void setInitialValue(const C_FLOAT64 & initialValue);

};



