// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

/**
 * Class CDataObject
 *
 * This class is the base class for all global accessible objects in COPASI.
 *
 * Copyright Stefan Hoops 2002
 */

#ifndef COPASI_CDataObject
#define COPASI_CDataObject

#define NO_PARENT static_cast< CDataContainer * >((void *) 0)
#define INHERIT_PARENT static_cast< CDataContainer * >((void *) -1)

#include <string>
#include <list>

#include "copasi/core/CObjectInterface.h"
#include "copasi/core/CFlags.h"
#include "copasi/undo/CUndoObjectInterface.h"
#include "copasi/utilities/CValidity.h"

class CDataObject;
class CDataContainer;
class CModel;
class CDataModel;
class CUnit;

template <class CType> class CDataObjectReference;

//********************************************************************************

class CDataObject: public CObjectInterface, public CUndoObjectInterface
{
public:
  typedef std::set< const CDataObject * > DataObjectSet;

  enum Flag
  {
    Container,
    Vector,
    Matrix,
    NameVector,
    Reference,
    ValueBool,
    ValueInt,
    ValueInt64,
    ValueDbl,
    NonUniqueName,
    StaticString,
    ValueString,
    Separator,
    DisplayName,
    ModelEntity,
    Array,
    DataModel,
    Root,
    Gui,
    __SIZE
  };

protected:
  //Operations
  CDataObject();

  CDataObject(const std::string & name,
              const CDataContainer * pParent = NO_PARENT,
              const std::string & type = "CN",
              const CFlags< Flag > & flag = CFlags< Flag >::None);

public:
  /**
   * Static method to create a CDataObject based on the provided data
   * @param const CData & data
   * @return CDataObject * pDataObject
   */
  static CDataObject * fromData(const CData & data, CUndoObjectInterface * pParent);

  /**
   * Destruct the object
   */
  virtual void destruct() override;

  /**
   * Retrieve the data describing the object
   * @return CData data
   */
  virtual CData toData() const override;

  /**
   * Apply the provided data to the object
   * @param const CData & data
   * @return bool success
   */
  // API use by setData
  virtual bool applyData(const CData & data, CUndoData::CChangeSet & changes) override;

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
                              const CCore::Framework & framework = CCore::Framework::ParticleNumbers) const override;

  static void sanitizeObjectName(std::string & name);

  // API
  CDataObject(const CDataObject & src,
              const CDataContainer * pParent = NULL);

  virtual ~CDataObject();

  /**
   * Calculate the objects value.
   */
  virtual void calculateValue() override;

  /**
   * Retrieve the CN of the object
   * @return CCommonName
   */
  // API (for reporting and expressions)
  virtual CCommonName getCN() const override;

  /**
   * Retrieve a descendant object by its CN.
   * @param const CCommonName & cn
   * @return const CObjectInterface * pObject
   */
  virtual const CObjectInterface * getObject(const CCommonName & cn) const override;

  /**
   * Retrieve the prerequisites, i.e., the objects which need to be evaluated
   * before this.
   * @return const CObjectInterface::ObjectSet & prerequisites
   */
  virtual const CObjectInterface::ObjectSet & getPrerequisites() const override;

  /**
   * Check whether a given object is a prerequisite for a context.
   * @param const CObjectInterface * pObject
   * @param const CCore::SimulationContextFlag & context
   * @param const CObjectInterface::ObjectSet & changedObjects
   * @return bool isPrerequisiteForContext
   */
  virtual bool isPrerequisiteForContext(const CObjectInterface * pObject,
                                        const CCore::SimulationContextFlag & context,
                                        const CObjectInterface::ObjectSet & changedObjects) const override;

  /**
   * This is the output method for any object. The default implementation
   * provided with CDataObject uses the ostream operator<< of the object
   * to print the object.To override this default behavior one needs to
   * reimplement the virtual print function.
   * @param std::ostream * ostream
   */
  // API implement ostream
  virtual void print(std::ostream * ostream) const override;

  /**
   * Retrieve a pointer to the value of the object
   */
  virtual void * getValuePointer() const override;

  /**
   * Retrieve a pointer to the data object
   * @return const DATA_OBJECT * dataObject
   */
  virtual const CDataObject * getDataObject() const override;

  /**
   * Retrieve the display name of the object
   * @param bool regular (default: true)
   * @param bool richtext (default: false)
   * @return std::string objectDisplayName
   */
  // API
  virtual std::string getObjectDisplayName() const override;

  /**
   * Get the aggregation of any issues associated with this object
   * @return const CValidity & validity
   */
  // API
  virtual const CValidity & getValidity() const override;

  /**
   * This method is called whenever the validity of the object or a contained object changes.
   * @param const CValidity & changedValidity
   */
  void validityChanged(const CValidity & changedValidity) override;

  /**
   * This method is called whenever the validity of a contained object is removed.
   * @param const CValidity & changedValidity
   */
  void validityRemoved(const CValidity & changedValidity);

  /**
   * Set the name of the object.
   * Note: An attempt set the name to "" results in the name
   *       being set to "No Name".
   * @param const std::string & name
   * @return success
   */
  // API
  bool setObjectName(const std::string & name);

  // API
  const std::string & getObjectName() const;

  const std::string & getObjectType() const;

  virtual bool setObjectParent(const CDataContainer * pParent);

  CDataContainer * getObjectParent() const;

  void addReference(const CDataContainer * pReference);

  void removeReference(const CDataContainer * pReference);

  /**
   * Returns a pointer to the CDataModel the element belongs to.
   * If there is no instance of CDataModel in the ancestor tree, NULL
   * is returned.
   */
  CDataModel* getObjectDataModel() const;

  CDataContainer * getObjectAncestor(const std::string & type) const;

  bool prerequisitsContains(const DataObjectSet & objects) const;

  /**
   * Retrieve the units of the object.
   * @return std::string units
   */
  // API
  virtual const std::string getUnits() const;

  bool hasFlag(const Flag & flag) const;

  virtual const CDataObject * getValueObject() const;

  friend std::ostream &operator<<(std::ostream &os, const CDataObject & o);

  virtual const std::string & getKey() const;

  const CObjectInterface * getObjectFromCN(const CCommonName & cn) const;

  void addIssue(const CIssue & issue);

  void removeIssue(const CIssue & issue);

private:
  void refreshAggregateValidity();

  std::string mObjectName;

  std::string mObjectType;

  CDataContainer * mpObjectParent;

  mutable std::string mObjectDisplayName;
  mutable CDataObjectReference< std::string > * mpObjectDisplayName;
  mutable CDataObjectReference< std::string > * mpObjectName;

  CFlags< Flag > mObjectFlag;

  std::set< const CValidity * > mReferencedValidities;
  CValidity mAggregateValidity;

protected:
  std::set< CDataContainer * > mReferences;
  ObjectSet mPrerequisits;
};

#endif // COPASI_CDataObject
