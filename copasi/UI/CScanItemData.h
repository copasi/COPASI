// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CScanItemData.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/12/22 19:51:57 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CScanItemData
#define COPASI_CScanItemData

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
