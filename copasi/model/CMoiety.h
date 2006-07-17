/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CMoiety.h,v $
   $Revision: 1.25 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/07/17 17:30:42 $
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

#include "CMetab.h"
#include "CChemEqElement.h"
#include "utilities/CCopasiVector.h"

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
     *
     */
    C_FLOAT64 dependentNumber();

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

  private:
    /**
     * Initialize the contained CCopasiObjects
     */
    void initObjects();
  };

#endif // COPASI_CMoiety
