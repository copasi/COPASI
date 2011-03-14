// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CMetab.h,v $
//   $Revision: 1.96 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/03/14 19:19:37 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CMetab class.
 *  Derived from Gepasi's cmetab.cpp. (C) Pedro Mendes 1995-2000.
 *  Converted for COPASI by Stefan Hoops 2001
 */

#ifndef COPASI_CMetab
#define COPASI_CMetab

#include <string>
#include <iostream>
#include <set>

#include "copasi/report/CCopasiObjectReference.h"
#include "copasi/model/CModelValue.h"
#include "copasi/model/CMoiety.h"

class CCompartment;
class CReadConfig;
class CMetabOld;
class CModel;
class CConcentrationReference;

class CMetab : public CModelEntity
{
  friend void CMoiety::add(C_FLOAT64 value, CMetab * pMetabolite);

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

  // Attributes
private:
  /**
   *  Concentration of the metabolite as double.
   */
  C_FLOAT64 mConc;

  /**
   *  Initial concentration of the metabolite as double
   */
  C_FLOAT64 mIConc;

  /**
   * The rate of concentration change
   */
  C_FLOAT64 mConcRate;

  /**
   *  Transition time of the metabolite
   */
  C_FLOAT64 mTT;

  /**
   *  pointer to the compartment the metabolite is located in.
   *  The metab needs to know about volumes.
   */
  const CCompartment * mpCompartment;

  /**
   * If dependent the moiety the metabolite is calculated from
   */
  const CMoiety * mpMoiety;

  std::vector< std::pair< C_FLOAT64, const C_FLOAT64 * > > mRateVector;

protected:
  CCopasiObjectReference<C_FLOAT64> *mpIConcReference;
  CConcentrationReference *mpConcReference;
  CCopasiObjectReference<C_FLOAT64> *mpConcRateReference;
  CCopasiObjectReference<C_FLOAT64> *mpTTReference;

  // Operations
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

  /**
   * Retrieve the units of the child object.
   * @return std::string units
   */
  virtual std::string getChildObjectUnits(const CCopasiObject * pObject) const;

  /**
   * Retrieve the object representing the value;
   */
  virtual const CCopasiObject * getValueObject() const;

  /**
   * Retrieve a pointer to the value;
   */
  virtual void * getValuePointer() const;

  virtual std::string getObjectDisplayName(bool regular = true, bool richtext = false) const;

  /**
   *  Cleanup
   */
  void cleanup();
  void initCompartment(const CCompartment * pCompartment = NULL);

  /**
   *  Assignment operator.
   */
  CMetab & operator=(const CMetabOld & rhs);

  /**
   *  Loads an object with data coming from a CReadConfig object.
   *  (CReadConfig object reads an input stream)
   *  @param pconfigbuffer reference to a CReadConfig object.
   *  @return Fail
   */
  C_INT32 load(CReadConfig & configbuffer);

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
   * Compile the model value.
   * @return bool success
   */
  virtual bool compile();

  /**
   * Compile the initial particle number and initial concentration dependencies.
   * @param const bool & updateConcentration
   * @return bool success
   */
  bool compileInitialValueDependencies(const bool & updateConcentration);

  /**
   * Check whether changing the initial concentration is allowed
   * @return bool allowed
   */
  bool isInitialConcentrationChangeAllowed();

  /**
   * Calculate the value or the rate depending whether we have an ASIGNMENT or ODE
   */
  virtual void calculate();

  /**
   * Retrieve the list of deleted numeric child objects;
   * @return std::set< const CCopasiObject * > deletedObjects
   */
  virtual std::set< const CCopasiObject * > getDeletedObjects() const;

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
  void setInitialConcentration(const C_FLOAT64 & initialConcentration);

  /**
   *
   */
  const C_FLOAT64 & getInitialConcentration() const;

  /**
   * Retrieve object referencing the initial concentration
   * @return CCopasiObject * initialConcentrationReference
   */
  CCopasiObject * getInitialConcentrationReference() const;

  /**
   * Retrieve object referencing the concentration
   * @return CConcentrationReference * concentrationReference
   */
  CConcentrationReference * getConcentrationReference() const;

  /**
   * Retrieve object referencing the concentration
   * @return CCopasiObject * concentrationRateReference
   */
  CCopasiObject * getConcentrationRateReference() const;

  /**
   * Refresh the initial value
   */
  virtual void refreshInitialValue();

  void refreshInitialConcentration();

  void refreshConcentration();

  void refreshNumber();

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
   * Calculate the concentration rate.
   */
  void refreshConcentrationRate();

  /**
   * Calculate the particle rate.
   */
  void refreshRate();

  /**
   * Calculate the transition time.
   */
  void refreshTransitionTime();

  /**
   * Set whether the metabolite is dependent, i.e., calculated
   * by a moiety
   * @param const CMoiety * pMoiety
   */
  void setDependentOn(const CMoiety * pMoiety);

  /**
   * Retrieve whether the metabolite dependent
   * @return bool dependent
   */
  bool isDependent() const;

  /**
   * Retrieve a pointer to the moiety the species depends on
   * @return const CMoiety * pMoiety;
   */
  const CMoiety * getMoiety() const;

  /**
   * ostream operator
   */
  friend std::ostream & operator<<(std::ostream &os, const CMetab & d);

private:
  /**
   * Initialize the contained CCopasiObjects
   */
  void initObjects();
};

class CMetabOld : public CCopasiContainer
{
  friend class CMetab;

  // Attributes

private:
  /**
   *  Concentration of the metabolite.
   */
  C_FLOAT64 mIConc;

  /**
   *  Status of the metabolite.
   *  One of (METAB_FIXED, METAB_VARIABLE, METAB_DEPENDENT, METAB_MOIETY).
   */
  CMetab::Status mStatus;

  /**
   *  Index of the compartment the metabolite is located in.
   */
  C_INT32 mCompartment;

  // Operations

public:
  /**
   * Default constructor
   * @param const std::string & name (default: "NoName")
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CMetabOld(const std::string & name = "NoName",
            const CCopasiContainer * pParent = NULL);

  /**
   * Copy constructor
   * @param const CMetabOld & src
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CMetabOld(const CMetabOld & src,
            const CCopasiContainer * pParent = NULL);

  /**
   *  Destructor.
   */
  ~CMetabOld();

  /**
   *  cleanup()
   */
  void cleanup();

  /**
   *  Loads an object with data coming from a CReadConfig object.
   *  (CReadConfig object reads an input stream)
   *  @param pconfigbuffer reference to a CReadConfig object.
   *  @return Fail
   */
  C_INT32 load(CReadConfig & configbuffer);

  C_INT32 getIndex() const;
};

class CConcentrationReference : public CCopasiObjectReference< C_FLOAT64 >
{
public:
  /**
   * Default constructor
   * @param const CCopasiContainer * pParent,
   * @param C_FLOAT64 & reference,
   */
  CConcentrationReference(const CCopasiContainer * pParent,
                          C_FLOAT64 & reference);

  /**
   * Copy constructor
   * @param const CConcentrationReference & src
   * @param const CCopasiContainer * pParent,
   */
  CConcentrationReference(const CConcentrationReference & src,
                          const CCopasiContainer * pParent);

  /**
   * Destructor
   */
  ~CConcentrationReference();

  /**
   * Retrieve the list of direct dependencies
   * @param const std::set< const CCopasiObject * > & context (default empty set)
   * @return const std::set< const CCopasiObject * > & directDependencies
   */
  virtual const std::set< const CCopasiObject * > &
  getDirectDependencies(const std::set< const CCopasiObject * > & context = std::set< const CCopasiObject * >()) const;

  /**
   * Retrieve the refresh call which calculates the concentration based on state values needed
   * when applying the initial state.
   * @return Refresh * applyInitialValueRefresh
   */
  Refresh * getApplyInitialValueRefresh() const;

  // Attributes
private:
  /**
   * The list of direct dependencies when the values is in the changed context,
   * i.e., it is always empty
   */
  static std::set< const CCopasiObject * > EmptyDependencies;

  /**
   * The refresh call needed when applying initial values.
   */
  Refresh * mpApplyInitialValuesRefresh;
};

class CParticleReference : public CCopasiObjectReference< C_FLOAT64 >
{
public:
  /**
   * Default constructor
   * @param const CCopasiContainer * pParent,
   * @param C_FLOAT64 & reference,
   */
  CParticleReference(const CCopasiContainer * pParent,
                     C_FLOAT64 & reference);

  /**
   * Copy constructor
   * @param const CParticleReference & src
   * @param const CCopasiContainer * pParent,
   */
  CParticleReference(const CParticleReference & src,
                     const CCopasiContainer * pParent);

  /**
   * Destructor
   */
  ~CParticleReference();

  /**
   * Retrieve the list of direct dependencies
   * @param const std::set< const CCopasiObject * > & context (default empty set)
   * @return const std::set< const CCopasiObject * > & directDependencies
   */
  virtual const std::set< const CCopasiObject * > &
  getDirectDependencies(const std::set< const CCopasiObject * > & context = std::set< const CCopasiObject * >()) const;

  // Attributes
private:
  /**
   * The list of direct dependencies when the values is in the changed context,
   * i.e., it is always empty
   */
  static std::set< const CCopasiObject * > EmptyDependencies;
};

#endif // COPASI_CMetab
