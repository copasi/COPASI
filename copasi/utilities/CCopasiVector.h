/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CCopasiVector.h,v $
   $Revision: 1.60 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/03/09 15:46:25 $
   End CVS Header */

#ifndef COPASI_CCopasiVector
#define COPASI_CCopasiVector

#ifdef WIN32
# pragma warning (disable: 4786)
#endif  // WIN32

#include <vector>
#include <string>
#include <iostream>
#include <assert.h>

#include "CCopasiMessage.h"
#include "report/CCopasiObjectName.h"
#include "report/CCopasiContainer.h"
#include "utilities/CCopasiTask.h"

class CReadConfig;
//class CWriteConfig;

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
       *  Default constructor
       */
      CCopasiVector(const std::string & name = "NoName",
                    const CCopasiContainer * pParent = NULL,
                    const unsigned C_INT32 &
                    flag = CCopasiObject::Vector):
          std::vector< CType * >(),
          CCopasiContainer(name, pParent, "Vector", flag | CCopasiObject::Vector)
      {CONSTRUCTOR_TRACE;}

      /**
       *  Copy constructor
       */
      CCopasiVector(const CCopasiVector < CType > & src,
                    const CCopasiContainer * pParent = NULL):
          std::vector< CType * >(src),
          CCopasiContainer(src, pParent)
      {
        CONSTRUCTOR_TRACE;

        unsigned C_INT32 i, imax = ((std::vector< CType * > *)this)->size();
        iterator Target = begin();
        const_iterator Source = src.begin();

        for (i = 0; i < imax; i++, Target++, Source++)
          *Target = new CType(**Source, this);
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

        clear();
      }

      /**
       *
       */
      virtual bool add(const CType & src)
      {
        CType * Element = new CType(src);

        // This is not very efficient !!!
        // It results in a lot of resizing of the vector !!!
        push_back(Element);
        return CCopasiContainer::add(Element);
      }

      /**
       *
       */
      virtual void swap(unsigned C_INT32 indexFrom, unsigned C_INT32 indexTo)
      {
        assert(indexFrom < ((std::vector< CType * > *)this)->size());
        assert(indexTo < ((std::vector< CType * > *)this)->size());

        iterator from = begin() + indexFrom;
        iterator to = begin() + indexTo;

        value_type tmp = *from;
        *from = *to;
        *to = tmp;
      }

      /**
       *
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
       *  @param "const unsigned C_INT32 &" indecx
       */
      virtual void remove(const unsigned C_INT32 & index)
      {
        iterator Target = begin() + index;
        assert(index < ((std::vector< CType * > *)this)->size());

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

      virtual bool remove(CCopasiObject * pObject)
      {
        const unsigned C_INT32 & index = getIndex(pObject);
        iterator Target = begin() + index;
        assert(index < ((std::vector< CType * > *)this)->size());

        if (*Target)
          CCopasiContainer::remove(*Target);

        erase(Target, Target + 1);

        return true;
      }

      /**
       *
       */
      const value_type operator[](unsigned C_INT32 index) const
        {
          assert(index < ((std::vector< CType * > *)this)->size());
          return *(begin() + index);
        }

      /**
       *
       */
      value_type & operator[](unsigned C_INT32 index)
      {
        assert(index < ((std::vector< CType * > *)this)->size());
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
       *  @return "unsigned C_INT32" size
       */
      virtual unsigned C_INT32 size() const
      {return ((std::vector< CType * > *)this)->size();}

      /**
       *  Resizes the vector
       *  @param "unsigned C_INT32" size
       *  @param 
       */
      virtual void resize(unsigned C_INT32 size,
                          const bool & allocate = true)
      {
        unsigned C_INT32 OldSize = ((std::vector< CType * > *)this)->size();

        if (OldSize == size) return; // Nothing to do.

        if (OldSize < size)
          {
            ((std::vector< CType * > *)this)->resize(size);
            unsigned C_INT32 i;
            iterator Target = begin() + OldSize;

            if (allocate)
              for (i = OldSize; i < size; i++, Target++)
                *Target = new CType("NoName", this);
            else
              for (i = OldSize; i < size; i++, Target++)
                *Target = NULL;
          }
        else
          {
            iterator Target = begin() + size;
            iterator End = end();

            for (; Target != End; Target++)
              if (*Target)
                {
                  if ((*Target)->getObjectParent() == this)
                    {
                      //                      (*Target)->cleanup();
                      CCopasiContainer::remove(*Target);
                      (*Target)->setObjectParent(NULL);
                      delete *Target;
                    }
                  else
                    CCopasiContainer::remove(*Target);
                }

            ((std::vector< CType * > *)this)->resize(size);
          }
      }

      /**
       *
       */
      virtual unsigned C_INT32 getIndex(const CCopasiObject * pObject) const
        {
          unsigned C_INT32 i, imax = size();
          const_iterator Target = begin();

          for (i = 0; i < imax; i++, Target++)
            if (*Target == (void *) pObject) return i;

          return C_INVALID_INDEX;
        }
#ifdef WIN32
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
       *  Default constructor
       */
      CCopasiVectorS(const std::string & name = "NoName",
                     const CCopasiContainer * pParent = NULL):
      CCopasiVector< CType >(name, pParent){}

      /**
       *  Copy constructor
       */
      CCopasiVectorS(const CCopasiVectorS < CType > & src,
                     const CCopasiContainer * pParent = NULL) :
      CCopasiVector < CType > (src, pParent) {}

      /**
       *  Destructor
       */
      virtual ~CCopasiVectorS() {}

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
        ((std::vector< CType * > *)this)->resize(size);

        iterator Target = begin();
        for (i = 0; i < size; i++, Target++)*Target = NULL;

        for (i = 0, Target = begin(); i < size; i++, Target++)
          {
            *Target = new CType("NoName", this);
            (*Target)->load(configbuffer);
          }
      }

      /**
       *  Saves the contents of the object to a CWriteConfig object.
       *  (Which usually has a file attached but may also have socket)
       *  @param "CWriteConfig &" configbuffer reference to a CWriteConfig object.
       */
      /*virtual void save(CWriteConfig & configbuffer)
      {
        unsigned C_INT32 i, imax = size();
        iterator Target = begin();

        for (i = 0; i < imax; i++, Target++)
          (*Target)->save(configbuffer);
      }*/

      /**
       *
       */
      value_type & operator[](unsigned C_INT32 index)
      {return ((CCopasiVector <CType>*) this)->operator[](index);}

      /**
       *
       */
      const value_type operator[](unsigned C_INT32 index) const
        {return ((CCopasiVector <CType>*) this)->operator[](index);}
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
       *  Default constructor
       */
      CCopasiVectorN(const std::string & name = "NoName",
                     const CCopasiContainer * pParent = NULL):
          CCopasiVector< CType >(name, pParent,
                                 CCopasiObject::Container
                                 + CCopasiObject::Vector
                                 + CCopasiObject::NameVector)
      {}

      /**
       *  Copy constructor
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
       *
       */

      virtual bool add(const CType & src)
      {
        if (!isInsertAllowed(&src))
          CCopasiMessage(CCopasiMessage::ERROR,
                         MCCopasiVector + 2, src.getObjectName().c_str());

        CType * Element = new CType(src);

        push_back(Element);
        return CCopasiContainer::add(Element);
      }

      /**
       *
       */
      virtual bool add(CType * src, bool adopt = false)
      {
        if (!isInsertAllowed(src))
          CCopasiMessage(CCopasiMessage::ERROR,
                         MCCopasiVector + 2, src->getObjectName().c_str());

        // This is not very efficient !!!
        // It results in a lot of resizing of the vector !!!
        push_back(src);
        return CCopasiContainer::add(src, adopt);
      }

      /**
       *
       */
      virtual void remove(const std::string & name)
      {
        unsigned C_INT32 Index = getIndex(name);

        if ((signed) Index == -1)
          CCopasiMessage(CCopasiMessage::ERROR,
                         MCCopasiVector + 1, name.c_str());

        CCopasiVector< CType >::remove(Index);

        return;
      }

      /**
       *
       */
      value_type & operator[](unsigned C_INT32 index)
    {return ((CCopasiVector <CType>*) this)->operator[](index);}

      /**
       *
       */
      const value_type operator[](unsigned C_INT32 index) const
        {return ((CCopasiVector <CType>*) this)->operator[](index);}

      /**
       *
       */
      value_type & operator[](const std::string &name)
      {
        C_INT32 Index = getIndex(name);

        if (Index == -1)
          CCopasiMessage(CCopasiMessage::ERROR,
                         MCCopasiVector + 1, name.c_str());

        return *(begin() + Index);
      }

      /**
       *
       */
      const value_type operator[](const std::string &name) const
        {
          C_INT32 Index = getIndex(name);

          if (Index == -1)
            CCopasiMessage(CCopasiMessage::ERROR,
                           MCCopasiVector + 1, name.c_str());

          return *(begin() + Index);
        }

      /**
       *
       */
      virtual const CCopasiObject * getObject(const CCopasiObjectName &name) const
        {
          C_INT32 Index = getIndex(name.getElementName(0));
          if (Index == -1) return NULL;

          CCopasiObject * pObject = *(begin() + Index);

          if (name.getObjectType() == pObject->getObjectType())
            return pObject; //exact match of type and name

          if (name.getObjectName() == "")
            return pObject; //cn contains no "="; type cannot be checked

          std::cout << "CCopasiVector::getObject: Vector contains object of right name but wrong type" << std::endl;
          std::cout << "  CN            " << name << std::endl;
          std::cout << "  CN.getName(0) " << name.getElementName(0) << std::endl;
          std::cout << "  Index         " << Index << std::endl;
          std::cout << "  CN.getObjName " << name.getObjectName() << std::endl;
          std::cout << "  CN.getObjType " << name.getObjectType() << std::endl << std::endl;

          return NULL;
        }

      /**
       *
       */
      virtual unsigned C_INT32 getIndex(const std::string &name) const
        {
          unsigned C_INT32 i, imax = size();
          const_iterator Target = begin();

          for (i = 0; i < imax; i++, Target++)
            if (*Target && (*Target)->getObjectName() == name) return i;

          return C_INVALID_INDEX;
        }

    private:
      /**
       *
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
       *  Default constructor
       */
      CCopasiVectorNS(const std::string & name = "NoName",
                      const CCopasiContainer * pParent = NULL):
          CCopasiVectorN< CType >(name, pParent)
      {}

      /**
       *  Copy constructor
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
       *  @param "CReadConfig &" configbuffer reference to a CReadConfig object
       *  @param "const unsigend C_INT32 &" size
       */
      virtual void load(CReadConfig & configbuffer, unsigned C_INT32 size)
      {
        unsigned C_INT32 i;

        cleanup();
        ((std::vector< CType * >*)this)->resize(size);

        iterator Target = begin();
        for (i = 0; i < size; i++, Target++) *Target = NULL;

        for (i = 0, Target = begin(); i < size; i++, Target++)
          {
            *Target = new CType("NoName", this);
            (*Target)->load(configbuffer);
          }
      }

      /**
       *  Saves the contents of the object to a CWriteConfig object.
       *  (Which usually has a file attached but may also have socket)
       *  @param "CWriteConfig &" configbuffer reference to a CWriteConfig object.
       */
      /*virtual void save(CWriteConfig & configbuffer)
      {
        unsigned C_INT32 i, imax = size();
        iterator Target = begin();

        for (i = 0; i < imax; i++, Target++)
          (*Target)->save(configbuffer);
      }*/

      /**
       *
       */
      value_type & operator[](unsigned C_INT32 index)
      {return ((CCopasiVector <CType>*) this)->operator[](index);}

      /**
       *
       */
      const value_type operator[](unsigned C_INT32 index) const
        {return ((const CCopasiVector <CType>*) this)->operator[](index);}

      /**
       *
       */
      value_type & operator[](const std::string &name)
      {return ((CCopasiVectorN <CType>*) this)->operator[](name);}

      /**
       *
       */
      const value_type operator[](const std::string &name) const
        {return ((CCopasiVectorN <CType>*) this)->operator[](name);}

    private:

      /** @associates <{CCopasiVectorS< CType >}>
       * @directed*/
      /*# int lnkCCopasiVectorS; */
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
