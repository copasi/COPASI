// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CScanItemData
#define COPASI_CScanItemData

#include "copasi/copasi.h"
#include "copasi/scan/CScanProblem.h"

class CCopasiParameterGroup;

class CScanItemData
{
private:
  CScanItemData();

protected:
  CScanItemData(const CScanProblem::Type & type);

public:
  CScanItemData(const CScanItemData & src);

  virtual ~CScanItemData();

  virtual void load(const CCopasiParameterGroup * pItem) = 0;

  virtual bool save(CCopasiParameterGroup * pItem) const = 0;

  const CScanProblem::Type & getType() const;

protected:
  CScanProblem::Type mType;
  CCopasiParameterGroup * mpData;
};

#endif // COPASI_CScanItemData
