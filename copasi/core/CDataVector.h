// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CDataVector
#define COPASI_CDataVector

#ifdef WIN32
# pragma warning (disable: 4786)
#endif  // WIN32

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <iterator>
#include <cstddef>

#include "copasi/utilities/CCopasiMessage.h"
#include "copasi/utilities/utility.h"

#include "copasi/core/CRegisteredCommonName.h"
#include "copasi/core/CDataContainer.h"

#include "copasi/undo/CData.h"
#undef min
#undef max
#undef ERROR

class CReadConfig;

template <class CType> class CDataVector;

template <class CType>
std::ostream &operator<<(std::ostream &os, const CDataVector<CType> & d);

template < class CType > class CDataVector:
  protected std::vector< CType * >, public CDataContainer
{
public:
  typedef CDataObjectMap::type_iterator< CType > name_iterator;
  typedef CDataObjectMap::const_type_iterator< CType > const_name_iterator;

public:
#ifndef SWIG
  class iterator: public std::vector< CType * >::iterator
  {
  public:
    iterator(): std::vector< CType * >::iterator() {}

    iterator(const iterator & src): std::vector< CType * >::iterator(src) {}

    iterator(const typename std::vector< CType * >::iterator & src): std::vector< CType * >::iterator(src) {}

    ~iterator() {}

    CType & operator*() const
    {
      return *std::vector< CType * >::iterator::operator*();
    }

    CType * operator->() const
    {
      return std::vector< CType * >::iterator::operator*();
    }

    operator CType * () const
    {
      return std::vector< CType * >::iterator::operator*();
    }

    iterator & operator=(CType * pType)
    {
      std::vector< CType * >::iterator::operator*() = pType;
      return *this;
    }

    iterator & operator++()
    {
      std::vector< CType * >::iterator::operator++();
      return *this;
    }

    iterator operator++(int)
    {
      return iterator(std::vector< CType * >::iterator::operator++());
    }

    iterator & operator--()
    {
      std::vector< CType * >::iterator::operator--();
      return *this;
    }

    iterator operator--(int)
    {
      return iterator(std::vector< CType * >::iterator::operator--());
    }

    iterator & operator+=(const typename std::vector< CType * >::iterator::difference_type & n)
    {
      std::vector< CType * >::iterator::operator+=(n);
      return *this;
    }

    iterator operator+(const typename std::vector< CType * >::iterator::difference_type & n) const
    {
      return iterator(std::vector< CType * >::iterator::operator+(n));
    }

    iterator & operator-=(const typename std::vector< CType * >::iterator::difference_type & n)
    {
      std::vector< CType * >::iterator::operator-=(n);
      return *this;
    }

    iterator operator-(const typename std::vector< CType * >::iterator::difference_type & n) const
    {
      return iterator(std::vector< CType * >::iterator::operator-(n));
    }
  };

  class const_iterator: public std::vector< CType * >::const_iterator
  {
  public:
    const_iterator(): std::vector< CType * >::const_iterator() {}

    const_iterator(const const_iterator & src): std::vector< CType * >::const_iterator(src) {}

    const_iterator(const iterator & src): std::vector< CType * >::const_iterator(src) {}

    const_iterator(const typename std::vector< CType * >::const_iterator & src): std::vector< CType * >::const_iterator(src) {}

    ~const_iterator() {}

    const CType & operator*() const
    {
      return *std::vector< CType * >::const_iterator::operator*();
    }

    const CType * operator->() const
    {
      return std::vector< CType * >::const_iterator::operator*();
    }

    operator const CType * () const
    {
      return std::vector< CType * >::const_iterator::operator*();
    }

    const_iterator & operator++()
    {
      std::vector< CType * >::const_iterator::operator++();
      return *this;
    }

    const_iterator operator++(int)
    {
      const_iterator Tmp(*this);
      operator++();
      return Tmp;
    }

    const_iterator & operator--()
    {
      std::vector< CType * >::const_iterator::operator--();
      return *this;
    }

    const_iterator operator--(int)
    {
      const_iterator Tmp(*this);
      operator--();
      return Tmp;
    }

    const_iterator & operator+=(const typename std::vector< CType * >::const_iterator::difference_type & n)
    {
      std::vector< CType * >::const_iterator::operator+=(n);
      return *this;
    }

    const_iterator operator+(const typename std::vector< CType * >::const_iterator::difference_type & n) const
    {
      return const_iterator(std::vector< CType * >::const_iterator::operator+(n));
    }

    const_iterator & operator-=(const typename std::vector< CType * >::const_iterator::difference_type & n)
    {
      std::vector< CType * >::const_iterator::operator-=(n);
      return *this;
    }

    const_iterator operator-(const typename std::vector< CType * >::const_iterator::difference_type & n) const
    {
      return const_iterator(std::vector< CType * >::const_iterator::operator-(n));
    }

    CType * constCast()
    {
      return const_cast< CType * >(std::vector< CType * >::const_iterator::operator*());
    }
  };

#endif // SWIG
  // Operations
  /**
   * Retrieve the data describing the object
   * @return CData data
   */
  virtual CData toData() const
  {
    CData Data;
    std::vector< CData > Content;

    const_iterator itContent = begin();
    const_iterator endContent = end();

    for (; itContent != endContent; ++itContent)
      {
        Content.push_back(itContent->toData());
      }

    if (!Content.empty())
      {
        Data.addProperty(CData::VECTOR_CONTENT, Content);
      }

    return Data;
  }

  /**
   * Apply the provided data to the object
   * @param const CData & data
   * @return bool success
   */
  virtual bool applyData(const CData & data, CUndoData::CChangeSet & changes)
  {
    bool success = true;
    const std::vector< CData > & Content = data.getProperty(CData::VECTOR_CONTENT).toDataVector();
    std::vector< CData >::const_iterator it = Content.begin();
    std::vector< CData >::const_iterator end = Content.end();

    for (; it != end; ++it)
      {
        size_t Index = it->getProperty(CData::OBJECT_INDEX).toSizeT();

        if (Index < size())
          {
            success &= operator[](Index).applyData(*it, changes);
          }
        else
          {
            CType * pNew = dynamic_cast< CType * >(insert(*it));

            if (pNew != NULL)
              {
                success &= pNew->applyData(*it, changes);
              }
            else
              {
                success = false;
              }
          }
      }

    return success;
  }

  /**
   * Create the undo data which represents the changes recording the
   * differences between the provided oldData and the current data.
   * @param CUndoData & undoData
   * @param const CUndoData::Type & type
   * @param const CData & oldData (default: empty data)
   * @param const CCore::Framework & framework (default: CCore::Framework::ParticleNumbers)
   * @return CUndoData undoData
   */
  virtual void createUndoData(CUndoData & undoData,
                              const CUndoData::Type & /* type */,
                              const CData & oldData = CData(),
                              const CCore::Framework & framework = CCore::Framework::ParticleNumbers) const
  {
    const std::vector< CData > & OldContent = oldData.getProperty(CData::VECTOR_CONTENT).toDataVector();
    std::vector< CData >::const_iterator itOld = OldContent.begin();
    std::vector< CData >::const_iterator endOld = OldContent.end();
    const_iterator itNew = begin();
    const_iterator endNew = end();

    for (; itOld != endOld && itNew != endNew; ++itOld, ++itNew)
      {
        CUndoData UndoData;
        itNew->createUndoData(UndoData, CUndoData::Type::CHANGE, *itOld, framework);

        if (!UndoData.empty())
          {
            undoData.appendData(UndoData.getOldData(), UndoData.getNewData());
          }
      }

    std::vector< CUndoData > PreProcessData;

    // Removal must be done in reverse order
    for (; itOld != endOld; ++itOld)
      {
        PreProcessData.push_back(CUndoData(CUndoData::Type::REMOVE, *itOld));
      }

    std::vector< CUndoData >::const_reverse_iterator itPre = PreProcessData.rbegin();
    std::vector< CUndoData >::const_reverse_iterator endPre = PreProcessData.rbegin();

    for (; itPre != endPre; ++itPre)
      {
        undoData.addPreProcessData(*itPre);
      }

    for (; itNew != endNew; ++itNew)
      {
        undoData.addPostProcessData(CUndoData(CUndoData::Type::INSERT, itNew->toData()));
      }
  }

  /**
   * Create and insert an undo object based on the given data.
   * This method needs to be re-implemented in container which support INSERT and REMOVE
   * @param const CData & data
   * @return CUndoObjectInterface * pUndoObject
   */
  virtual CUndoObjectInterface * insert(const CData & data)
  {
    CType * pNew = NULL;
    size_t Index = 0;

    if (data.isSetProperty(CData::OBJECT_POINTER))
      {
        // We have a reference and the object already exists;
        pNew = dynamic_cast< CType * >(reinterpret_cast< CObjectInterface * >(const_cast< void * >(data.getProperty(CData::OBJECT_POINTER).toVoidPointer())));
        Index = data.getProperty(CData::OBJECT_REFERENCE_INDEX).toSizeT();

        if (pNew != NULL)
          {
            // Prevent multiple inserts of the same object
            if (getIndex(pNew) ==  C_INVALID_INDEX)
              {
                std::vector< CType * >::insert(std::vector< CType * >::begin() + std::min(Index, std::vector< CType * >::size()), pNew);
              }
            else
              {
                updateIndex(Index, dynamic_cast< CDataObject * >(pNew));
              }

            CDataContainer::add(pNew, false);
          }
      }
    else
      {
        pNew = CType::fromData(data, this);
        Index = data.getProperty(CData::OBJECT_INDEX).toSizeT();

        if (pNew != NULL &&
            pNew->getObjectType() != data.getProperty(CData::OBJECT_TYPE).toString())
          {
            delete pNew;
            pNew = NULL;
          }

        if (pNew != NULL)
          {
            std::vector< CType * >::insert(std::vector< CType * >::begin() + std::min(Index, std::vector< CType * >::size()), pNew);
            CDataContainer::add(pNew, true);
          }
      }

    return dynamic_cast< CDataObject * >(pNew);
  }

  /**
   * Update the index of a contained object
   * This method needs to be re-implemented in container which care about the order of contained objects
   * @param const size_t & index
   * @param const CUndoObjectInterface * pUndoObject
   */
  virtual void updateIndex(const size_t & index, const CUndoObjectInterface * pUndoObject)
  {
    const CType * pObject = dynamic_cast< const CType * >(pUndoObject);

    size_t Index = getIndex(pObject);

    // We only update the index of container objects.
    if (Index == C_INVALID_INDEX ||
        Index == index)
      {
        return;
      }

    std::vector< CType * >::erase(std::vector< CType * >::begin() + Index);
    std::vector< CType * >::insert(std::vector< CType * >::begin() + std::min(index, std::vector< CType * >::size()), const_cast< CType * >(pObject));
  }

protected:
  CDataVector(const CDataVector < CType > & src);

public:
  /**
   * Default constructor
   * @param const const std::string & name (Default: "NoName")
   * @param const CDataContainer * pParent (Default: NULL)
   * @param const size_t & flag (Default: flag | CDataObject::Vector)
   */
  CDataVector(const std::string & name = "NoName",
              const CDataContainer * pParent = NO_PARENT,
              const CFlags< Flag > & flag = CFlags< Flag >::None):
    std::vector< CType * >(),
    CDataContainer(name, pParent, "Vector", flag | CDataObject::Vector)
  {CONSTRUCTOR_TRACE;}

  /**
   * Copy constructor
   * @param const CDataVector < CType > & src
   * @param const CDataContainer * pParent (Default: NULL)
   */
  CDataVector(const CDataVector < CType > & src,
              const CDataContainer * pParent):
    std::vector< CType * >(src),
    CDataContainer(src, pParent)
  {
    CONSTRUCTOR_TRACE;

    size_t i, imax = size();
    iterator Target = begin();
    const_iterator Source = src.begin();

    for (i = 0; i < imax; i++, Target++, Source++)
      {
        try
          {
            Target = new CType(*Source, this);
          }
        catch (...)
          {
            Target = NULL;
          }

        if (Target == NULL)
          CCopasiMessage ex(CCopasiMessage::EXCEPTION, MCopasiBase + 1, imax * sizeof(CType));
      }
  }

  /**
   *  Destructor
   */
  virtual ~CDataVector()
  {
    cleanup();
    DESTRUCTOR_TRACE;
  }

  /**
   * Assignment operator.
   * @param const CDataVector< CType > & rhs
   * @return CDataVector< CType > & lhs
   */
  CDataVector< CType > & operator = (const CDataVector< CType > & rhs)
  {
    if (this == &rhs)
      return *this;

    cleanup();

    const_iterator it = rhs.begin();
    const_iterator end = rhs.end();

    for (; it != end; ++it)
      add(*it);

    return *this;
  }

  /**
   * Assignment operator. The effect of this operator is that both vectors will
   * share the same objects. However, the parentship of the objects is not affected
   * This means that the assigned vector must be used with some care.
   * @param const std::vector< CType * > & rhs
   * @return CDataVector< CType > & lhs
   */
  CDataVector< CType > & operator = (const std::vector< CType * > & rhs)
  {
    cleanup();

    typename std::vector< CType * >::const_iterator it = rhs.begin();
    typename std::vector< CType * >::const_iterator end = rhs.end();

    for (; it != end; ++it)
      add(*it, false);

    return *this;
  }

#ifndef SWIG
  bool operator != (const CDataVector< CType > & rhs)
  {
    if (size() != rhs.size())
      {
        return true;
      }

    const_iterator itRhs = rhs.begin();
    const_iterator endRhs = rhs.end();
    const_iterator it = begin();

    for (; itRhs != endRhs; ++itRhs, ++it)
      if (*it != *itRhs)
        {
          return true;
        }

    return false;
  }
#endif

  /**
   * This creates a deep copy of the source, i.e., all objects are copied and
   * the parent of these copies is the current vector.
   * @param const CDataVector< CType > & source
   */
  void deepCopy(const CDataVector< CType > & source)
  {
    cleanup();
    resize(source.size());

    size_t i, imax = size();
    iterator Target = begin();
    const_iterator Source = source.begin();

    for (i = 0; i < imax; i++, Target++, Source++)
      {
        try
          {
            Target = new CType(*Source, this);
          }
        catch (...)
          {
            Target = NULL;
          }

        if (Target == NULL)
          CCopasiMessage ex(CCopasiMessage::EXCEPTION, MCopasiBase + 1, imax * sizeof(CType));
      }
  }

  iterator begin() {return iterator(std::vector< CType * >::begin());}

  const_iterator begin() const  {return const_iterator(std::vector< CType * >::begin());}

  iterator end()  {return iterator(std::vector< CType * >::end());}

  const_iterator end() const  {return const_iterator(std::vector< CType * >::end());}

  name_iterator beginName() {return mObjects.begin();}

  const_name_iterator beginName() const  {return mObjects.begin();}

  name_iterator endName()  {return mObjects.end();}

  const_name_iterator endName() const  {return mObjects.end();}

  /**
   *  Cleanup
   */
  virtual void cleanup()
  {
    typename std::vector< CType * >::iterator it = std::vector< CType * >::begin();
    typename std::vector< CType * >::iterator End = std::vector< CType * >::end();

    for (; it != End; it++)
      if (*it != NULL &&
          (*it)->getObjectParent() == this)
        {
          CDataContainer::remove(*it);
          (*it)->setObjectParent(NULL);
          delete (*it);
          *it = NULL;
        }

    CDataVector< CType >::clear();
  }

  /**
   * Add a copy of the object to the end of the vector.
   * @param const CType & src
   * @return bool success.
   */
  virtual bool add(const CType & src)
  {
    CType * pCopy = NULL;

    try
      {
        pCopy = new CType(src, this);
      }

    catch (...)
      {
        pCopy = NULL;
      }

    if (pCopy == NULL)
      CCopasiMessage ex(CCopasiMessage::EXCEPTION, MCopasiBase + 1, sizeof(CType));

    // This is not very efficient !!!
    // It results in a lot of resizing of the vector !!!
    std::vector< CType * >::push_back(pCopy);
    return CDataContainer::add(pCopy, true);
  }

  /**
   * Swap two objects in the vector.
   * @param const size_t & indexFrom
   * @param const size_t & indexTo
   */
  virtual void swap(const size_t & indexFrom, const size_t & indexTo)
  {
    size_t Size = size();

    if (!(indexFrom < Size))
      CCopasiMessage ex(CCopasiMessage::EXCEPTION, MCDataVector + 3, indexFrom, Size - 1);

    if (!(indexTo < Size))
      CCopasiMessage ex(CCopasiMessage::EXCEPTION, MCDataVector + 3, indexTo, Size - 1);

    typename std::vector< CType * >::iterator from = std::vector< CType * >::begin() + indexFrom;
    typename std::vector< CType * >::iterator to = std::vector< CType * >::begin() + indexTo;

    typename std::vector< CType * >::value_type tmp = *from;
    *from = *to;
    *to = tmp;
  }

  /**
   * Add an object to the end of the vector, if adopt is true the vector.
   * becomes the parent of the object.
   * @param CType * src
   * @param const bool & adopt (Default: false)
   * @return bool success
   */
  virtual bool add(CDataObject * pObject, const bool & adopt = true)
  {
    // This is not very efficient !!!
    // It results in a lot of resizing of the vector !!!

    CType * pNew = dynamic_cast< CType * >(pObject);

    if (pNew != NULL)
      {
        std::vector< CType * >::push_back(pNew);
      }

    return CDataContainer::add(pObject, adopt);
  }

  /**
   *  Removes the index-th element from the vector
   *  @param const size_t & index
   */
  virtual void remove(const size_t & index)
  {
    if (!(index < size()))
      return;

    typename std::vector< CType * >::iterator Target = std::vector< CType * >::begin() + index;

    if (*Target)
      {
        if ((*Target)->getObjectParent() == this)
          {
            //                (*Target)->cleanup();
            delete *Target;
          }
        else
          {
            CDataContainer::remove(*Target);
            std::vector< CType * >::erase(Target, Target + 1);
          }
      }
  }

  /**
   * Removes the pointer to the object, from the vector
   * @param CDataObject * pObject
   * @return bool success
   */
  virtual bool remove(CDataObject * pObject)
  {
    const size_t index = getIndex(pObject);

    bool success = true;

    if (index != C_INVALID_INDEX)
      {
        typename std::vector< CType * >::iterator Target = std::vector< CType * >::begin() + index;
        // Note: erase does not delete pointed to objects
        std::vector< CType * >::erase(Target, Target + 1);
      }
    else
      success = false;

    success &= CDataContainer::remove(pObject);

    return success;
  }

  /**
   * Retrieve the indexed object.
   * @param const size_t & index
   * @return const value_type & object
   */
  const CType & operator[](const size_t & index) const
  {
    if (!(index < size()))
      CCopasiMessage ex(CCopasiMessage::EXCEPTION, MCDataVector + 3, index, size() - 1);

    return **(std::vector< CType *>::begin() + index);
  }

  /**
   * Retrieve the indexed object.
   * @param const size_t & index
   * @return value_type & object
   */
  CType & operator[](const size_t & index)
  {
    if (!(index < size()))
      CCopasiMessage ex(CCopasiMessage::EXCEPTION, MCDataVector + 3, index, size() - 1);

    return **(std::vector< CType *>::begin() + index);
  }

  /**
   * Retrieve a the CDataObject with the given name.
   * @param const CCommonName &name
   * @return const CObjectInterface * object
   */
  virtual const CObjectInterface * getObject(const CCommonName &name) const
  {
    size_t Index = name.getElementIndex();

    if (Index < size())
      {
        CDataObject * pObject = *(std::vector< CType * >::begin() + Index);

        if (dynamic_cast< const CType *>(pObject) != NULL)
          return pObject->getObject(name.getRemainder());
      }

    return CDataContainer::getObject(name);
  }

  /**
   *  Retrieves the size of the vector
   *  @return size_t size
   */
  virtual size_t size() const
  {return std::vector< CType * >::size();}

  /**
   * @return a boolean indicating whether vector is empty
   */
  virtual bool empty() const
  {
    return std::vector< CType * >::empty();
  }

  /**
   *  Resizes the vector but does not create new member objects
   *  @param const size_t & newSize
   */
  virtual void resize(const size_t & newSize)
  {
    size_t OldSize = size();

    if (OldSize == newSize) return; // Nothing to do.

    if (OldSize < newSize)
      {
        std::vector< CType * >::resize(newSize);

        size_t i;
        typename std::vector< CType * >::iterator Target = std::vector< CType * >::begin() + OldSize;

        for (i = OldSize; i < newSize; i++, Target++)
          *Target = NULL;
      }
    else
      {
        typename std::vector< CType * >::iterator Target = std::vector< CType * >::begin() + newSize;
        typename std::vector< CType * >::iterator End = std::vector< CType * >::end();

        for (; Target != End; Target++)
          if (*Target)
            {
              if ((*Target)->getObjectParent() == this)
                {
                  CDataContainer::remove(*Target);
                  (*Target)->setObjectParent(NULL);
                  delete *Target;
                }
              else
                CDataContainer::remove(*Target);
            }

        std::vector< CType * >::resize(newSize);
      }
  }

  virtual void clear()
  {
    mValidity.clear();

    if (size() == 0) return; // Nothing to do.

    typename std::vector< CType * >::iterator Target = std::vector< CType * >::begin();
    typename std::vector< CType * >::iterator End = std::vector< CType * >::end();

    for (; Target != End; Target++)
      if (*Target)
        {
          if ((*Target)->getObjectParent() == this)
            {
              CDataContainer::remove(*Target);
              (*Target)->setObjectParent(NULL);
              delete *Target;
            }
          else
            CDataContainer::remove(*Target);
        }

    std::vector< CType * >::clear();
  }

  /**
   * Retrieve the index of the pointed to object in the vector. If the object
   * is not found C_INVALID_INDEX is returned.
   * @param const CDataObject * pObject
   * @return size_t index
   */
  virtual size_t getIndex(const CDataObject * pObject) const
  {
    size_t i, imax = size();
    typename std::vector< CType * >::const_iterator itTarget = std::vector< CType * >::begin();

    for (i = 0; i < imax; i++, itTarget++)
      {
        if (pObject == static_cast< const CDataObject * >(*itTarget))
          {
            return i;
          }
      }

    return CDataContainer::getIndex(pObject);
  }

  /**
   * ostream operator
   * @param std::ostream & os
   * @param const CDataVector<CType> & d
   * @return std::ostream & os
   */
#if defined SWIG
  friend std::ostream &operator << (std::ostream &os,
                                    const CDataVector<CType> & d);
#else
#if defined _MSC_VER && _MSC_VER < 1201 // 1200 Identifies Visual C++ 6.0
  friend std::ostream &operator << (std::ostream &os,
                                    const CDataVector<CType> & d);
#else
  friend std::ostream &operator << <>(std::ostream &os,
                                      const CDataVector<CType> & d);
#endif // WIN32
#endif // SWIG
};

template < class CType > class CDataVectorS: public CDataVector < CType >
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
   * @param const CDataContainer * pParent (Default: NULL)
   */
  CDataVectorS(const std::string & name = "NoName",
               const CDataContainer * pParent = NO_PARENT):
    CDataVector< CType >(name, pParent) {}

  /**
   * Copy constructor
   * @param const CDataVectorS < CType > & src
   * @param const CDataContainer * pParent (Default: NULL)
   */
  CDataVectorS(const CDataVectorS < CType > & src,
               const CDataContainer * pParent) :
    CDataVector < CType > (src, pParent) {}

  /**
   *  Destructor
   */
  virtual ~CDataVectorS() {}

  /**
   * Loads an object with data coming from a CReadConfig object.
   * (CReadConfig object reads an input stream)
   * @param CReadConfig & configbuffer
   * @param const size_t & size
   */
  virtual void load(CReadConfig & configbuffer, size_t size)
  {
    size_t i;

    CDataVector< CType >::cleanup();
    CDataVector< CType >::resize(size);

    typename std::vector< CType * >::iterator Target = std::vector< CType * >::begin();

    for (i = 0; i < size; i++, Target++)*Target = NULL;

    for (i = 0, Target = std::vector< CType * >::begin(); i < size; i++, Target++)
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
          CCopasiMessage ex(CCopasiMessage::EXCEPTION, MCopasiBase + 1, size * sizeof(CType));

        (*Target)->load(configbuffer);
      }
  }
};

template < class CType > class CDataVectorN: public CDataVector < CType >
{
  // Operations
public:
  typedef CDataObjectMap::type_iterator< CType > name_iterator;
  typedef CDataObjectMap::const_type_iterator< CType > const_name_iterator;

  /**
   * Retrieve the data describing the object
   * @return CData data
   */
  virtual CData toData() const
  {
    CData Data;
    std::vector< CData > Content;

    const_name_iterator itContent = CDataVector< CType >::beginName();
    const_name_iterator endContent = CDataVector< CType >::endName();

    for (; itContent != endContent; ++itContent)
      {
        Content.push_back(itContent->toData());
      }

    Data.addProperty(CData::VECTOR_CONTENT, Content);

    return Data;
  }

  /**
   * Apply the provided data to the object
   * @param const CData & data
   * @return bool success
   */
  virtual bool applyData(const CData & data, CUndoData::CChangeSet & changes)
  {
    bool success = true;
    bool inserted = false;
    const std::vector< CData > & Content = data.getProperty(CData::VECTOR_CONTENT).toDataVector();
    std::vector< CData >::const_iterator it = Content.begin();
    std::vector< CData >::const_iterator end = Content.end();

    for (; it != end; ++it)
      {
        CType * pObject = const_cast< CType * >(dynamic_cast< const CType *>(getObject("[" + CCommonName::escape(it->getProperty(CData::OBJECT_NAME).toString()) + "]")));

        if (pObject == NULL)
          {
            pObject = dynamic_cast< CType * >(CDataVector< CType >::insert(*it));
            inserted &= (pObject != NULL);
          }

        if (pObject != NULL)
          {
            success &= pObject->applyData(*it, changes);
          }
        else
          {
            success = false;
          }
      }

    // If we inserted into the vector it is possible that the order is no longer correct
    if (inserted)
      {
        it = Content.begin();

        for (; it != end; ++it)
          {
            size_t Index = getIndex(it->getProperty(CData::OBJECT_NAME).toString());

            if (Index < CDataVector< CType >::size())
              {
                success &= operator[](Index).applyData(*it, changes);
              }
            else
              {
                success = false;
              }
          }
      }

    return success;
  }

  /**
   * Create the undo data which represents the changes recording the
   * differences between the provided oldData and the current data.
   * @param CUndoData & undoData
   * @param const CUndoData::Type & type
   * @param const CData & oldData (default: empty data)
   * @param const CCore::Framework & framework (default: CCore::Framework::ParticleNumbers)
   * @return CUndoData undoData
   */
  virtual void createUndoData(CUndoData & undoData,
                              const CUndoData::Type & /* type */,
                              const CData & oldData = CData(),
                              const CCore::Framework & framework = CCore::Framework::ParticleNumbers) const
  {
    const std::vector< CData > & OldContent = oldData.getProperty(CData::VECTOR_CONTENT).toDataVector();
    std::vector< CData >::const_iterator itOld = OldContent.begin();
    std::vector< CData >::const_iterator endOld = OldContent.end();
    const_name_iterator itNew = CDataVector< CType >::beginName();
    const_name_iterator endNew = CDataVector< CType >::endName();

    std::map< size_t, CData > Deleted;
    std::map< size_t, CData > Inserted;
    std::map< size_t, CData > OldData;
    std::map< size_t, CData > NewData;

    while (itOld != endOld &&
           itNew != endNew)
      {
        const std::string & OldName = itOld->getProperty(CData::OBJECT_NAME).toString();
        const std::string & NewName = itNew->getObjectName();

        if (OldName < NewName)
          {
            Deleted[itOld->getProperty(CData::OBJECT_INDEX).toSizeT()] = *itOld;
            ++itOld;
          }
        else if (OldName > NewName)
          {
            Inserted[CDataVector< CType >::getIndex(*itNew)] = itNew->toData();
            ++itNew;
          }
        else
          {
            CUndoData UndoData;
            itNew->createUndoData(UndoData, CUndoData::Type::CHANGE, *itOld, framework);

            if (!UndoData.empty())
              {
                OldData[itOld->getProperty(CData::OBJECT_INDEX).toSizeT()] = UndoData.getOldData();
                NewData[CDataVector< CType >::getIndex(*itNew)] = UndoData.getNewData();
              }

            ++itOld;
            ++itNew;
          }
      }

    for (; itOld != endOld; ++itOld)
      {
        Deleted[itOld->getProperty(CData::OBJECT_INDEX).toSizeT()] = *itOld;
      }

    for (; itNew != endNew; ++itNew)
      {
        Inserted[CDataVector< CType >::getIndex(*itNew)] = itNew->toData();
      }

    // Removal must be done in reverse order
    std::map< size_t, CData >::reverse_iterator itReverse = Deleted.rbegin();
    std::map< size_t, CData >::reverse_iterator endReverse = Deleted.rend();

    for (; itReverse != endReverse; ++itReverse)
      {
        undoData.addPreProcessData(CUndoData(CUndoData::Type::REMOVE, itReverse->second));
      }

    std::map< size_t, CData >::iterator it = Inserted.begin();
    std::map< size_t, CData >::iterator end = Inserted.end();

    for (; it != end; ++it)
      {
        undoData.addPostProcessData(CUndoData(CUndoData::Type::INSERT, it->second));
      }

    std::vector< CData > OldContentData;
    it = OldData.begin();
    end = OldData.end();

    for (size_t Index = 0; it != end; ++it, ++Index)
      {
        it->second.addProperty(CData::OBJECT_INDEX, Index);
        OldContentData.push_back(it->second);
      }

    std::vector< CData > NewContentData;
    it = NewData.begin();
    end = NewData.end();

    for (size_t Index = 0; it != end; ++it, ++Index)
      {
        it->second.addProperty(CData::OBJECT_INDEX, Index);
        NewContentData.push_back(it->second);
      }

    undoData.addProperty(CData::VECTOR_CONTENT, OldContentData, NewContentData);
  }

  /**
   * Default constructor
   * @param const std::string & name (Default: "NoName")
   * @param const CDataContainer * pParent (Default: NULL)
   */
  CDataVectorN(const std::string & name = "NoName",
               const CDataContainer * pParent = NO_PARENT):
    CDataVector< CType >(name, pParent, CDataObject::NameVector)
  {}

  /**
   * Copy constructor
   * @param const CDataVectorN < CType > & src
   * @param const CDataContainer * pParent (Default: NULL)
   */
  CDataVectorN(const CDataVectorN < CType > & src,
               const CDataContainer * pParent) :
    CDataVector < CType > (src, pParent)
  {}

  /**
   *  Destructor
   */
  virtual ~CDataVectorN() {}

  /**
   * Assignment operator.
   * @param const std::vector< CType * > & rhs
   * @return CDataVectorN< CType > & lhs
   */
  CDataVectorN< CType > & operator = (const std::vector< CType * > & rhs)
  {
    CDataVector< CType >::operator=(rhs);
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
        CCopasiMessage ex(CCopasiMessage::ERROR,
                          MCDataVector + 2, src.getObjectName().c_str());
        return false;
      }

    CType * Element;

    try
      {
        Element = new CType(src, this);
      }
    catch (...)
      {
        Element = NULL;
      }

    if (Element == NULL)
      CCopasiMessage ex(CCopasiMessage::EXCEPTION, MCopasiBase + 1, sizeof(CType));

    std::vector< CType * >::push_back(Element);
    return CDataContainer::add(Element, true);
  }

  /**
   * Add an object to the end of the vector, if adobt is true the vector.
   * becomes the parent of the object.
   * @param CType * src
   * @param const bool & adopt (Default: false)
   * @return bool success
   */
  virtual bool add(CDataObject * pObject, const bool & adopt = true)
  {
    // This is not very efficient !!!
    // It results in a lot of resizing of the vector !!!

    CType * pNew = dynamic_cast< CType * >(pObject);

    if (pNew != NULL)
      {
        if (!isInsertAllowed(pNew))
          {
            CCopasiMessage ex(CCopasiMessage::ERROR,
                              MCDataVector + 2, pNew->getObjectName().c_str());
            return false;
          }

        std::vector< CType * >::push_back(pNew);
      }

    return CDataContainer::add(pObject, adopt);
  }

  /**
   * Remove the object with the given name from the vector.
   * @param const std::string & name
   */
  virtual void remove(const std::string & name)
  {
    size_t Index = getIndex(name);

    if (Index == C_INVALID_INDEX)
      {
        CCopasiMessage ex(CCopasiMessage::ERROR,
                          MCDataVector + 1, name.c_str());
        return;
      }

    CDataVector< CType >::remove(Index);
    return;
  }

  /**
   * Retrieve the indexed object.
   * @param const size_t & index
   * @return value_type & object
   */
  CType & operator[](const size_t & index)
  {return CDataVector< CType >::operator[](index);}

  /**
   * Retrieve the indexed object.
   * @param const size_t & index
   * @return const value_type & object
   */
  const CType & operator[](const size_t & index) const
  {return CDataVector< CType >::operator[](index);}

  /**
   * Retrieve the named object.
   * @param const std::string & name
   * @return value_type & object
   */
  CType & operator[](const std::string & name)
  {
    CDataContainer::objectMap::range Range = CDataVector< CType >::getObjects().equal_range(name);

    CType * pType = NULL;

    for (; Range.first != Range.second && pType == NULL; ++Range.first)
      {
        pType = dynamic_cast< CType * >(*Range.first);
      }

    if (pType == NULL)
      {
        CCopasiMessage ex(CCopasiMessage::EXCEPTION,
                          MCDataVector + 1, name.c_str());
      }

    return *pType;
  }

  /**
   * Retrieve the named object.
   * @param const std::string & name
   * @return const value_type & object
   */
  const CType & operator[](const std::string &name) const
  {
    CDataContainer::objectMap::range Range = CDataVector< CType >::getObjects().equal_range(name);

    CType * pType = NULL;

    for (; Range.first != Range.second && pType == NULL; ++Range.first)
      {
        pType = dynamic_cast< CType * >(*Range.first);
      }

    if (pType == NULL)
      {
        CCopasiMessage ex(CCopasiMessage::EXCEPTION,
                          MCDataVector + 1, name.c_str());
      }

    return *pType;
  }

  /**
   * Retrieve a pointer to the named object.
   * @param const std::string & name
   * @return const CObjectInterface * pObject
   */
  virtual const CObjectInterface * getObject(const CCommonName &name) const
  {
    CCommonName ElementName = name.getElementName(0);

    if (!ElementName.empty())
      {
        CDataContainer::objectMap::range Range = CDataVector< CType >::getObjects().equal_range(ElementName);

        for (; Range.first != Range.second; ++Range.first)
          {
            if (dynamic_cast< CType * >(*Range.first) != NULL)
              return (*Range.first)->getObject(name.getRemainder());
          }
      }

    return CDataVector< CType >::getObject(name);
  }

  /**
   * Retrieve the index of the named object in the vector. If an object with the
   * given name is not found C_INVALID_INDEX is returned.
   * @param const std::string & name
   * @return size_t index
   */
  virtual size_t getIndex(const std::string &name) const
  {
    std::string Sanitized = name;
    CDataObject::sanitizeObjectName(Sanitized);
    std::string Unquoted = unQuote(Sanitized);

    size_t i, imax = CDataVector< CType >::size();
    typename std::vector< CType * >::const_iterator Target = std::vector< CType * >::begin();

    for (i = 0; i < imax; i++, ++Target)
      {
        if (*Target &&
            ((*Target)->getObjectName() == Sanitized ||
             (*Target)->getObjectName() == Unquoted))
          return i;
      }

    return C_INVALID_INDEX;
  }

  void createUniqueName(std::string & name) const
  {
    std::string Name = name;
    CDataObject::sanitizeObjectName(Name);
    size_t Index = 0;

    while (getIndex(name) != C_INVALID_INDEX)
      {
        Index++;
        std::ostringstream tmp;
        tmp << Name << "_" << Index;
        name = tmp.str();
      }
  }

private:
  /**
   * Check whether an insert of the given src into the vector is allowed
   * to avoid naming conflicts.
   * @param const CType * src
   * @return bool insertAllowed
   */
  virtual bool isInsertAllowed(const CType * src)
  {
    bool isInserAllowed = true;
    CDataContainer::objectMap::range Range = CDataVector< CType >::getObjects().equal_range(src->getObjectName());

    for (; Range.first != Range.second && isInserAllowed; ++Range.first)
      {
        isInserAllowed = (dynamic_cast< CType * >(*Range.first) == NULL ||
                          (dynamic_cast< CType * >(*Range.first) == src &&
                           getIndex(src->getObjectName()) == C_INVALID_INDEX));
      }

    return isInserAllowed;
  }
};

template < class CType > class CDataVectorNS: public CDataVectorN < CType >
{
  // Operations
public:
  /**
   * Default constructor
   * @param const std::string & name (Default: "NoName")
   * @param const CDataContainer * pParent (Default: NULL)
   */
  CDataVectorNS(const std::string & name = "NoName",
                const CDataContainer * pParent = NO_PARENT):
    CDataVectorN< CType >(name, pParent)
  {}

  /**
   * Copy constructor
   * @param const CDataVectorNS < CType > & src
   * @param const CDataContainer * pParent (Default: NULL)
   */
  CDataVectorNS(const CDataVectorNS < CType > & src,
                const CDataContainer * pParent) :
    CDataVectorN< CType >(src, pParent) {}

  /**
   *  Destructor
   */
  virtual ~CDataVectorNS() {}

  /**
   *  Loads an object with data coming from a CReadConfig object.
   *  (CReadConfig object reads an input stream)
   *  @param CReadConfig & configbuffer
   *  @param const size_t & size
   */
  virtual void load(CReadConfig & configbuffer, size_t size)
  {
    size_t i = 0;

    CDataVector< CType >::cleanup();
    CDataVector< CType >::resize(size);

    typename std::vector< CType * >::iterator Target = std::vector< CType * >::begin();

    for (i = 0; i < size; i++, Target++) *Target = NULL;

    for (i = 0, Target = std::vector< CType * >::begin(); i < size; i++, Target++)
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
          CCopasiMessage ex(CCopasiMessage::EXCEPTION, MCopasiBase + 1, size * sizeof(CType));

        (*Target)->load(configbuffer);
      }
  }
};

template <class CType>
std::ostream &operator<<(std::ostream &os, const CDataVector<CType> & d)
{
  os << "   +++Vektor;  size: " << d.size() << std::endl;

  unsigned int i;

  for (i = 0; i < d.size(); i++)
    os << "   " << d[i];

  if (d.size() == 0)
    os << "   empty" << std::endl;

  os << "   ---Vektor" << std::endl;

  return os;
}

#endif // COPASI_CDataVector
