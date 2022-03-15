// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CUndoObjectInterface
#define COPASI_CUndoObjectInterface

#include <crossguid/guid.hpp>

#include "copasi/undo/CUndoData.h"

class CUndoObjectInterface
{
public:
  /**
   * Default constructor
   */
  CUndoObjectInterface();

  /**
   * Copy constructor
   * @param const CUndoObjectInterface & src
   */
  CUndoObjectInterface(const CUndoObjectInterface & src);

  /**
   * Destructor
   */
  virtual ~CUndoObjectInterface();

  /**
   * Static template method to create an undo object based on the provided data
   * An undo object which support INSERT and REMOVE must specialize this method
   * @param const CData & data
   * @param CUndoObjectInterface * pParent
   * @return CUndoObjectInterface * pUndoObject
   */
  template < class CType > static CType * fromData(const CData & /* data */, CUndoObjectInterface * /* pParent */)
  {
    return NULL;
  }

  /**
   * Destruct the object
   */
  virtual void destruct() = 0;

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
  virtual bool applyData(const CData & data, CUndoData::CChangeSet & changes) = 0;

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

  /**
   * Retrieve the UUID
   * @return const xg::Guid & uuid
   */
  const xg::Guid & getUuid() const;

  /**
   * Set the  UUID. This method will fail once the UUID has been set for the object.
   * @param const xg::Guid & uuid
   * @return bool success
   */
  bool setUuid(const xg::Guid & uuid);

  /**
   * Set the  UUID. This method will fail once the UUID has been set for the object.
   * @param const std::string & uuid
   * @return bool success
   */
  bool setUuid(const std::string & uuid);

  /**
   * If the UUID has not been locked this method generates, sets, and locks the UUID.
   * Otherwise this method will fail
   * @return bool success
   */
  bool generateUuid();

private:
  xg::Guid * mpUuid;
  bool mUuidLocked;
};

// std::ostream & operator << (std::ostream & os, const uuid_t & o);
// std::istream & operator >> (std::istream & is, uuid_t & i);

#endif // COPASI_CUndoObjectInterface
