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
 *  CChemEqElement class.
 *  Describing an element of a chemical equation Stefan Hoops 2001
 *
 *  Created for COPASI by Stefan Hoops 2001
 */

#ifndef COPASI_CChemEqElement
#define COPASI_CChemEqElement

#include <string>

#include "copasi/core/CDataContainer.h"

class CMetab;

template <class CType> class CDataVectorN;

class CChemEqElement : public CDataContainer
{
  //  Attributes

private:
  /**
   * The name of the metabolite the element
   */
  std::string mMetaboliteKey;

  /**
   * The multiplicity of the metabolite
   */
  C_FLOAT64 mMultiplicity;

protected:
  CChemEqElement(const CChemEqElement & src);

public:
  /**
   * Static method to create a CDataObject based on the provided data
   * @param const CData & data
   * @return CChemEqElement * pDataObject
   */
  static CChemEqElement * fromData(const CData & data, CUndoObjectInterface * pParent);

  /**
   * Default constructor
   * @param const std::string & name (default: "NoName")
   * @param const CDataContainer * pParent (default: NULL)
   */
  CChemEqElement(const std::string & name = "Chem Eq Element",
                 const CDataContainer * pParent = NO_PARENT);

  /**
   * Copy constructor
   * @param "const CChemEqElement &" src
   * @param const CDataContainer * pParent (default: NULL)
   */
  CChemEqElement(const CChemEqElement & src,
                 const CDataContainer * pParent);

  /**
   * Destructor
   */
  ~CChemEqElement();

  /**
   * cleanup
   */
  void cleanup();

  /**
   * Set the multiplicity of the element.
   * @param "const C_FLOAT64" multiplicity
   */
  void setMultiplicity(const C_FLOAT64 multiplicity);

  /**
   * Add to the multiplicity of the element.
   * @param "const C_FLOAT64" multiplicity (default = 1.0)
   */
  void addToMultiplicity(const C_FLOAT64 multiplicity = 1.0);

  /**
   * Retrieves the multiplicity of the element.
   * @return const C_FLOAT64 & multiplicity
   */
  const C_FLOAT64 & getMultiplicity() const;

  /**
   * Set the metabolite of the element.
   * @param CMetab * metabolite
   */
  void setMetabolite(const std::string & key);

  /**
   * Retrieves the metabolite of the element.
   * @return "CMetab *" metabolite
   */
  const CMetab * getMetabolite() const;

  /**
   * Retrieve the key of the species
   * @return const std::string & speciesKey
   */
  const std::string & getMetaboliteKey() const;

  friend std::ostream & operator<<(std::ostream &os,
                                   const CChemEqElement & d);

private:
  void initObjects();
};

#endif // COPASI_CChemEqElement
