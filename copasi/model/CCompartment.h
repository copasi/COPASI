// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CCompartment.h,v $
//   $Revision: 1.49.4.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/11/19 19:24:07 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * CCompartment
 *
 * Derived from Gepasi's ccompart.cpp
 * (C) Pedro Mendes 1995-2000
 *
 *  Converted for COPASI by Pedro Mendes
 */
#ifndef COPASI_CCompartment
#define COPASI_CCompartment

#include <string>

#include "model/CModelValue.h"
#include "utilities/CCopasiVector.h"
#include "model/CMetab.h"

class CReadConfig;

class CCompartment : public CModelEntity
  {
  private:
    /**
     * Metabolites located in the compartment.
     * @supplierCardinality 0..*
     * @associates <{CMetab}>
     */
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
     * Destructor.
     * The destructor does nothing.
     */
    virtual ~CCompartment();

    /**
     * Retrieve the units of the child object.
     * @return std::string units
     */
    virtual std::string getChildObjectUnits(const CCopasiObject * pObject) const;

    /**
     * Cleanup
     */
    void cleanup();

    /**
     * Retrieve the list of deleted numeric child objects;
     * @return std::set< const CCopasiObject * > deletedObjects
     */
    virtual std::set< const CCopasiObject * > getDeletedObjects() const;

    /**
     * Loads an object with data coming from a CReadConfig object.
     * (CReadConfig object reads an input stream)
     * @param pconfigbuffer reference to a CReadConfig object.
     * @return mFail
     * @see mFail
     */
    C_INT32 load(CReadConfig & configbuffer);

    /**
     * Retrieve the vector of contained metabolites
     * @return CCopasiVectorNS < CMetab > & metabolites
     */
    CCopasiVectorNS < CMetab > & getMetabolites();

    /**
     * Retrieve the vector of contained metabolites
     * @return const CCopasiVectorNS < CMetab > & metabolites
     */
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

    /**
     * Friend declaration for ostream operator <<
     * @param std::ostream & os
     * @param const CCompartment & d
     * @return std::ostream & os
     */
    friend std::ostream & operator<<(std::ostream &os, const CCompartment & d);

  private:
    /**
     * Initialize the contained CCopasiObjects
     */
    void initObjects();
  };

#endif // COPASI_CCompartment
