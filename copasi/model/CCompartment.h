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

class CReadConfig;

class CWriteConfig;

#include "CMetab.h"
#include "utilities/CCopasiVector.h"

class CCompartment
  {
    // Attributes

  private:
    /**
     *  Name of the compartment.
     */
    string mName;

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
    CCopasiVectorNS < CMetab > mMetabolites;
    // Operations

  public:
    /**
     *  Default constructor. 
     *  Creates an empty object with mName="compartment" and mVolume=1
     */
    CCompartment();

    /**
     *  Copy constructor.
     *  @param "const CCompartment &" src
     */
    CCompartment(const CCompartment & src);

    /**
     *  Specified constructor. 
     *  Creates an object with contents passed as arguments
     *  @param name name of the comnpartment.
     *  @param volume volume of the compartment.
     */
    CCompartment(const string & name, C_FLOAT64 volume);

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
     *  Assignement operator. 
     *  Copies the contents from one CCompartment object to another.
     *  @param ptRHS reference to the recipient object.
     */
    CCompartment & operator=(const CCompartment & rhs);

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
     *  Returns a string with the name of this compartment.
     *  @return mName
     *  @see mName
     */
    string getName() const;

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
    CCopasiVectorNS < CMetab > & metabolites();

    /*
     *  Adds a metabolite to the compartment. Only the concentration is taken from
     *  the metabolite, the number of particles is calculated according to the
     *  volume of the compartment
     */
    void addMetabolite(CMetab & metabolite);

    /**
     *  Sets the name of this compartment.
     *  @param name string with the name of the compartment.
     *  @see mName
     */
    void setName(const string & name);

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

    friend ostream & operator<<(ostream &os, const CCompartment & d)
    {
      os << "++++CCompartment: " << d.mName << " mVolume " << d.mVolume
      << " mVolumeInv " << d.mVolumeInv << endl;
      os << "    CCompartment.mMetabolites " << endl << d.mMetabolites;
      os << "----CCompartment " << endl;

      return os;
    }

  private:

    /*
     *
     */
    C_INT16 isValidName() const;

    /**
     * insert operator
     */
  };

#endif // COPASI_CCompartment
