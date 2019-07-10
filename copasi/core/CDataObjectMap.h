// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CDataObjectMap
#define COPASI_CDataObjectMap

#include <map>
#include <set>
#include <string>

class CDataObject;

class CDataObjectMap: private std::map< std::string, std::set< CDataObject * > >
{
public:
  class const_iterator;

  class iterator
  {
    friend class const_iterator;

  public:
    iterator();

    iterator(const CDataObjectMap & map,
             const bool & begin);

    iterator(const iterator & src);

    ~iterator();

    CDataObject * operator*() const;

    CDataObject * operator->() const;

    iterator & operator++();

    iterator operator++(int);

    bool operator != (const iterator & rhs) const;

  protected:
    const std::map< std::string, std::set< CDataObject * > > * mpMap;
    bool mNameEnd;
    std::map< std::string, std::set< CDataObject * > >::iterator mName;
    bool mObjectEnd;
    std::set< CDataObject * >::iterator mObject;
  };

  class const_iterator
  {
  public:
    const_iterator();

    const_iterator(const CDataObjectMap & map,
                   const bool & begin);

    const_iterator(const const_iterator & src);

    const_iterator(const iterator & src);

    ~const_iterator();

    CDataObject * operator*() const;

    CDataObject * operator->() const;

    const_iterator & operator++();

    const_iterator operator++(int);

    bool operator != (const const_iterator & rhs) const;

  protected:
    const std::map< std::string, std::set< CDataObject * > > * mpMap;
    bool mNameEnd;
    std::map< std::string, std::set< CDataObject * > >::iterator mItName;
    bool mObjectEnd;
    std::set< CDataObject * >::iterator mItpObject;
  };

  template < class CType > class type_iterator : protected CDataObjectMap::iterator
  {
  public:
    type_iterator() :
      CDataObjectMap::iterator()
    {}

    type_iterator(const type_iterator< CType > & src) :
      CDataObjectMap::iterator(src)
    {}

    type_iterator(const CDataObjectMap::iterator & src) :
      CDataObjectMap::iterator(src)
    {
      if (dynamic_cast< CType * >(CDataObjectMap::iterator::operator*()) == NULL)
        {
          operator++();
        }
    }

    CType * operator*() const
    {
      return dynamic_cast< CType * >(CDataObjectMap::iterator::operator*());
    }

    CType * operator->() const
    {
      return dynamic_cast< CType * >(CDataObjectMap::iterator::operator->());
    }

    type_iterator< CType > & operator++()
    {
      do
        {
          CDataObjectMap::iterator::operator++();
        }
      while (dynamic_cast< CType * >(CDataObjectMap::iterator::operator*()) == NULL &&
             (!mNameEnd || !mObjectEnd));

      return *this;
    }

    type_iterator operator++(int)
    {
      type_iterator< CType > Current(*this);

      operator++();

      return Current;
    }

    bool operator != (const type_iterator & rhs) const
    {
      return CDataObjectMap::iterator::operator !=(rhs);
    }
  };

  template < class CType > class const_type_iterator : protected CDataObjectMap::const_iterator
  {
  public:
    const_type_iterator() :
      CDataObjectMap::const_iterator()
    {}

    const_type_iterator(const type_iterator< CType > & src) :
      CDataObjectMap::const_iterator(src)
    {}

    const_type_iterator(const CDataObjectMap::const_iterator & src) :
      CDataObjectMap::const_iterator(src)
    {
      if (dynamic_cast< CType * >(CDataObjectMap::const_iterator::operator*()) == NULL)
        {
          operator++();
        }
    }

    CType * operator*() const
    {
      return dynamic_cast< CType * >(CDataObjectMap::const_iterator::operator*());
    }

    CType * operator->() const
    {
      return dynamic_cast< CType * >(CDataObjectMap::const_iterator::operator->());
    }

    const_type_iterator< CType > & operator++()
    {
      do
        {
          CDataObjectMap::const_iterator::operator++();
        }
      while ((!mNameEnd || !mObjectEnd) &&
             dynamic_cast< CType * >(CDataObjectMap::const_iterator::operator*()) == NULL);

      return *this;
    }

    const_type_iterator< CType > operator++(int)
    {
      const_type_iterator< CType > Current(*this);

      operator++();

      return Current;
    }

    bool operator != (const const_type_iterator & rhs) const
    {
      return CDataObjectMap::const_iterator::operator !=(rhs);
    }
  };

public:
  typedef std::map< std::string, std::set< CDataObject * > > data;
  typedef std::pair< std::set< CDataObject * >::const_iterator, std::set< CDataObject * >::const_iterator > range;

  CDataObjectMap();

  CDataObjectMap(const CDataObjectMap & src);

  ~CDataObjectMap();

  std::pair< std::set< CDataObject * >::iterator, bool > insert(CDataObject * pObject);
  bool erase(CDataObject * pObject);
  void clear();

  bool contains(CDataObject * pObject) const;
  void objectRenamed(CDataObject * pObject, const std::string & oldName);

  std::pair< std::set< CDataObject * >::const_iterator, std::set< CDataObject * >::const_iterator > equal_range(const std::string & name) const;

  iterator begin();
  iterator end();

  const_iterator begin() const;
  const_iterator end() const;
};

#endif // COPASI_CDataObjectMap
