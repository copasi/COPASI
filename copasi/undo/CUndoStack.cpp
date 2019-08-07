// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

/*
 * CQUndoCommand.cpp
 *
 *  Created on: Jan 31, 2017
 *      Author: shoops
 */

#include "copasi/copasi.h"

#include "CUndoStack.h"
#include "CUndoData.h"

#include "copasi/CopasiDataModel/CDataModel.h"

CUndoStack::CUndoStack():
  std::vector< CUndoData * >(),
  mpDataModel(NULL),
  mCurrent(C_INVALID_INDEX),
  mLastExecuted(C_INVALID_INDEX)
{}

CUndoStack::CUndoStack(const CDataModel & dataModel):
  std::vector< CUndoData * >(),
  mpDataModel(const_cast< CDataModel * >(&dataModel)),
  mCurrent(C_INVALID_INDEX),
  mLastExecuted(C_INVALID_INDEX)
{}

CUndoStack::~CUndoStack()
{
  clear();
}

void CUndoStack::clear()
{
  iterator it = std::vector< CUndoData * >::begin();
  iterator end = std::vector< CUndoData * >::end();

  for (; it != end; ++it)
    {
      delete *it;
    }

  std::vector< CUndoData * >::clear();
  mCurrent = C_INVALID_INDEX;
  mLastExecuted = C_INVALID_INDEX;
}

const CUndoData & CUndoStack::operator [](const size_t & index) const
{
  return *std::vector< CUndoData * >::operator[](index);
}

CUndoData::CChangeSet CUndoStack::setCurrentIndex(const size_t & index, const bool & execute)
{
  CUndoData::CChangeSet Changes;

  // Nothing to do
  if (index == mCurrent ||
      (index >= size() &&
       index != C_INVALID_INDEX))
    {
      return Changes;
    }

  // If the index is smaller than the current or equal to C_INVALID_INDEX we must undo
  if ((index < mCurrent && mCurrent != C_INVALID_INDEX) ||
      index == C_INVALID_INDEX)
    {
      // The first data which can be undone is mCurrent
      std::vector< CUndoData * >::reverse_iterator it = std::vector< CUndoData * >::rbegin() + (size() - mCurrent - 1);
      std::vector< CUndoData * >::reverse_iterator end = (index != C_INVALID_INDEX) ? it + (mCurrent - index) : std::vector< CUndoData * >::rend();

      for (; it != end; ++it)
        {
          (*it)->undo(*mpDataModel, Changes, execute);
        }

      mLastExecuted = index + 1;
    }
  else if (index < size())
    {
      // The first data which can be applied is mCurrent + 1.
      std::vector< CUndoData * >::iterator it = std::vector< CUndoData * >::begin() + (mCurrent + 1);
      std::vector< CUndoData * >::iterator end = it + (index - mCurrent);

      for (; it != end; ++it)
        {
          (*it)->apply(*mpDataModel, Changes, execute);
        }

      mLastExecuted = index;
    }

  mCurrent = index;

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

std::pair< const CUndoData *, bool > CUndoStack::getLastExecution() const
{
  if (mLastExecuted >= size())
    return std::make_pair((CUndoData *) NULL, false);

  return std::make_pair(&operator[](mLastExecuted), mLastExecuted == mCurrent);
}

CUndoData::CChangeSet CUndoStack::record(const CUndoData & data, const bool & execute)
{
  // Remove all not applied data, i.e., all data which we can redo
  while (canRedo())
    {
      delete * std::vector< CUndoData * >::rbegin();
      std::vector< CUndoData * >::pop_back();
    }

  push_back(new CUndoData(data));

  assert(canRedo());

  // We can not use redo() since it implies execute = true!
  return setCurrentIndex(mCurrent + 1, execute);
}

bool CUndoStack::canUndo() const
{
  return mCurrent != C_INVALID_INDEX;
}

bool CUndoStack::canRedo() const
{
  return mCurrent + 1 < size();
}

CUndoData::CChangeSet CUndoStack::undo()
{
  if (canUndo())
    {
      return setCurrentIndex(mCurrent - 1, true);
    }

  return CUndoData::CChangeSet();
}

CUndoData::CChangeSet CUndoStack::redo()
{
  if (canRedo())
    {
      return setCurrentIndex(mCurrent + 1, true);
    }

  return CUndoData::CChangeSet();
}
