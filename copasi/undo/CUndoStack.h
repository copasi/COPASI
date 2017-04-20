// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CUndoStack
#define COPASI_CUndoStack

#include <vector>

class CUndoData;
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

  const CUndoData & operator [](const size_t & index) const;
  size_t setCurrent(const size_t & index);
  size_t size() const;
  size_t currentIndex() const;
  size_t record(const CUndoData & data);

  const_iterator begin() const;
  const_iterator end() const;
  const_iterator current() const;

private:
  CDataModel * mpDataModel;

  /**
   * The index of the last applied data, i.e., itself and all
   * data with lower index can be undone.
   */
  size_t mCurrent;
};

#endif // COPASI_CQUndoCommand
