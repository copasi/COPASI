// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
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
 *  CMetab class.
 *  Derived from Gepasi's cmetab.cpp. (C) Pedro Mendes 1995-2000.
 *  Converted for COPASI by Stefan Hoops 2001
 */

#ifndef COPASI_CMetab
#define COPASI_CMetab

#include <string>
#include <iostream>
#include <set>

#include "copasi/core/CDataObjectReference.h"
#include "copasi/model/CModelValue.h"
#include "copasi/model/CMoiety.h"
#include "copasi/model/CModelParameter.h"

class CCompartment;
class CReadConfig;
class CMetabOld;
class CModel;
class CUnit;

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
                                   const CCompartment & compartment);

  /**
   * Converts the number to concentration
   * @param const C_FLOAT64 & number
   * @param const CCompartment & compartment
   * @param const CModel & model
   * @return C_FLOAT64 concentration
   */
  static C_FLOAT64 convertToConcentration(const C_FLOAT64 & number,
                                          const CCompartment & compartment);

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
   * The intensive noise
   */
  C_FLOAT64 mIntensiveNoise;

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

  bool mIsInitialConcentrationChangeAllowed;
  bool mIsInitialParticleNumberChangeAllowed;

protected:
  CDataObjectReference< C_FLOAT64 > *mpIConcReference;
  CDataObjectReference< C_FLOAT64 > *mpConcReference;
  CDataObjectReference< C_FLOAT64 > *mpConcRateReference;
  CDataObjectReference< C_FLOAT64 > *mpIntensiveNoiseReference;
  CDataObjectReference< C_FLOAT64 > *mpTTReference;

  CMetab(const CMetab & src);

  // Operations
public:
  /**
   * Static method to create a CDataObject based on the provided data
   * @param const CData & data
   * @return CMetab * pDataObject
   */
  static CMetab * fromData(const CData & data, CUndoObjectInterface * pParent);

  /**
   * Retrieve the data describing the object
   * @return CData data
   */
  virtual CData toData() const override;

  /**
   * Apply the provided data to the object
   * @param const CData & data
   * @return bool success
   */
  virtual bool applyData(const CData & data, CUndoData::CChangeSet & changes) override;

  /**
   * Create the undo data which represents the changes recording the
   * differences between the provided oldData and the current data.
   * @param CUndoData & undoData
   * @param const CUndoData::Type & type
   * @param const CData & oldData (default: empty data)
   * @param const CCore::Framework & framework (default: CCore::Framework::ParticleNumbers)
   * @return CUndoData undoData
   */
  virtual void createUndoData(CUndoData & undoData,
                              const CUndoData::Type & type,
                              const CData & oldData = CData(),
                              const CCore::Framework & framework = CCore::Framework::ParticleNumbers) const override;

  /**
   * Default constructor
   * @param const std::string & name (default: "NoName")
   * @param const CDataContainer * pParent (default: NULL)
   */
  CMetab(const std::string & name = "NoName",
         const CDataContainer * pParent = NO_PARENT);

  /**
   * Copy constructor
   * @param const CMetab & src
   * @param const CDataContainer * pParent (default: NULL)
   */
  CMetab(const CMetab & src,
         const CDataContainer * pParent);

  /**
   *  Destructor.
   */
  ~CMetab();

  /**
   * Retrieve the units of the object.
   * @return std::string units
   */
  virtual const std::string getUnits() const override;

  /**
   * Retrieve the units of the child object.
   * @return const & CUnit units
   */
  virtual std::string getChildObjectUnits(const CDataObject * pObject) const override;

  /**
   * Retrieve the object representing the value;
   */
  virtual const CDataObject * getValueObject() const override;

  /**
   * Retrieve a pointer to the value;
   */
  virtual void * getValuePointer() const override;

  virtual std::string getObjectDisplayName() const override;

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
   * @param const CDataContainer * pParent
   * @return bool success
   */
  virtual bool setObjectParent(const CDataContainer * pParent) override;

  /**
   * moves the species to the compartment with the given name,
   * removes it from the old compartment (if there was one),
   * and updates references to the species if needed
   */
  bool setCompartment(const std::string& compName);

  /**
   * Compile the model value.
   * @return CIssue firstWorstIssue
   */
  virtual CIssue compile() override;

  /**
   * Determine whether changing the initial concentration is allowed
   */
  void compileIsInitialValueChangeAllowed();

  /**
   * Check whether changing the initial concentration is allowed
   * @return const bool & allowed
   */
  const bool & isInitialValueChangeAllowed(CCore::Framework framework) const;

  /**
   * Calculate the value or the rate depending whether we have an ASIGNMENT or ODE
   */
  virtual void calculate() override;

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
   * @return CConcentrationReference * initialConcentrationReference
   */
  CDataObject * getInitialConcentrationReference() const;

  /**
   * Retrieve object referencing the concentration
   * @return CConcentrationReference * concentrationReference
   */
  CDataObject * getConcentrationReference() const;

  /**
   * Retrieve object referencing the concentration
   * @return CDataObject * concentrationRateReference
   */
  CDataObject * getConcentrationRateReference() const;

  /**
   * Retrieve object referencing the concentration
   * @return CDataObject * concentrationRateReference
   */
  CDataObject * getIntensiveNoiseReference() const;

  /**
   *
   */
  const CCompartment * getCompartment() const;

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
   * Retrieve object referencing the Transition Time
   * @return CDataObject * transitionTimeReference
   */
  CDataObject * getTransitionTimeReference() const;

  /**
   * Return rate of production of this metaboLite
   */
  C_FLOAT64 getConcentrationRate() const;

  /**
   * Set whether the metabolite is dependent, i.e., calculated
   * by a moiety
   * @param const CMoiety * pMoiety
   */
  void setDependsOnMoiety(const CMoiety * pMoiety);

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
   * Retrieve the count of structural dependent reactions
   * @return const size_t countOfDependentReactions
   */
  size_t getCountOfDependentReactions() const;

  /**
   * ostream operator
   */
  friend std::ostream & operator<<(std::ostream &os, const CMetab & d);

private:
  /**
   * Initialize the contained CDataObjects
   */
  void initObjects();
};

class CMetabOld : public CDataContainer
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
   * Static method to create a CDataObject based on the provided data
   * @param const CData & data
   * @return CMetabOld * pDataObject
   */
  static CMetabOld * fromData(const CData & data, CUndoObjectInterface * pParent);

  /**
   * Retrieve the data describing the object
   * @return CData data
   */
  virtual CData toData() const;

  /**
   * Apply the provided data to the object
   * @param const CData & data
   * @return bool success
   */
  virtual bool applyData(const CData & data, CUndoData::CChangeSet & changes);

  /**
   * Default constructor
   * @param const std::string & name (default: "NoName")
   * @param const CDataContainer * pParent (default: NULL)
   */
  CMetabOld(const std::string & name = "NoName",
            const CDataContainer * pParent = NO_PARENT);

  /**
   * Copy constructor
   * @param const CMetabOld & src
   * @param const CDataContainer * pParent (default: NULL)
   */
  CMetabOld(const CMetabOld & src,
            const CDataContainer * pParent);

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

#endif // COPASI_CMetab
