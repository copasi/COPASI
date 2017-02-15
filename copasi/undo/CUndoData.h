// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CUndoData
#define COPASI_CUndoData

#include <ctime>

#include "CData.h"

class CCopasiObject;
class CCopasiContainer;
class CCopasiDataModel;
class CMetab;

template < class CType > class CCopasiVector;

class CUndoData
{
private:
  CUndoData();

public:
  enum Type
  {
    INSERT = 0,
    REMOVE,
    CHANGE
  };

  CUndoData(const Type & type, const CCopasiObject * pObject, const size_t & authorId = C_INVALID_INDEX);

  CUndoData(const CUndoData & src);

  ~CUndoData();

  const Type & getType() const;

  bool addProperty(const CData::Property & property, const CDataValue & value);

  bool addProperty(const CData::Property & property, const CDataValue & oldValue, const CDataValue & newValue);

  bool addDependentData(const CUndoData & dependentData);

  void recordDependentParticleNumberChange(const double factor, const CCopasiVector< CMetab > & species);

  const CData & getOldData() const;

  const CData & getNewData() const;

  const std::vector< CUndoData > getDependentData() const;

  bool apply(const CCopasiDataModel & dataModel) const;

  bool undo(const CCopasiDataModel & dataModel) const;

  const std::time_t & getTime() const;

  std::tm * getLocalTime() const;

  std::tm * getUTCTime() const;

  const size_t getAuthorID() const;

private:
  bool addProperty(const std::string & name, const CDataValue & value);

  bool addProperty(const std::string & name, const CDataValue & oldValue, const CDataValue & newValue);

  bool insert(const CCopasiDataModel & dataModel, const bool & apply) const;
  bool remove(const CCopasiDataModel & dataModel, const bool & apply) const;
  bool change(const CCopasiDataModel & dataModel, const bool & apply) const;
  bool processDependentData(const CCopasiDataModel & dataModel, const bool & apply) const;

  const CData & getData(const bool & apply) const;

  static CCopasiContainer * getParent(const CCopasiDataModel & dataModel, const CData & data);
  static CCopasiObject * getObject(const CCopasiDataModel & dataModel, const CData & data);

  Type mType;

  CData mOldData;

  CData mNewData;

  std::vector< CUndoData > mDependentData;

  std::time_t mTime;

  size_t mAuthorID;
};

#endif // COPASI_CUndoData
