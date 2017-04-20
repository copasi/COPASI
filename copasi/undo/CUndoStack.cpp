// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

/*
 * CQUndoCommand.cpp
 *
 *  Created on: Jan 31, 2017
 *      Author: shoops
 */

#include "copasi.h"

#include "CUndoStack.h"
#include "CUndoData.h"

#include "CopasiDataModel/CDataModel.h"

CUndoStack::CUndoStack():
  std::vector< CUndoData * >(),
  mpDataModel(NULL),
  mCurrent(C_INVALID_INDEX)
{}

CUndoStack::CUndoStack(const CDataModel & dataModel):
  std::vector< CUndoData * >(),
  mpDataModel(const_cast< CDataModel * >(&dataModel)),
  mCurrent(C_INVALID_INDEX)
{}

CUndoStack::~CUndoStack()
{
  iterator it = std::vector< CUndoData * >::begin();
  iterator end = std::vector< CUndoData * >::end();

  for (; it != end; ++it)
    {
      delete *it;
    }

  clear();
}

const CUndoData & CUndoStack::operator [](const size_t & index) const
{
  return *std::vector< CUndoData * >::operator[](index);
}

size_t CUndoStack::setCurrent(const size_t & index)
{
  // Nothing to do
  if (index == mCurrent)
    {
      return mCurrent;
    }

  // If the index is larger than the current index and valid
  // we need to re-apply data
  if (index > mCurrent &&
      index != C_INVALID_INDEX)
    {
      std::vector< CUndoData * >::iterator it = std::vector< CUndoData * >::begin() + mCurrent;
      std::vector< CUndoData * >::iterator end = std::vector< CUndoData * >::end();

      for (; it != end; ++it)
        {
          (*it)->apply(*mpDataModel);
        }
    }
  // We need to undo all data starting with mCurrent and ending just before index;
  else
    {
      // The reverse iterator need to point to mCurrent therefore the forward iterator need to point beyond.
      std::vector< CUndoData * >::reverse_iterator it(std::vector< CUndoData * >::begin() + (mCurrent + 1));
      // If index == C_INVALID_INDEX then index + 1 = 0, i.e., just what we want.
      std::vector< CUndoData * >::reverse_iterator end(std::vector< CUndoData * >::rend() - (index + 1));

      for (; it != end; ++it)
        {
          (*it)->undo(*mpDataModel);
        }
    }

  mCurrent = index;

  return mCurrent;
}

size_t CUndoStack::size() const
{
  return std::vector< CUndoData * >::size();
}

size_t CUndoStack::currentIndex() const
{
  return mCurrent;
}

CUndoStack::const_iterator CUndoStack::begin() const
{
  return std::vector< CUndoData * >::begin();
}

CUndoStack::const_iterator CUndoStack::end() const
{
  return std::vector< CUndoData * >::end();
}

size_t CUndoStack::record(const CUndoData & data)
{
  mCurrent++;

  // Check whether we need to remove not applied data, i.e., all data
  // after mCurrent
  if (mCurrent != size())
    {
      iterator Current = std::vector< CUndoData * >::begin() + mCurrent;

      iterator it = Current;
      iterator end = std::vector< CUndoData * >::end();

      for (; it != end; ++it)
        delete *it;

      erase(Current, std::vector< CUndoData * >::end());
    }

  push_back(new CUndoData(data));

  assert(mCurrent == size() - 1);

  return mCurrent;
}
