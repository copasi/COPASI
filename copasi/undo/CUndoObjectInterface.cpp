// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#include "copasi/undo/CUndoObjectInterface.h"

CUndoObjectInterface::CUndoObjectInterface()
{}

// virtual
CUndoObjectInterface::~CUndoObjectInterface()
{}

// virtual
CUndoObjectInterface * CUndoObjectInterface::insert(const CData & data)
{
  return NULL;
}

// virtual
void CUndoObjectInterface::updateIndex(const size_t & index, const CUndoObjectInterface * pUndoObject)
{}
