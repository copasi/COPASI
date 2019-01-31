// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CUndoStack
#define COPASI_CUndoStack

#include <vector>
#include <map>

#include <copasi/undo/CUndoData.h>

class CDataModel;

class CUndoStack : private std::vector< CUndoData * >
{
private:
  CUndoStack();

public:
  typedef std::vector< CUndoData * >::iterator iterator;
  typedef std::vector< CUndoData * >::const_iterator const_iterator;

  CUndoStack(const CDataModel & dataModel);

  ~CUndoStack();

  void clear();
  size_t size() const;
  const CUndoData & operator [](const size_t & index) const;

  CUndoData::CChangeSet setCurrentIndex(const size_t & index, const bool & execute = true);
  size_t currentIndex() const;
  CUndoData::CChangeSet record(const CUndoData & data, const bool & execute);

  const_iterator begin() const;
  const_iterator end() const;

  /**
   * Retrieve the last executed data and indicated whether it was a redo
   * @return std::pair< const CUndoData &, bool > lastExecutedData
   */
  std::pair< const CUndoData *, bool > getLastExecution() const;

  bool canUndo() const;
  bool canRedo() const;

  CUndoData::CChangeSet undo();
  CUndoData::CChangeSet redo();

private:
  CDataModel * mpDataModel;

  /**
   * The index of the last applied data, i.e., itself and all
   * data with lower index can be undone.
   */
  size_t mCurrent;

  size_t mLastExecuted;
};

#endif // COPASI_CQUndoCommand
