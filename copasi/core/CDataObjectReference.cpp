// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#include <assert.h>

#include "CDataObjectReference.h"
#include "CDataContainer.h"

template<>
CDataObjectReference< double >::CDataObjectReference(const std::string & name,
    const CDataContainer * pParent,
    double & reference,
    const CFlags< Flag > & flag):
  CDataObject(name, pParent, "Reference",
              flag | CDataObject::Reference | CDataObject::NonUniqueName | CDataObject::ValueDbl),
  mpReference(&reference)
{
  assert(pParent != NULL);
}

template<>
CDataObjectReference< int >::CDataObjectReference(const std::string & name,
    const CDataContainer * pParent,
    int & reference,
    const CFlags< Flag > & flag):
  CDataObject(name, pParent, "Reference",
              flag | CDataObject::Reference | CDataObject::NonUniqueName | CDataObject::ValueInt),
  mpReference(&reference)
{
  assert(pParent != NULL);
}

template<>
CDataObjectReference< bool >::CDataObjectReference(const std::string & name,
    const CDataContainer * pParent,
    bool & reference,
    const CFlags< Flag > & flag):
  CDataObject(name, pParent, "Reference",
              flag | CDataObject::Reference | CDataObject::NonUniqueName | CDataObject::ValueBool),
  mpReference(&reference)
{
  assert(pParent != NULL);
}

template<>
CDataObjectReference< std::string >::CDataObjectReference(const std::string & name,
    const CDataContainer * pParent,
    std::string & reference,
    const CFlags< Flag > & flag):
  CDataObject(name, pParent, "String",
              flag | CDataObject::ValueString),
  mpReference(&reference)
{}
