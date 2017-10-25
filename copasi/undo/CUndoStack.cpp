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

CUndoData::ChangeSet CUndoStack::getChangeSet(const size_t & index) const
{
  return const_cast< CUndoStack * >(this)->setCurrentIndex(false);
}

CUndoData::ChangeSet CUndoStack::setCurrentIndex(const size_t & index, const bool & execute)
{
  CUndoData::ChangeSet Changes;

  // Nothing to do
  if (index == mCurrent)
    {
      return Changes;
    }

  // If the index is smaller than the current or equal to C_INVALID_INDEX we must undo
  if ((index < mCurrent && mCurrent != C_INVALID_INDEX) ||
      index == C_INVALID_INDEX)
    {
      // The first data which can be undone is mCurrent
      std::vector< CUndoData * >::iterator it(std::vector< CUndoData * >::begin() + mCurrent);

      for (size_t i = mCurrent; i != index; --i, --it)
        {
          (*it)->undo(*mpDataModel, Changes, execute);
        }

      mCurrent = index;
    }
  else if (index < size())
    {
      // The first data which can be applied is mCurrent + 1.
      std::vector< CUndoData * >::iterator it = std::vector< CUndoData * >::begin() + mCurrent + 1;

      for (size_t i = mCurrent; i != index; ++i, ++it)
        (*it)->apply(*mpDataModel, Changes, execute);

      mCurrent = index;
    }

  return Changes;
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

CUndoData::ChangeSet CUndoStack::record(const CUndoData & data, const bool & execute)
{
  size_t Unapplied = mCurrent + 1;

  // Check whether we need to remove not applied data, i.e., all data
  // after mCurrent
  if (Unapplied != size())
    {
      iterator Current = std::vector< CUndoData * >::begin() + Unapplied;

      iterator it = Current;
      iterator end = std::vector< CUndoData * >::end();

      for (; it != end; ++it)
        delete *it;

      erase(Current, std::vector< CUndoData * >::end());
    }

  push_back(new CUndoData(data));

  assert(Unapplied == size() - 1);

  return setCurrentIndex(Unapplied, execute);
}
