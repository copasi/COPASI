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

class CReadConfig;
class CWriteConfig;

template < class CType > class CCopasiVector:
        protected std::vector< CType * >, protected CCopasiObject
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
                    const CCopasiContainer * pParent = &RootContainer,
                    const unsigned C_INT32 & flag = CCopasiObject::Vector):
          std::vector< CType * >(),
          CCopasiObject(name, pParent, "Vector", flag)
      {CONSTRUCTOR_TRACE;}

      /**
       *  Copy constructor
       */
      CCopasiVector(const CCopasiVector < CType > & src):
          std::vector< CType * >(src),
          CCopasiObject(src)
      {
        CONSTRUCTOR_TRACE;
        unsigned C_INT32 i, imax = ((std::vector< CType * > *)this)->size();
        iterator Target = begin();
        const_iterator Source = src.begin();

        for (i = 0; i < imax; i++, Target++, Source++)
          *Target = new CType(**Source);
      }

      /**
       *  Destructor
       */
    virtual ~CCopasiVector() {DESTRUCTOR_TRACE;}

      /**
       *  Cleanup
       */
      virtual void cleanup()
      {
        unsigned C_INT32 i, imax = ((std::vector< CType * >*)this)->size();
        iterator Target = begin();

        for (i = 0; i < imax; i++, Target++)
          {
            if (*Target)
              {
                (*Target)->cleanup();
                delete *Target;
                *Target = NULL;
              }
          }

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
      virtual void add
      (CType * src)
      {
        // This is not very efficient !!!
        // It results in a lot of resizing of the vector !!!
        push_back(src);
      }

      /**
       *  Removes the index-th element from the vector
       *  @param "const unsigned C_INT32 &" indecx
       */
      virtual void remove
      (const unsigned C_INT32 & index)
      {
        iterator Target = begin() + index;
        assert(index < ((std::vector< CType * > *)this)->size());

        if (*Target)
          {
            (*Target)->cleanup();
            delete *Target;
            *Target = NULL;
          }

        erase(Target, Target + 1);
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
      value_type operator[](unsigned C_INT32 index)
      {
        assert(index < ((std::vector< CType * > *)this)->size());
        return *(begin() + index);
      }

      /**
       *
       */
      virtual CCopasiObject * getObject(const CCopasiObjectName &name) const
      {return (CCopasiObject *) (*this)[name.getIndex()];}

      /**
       *  Retrieves the size of the vector
       *  @return "unsigned C_INT32" size
       */
      virtual unsigned C_INT32 size() const
      {return ((std::vector< CType * > *)this)->size();}

      /**
       *  Resizes the vector
       *  @param "unsigned C_INT32" size
       */
      virtual void resize(unsigned C_INT32 size)
      {
        unsigned C_INT32 OldSize = ((std::vector< CType * > *)this)->size();

        ((std::vector< CType * > *)this)->resize(size);
        unsigned C_INT32 i;
        iterator Target = begin() + OldSize;

        for (i = OldSize; i < size; i++, Target++)
          *Target = new CType;
      }

      friend std::ostream &operator<<(std::ostream &os, const CCopasiVector<CType> & d)
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
                     const CCopasiContainer * pParent = &RootContainer):
      CCopasiVector< CType >(name, pParent){}

      /**
       *  Copy constructor
       */
      CCopasiVectorS(const CCopasiVectorS < CType > & src) :
      CCopasiVector < CType > (src) {}

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

        for (i = 0; i < size; i++, Target++)
          {
            *Target = new CType;
            (*Target)->load(configbuffer);
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

        for (i = 0; i < imax; i++, Target++)
          (*Target)->save(configbuffer);
      }

      /**
       *
       */
      value_type operator[](unsigned C_INT32 index)
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
                     const CCopasiContainer * pParent = &RootContainer):
          CCopasiVector< CType >(name, pParent,
                                 CCopasiObject::Vector
                             + CCopasiObject::NameVector){}

      /**
       *  Copy constructor
       */
      CCopasiVectorN(const CCopasiVectorN < CType > & src) :
      CCopasiVector < CType > (src) {}

      /**
       *  Destructor
       */
      virtual ~CCopasiVectorN() {}

      /**
       *
       */

      virtual void add
      (const CType & src)
      {
        if (!isInsertAllowed(&src))
          CCopasiMessage(CCopasiMessage::ERROR,
                         MCCopasiVector + 2, src.getName().c_str());

        CType * Element = new CType(src);

        push_back(Element);
      }

      /**
       *
       */
      virtual void add
      (CType * src)
      {
        if (!isInsertAllowed(src))
          CCopasiMessage(CCopasiMessage::ERROR,
                         MCCopasiVector + 2, src->getName().c_str());

        // This is not very efficient !!!
        // It results in a lot of resizing of the vector !!!
        push_back(src);
      }

      /**
       *
       */
      virtual void remove
      (const std::string & name)
      {
        unsigned C_INT32 Index = getIndex(name);

        if ((signed) Index == -1)
          CCopasiMessage(CCopasiMessage::ERROR,
                         MCCopasiVector + 1, name.c_str());

        CCopasiVector< CType >::remove
        (Index);

        return;
      }

      /**
       *
       */
      value_type operator[](unsigned C_INT32 index)
    {return ((CCopasiVector <CType>*) this)->operator[](index);}

      /**
       *
       */
      const value_type operator[](unsigned C_INT32 index) const
      {return ((CCopasiVector <CType>*) this)->operator[](index);}

      /**
       *
       */
      value_type operator[](const std::string &name)
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
      virtual CCopasiObject * getObject(const CCopasiObjectName &name) const
        {return (CCopasiObject *) (*this)[name.getName()];}

        /**
         *
         */
        virtual unsigned C_INT32 getIndex(const std::string &name) const
        {
          unsigned C_INT32 i, imax = size();
          const_iterator Target = begin();

          for (i = 0; i < imax; i++, Target++)
          if ((*Target)->getName() == name) return i;

            return C_INVALID_INDEX;
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

private:
              /**
               *
               */
              virtual bool isInsertAllowed(const CType * src)
              {return (getIndex(src->getName()) == (unsigned C_INT32) - 1);}
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
                      const CCopasiContainer * pParent = &RootContainer):
      CCopasiVectorN< CType >(name, pParent) {}

      /**
       *  Copy constructor
       */
      CCopasiVectorNS(const CCopasiVectorNS < CType > & src) :
      CCopasiVectorN< CType >(src) {}

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

        for (i = 0; i < size; i++, Target++)
          {
            *Target = new CType;
            (*Target)->load(configbuffer);
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

        for (i = 0; i < imax; i++, Target++)
          (*Target)->save(configbuffer);
      }

      /**
       *
       */
      value_type operator[](unsigned C_INT32 index)
    {return ((CCopasiVector <CType>*) this)->operator[](index);}

      /**
       *
       */
      const value_type operator[](unsigned C_INT32 index) const
      {return ((const CCopasiVector <CType>*) this)->operator[](index);}

      /**
       *
       */
      value_type operator[](const std::string &name)
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

#endif // COPASI_CCopasiVector
