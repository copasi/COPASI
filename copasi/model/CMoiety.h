// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
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
 *  CMoiety
 *
 *  New class created for Copasi by Stefan Hoops
 *  (C) Stefan Hoops 2001
 */

#ifndef COPASI_CMoiety
#define COPASI_CMoiety

#include <string>
#include <vector>

#include "copasi/model/CChemEqElement.h"
#include "copasi/core/CDataVector.h"
#include "copasi/core/CDataObjectReference.h"
class CMetab;

class CTotalNumberReference : public CDataObjectReference< C_FLOAT64 >
{
  /**
   * Hidden default constructor
   */
  CTotalNumberReference();

public:
  /**
   * Specific constructor
   * @param const std::string & name
   * @param const CDataContainer * pParent,
   * @param C_FLOAT64 & reference,
   */
  CTotalNumberReference(const std::string & name,
                        const CDataContainer * pParent,
                        C_FLOAT64 & reference);

  /**
   * Copy constructor
   * @param const CTotalNumberReference & src
   * @param const CDataContainer * pParent,
   */
  CTotalNumberReference(const CTotalNumberReference & src,
                        const CDataContainer * pParent);

  /**
   * Destructor
   */
  ~CTotalNumberReference();

  /**
   * Check whether a given object is a prerequisite for a context.
   * @param const CObjectInterface * pObject
   * @param const CCore::SimulationContextFlag & context
   * @param const CObjectInterface::ObjectSet & changedObjects
   * @return bool isPrerequisiteForContext
   */
  virtual bool isPrerequisiteForContext(const CObjectInterface * pObject,
                                        const CCore::SimulationContextFlag & context,
                                        const CObjectInterface::ObjectSet & changedObjects) const;
};

class CDependentNumberReference : public CDataObjectReference< C_FLOAT64 >
{
  /**
   * Hidden default constructor
   */
  CDependentNumberReference();

public:
  /**
   * Specific constructor
   * @param const std::string & name
   * @param const CDataContainer * pParent,
   * @param C_FLOAT64 & reference,
   */
  CDependentNumberReference(const std::string & name,
                            const CDataContainer * pParent,
                            C_FLOAT64 & reference);

  /**
   * Copy constructor
   * @param const CDependentNumberReference & src
   * @param const CDataContainer * pParent,
   */
  CDependentNumberReference(const CDependentNumberReference & src,
                            const CDataContainer * pParent);

  /**
   * Destructor
   */
  ~CDependentNumberReference();

  /**
   * Check whether a given object is a prerequisite for a context.
   * @param const CObjectInterface * pObject
   * @param const CCore::SimulationContextFlag & context
   * @param const CObjectInterface::ObjectSet & changedObjects
   * @return bool isPrerequisiteForContext
   */
  virtual bool isPrerequisiteForContext(const CObjectInterface * pObject,
                                        const CCore::SimulationContextFlag & context,
                                        const CObjectInterface::ObjectSet & changedObjects) const;
};

class CMoiety : public CDataContainer
{
  // Attributes
private:
  /**
   * The default conversion factor used if the moiety is not part of a model
   */
  static const C_FLOAT64 DefaultFactor;

  /**
   * The key of the moiety
   */
  std::string mKey; //By G

  /**
   *  Number of Particles of Moiety.
   */
  C_FLOAT64 mNumber;

  /**
   *  Initial Number of Particles of Moiety.
   */
  C_FLOAT64 mINumber;

  /**
   *  The total Amount of the Moiety.
   */
  C_FLOAT64 mIAmount;

  /**
   *  Vector of linear dependent CChemEqElement
   * @supplierCardinality 0..*
   */
  /** @dia:route 7,3; h,41.0337,110.831,46.5202,117.862,52.0066 */
  // CDataVector < CChemEqElement > mEquation;
  std::vector<std::pair< C_FLOAT64, CMetab * > > mEquation;

  /**
   * A pointer to the object for the initial total particle number
   */
  CTotalNumberReference *mpINumberReference;

  /**
   * A pointer to the object for the total particle number
   * This is used during events
   */
  CTotalNumberReference *mpNumberReference;

  /**
   * A pointer to the object for the dependent particle number
   */
  CDependentNumberReference *mpDNumberReference;

  /**
   * A pointer to the conversion factor between the particle number and the amount.
   */
  const C_FLOAT64 * mpConversionFactor;

  // Operations
public:
  /**
   * Static method to create a CDataObject based on the provided data
   * @param const CData & data
   * @return CMoiety * pDataObject
   */
  static CMoiety * fromData(const CData & data, CUndoObjectInterface * pParent);

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
  CMoiety(const std::string & name = "NoName",
          const CDataContainer * pParent = NO_PARENT);

  /**
   * Copy constructor
   * @param "const CMoiety &" src
   * @param const CDataContainer * pParent (default: NULL)
   */
  CMoiety(const CMoiety & src,
          const CDataContainer * pParent);

  /**
   *  Destructor
   */
  ~CMoiety();

  /**
   * Add a metabolite to a moiety
   * @param C_FLOAT64 value
   * @param CMetab * metabolite
   */
  void add(C_FLOAT64 value, CMetab * metabolite);

  /**
   *
   */
  void cleanup();

  /**
   * Refresh the initial total particle number
   */
  void refreshInitialValue();

  /**
   * Retrieve the object for the total particle number
   * @return CDataObject * initialValueReference
   */
  CDataObject * getInitialValueReference() const;

  /**
   * Refresh the total particle number
   */
  void refreshValue();

  /**
   * Retrieve the object for the total particle number
   * @return CDataObject * valueReference
   */
  CDataObject * getValueReference() const;

  /**
   * get the string representation of the moiety using the CMetabNameInterface
   */
  std::string getDescription(const CModel* model) const;

  /**
   * Retrieve and refresh the dependent number;
   * @return const C_FLOAT64 & dependentNumber
   */
  const C_FLOAT64 & dependentNumber();

  /**
   * Retrieve the dependent number;
   * @return const C_FLOAT64 & dependentNumber
   */
  const C_FLOAT64 & getDependentNumber() const;

  /**
   * Retrieve the object for the initial total particle number
   * @return CDataObject * initialTotalNumberReference
   */
  CDataObject * getInitialTotalNumberReference() const;

  /**
   * Retrieve the object for the total particle number
   * @return CDataObject * totalNumberReference
   */
  CDataObject * getTotalNumberReference() const;

  /**
   * Retrieve the object for the dependent particle number
   * @return CDataObject * dependentNumberReference
   */
  CDataObject * getDependentNumberReference() const;

  /**
   *
   */
  C_FLOAT64 getNumber() const;

  /**
   *  Returns a string with the name of this compartment.
   *  @return std::string key
   */
  virtual const std::string & getKey() const; //By G

  /**
   * Sets the parent of the moiety;
   * @param const CDataContainer * pParent
   * @return bool success
   */
  virtual bool setObjectParent(const CDataContainer * pParent);

  /**
   * Refreshes the value of the dependent number
   */
  void refreshDependentNumber();

  /**
   * Retrieve the infix expression, which can be used to calculate the
   * total amount.
   * @return std::string expression
   */
  std::string getExpression() const;

  /**
   * Retrieve the total amount
   * @return const C_FLOAT64 & amount
   */
  const C_FLOAT64 & getAmount() const;

  /**
   * Refresh the total amount
   */
  void refreshAmount();

  /**
   * Retrieve the components of the total mass equation
   * @return const std::vector<std::pair< C_FLOAT64, CMetab * > > & equation
   */
  const std::vector<std::pair< C_FLOAT64, CMetab * > > & getEquation() const;

private:
  /**
   * Initialize the contained CDataObjects
   */
  void initObjects();

  /**
   * Initialize the number to amount conversion factor
   */
  void initConversionFactor();
};

#endif // COPASI_CMoiety
