// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
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
#include "copasi/core/CDataVector.h"
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
  CDataVectorNS < CMetab > mMetabolites;

public:
  static CCompartment * fromData(const CData & data);
  virtual CData toData() const;
  virtual bool applyData(const CData & data);

  /**
   * Default constructor.
   * @param const std::string & name (default: "NoName")
   * @param const CDataContainer * pParent (default: NULL)
   */
  CCompartment(const std::string & name = "NoName",
               const CDataContainer * pParent = NO_PARENT);

  /**
   * Copy constructor.
   * @param "const CCompartment &" src
   * @param const CDataContainer * pParent (default: NULL)
   */
  CCompartment(const CCompartment & src,
               const CDataContainer * pParent);

  /**
   * Destructor.
   * The destructor does nothing.
   */
  virtual ~CCompartment();

  /**
   * Retrieve the units of the object.
   * @return std::string units
   */
  virtual const std::string getUnits() const;

  /**
   * Cleanup
   */
  void cleanup();

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
   * @return CDataVectorNS < CMetab > & metabolites
   */
  CDataVectorNS < CMetab > & getMetabolites();

  /**
   * Retrieve the vector of contained metabolites
   * @return const CDataVectorNS < CMetab > & metabolites
   */
  const CDataVectorNS < CMetab > & getMetabolites() const;

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
   *  Set the dimensionality of the compartment. May be 0, 1, 2, or 3.
   *  If the value is not valid it will be ignored and the return value will be false
   */
  bool setDimensionality(unsigned C_INT32 dim);

  /**
   *  Get the dimensionality of the compartment
   */
  unsigned C_INT32 getDimensionality() const;

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

protected:
  /**
   * The dimensionality of the compartment. Can be 0, 1, 2, or 3
   */
  unsigned C_INT32 mDimensionality;
};

#endif // COPASI_CCompartment
