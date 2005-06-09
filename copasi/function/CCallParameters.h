/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CCallParameters.h,v $
   $Revision: 1.16 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/06/09 16:42:35 $
   End CVS Header */

/**
 * CFunctionParameterMap
 * 
 * Created for Copasi by Stefan Hoops
 * (C) Stefan Hoops 2002
 */

#ifndef COPASI_CCallParameters
#define COPASI_CCallParameters

#include <vector>
#include "CFunctionParameter.h"
#include "CFunctionParameters.h"
#include "report/CCopasiObject.h"

/**
 * CCallParameterPointers
 *
 * This is what is actually passed to a function. Some of the void* can be
 * pointers to vector<const CCopasiObject*>
 */
template < typename Type >
class CCallParameters : private std::vector<void *>
  {
  public:
    union UType
      {
        const Type * value;
        std::vector<const Type *> * vector;
      };

    typedef typename std::vector< UType >::const_iterator const_iterator;

    // Operations
  public:
    CCallParameters(const unsigned C_INT32 & size = 0):
        std::vector<void *>(size)
    {}

    CCallParameters(const CCallParameters & src):
        std::vector<void *>(src)
    {}

    ~CCallParameters() {}

    void resize(const unsigned C_INT32 & size)
    {
      ((std::vector<UType> *)this)->resize(size);

      typename std::vector<UType>::iterator it
      = ((std::vector<UType> *)this)->begin();
      typename std::vector<UType>::iterator end
      = ((std::vector<UType> *)this)->end();

      for (; it != end; ++it) it->value = NULL;
    }

    inline void clear()
  {((std::vector<UType> *)this)->clear();}

    inline unsigned C_INT32 size() const
      {return ((const std::vector< UType > *)this)->size();}

    inline UType & operator[](const unsigned C_INT32 & index)
    {return (*(std::vector< UType > *)this)[index];}

    inline const UType & operator[](const unsigned C_INT32 & index) const
      {return (*(const std::vector< UType > *)this)[index];}

    inline const_iterator begin() const
      {return ((const std::vector< UType > *)this)->begin();}

    inline const_iterator end() const
      {return ((const std::vector< UType > *)this)->end();}
  };

/**
 * CFunctionParameterMap         
 *
 * This class describes how a reaction fills the call parameters of a function.
 * It is generated from a CFunctionParameters object.
 * The reaction provides what exactly is to be passed as function parameters.
 */
class CFunctionParameterMap
  {
  public:

    CFunctionParameterMap();

    CFunctionParameterMap(const CFunctionParameterMap & src);

    /**
     * Destructor();
     */
    ~CFunctionParameterMap();

    /**
     * Sets a specific parameter. Works only if the parameter is no vector
     */
    void setCallParameter(const std::string paramName, const CCopasiObject* obj);

    /**
     * Adds an object to a specific parameter vector. Works only if the parameter is a vector
     */
    void addCallParameter(const std::string paramName, const CCopasiObject* obj);

    /**
     * Removes an object from a specific parameter vector. Works only if the parameter is a vector
     */
    void removeCallParameter(const std::string paramName, const CCopasiObject* obj);

    /**
     * Removes all objects from a specific parameter vector. Works only if the parameter is a vector.
     */
    void clearCallParameter(const std::string paramName);

    /**
     * Initializes a CallParameters object from a CFunctionParameters object.
     */
    void initializeFromFunctionParameters(const CFunctionParameters & src);

    unsigned C_INT32 findParameterByName(const std::string & name,
                                         CFunctionParameter::DataType & dataType) const;

  private:

    /**
     * Clear the mPointers and mObjects vectors.
     */
    void clearCallParameters();

    /**
     * Create the mPointers and mObjects vectors with
     * type information from the CFunctionParameters object.
     */
    void initCallParameters();

    /**
     * Check if all pointers are !=NULL.
     */
    void checkCallParameters() const;

    /**
     * This is a vector of pointers to the data that is passed to a function
     */
    CCallParameters<C_FLOAT64> mPointers;

    /**
     * This is a vector of pointers to objects. Each objects needs to have a value
     * that can be passed to a function
     */
    CCallParameters<CCopasiObject> mObjects;

    /**
     * The CFunctionParameters object provides the data types of the call parameters
     */
    CFunctionParameters * mpFunctionParameters;

    // these are preliminary
  public:
    const CFunctionParameters & getFunctionParameters() const;

    CCallParameters<C_FLOAT64> & getPointers();

    CCallParameters<CCopasiObject> & getObjects();

    const CCallParameters<CCopasiObject> & getObjects() const;

    std::vector< const CCopasiObject * > getObjects(const unsigned C_INT32 & index) const;
  };

#endif // COPASI_CCallParameters
