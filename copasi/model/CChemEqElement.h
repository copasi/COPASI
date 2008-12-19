/* Begin CVS Header
  $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CChemEqElement.h,v $
  $Revision: 1.29.26.1 $
  $Name:  $
  $Author: shoops $
  $Date: 2008/11/12 18:43:06 $
  End CVS Header */

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
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

#include "report/CCopasiContainer.h"

class CMetab;

template <class CType> class CCopasiVectorN;

class CChemEqElement : public CCopasiContainer
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

  public:
    /**
     * Default constructor
     * @param const std::string & name (default: "NoName")
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CChemEqElement(const std::string & name = "Chem Eq Element",
                   const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor
     * @param "const CChemEqElement &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CChemEqElement(const CChemEqElement & src,
                   const CCopasiContainer * pParent = NULL);

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
     * @return C_FLOAT64 multiplicity
     */
    C_FLOAT64 getMultiplicity() const;

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
