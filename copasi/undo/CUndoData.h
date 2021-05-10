// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CUndoData
#define COPASI_CUndoData

#include <ctime>
#include <set>
#include <map>

#include "CData.h"

class CDataObject;
class CDataContainer;
class CDataModel;
class CUndoObjectInterface;

template < class CType > class CDataVector;

class CUndoData
{
public:
  enum struct Type
  {
    INSERT = 0,
    CHANGE,
    REMOVE,
    __SIZE
  };

  struct ChangeInfo
  {
    Type type;
    std::string objectType;
    std::string objectBefore;
    std::string objectAfter;
  };

  class CChangeSet : private std::vector< ChangeInfo >
  {
  public:
    typedef std::vector< ChangeInfo >::const_iterator const_iterator;

    CChangeSet();

    CChangeSet(const CChangeSet & src);

    ~CChangeSet();

    void add(const ChangeInfo & info);

    const_iterator begin() const;

    iterator begin();

    const_iterator end() const;

    iterator end();

    void clear();

    bool empty() const;

  private:
    void remove(const size_t & index);

    std::map< std::string, size_t > mMap;
  };

  static const CEnumAnnotation< std::string, Type > TypeName;

  static CUndoObjectInterface * getObject(const CDataModel & dataModel, const CData & data);

  friend std::ostream & operator << (std::ostream & os, const CUndoData & o);

  CUndoData();

  CUndoData(const Type & type, const CUndoObjectInterface * pObject, const size_t & authorId = C_INVALID_INDEX);

  CUndoData(const Type & type, const CData & data, const size_t & authorId = C_INVALID_INDEX);

  CUndoData(const CUndoData & src);

  ~CUndoData();

  const Type & getType() const;

  bool addProperty(const CData::Property & property, const CDataValue & value);

  bool addProperty(const CData::Property & property, const CDataValue & oldValue, const CDataValue & newValue);

  bool removeProperty(const CData::Property & property);

  bool isSetProperty(const CData::Property & property) const;

  bool appendData(const CData & data);

  bool appendData(const CData & oldData, const CData & newData);

  bool addPreProcessData(const CUndoData & dependentData);

  bool addPreProcessData(std::vector< CUndoData > & dependentData);

  bool addPostProcessData(const CUndoData & dependentData);

  bool addPostProcessData(std::vector< CUndoData > & dependentData);

  const CData & getOldData() const;

  const CData & getNewData() const;

  const std::vector< CUndoData > & getPreProcessData() const;

  std::vector< CUndoData > & getPreProcessData();

  const std::vector< CUndoData > & getPostProcessData() const;

  std::vector< CUndoData > & getPostProcessData();

  const std::set< std::string > & getChangedProperties() const;

  bool isChangedProperty(const CData::Property & property) const;

  bool apply(const CDataModel & dataModel, CChangeSet & changes, const bool & execute) const;

  bool undo(const CDataModel & dataModel, CChangeSet & changes, const bool & execute) const;

  bool addMetaDataProperty(const std::string & property, const CDataValue & value);

  bool appendMetaData(const CData & data);

  bool removeMetaDataProperty(const std::string & property);

  bool isSetMetaDataProperty(const std::string & property) const;

  const CDataValue & getMetaDataProperty(const std::string & property) const;

  const CData & getMetaData() const;

  const std::time_t & getTime() const;

  std::tm * getLocalTime() const;

  std::tm * getUTCTime() const;

  const size_t & getAuthorID() const;

  std::string getObjectDisplayName() const;

  std::string getObjectCN(const bool & apply) const;

  std::string getObjectType() const;

  bool operator < (const CUndoData & rhs) const;

  bool empty() const;

  void clear();

private:
  bool addProperty(const std::string & name, const CDataValue & value);

  bool addProperty(const std::string & name, const CDataValue & oldValue, const CDataValue & newValue);

  bool removeProperty(const std::string & name);

  bool isSetProperty(const std::string & name) const;

  bool isChangedProperty(const std::string & name) const;

  bool insert(const CDataModel & dataModel, const bool & apply, CChangeSet & changes, const bool & execute) const;
  bool remove(const CDataModel & dataModel, const bool & apply, CChangeSet & changes, const bool & execute) const;
  bool change(const CDataModel & dataModel, const bool & apply, CChangeSet & changes, const bool & execute) const;

  bool executePreProcessData(const CDataModel & dataModel, const bool & apply, CChangeSet & changes, const bool & execute) const;
  bool executePostProcessData(const CDataModel & dataModel, const bool & apply, CChangeSet & changes, const bool & execute) const;

  const CData & getData(const bool & apply) const;

  static CDataContainer * getParent(const CDataModel & dataModel, const CData & data);

  Type mType;

  CData mOldData;

  CData mNewData;

  std::vector< CUndoData > mPreProcessData;

  std::vector< CUndoData > mPostProcessData;

  std::time_t mTime;

  size_t mAuthorID;

  std::set< std::string > mChangedProperties;

  CData mMetaData;
};

#endif // COPASI_CUndoData
