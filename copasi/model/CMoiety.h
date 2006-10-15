/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CMoiety.h,v $
   $Revision: 1.29 $
   $Name:  $
   $Author: gauges $
   $Date: 2006/10/15 07:32:22 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
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
     * The key of the moiety
     */
    std::string mKey; //By G

    /**
     *  Number of Particles of Moietiy.
     */
    C_FLOAT64 mNumber;

    /**
     *  Rate of change of particles of Moietiy.
     */
    C_FLOAT64 mRate;

    /**
     * A pointer to the reference of the dependent rate
     */
    CCopasiObjectReference<C_FLOAT64> *mpRateReference;

    /**
     *  Initial Number of Particles of Moietiy.
     */
    C_FLOAT64 mINumber;

    /**
     *  Vector of linear dependent CChemEqElement
     * @supplierCardinality 0..*
     */
    /** @dia:route 7,3; h,41.0337,110.831,46.5202,117.862,52.0066 */
    // CCopasiVector < CChemEqElement > mEquation;
    std::vector<std::pair< C_FLOAT64, CMetab * > > mEquation;

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
     *  Saves the contents of the object to a CWriteConfig object.
     *  This saves the data in Gepasi 3.21 file format
     *  @param pconfigbuffer reference to a CWriteConfig object.
     *  @return Fail
     */
    //    C_INT32 saveOld(CWriteConfig & configBuffer);

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
     *
     */
    void setInitialValue();

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
     * Retrieve the dependent rate;
     * @return const C_FLOAT64 & dependentRate
     */
    const C_FLOAT64 & getDependentRate() const;

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
     * Refreshes the value of the dependent number
     */
    void refreshDependentNumber();

    /**
     * Refreshes the value of the dependent rate
     */
    void refreshDependentRate();

  private:
    /**
     * Initialize the contained CCopasiObjects
     */
    void initObjects();
  };

#endif // COPASI_CMoiety
