#ifndef COPASI_CCopasiVectorN
#define COPASI_CCopasiVectorN

#include <vector>
#include <iostream>
#include <assert.h>

#include "CCopasiMessage.h"
#include "CReadConfig.h"
#include "CWriteConfig.h"


template < class CType >
class CCopasiVectorN : public vector < CType * >
{
 public:
  typedef CType* value_type;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;
  typedef value_type* iterator;
  typedef const value_type* const_iterator;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;
 
  // Operations
 public:
  /**
   *  Default constructor
   */
  CCopasiVectorN() : vector < CType * > (){} 

  /**
   *  Copy constructor
   */
  CCopasiVectorN(const CCopasiVectorN < CType > & src) :
    vector < CType * > (src)
    {
      unsigned C_INT32 i, imax = src.size();
      
      resize(imax);
      
      for (i=0; i<imax; i++)
	((vector < CType * >) (*this))[i] 
	  = new CType(*((vector < CType * >) src)[i]);
    }

  /**
   *  Destructor
   */
  virtual ~CCopasiVectorN() {cleanup();}

  /**
   *  Cleanup
   */
  virtual void cleanup()
    {
      unsigned C_INT32 i, imax = size();
      
      for (i=0; i<imax; i++)
	((vector < CType * >) (*this))[i]->cleanup();
  
      clear();
    }
  
  /**
   *  Loads an object with data coming from a CReadConfig object.
   *  (CReadConfig object reads an input stream)
   *  @param "CReadConfig &" configbuffer reference to a CReadConfig object
   *  @param "const unsigend C_INT32 &" size
   */
  virtual void load(CReadConfig & configbuffer, unsigned C_INT32 size)
    {
      unsigned C_INT32 i;
      
      cleanup();
      resize(size);
      
      ((vector < CType * >) (*this))[0] = new CType;
      ((vector < CType * >) (*this))[0]->load(configbuffer);
      
      for (i=1; i<size; i++)
	{
	  ((vector < CType * >) (*this))[i] = new CType;
	  ((vector < CType * >) (*this))[i]->load(configbuffer);
	}
    }
  
  /**
   *  Saves the contents of the object to a CWriteConfig object.
   *  (Which usually has a file attached but may also have socket)
   *  @param "CWriteConfig &" configbuffer reference to a CWriteConfig object.
   */
  virtual void save(CWriteConfig & configbuffer)
    {
      unsigned C_INT32 i, imax = size();
      
      for (i=0; i<imax; i++)
	((vector < CType * >) (*this))[i]->save(configbuffer);
    }

  /**
   *
   */
  virtual void add(const CType & src)
    {
      if ( ! isInsertAllowed(src) ) fatalError();
      // This is not very efficient !!!
      // It results in a lot of resizing of the vector !!!
      CType * Element = new CType(src);
      
      push_back(Element);
    }

  /**
   *  Removes the index-th element from the vector
   *  @param "const unsigned C_INT32 &" indecx
   */
  virtual void remove(const unsigned C_INT32 & index)
    {
      assert(index < size());

      ((vector < CType * >) (*this))[index]->cleanup();
      delete ((vector < CType * >) (*this))[index];
      
      erase(&((vector < CType * >) (*this))[index],
	    &((vector < CType * >) (*this))[index+1]);
    }

  /**
   *
   */
  virtual void remove(const string & name)
    {
      C_INT32 Index = getIndex(name);
      if ( Index == -1 ) fatalError();
    
      return remove(Index);
    }

  CType * operator[](const string &name) 
    {
      C_INT32 Index = getIndex(name);
      if ( Index == -1 ) fatalError();
            
      return *(begin() + Index);
    }   

  CType * & operator[](unsigned C_INT32 index) 
    {
      assert(index < size());
      return *(begin() + index);
    }   

  const CType * & operator[](unsigned C_INT32 index) const
    {
      assert(index < size());
      return *(begin() + index);
    }   

  /**
   *
   */
  unsigned C_INT32 size() const 
    {
      return vector < CType * >::size();
    }

 private:
  /**
   *
   */
  virtual C_INT16 isInsertAllowed(const CType & src)
    {return (getIndex(src.getName()) == (unsigned C_INT32) -1);}
 
  /**
   *
   */
  unsigned C_INT32 getIndex(const string &name) const
    {
      unsigned C_INT32 i,imax = size();
      
      for (i=0; i<imax; i++)
	if (name == ((vector < CType * >) (*this))[i]->getName() ) 
	  return i;
            
      return -1;
    }
};
#endif // COPASI_CCopasiVectorN
