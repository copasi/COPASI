#ifndef COPASI_CCopasiVectorN
#define COPASI_CCopasiVectorN

#include <vector>
#include <iostream>
#include <assert.h>

#include "CCopasiMessage.h"
#include "CReadConfig.h"
#include "CWriteConfig.h"


template < class CType >
class CCopasiVectorN : protected vector < CType * >
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
      unsigned C_INT32 i, imax = size();
      iterator Target = begin();
      const_iterator Source = src.begin();
      
      for (i=0; i<imax; i++)
	*(Target++) = new CType(**(Source++));
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
      iterator Target = begin();
      
      for (i=0; i<imax; i++)
	(*(Target++))->cleanup();
  
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
      
      iterator Target = begin();
 
      for (i=0; i<size; i++)
	{
	  *Target = new CType;
	  (*(Target++))->load(configbuffer);
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
      iterator Target = begin();
      
      for (i=0; i<imax; i++)
	(*(Target++))->save(configbuffer);
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
      iterator Target = begin() + index;
      assert(index < size());

      (*Target)->cleanup();
      delete *Target;
      erase(Target, Target + 1);
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
      const_iterator Target = begin();
      
      for (i=0; i<imax; i++)
	if (name == (*(Target++))->getName()) return i;
            
      return -1;
    }
};
#endif // COPASI_CCopasiVectorN
