// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CMoiety.h,v $
//   $Revision: 1.33.4.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/10/22 18:37:28 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
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
 *  CMoiety
 *
 *  New class created for Copasi by Stefan Hoops
 *  (C) Stefan Hoops 2001
 */

#ifndef COPASI_CMoiety
#define COPASI_CMoiety

#include <string>
#include <vector>

#include "model/CChemEqElement.h"
#include "utilities/CCopasiVector.h"

class CMetab;

/** @dia:pos 52.0066,117.162 */
class CMoiety : public CCopasiContainer
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
  // CCopasiVector < CChemEqElement > mEquation;
  std::vector<std::pair< C_FLOAT64, CMetab * > > mEquation;

  /**
   * A pointer to the object for the initial total particle number
   */
  CCopasiObjectReference<C_FLOAT64> *mpINumberReference;

  /**
   * A pointer to the object for the total particle number
   * This is used during events
   */
  CCopasiObjectReference<C_FLOAT64> *mpNumberReference;

  /**
   * A pointer to the object for the dependent particle number
   */
  CCopasiObjectReference<C_FLOAT64> *mpDNumberReference;

  /**
   * A pointer to the conversion factor between the particle number and the amount.
   */
  const C_FLOAT64 * mpConversionFactor;

  // Operations
public:
  /**
   * Default constructor
   * @param const std::string & name (default: "NoName")
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CMoiety(const std::string & name = "NoName",
          const CCopasiContainer * pParent = NULL);

  /**
   * Copy constructor
   * @param "const CMoiety &" src
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CMoiety(const CMoiety & src,
          const CCopasiContainer * pParent = NULL);

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
   * @return CCopasiObject * initialValueReference
   */
  CCopasiObject * getInitialValueReference() const;

  /**
   * Refresh the total particle number
   */
  void refreshValue();

  /**
   * Retrieve the object for the total particle number
   * @return CCopasiObject * valueReference
   */
  CCopasiObject * getValueReference() const;

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
   * @param const CCopasiContainer * pParent
   * @return bool success
   */
  virtual bool setObjectParent(const CCopasiContainer * pParent);

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

private:
  /**
   * Initialize the contained CCopasiObjects
   */
  void initObjects();

  /**
   * Initialize the number to amount conversion factor
   */
  void initConversionFactor();
};

#endif // COPASI_CMoiety
