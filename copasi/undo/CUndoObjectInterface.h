// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CUndoObjectInterface
#define COPASI_CUndoObjectInterface

#include "copasi/undo/CUndoData.h"

class CUndoObjectInterface
{
public:
  /**
   * Default constructor
   */
  CUndoObjectInterface();

  /**
   * Destructor
   */
  virtual ~CUndoObjectInterface();

  /**
   * Static template method to create an undo object based on the provided data
   * An undo object which support INSERT and REMOVE must specialize this method
   * @param const CData & data
   * @return CUndoObjectInterface * pUndoObject
   */
  template < class CType > static CType * fromData(const CData & data)
  {
    return NULL;
  }

  /**
   * Retrieve the data describing the object
   * @return CData data
   */
  virtual CData toData() const = 0;

  /**
   * Apply the provided data to the object
   * @param const CData & data
   * @return bool success
   */
  virtual bool applyData(const CData & data, CUndoData::ChangeSet & changes) = 0;

  /**
   * Create the undo data which represents the changes recording the
   * differences between the provided oldData and the current data.
   * @param CUndoData & undoData
   * @param const CUndoData::Type & type
   * @param const CData & oldData (default: empty data)
   * @param const CCore::Framework & framework (default: CCore::Framework::ParticleNumbers)
   * @return CUndoData undoData
   */
  virtual void createUndoData(CUndoData & undoData,
                              const CUndoData::Type & type,
                              const CData & oldData = CData(),
                              const CCore::Framework & framework = CCore::Framework::ParticleNumbers) const = 0;

  /**
   * Create and insert an undo object based on the given data.
   * This method needs to be re-implemented in container which support INSERT and REMOVE
   * @param const CData & data
   * @return CUndoObjectInterface * pUndoObject
   */
  virtual CUndoObjectInterface * insert(const CData & data);

  /**
   * Update the index of a contained object
   * This method needs to be re-implemented in container which care about the order of contained objects
   * @param const size_t & index
   * @param const CUndoObjectInterface * pUndoObject
   */
  virtual void updateIndex(const size_t & index, const CUndoObjectInterface * pUndoObject);
};

#endif // COPASI_CUndoObjectInterface
