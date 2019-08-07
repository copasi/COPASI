// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "COutputDefinitionVector.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/core/CRootContainer.h"

COutputDefinitionVector::COutputDefinitionVector(const std::string & name,
    const CDataContainer * pParent):
  CDataVectorN< CPlotSpecification >(name, pParent),
  mKey(CRootContainer::getKeyFactory()->add("COutputDefinitionVector", this))
{}

COutputDefinitionVector::~COutputDefinitionVector()
{
  cleanup();
}

void COutputDefinitionVector::cleanup()
{
  CRootContainer::getKeyFactory()->remove(mKey);
}

const std::string& COutputDefinitionVector::getKey() const
{
  return mKey;
}

CPlotSpecification* COutputDefinitionVector::createPlotSpec(const std::string & name,
    CPlotItem::Type type)
{
  size_t i;

  for (i = 0; i < size(); i++)
    if (operator[](i).getObjectName() == name)
      return NULL; // duplicate name

  CPlotSpecification* pNewPlotSpec = new CPlotSpecification(name, this, type);
  pNewPlotSpec->setObjectName(name);

  add(pNewPlotSpec, true);
  return pNewPlotSpec;
}

bool COutputDefinitionVector::removePlotSpec(const std::string & key)
{
  CPlotSpecification* pPl =
    dynamic_cast<CPlotSpecification*>(CRootContainer::getKeyFactory()->get(key));
  size_t index = this->CDataVector<CPlotSpecification>::getIndex(pPl);

  if (index == C_INVALID_INDEX)
    return false;

  this->CDataVector<CPlotSpecification>::remove(index);

  return true;
}
