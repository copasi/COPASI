/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CCompartment.h,v $
   $Revision: 1.29 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/11/03 20:47:20 $
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

#include "report/CCopasiContainer.h"
#include "utilities/CCopasiVector.h"
#include "CMetab.h"

class CReadConfig;
class CWriteConfig;

/** @dia:pos 128.756,33.503 */
class CCompartment : public CCopasiContainer
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
    /** @dia:route 3,9; h,128.756,34.203,126.793,53.4961,117.263 */
    CCopasiVectorNS < CMetab > mMetabolites;
    // Operations

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
     *  Init
     */ 
    // void initialize();

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
     *  Saves the contents of the object to a CWriteConfig object.
     *  (Which usually has a file attached but may also have socket)
     *  @param pconfigbuffer reference to a CWriteConfig object.
     *  @return mFail
     *  @see mFail
     */
    C_INT32 save(CWriteConfig & configbuffer);

    /**
     *  Saves the contents of the object to a CWriteConfig object.
     *  Writes the data in Gepasi 3.21 file format
     *  @param pconfigbuffer reference to a CWriteConfig object.
     *  @return mFail
     *  @see mFail
     */
    C_INT32 saveOld(CWriteConfig & configbuffer);

    /**
     *  Saves the contents of the object to a ofstream object.
     *  Writes the data in SBML file format
     *  @param "std::ofstream &" fout ofstream that should be already open
     */
    void saveSBML(std::ofstream &fout);

    /**
     *  Returns a string with the name of this compartment.
     *  @return std::string key
     */
    std::string getKey() const;

    /**
     *  Returns a string with the name of this compartment.
     *  @return mName
     *  @see mName
     */
    const std::string & getName() const;

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
    bool addMetabolite(const CMetab & metabolite);

    /**
     *  Adds a metabolite to the compartment. Only the concentration is taken from
     *  the metabolite, the number of particles is calculated according to the
     *  volume of the compartment
     *  @param CMetab * metabolite;
     *  @return bool success
     */
    bool addMetabolite(CMetab * metabolite);

    /**
     *  Sets the name of this compartment.
     *  @param name string with the name of the compartment.
     *  @see mName
     */
    bool setName(const std::string & name);

    /**
     *  Sets the initial volume of this compartment.
     *  @param volume the volume of the compartment.
     *  @see mVolume
     */
    void setInitialVolume(C_FLOAT64 volume);

    /**
     *  Sets the volume of this compartment.
     *  @param volume the volume of the compartment.
     *  @see mVolume
     */
    void setVolume(C_FLOAT64 volume);

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
