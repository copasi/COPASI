// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CCopasiVector.h,v $
//   $Revision: 1.76.4.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/02/11 20:34:44 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CCopasiVector
#define COPASI_CCopasiVector

#ifdef WIN32
# pragma warning (disable: 4786)
#endif  // WIN32

#include <vector>
#include <string>
#include <iostream>

#include "utilities/CCopasiMessage.h"
#include "utilities/utility.h"

#include "report/CCopasiObjectName.h"
#include "report/CCopasiContainer.h"

class CReadConfig;

template <class CType> class CCopasiVector;

template <class CType>
std::ostream &operator<<(std::ostream &os, const CCopasiVector<CType> & d);

template < class CType > class CCopasiVector:
        protected std::vector< CType * >, public CCopasiContainer
    {
    public:
      typedef typename std::vector< CType * >::value_type value_type;
      typedef typename std::vector< CType * >::iterator iterator;
      typedef typename std::vector< CType * >::const_iterator const_iterator;

      // Operations

    public:
      /**
       * Default constructor
       * @param const const std::string & name (Default: "NoName")
       * @param const CCopasiContainer * pParent (Default: NULL)
       * @param const unsigned C_INT32 & flag (Default: flag | CCopasiObject::Vector)
       */
      CCopasiVector(const std::string & name = "NoName",
                    const CCopasiContainer * pParent = NULL,
                    const unsigned C_INT32 &
                    flag = CCopasiObject::Vector):
          std::vector< CType * >(),
          CCopasiContainer(name, pParent, "Vector", flag | CCopasiObject::Vector)
      {CONSTRUCTOR_TRACE;}

      /**
       * Copy constructor
       * @param const CCopasiVector < CType > & src
       * @param const CCopasiContainer * pParent (Default: NULL)
       */
      CCopasiVector(const CCopasiVector < CType > & src,
                    const CCopasiContainer * pParent = NULL):
          std::vector< CType * >(src),
          CCopasiContainer(src, pParent)
      {
        CONSTRUCTOR_TRACE;

        unsigned C_INT32 i, imax = size();
        iterator Target = begin();
        const_iterator Source = src.begin();

        for (i = 0; i < imax; i++, Target++, Source++)
          {
            try
              {
                *Target = new CType(**Source, this);
              }
            catch (...)
              {
                *Target = NULL;
              }

            if (*Target == NULL)
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCopasiBase + 1, imax * sizeof(CType));
          }
      }

      /**
       *  Destructor
       */
      virtual ~CCopasiVector()
      {
        cleanup();
        DESTRUCTOR_TRACE;
      }

      /**
       * Assignment operator. The effect of this operator is that both vectors will
       * share the same objects. However, the parentship of the objects is not affected
       * This means that the assigned vector must be used with some care.
       * @param const CCopasiVector< CType > & rhs
       * @return CCopasiVector< CType > & lhs
       */
      CCopasiVector< CType > & operator = (const CCopasiVector< CType > & rhs)
      {
        cleanup();

        const_iterator it = rhs.begin();
        const_iterator end = rhs.end();

        for (;it != end; ++it)
          add(*it, false);

        return *this;
      }

      /**
       * Assignment operator.
       * @param const std::vector< CType * > & rhs
       * @return CCopasiVector< CType > & lhs
       */
      CCopasiVector< CType > & operator = (const std::vector< CType * > & rhs)
      {
        cleanup();

        typename std::vector< CType * >::const_iterator it = rhs.begin();
        typename std::vector< CType * >::const_iterator end = rhs.end();

        for (;it != end; ++it)
          add(*it, false);

        return *this;
      }

      /**
       * This creates a deep copy of the source, i.e., all objects are copied and
       * the parent of these copies is the current vector.
       * @param const CCopasiVector< CType > & source
       */
      void deepCopy(const CCopasiVector< CType > & source)
      {
        cleanup();
        resize(source.size());

        unsigned C_INT32 i, imax = size();
        iterator Target = begin();
        const_iterator Source = source.begin();

        for (i = 0; i < imax; i++, Target++, Source++)
          {
            try
              {
                *Target = new CType(**Source, this);
              }
            catch (...)
              {
                *Target = NULL;
              }

            if (*Target == NULL)
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCopasiBase + 1, imax * sizeof(CType));
          }
      }

      iterator begin()
    {return static_cast< std::vector< CType * > *>(this)->begin();}

      const_iterator begin() const
        {return static_cast<const std::vector< CType * > *>(this)->begin();}

      iterator end()
      {return static_cast< std::vector< CType * > *>(this)->end();}

      const_iterator end() const
        {return static_cast<const std::vector< CType * > *>(this)->end();}

      /**
       *  Cleanup
       */
      virtual void cleanup()
      {
        iterator it = begin();
        iterator End = end();

        for (; it != End; it++)
          if (*it)
            if ((*it)->getObjectParent() == this)
              {
                //                (*it)->cleanup();
                CCopasiContainer::remove(*it);
                (*it)->setObjectParent(NULL);
                delete(*it);
                *it = NULL;
              }

        CCopasiVector< CType >::clear();
      }

      /**
       * Add a copy of the object to the end of the vector.
       * @param const CType & src
       * @return bool success.
       */
      virtual bool add(const CType & src)
      {
        CType * Element;
        try
          {
            Element = new CType(src);
          }
        catch (...)
          {
            Element = NULL;
          }

        if (Element == NULL)
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCopasiBase + 1, sizeof(CType));

        // This is not very efficient !!!
        // It results in a lot of resizing of the vector !!!
        push_back(Element);
        return CCopasiContainer::add(Element);
      }

      /**
       * Swap two objects in the vector.
       * @param const unsigned C_INT32 & indexFrom
       * @param const unsigned C_INT32 & indexTo
       */
      virtual void swap(const unsigned C_INT32 & indexFrom, const unsigned C_INT32 & indexTo)
      {
        unsigned C_INT32 Size = size();
        if (!(indexFrom < Size))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCCopasiVector + 3, indexFrom, Size - 1);

        if (!(indexTo < Size))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCCopasiVector + 3, indexTo, Size - 1);

        iterator from = begin() + indexFrom;
        iterator to = begin() + indexTo;

        value_type tmp = *from;
        *from = *to;
        *to = tmp;
      }

      /**
       * Add an object to the end of the vector, if adobt is true the vector.
       * becomes the parent of the object.
       * @param CType * src
       * @param const bool & adopt (Default: false)
       * @return bool success
       */
      virtual bool add(CType * src, bool adopt = false)
      {
        // This is not very efficient !!!
        // It results in a lot of resizing of the vector !!!
        push_back(src);
        return CCopasiContainer::add(src, adopt);
      }

      /**
       *  Removes the index-th element from the vector
       *  @param const unsigned C_INT32 & index
       */
      virtual void remove(const unsigned C_INT32 & index)
      {
        if (!(index < size()))
          return;

        iterator Target = begin() + index;

        if (*Target)
          {
            if ((*Target)->getObjectParent() == this)
              {
                //                (*Target)->cleanup();
                delete *Target;
              }
            else
              {
                CCopasiContainer::remove(*Target);
                erase(Target, Target + 1);
              }
          }
      }

      /**
       * Removes the pointed to object from the vector
       * @param CCopasiObject * pObject
       * @return bool success
       */
      virtual bool remove(CCopasiObject * pObject)
      {
        const unsigned C_INT32 index = getIndex(pObject);

        bool success = true;

        if (index != C_INVALID_INDEX)
          {
            iterator Target = begin() + index;
            erase(Target, Target + 1);

            success = false;
          }

        success &= CCopasiContainer::remove(pObject);

        return success;
      }

      /**
       * Retrieve the indexed object.
       * @param const unsigned C_INT32 & index
       * @return const value_type & object
       */
      const value_type & operator[](const unsigned C_INT32 & index) const
        {
          if (!(index < size()))
            CCopasiMessage(CCopasiMessage::EXCEPTION, MCCopasiVector + 3, index, size() - 1);

          return *(begin() + index);
        }

      /**
       * Retrieve the indexed object.
       * @param const unsigned C_INT32 & index
       * @return value_type & object
       */
      value_type & operator[](const unsigned C_INT32 & index)
      {
        if (!(index < size()))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCCopasiVector + 3, index, size() - 1);

        return *(begin() + index);
      }

      /**
       * Retrieve a the CCopasiObject with the given name.
       * @param const CCopasiObjectName &name
       * @return const CCopasiObject * object
       */
      virtual const CCopasiObject * getObject(const CCopasiObjectName &name) const
        {
          unsigned C_INT32 Index = name.getElementIndex();

          if (Index < size())
            {
              CCopasiObject * pObject = *(begin() + Index);

              if (name.getObjectType() == pObject->getObjectType())
                return pObject; //exact match of type and name

              if (name.getObjectName() == "")
                return pObject; //cn contains no "="; type cannot be checked
            }

          return NULL;
        }

      /**
       *  Retrieves the size of the vector
       *  @return unsigned C_INT32 size
       */
      virtual unsigned C_INT32 size() const
      {return static_cast< const std::vector< CType * > * >(this)->size();}

      /**
       *  Resizes the vector
       *  @param const unsigned C_INT32 & newSize
       *  @param const bool & allocate (Default: true)
       */
      virtual void resize(const unsigned C_INT32 & newSize,
                          const bool & allocate = true)
      {
        unsigned C_INT32 OldSize = size();

        if (OldSize == newSize) return; // Nothing to do.

        if (OldSize < newSize)
          {
            static_cast< std::vector< CType * > * >(this)->resize(newSize);

            unsigned C_INT32 i;
            iterator Target = begin() + OldSize;

            if (allocate)
              for (i = OldSize; i < newSize; i++, Target++)
                {
                  try
                    {
                      *Target = new CType("NoName", this);
                    }
                  catch (...)
                    {
                      *Target = NULL;
                    }

                  if (*Target == NULL)
                    CCopasiMessage(CCopasiMessage::EXCEPTION, MCopasiBase + 1, newSize * sizeof(CType));
                }
            else
              for (i = OldSize; i < newSize; i++, Target++)
                *Target = NULL;
          }
        else
          {
            iterator Target = begin() + newSize;
            iterator End = end();

            for (; Target != End; Target++)
              if (*Target)
                {
                  if ((*Target)->getObjectParent() == this)
                    {
                      CCopasiContainer::remove(*Target);
                      (*Target)->setObjectParent(NULL);
                      delete *Target;
                    }
                  else
                    CCopasiContainer::remove(*Target);
                }

            static_cast< std::vector< CType * > * >(this)->resize(newSize);
          }
      }

      /**
       * Retrieve the index of the pointed to object in the vector. If the object
       * is not found C_INVALID_INDEX is returned.
       * @param const CCopasiObject * pObject
       * @return unsigned C_INT32 index
       */
      virtual unsigned C_INT32 getIndex(const CCopasiObject * pObject) const
        {
          unsigned C_INT32 i, imax = size();
          const_iterator Target = begin();

          for (i = 0; i < imax; i++, Target++)
            if (*Target == (void *) pObject) return i;

          return C_INVALID_INDEX;
        }

      /**
       * ostream operator
       * @param std::ostream & os
       * @param const CCopasiVector<CType> & d
       * @return std::ostream & os
       */
#if defined _MSC_VER && _MSC_VER < 1201 // 1200 Identifies Visual C++ 6.0
      friend std::ostream &operator << (std::ostream &os,
                                        const CCopasiVector<CType> & d);
#else
      friend std::ostream &operator << <>(std::ostream &os,
                                          const CCopasiVector<CType> & d);
#endif // WIN32
    };

template < class CType > class CCopasiVectorS: public CCopasiVector < CType >
    {
    public:
      typedef typename std::vector< CType * >::value_type value_type;
      typedef typename std::vector< CType * >::iterator iterator;
      typedef typename std::vector< CType * >::const_iterator const_iterator;

      // Operations
    public:
      /**
       * Default constructor
       * @param const std::string & name (Default: "NoName")
       * @param const CCopasiContainer * pParent (Default: NULL)
       */
      CCopasiVectorS(const std::string & name = "NoName",
                     const CCopasiContainer * pParent = NULL):
      CCopasiVector< CType >(name, pParent){}

      /**
       * Copy constructor
       * @param const CCopasiVectorS < CType > & src
       * @param const CCopasiContainer * pParent (Default: NULL)
       */
      CCopasiVectorS(const CCopasiVectorS < CType > & src,
                     const CCopasiContainer * pParent = NULL) :
      CCopasiVector < CType > (src, pParent) {}

      /**
       *  Destructor
       */
      virtual ~CCopasiVectorS() {}

      /**
       * Loads an object with data coming from a CReadConfig object.
       * (CReadConfig object reads an input stream)
       * @param CReadConfig & configbuffer
       * @param const unsigend C_INT32 & size
       */
      virtual void load(CReadConfig & configbuffer, unsigned C_INT32 size)
      {
        unsigned C_INT32 i;

        CCopasiVector< CType >::cleanup();
        CCopasiVector< CType >::resize(size, false);

        iterator Target = CCopasiVector< CType >::begin();
        for (i = 0; i < size; i++, Target++)*Target = NULL;

        for (i = 0, Target = CCopasiVector< CType >::begin(); i < size; i++, Target++)
          {
            try
              {
                *Target = new CType("NoName", this);
              }
            catch (...)
              {
                *Target = NULL;
              }

            if (*Target == NULL)
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCopasiBase + 1, size * sizeof(CType));
            (*Target)->load(configbuffer);
          }
      }
    };

template < class CType > class CCopasiVectorN: public CCopasiVector < CType >
    {
    public:
      typedef typename std::vector< CType * >::value_type value_type;
      typedef typename std::vector< CType * >::iterator iterator;
      typedef typename std::vector< CType * >::const_iterator const_iterator;

      // Operations
    public:
      /**
       * Default constructor
       * @param const std::string & name (Default: "NoName")
       * @param const CCopasiContainer * pParent (Default: NULL)
       */
      CCopasiVectorN(const std::string & name = "NoName",
                     const CCopasiContainer * pParent = NULL):
          CCopasiVector< CType >(name, pParent,
                                 CCopasiObject::Container
                                 + CCopasiObject::Vector
                                 + CCopasiObject::NameVector)
      {}

      /**
       * Copy constructor
       * @param const CCopasiVectorN < CType > & src
       * @param const CCopasiContainer * pParent (Default: NULL)
       */
      CCopasiVectorN(const CCopasiVectorN < CType > & src,
                     const CCopasiContainer * pParent = NULL) :
          CCopasiVector < CType > (src, pParent)
      {}

      /**
       *  Destructor
       */
      virtual ~CCopasiVectorN() {}

      /**
       * Assignment operator.
       * @param const std::vector< CType * > & rhs
       * @return CCopasiVectorN< CType > & lhs
       */
      CCopasiVectorN< CType > & operator = (const std::vector< CType * > & rhs)
      {
        CCopasiVector< CType >::operator=(rhs);
        return *this;
      }

      /**
       * Add a copy of the object to the end of the vector.
       * @param const CType & src
       * @return bool success.
       */
      virtual bool add(const CType & src)
      {
        if (!isInsertAllowed(&src))
          {
            CCopasiMessage(CCopasiMessage::ERROR,
                           MCCopasiVector + 2, src.getObjectName().c_str());
            return false;
          }

        CType * Element;
        try
          {
            Element = new CType(src);
          }
        catch (...)
          {
            Element = NULL;
          }

        if (Element == NULL)
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCopasiBase + 1, sizeof(CType));

        push_back(Element);
        return CCopasiContainer::add(Element);
      }

      /**
       * Add an object to the end of the vector, if adobt is true the vector.
       * becomes the parent of the object.
       * @param CType * src
       * @param const bool & adopt (Default: false)
       * @return bool success
       */
      virtual bool add(CType * src, const bool & adopt = false)
      {
        if (!isInsertAllowed(src))
          {
            CCopasiMessage(CCopasiMessage::ERROR,
                           MCCopasiVector + 2, src->getObjectName().c_str());
            return false;
          }

        // This is not very efficient !!!
        // It results in a lot of resizing of the vector !!!
        push_back(src);
        return CCopasiContainer::add(src, adopt);
      }

      /**
       * Remove the object with the given name from the vector.
       * @param const std::string & name
       */
      virtual void remove(const std::string & name)
      {
        unsigned C_INT32 Index = getIndex(name);

        if (Index == C_INVALID_INDEX)
          {
            CCopasiMessage(CCopasiMessage::ERROR,
                           MCCopasiVector + 1, name.c_str());
            return;
          }

        CCopasiVector< CType >::remove(Index);
        return;
      }

      /**
       * Retrieve the indexed object.
       * @param const unsigned C_INT32 & index
       * @return value_type & object
       */
      value_type & operator[](const unsigned C_INT32 & index)
      {return CCopasiVector< CType >::operator[](index);}

      /**
       * Retrieve the indexed object.
       * @param const unsigned C_INT32 & index
       * @return const value_type & object
       */
      const value_type & operator[](const unsigned C_INT32 & index) const
        {return CCopasiVector< CType >::operator[](index);}

      /**
       * Retrieve the named object.
       * @param const std::string & name
       * @return value_type & object
       */
      value_type & operator[](const std::string & name)
      {
        unsigned C_INT32 Index = getIndex(name);

        if (Index == C_INVALID_INDEX)
          CCopasiMessage(CCopasiMessage::EXCEPTION,
                         MCCopasiVector + 1, name.c_str());

        return *(CCopasiVector< CType >::begin() + Index);
      }

      /**
       * Retrieve the named object.
       * @param const std::string & name
       * @return const value_type & object
       */
      const value_type & operator[](const std::string &name) const
        {
          unsigned C_INT32 Index = getIndex(name);

          if (Index == C_INVALID_INDEX)
            CCopasiMessage(CCopasiMessage::EXCEPTION,
                           MCCopasiVector + 1, name.c_str());

          return *(CCopasiVector< CType >::begin() + Index);
        }

      /**
       * Retrieve a pointer to the named object.
       * @param const std::string & name
       * @return const CCopasiObject * pObject
       */
      virtual const CCopasiObject * getObject(const CCopasiObjectName &name) const
        {
          C_INT32 Index = getIndex(name.getElementName(0));
          if (Index == -1) return NULL;

          CCopasiObject * pObject = *(CCopasiVector< CType >::begin() + Index);

          if (name.getObjectType() == pObject->getObjectType())
            return pObject; //exact match of type and name

          if (name.getObjectName() == "")
            return pObject; //cn contains no "="; type cannot be checked

#ifdef COPASI_DEBUG
          std::cout << "CCopasiVector::getObject: Vector contains object of right name but wrong type" << std::endl;
          std::cout << "  CN            " << name << std::endl;
          std::cout << "  CN.getName(0) " << name.getElementName(0) << std::endl;
          std::cout << "  Index         " << Index << std::endl;
          std::cout << "  CN.getObjName " << name.getObjectName() << std::endl;
          std::cout << "  CN.getObjType " << name.getObjectType() << std::endl << std::endl;
#endif // COPASI_DEBUG

          return NULL;
        }

      /**
       * Retrieve the index of the named object in the vector. If an object with the
       * given name is not found C_INVALID_INDEX is returned.
       * @param const std::string & name
       * @return unsigned C_INT32 index
       */
      virtual unsigned C_INT32 getIndex(const std::string &name) const
        {
          unsigned C_INT32 i, imax = CCopasiVector< CType >::size();
          const_iterator Target = CCopasiVector< CType >::begin();

          std::string Name = unQuote(name);
          for (i = 0; i < imax; i++, Target++)
            if (*Target &&
                ((*Target)->getObjectName() == name ||
                 (*Target)->getObjectName() == Name)) return i;

          return C_INVALID_INDEX;
        }

    private:
      /**
       * Check whether an insert of the given src into the vector is allowed
       * to avoid naming conflicts.
       * @param const CType * src
       * @return bool insertAllowed
       */
      virtual bool isInsertAllowed(const CType * src)
    {return (getIndex(src->getObjectName()) == C_INVALID_INDEX);}
    };

template < class CType > class CCopasiVectorNS: public CCopasiVectorN < CType >
    {
    public:
      typedef typename std::vector< CType * >::value_type value_type;
      typedef typename std::vector< CType * >::iterator iterator;
      typedef typename std::vector< CType * >::const_iterator const_iterator;

      // Operations
    public:
      /**
       * Default constructor
       * @param const std::string & name (Default: "NoName")
       * @param const CCopasiContainer * pParent (Default: NULL)
       */
      CCopasiVectorNS(const std::string & name = "NoName",
                      const CCopasiContainer * pParent = NULL):
          CCopasiVectorN< CType >(name, pParent)
      {}

      /**
       * Copy constructor
       * @param const CCopasiVectorNS < CType > & src
       * @param const CCopasiContainer * pParent (Default: NULL)
       */
      CCopasiVectorNS(const CCopasiVectorNS < CType > & src,
                      const CCopasiContainer * pParent = NULL) :
      CCopasiVectorN< CType >(src, pParent) {}

      /**
       *  Destructor
       */
      virtual ~CCopasiVectorNS() {}

      /**
       *  Loads an object with data coming from a CReadConfig object.
       *  (CReadConfig object reads an input stream)
       *  @param CReadConfig & configbuffer
       *  @param const unsigend C_INT32 & size
       */
      virtual void load(CReadConfig & configbuffer, unsigned C_INT32 size)
      {
        unsigned C_INT32 i;

        CCopasiVector< CType >::cleanup();
        CCopasiVector< CType >::resize(size, false);

        iterator Target = CCopasiVector< CType >::begin();
        for (i = 0; i < size; i++, Target++) *Target = NULL;

        for (i = 0, Target = CCopasiVector< CType >::begin(); i < size; i++, Target++)
          {
            try
              {
                *Target = new CType("NoName", this);
              }
            catch (...)
              {
                *Target = NULL;
              }

            if (*Target == NULL)
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCopasiBase + 1, size * sizeof(CType));
            (*Target)->load(configbuffer);
          }
      }
    };

template <class CType>
std::ostream &operator<<(std::ostream &os, const CCopasiVector<CType> & d)
{
  os << "   +++Vektor;  size: " << d.size() << std::endl;

  unsigned int i;

  for (i = 0; i < d.size(); i++)
    os << "   " << *(d[i]);

  if (d.size() == 0)
    os << "   empty" << std::endl;

  os << "   ---Vektor" << std::endl;

  return os;
}

#endif // COPASI_CCopasiVector
