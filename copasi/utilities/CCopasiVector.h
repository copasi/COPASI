#ifndef COPASI_CCopasiVector
#define COPASI_CCopasiVector

#include <vector>
#include <iostream>
#include <assert.h>

#include "CReadConfig.h"
#include "CWriteConfig.h"

template < class CType >
class CCopasiVector : protected vector < CType * >
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
  CCopasiVector() : vector < CType * > (){} 

  /**
   *  Copy constructor
   */
  CCopasiVector(const CCopasiVector < CType > & src) :
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
  virtual ~CCopasiVector() {cleanup();}

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
   *
   */
  virtual void add(const CType & src)
    {
      CType * Element = new CType(src);
      
      // This is not very efficient !!!
      // It results in a lot of resizing of the vector !!!
      push_back(Element);
    }

  /**
   *
   */
  virtual void add(CType * src)
    {
      // This is not very efficient !!!
      // It results in a lot of resizing of the vector !!!
      push_back(src);
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
  const CType * operator[](unsigned C_INT32 index) const
    {
      assert(index < size());
      return *(begin() + index);
    }   

  /**
   *
   */
  CType * & operator[](unsigned C_INT32 index) 
    {
      assert(index < size());
      return *(begin() + index);
    }   

  /**
   *  Retrieves the size of the vector
   *  @return "unsigned C_INT32" size
   */
  virtual unsigned C_INT32 size() const {return vector < CType * >::size();}

  /**
   *  Resizes the vector
   *  @param "unsigned C_INT32" size
   */
  virtual void resize(unsigned C_INT32 size) 
    {
      unsigned C_INT32 OldSize = vector < CType * >::size();
      
      vector < CType * >::resize(size);
      unsigned C_INT32 i;
      iterator Target = begin() + OldSize;
      
      for (i=OldSize; i<size; i++)
	*(Target++) = new CType;
    }
  
};

template < class CType > class CCopasiVectorS 
: public CCopasiVector < CType >
{
  // Operations
 public:
  /**
   *  Default constructor
   */
  CCopasiVectorS() : CCopasiVector < CType > (){} 

  /**
   *  Copy constructor
   */
  CCopasiVectorS(const CCopasiVectorS < CType > & src) :
      CCopasiVector < CType > (src) {}

  /**
   *  Destructor
   */
  virtual ~CCopasiVectorS() {cleanup();}

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
      vector < CType * >::resize(size);
      
      CCopasiVector< CType >::iterator Target = begin();
 
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
      CCopasiVector< CType >::iterator Target = begin();
      
      for (i=0; i<imax; i++)
	(*(Target++))->save(configbuffer);
    }

  /**
   *
   */
  CType * & operator[](unsigned C_INT32 index) 
    {return ((CCopasiVector <CType>*) this)->operator [](index);}

  /**
   *
   */
  const CType * operator[](unsigned C_INT32 index) const
    {return ((CCopasiVector <CType>*) this)->operator [](index);}
};

template < class CType > class CCopasiVectorN 
: public CCopasiVector < CType >
{
  // Operations
 public:
  /**
   *  Default constructor
   */
  CCopasiVectorN() : CCopasiVector < CType > (){} 

  /**
   *  Copy constructor
   */
  CCopasiVectorN(const CCopasiVectorN < CType > & src) :
      CCopasiVector < CType > (src) {}

  /**
   *  Destructor
   */
  virtual ~CCopasiVectorN() {cleanup();}

  /**
   *
   */
  virtual void add(const CType & src)
    {
      CType * Element = new CType(src);
      add(Element);
    }

  /**
   *
   */
  virtual void add(CType * src)
    {
      isInsertAllowed(src);
      // This is not very efficient !!!
      // It results in a lot of resizing of the vector !!!
      push_back(src);
    }

  /**
   *
   */
  virtual void remove(const string & name)
    {
      unsigned C_INT32 Index = getIndex(name);
      if ((signed) Index == -1 ) fatalError();
      
      CCopasiVector< CType >::remove(Index);
      return;
    }

  /**
   *
   */
  CType * & operator[](unsigned C_INT32 index) 
    {return ((CCopasiVector <CType>*) this)->operator [](index);}

  /**
   *
   */
  const CType * & operator[](unsigned C_INT32 index) const
    {return ((CCopasiVector <CType>*) this)->operator [](index);}

  /**
   *
   */
  CType * operator[](const string &name) 
    {
      C_INT32 Index = getIndex(name);
      if ( Index == -1 ) fatalError();
            
      return *(begin() + Index);
    }   

 private:
  /**
   *
   */
  virtual C_INT16 isInsertAllowed(const CType * src)
    {return (getIndex(src->getName()) == (unsigned C_INT32) -1);}
 
  /**
   *
   */
  virtual unsigned C_INT32 getIndex(const string &name) const
    {
      unsigned C_INT32 i,imax = size();
      CCopasiVector< CType >::const_iterator Target = begin();
      
      for (i=0; i<imax; i++)
	  if ((*(Target++))->getName() == name) return i;
      
      return -1;
    }
};

template < class CType > class CCopasiVectorNS 
: public CCopasiVectorN < CType >
{
  // Operations
 public:
  /**
   *  Default constructor
   */
  CCopasiVectorNS() : CCopasiVectorN < CType > (){} 

  /**
   *  Copy constructor
   */
  CCopasiVectorNS(const CCopasiVectorNS < CType > & src) :
      CCopasiVectorN < CType > (src) {}

  /**
   *  Destructor
   */
  virtual ~CCopasiVectorNS() 
    {cleanup();}

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
      vector < CType * >::resize(size);
      
      CCopasiVector< CType >::iterator Target = begin();
 
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
      CCopasiVector< CType >::iterator Target = begin();
      
      for (i=0; i<imax; i++)
	(*(Target++))->save(configbuffer);
    }

  /**
   *
   */
  CType * & operator[](unsigned C_INT32 index) 
    {return ((CCopasiVector <CType>*) this)->operator [](index);}

  /**
   *
   */
  const CType * & operator[](unsigned C_INT32 index) const
    {return ((CCopasiVector <CType>*) this)->operator [](index);}

  /**
   *
   */
  CType * operator[](const string &name) 
    {return ((CCopasiVectorN <CType>*) this)->operator [](name);}   
};
#endif // COPASI_CCopasiVector
