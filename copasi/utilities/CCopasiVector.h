#ifndef COPASI_C_CopasiVector
#define COPASI_C_CopasiVector

#include <vector>
#include <iostream>
#include <assert.h>

#include "CReadConfig.h"
#include "CWriteConfig.h"

template < class CType >
class C_CopasiVector : protected vector < CType * >
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
  C_CopasiVector() : vector < CType * > (){} 

  /**
   *  Copy constructor
   */
  C_CopasiVector(const C_CopasiVector < CType > & src) :
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
  virtual ~C_CopasiVector() {cleanup();}

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
   *
   */
  virtual unsigned C_INT32 size() const 
    {return vector < CType * >::size();}
};

template < class CType > class C_CopasiVectorS 
: public C_CopasiVector < CType >
{
  // Operations
 public:
  /**
   *  Default constructor
   */
  C_CopasiVectorS() : C_CopasiVector < CType > (){} 

  /**
   *  Copy constructor
   */
  C_CopasiVectorS(const C_CopasiVectorS < CType > & src) :
      C_CopasiVector < CType > (src) {}

  /**
   *  Destructor
   */
  virtual ~C_CopasiVectorS() {cleanup();}

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
      
      C_CopasiVector< CType >::iterator Target = begin();
 
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
      C_CopasiVector< CType >::iterator Target = begin();
      
      for (i=0; i<imax; i++)
	(*(Target++))->save(configbuffer);
    }

  /**
   *
   */
  CType * & operator[](unsigned C_INT32 index) 
    {return ((C_CopasiVector <CType>*) this)->operator [](index);}

  /**
   *
   */
  const CType * operator[](unsigned C_INT32 index) const
    {return ((C_CopasiVector <CType>*) this)->operator [](index);}
};

template < class CType > class C_CopasiVectorN 
: public C_CopasiVector < CType >
{
  // Operations
 public:
  /**
   *  Default constructor
   */
  C_CopasiVectorN() : C_CopasiVector < CType > (){} 

  /**
   *  Copy constructor
   */
  C_CopasiVectorN(const C_CopasiVectorN < CType > & src) :
      C_CopasiVector < CType > (src) {}

  /**
   *  Destructor
   */
  virtual ~C_CopasiVectorN() {cleanup();}

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
    
      return C_CopasiVector< CType >::remove(Index);
    }

  /**
   *
   */
  CType * & operator[](unsigned C_INT32 index) 
    {return ((C_CopasiVector <CType>*) this)->operator [](index);}

  /**
   *
   */
  const CType * & operator[](unsigned C_INT32 index) const
    {return ((C_CopasiVector <CType>*) this)->operator [](index);}

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
      C_CopasiVector< CType >::const_iterator Target = begin();
      
      for (i=0; i<imax; i++)
        if (name == (*(Target++))->getName()) return i;
            
      return -1;
    }
};

template < class CType > class C_CopasiVectorNS 
: public C_CopasiVectorN < CType >
{
  // Operations
 public:
  /**
   *  Default constructor
   */
  C_CopasiVectorNS() : C_CopasiVectorN < CType > (){} 

  /**
   *  Copy constructor
   */
  C_CopasiVectorNS(const C_CopasiVectorNS < CType > & src) :
      C_CopasiVectorN < CType > (src) {}

  /**
   *  Destructor
   */
  virtual ~C_CopasiVectorNS() 
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
      resize(size);
      
      C_CopasiVector< CType >::iterator Target = begin();
 
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
      C_CopasiVector< CType >::iterator Target = begin();
      
      for (i=0; i<imax; i++)
	(*(Target++))->save(configbuffer);
    }

  /**
   *
   */
  CType * & operator[](unsigned C_INT32 index) 
    {return ((C_CopasiVector <CType>*) this)->operator [](index);}

  /**
   *
   */
  const CType * & operator[](unsigned C_INT32 index) const
    {return ((C_CopasiVector <CType>*) this)->operator [](index);}

  /**
   *
   */
  CType * operator[](const string &name) 
    {return ((C_CopasiVectorN <CType>*) this)->operator [](name);}   
};
#endif // COPASI_C_CopasiVector
