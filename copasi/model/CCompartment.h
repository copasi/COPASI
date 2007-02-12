// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CCompartment.h,v $
//   $Revision: 1.47 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/02/12 14:27:07 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * CCompartment
 *
 * Derived from Gepasi's ccompart.cpp
 * (C) Pedro Mendes 1995-2000
 *
 *  Converted for Copasi by Pedro Mendes
 */
#ifndef COPASI_CCompartment
#define COPASI_CCompartment

#include <string>

#include "model/CModelValue.h"
#include "utilities/CCopasiVector.h"
#include "model/CMetab.h"

class CReadConfig;

/** @dia:pos 128.756,34.703 */
class CCompartment : public CModelEntity
  {
  private:
    /**
     *  Metabolites located in the compartment.
     *  @supplierCardinality 0..*
     *  @associates <{CMetab}>
     */
    /** @dia:route 3,9; h,128.756,35.403,118.742,53.4961,108.729 */
    CCopasiVectorNS < CMetab > mMetabolites;

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
    virtual ~CCompartment();

    /**
     *  Cleanup
     */
    void cleanup();

    /**
     * Retreive the list of deleted numeric child objects;
     * @return std::set< const CCopasiObject * > deletedObjects
     */
    virtual std::set< const CCopasiObject * > getDeletedObjects() const;

    /**
     *  Loads an object with data coming from a CReadConfig object.
     *  (CReadConfig object reads an input stream)
     *  @param pconfigbuffer reference to a CReadConfig object.
     *  @return mFail
     *  @see mFail
     */
    C_INT32 load(CReadConfig & configbuffer);

    /**
     *
     */
    CCopasiVectorNS < CMetab > & getMetabolites();
    const CCopasiVectorNS < CMetab > & getMetabolites() const;

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

    friend std::ostream & operator<<(std::ostream &os, const CCompartment & d);

  private:

    /**
     *  Check whether the name is valid.
     */
    //bool isValidName(const std::string & name) const;

    /**
     * Initialize the contained CCopasiObjects
     */
    void initObjects();
  };

#endif // COPASI_CCompartment
