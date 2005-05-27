/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CCompartment.h,v $
   $Revision: 1.38 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/05/27 12:07:30 $
   End CVS Header */

/**
 * CCompartment
 * 
 * Derived from Gepasi's ccompart.cpp
 * (C) Pedro Mendes 1995-2000
 * 
 *  Converted for Copasi by Pedro Mendes
 */
#ifndef COPASI_CCompartment
#define COPASI_CCompartment

#include <string>

#include "CModelValue.h"
#include "utilities/CCopasiVector.h"
#include "CMetab.h"

class CReadConfig;
//class CWriteConfig;

/** @dia:pos 128.756,34.703 */
class CCompartment : public CModelEntity
  {
    // Attributes

  private:
    /**
     *  The key of the compartment.
     */
    std::string mKey;

    /**
     *  The initial volume of the compartment.
     */
    C_FLOAT64 mInitialVolume;

    /**
     *  Volume of the compartment.
     */
    C_FLOAT64 mVolume;

    /**
     *  1/Volume of the compartment.
     */
    C_FLOAT64 mVolumeInv;

    /**
     *  Metabolites located in the compartment.
     *  @supplierCardinality 0..*
     *  @associates <{CMetab}>
     */
    /** @dia:route 3,9; h,128.756,35.403,118.742,53.4961,108.729 */
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
     *  Destructor. 
     *  The destructor does nothing.
     */
    ~CCompartment();

    /**
     *  Cleanup
     */
    void cleanup();

    /**
     *  Loads an object with data coming from a CReadConfig object.
     *  (CReadConfig object reads an input stream)
     *  @param pconfigbuffer reference to a CReadConfig object.
     *  @return mFail
     *  @see mFail
     */
    C_INT32 load(CReadConfig & configbuffer);

    /**
     *  Returns a string with the name of this compartment.
     *  @return std::string key
     */
    virtual const std::string & getKey() const;

    /**
     *  Returns a C_FLOAT64 with the volume of this compartment.
     *  @return const C_FLOAT64 & InitialVolume
     *  @see mInitialVolume
     */
    const C_FLOAT64 & getInitialVolume() const;

    /**
     *  Returns a C_FLOAT64 with the volume of this compartment.
     *  @return mVolume
     *  @see mVolume
     */
    const C_FLOAT64 & getVolume() const;

    /**
     *  Returns a C_FLOAT64 with the 1/volume of this compartment.
     *  @return mVolumeInv
     *  @see mVolumeInv
     */
    const C_FLOAT64 & getVolumeInv() const;

    /*
     *
     */
    CCopasiVectorNS < CMetab > & getMetabolites();
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

    bool removeMetabolite(CMetab *metabolite);

    /**
     *  Sets the name of this compartment.
     *  @param name string with the name of the compartment.
     *  @see mName
     */
    bool setName(const std::string & name);

    /**
     *  Sets the initial volume of this compartment.
     *  @param volume the volume of the compartment.
     *  @return bool success
     *  @see mVolume
     */
    bool setInitialVolume(const C_FLOAT64 & volume);

    /**
     *  Sets the volume of this compartment.
     *  @param const C_FLOAT64 & volume
     *  @return bool success
     *  @see mVolume
     */
    bool setVolume(const C_FLOAT64 & volume);

    /**
     * Returns the address of mVolume  Wei Sun
     */
    void * getVolumeAddr();

    friend std::ostream & operator<<(std::ostream &os, const CCompartment & d);

  private:

    /**
     *  Check whether the name is valid.
     */
    bool isValidName(const std::string & name) const;

    /**
     * Initialize the contained CCopasiObjects
     */
    void initObjects();
  };

#endif // COPASI_CCompartment
