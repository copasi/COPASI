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

#include "utilities/utilities.h"
#include "CMetab.h"

class CCompartment {
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
   *  Metabolites located in the compartment.
   *  @supplierCardinality 0..*
   *  @associates <{CMetab}>
   */
  CCopasiVectorN < CMetab > mMetabolites;
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
  C_FLOAT64 getVolume() const;

  /*
   *
   */
  CCopasiVectorN < CMetab > & metabolites();
    
  /*
   *
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
   *	Returns the address of mVolume		Wei Sun
   */
  void * getVolumeAddr();

 private:

  /*
   *
   */
  C_INT16 isValidName() const;
};

#endif // COPASI_CCompartment
