// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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

#include "copasi/utilities/CValidity.h"

class CDataObject;
class CDataContainer;
class CModel;
class CDataModel;
class CUnit;
class CData;
class CUndoData;

template <class CType> class CDataObjectReference;

//********************************************************************************

class CDataObject: public CObjectInterface
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

  CDataObject(const CDataObject & src);

public:
  /**
   * Static method to create a CDataObject based on the provided data
   * @param const CData & data
   * @return CDataObject * pDataObject
   */
  static CDataObject * fromData(const CData & data);

  /**
   * Retrieve the data describing the object
   * @return CData data
   */
  virtual CData toData() const;

  /**
   * Apply the provided data to the object
   * @param const CData & data
   * @return bool success
   */
  virtual bool applyData(const CData & data);

  /**
   * Append all required dependent undo data
   * @param CUndoData & undoData
   * @param const CCore::Framework & framework
   */
  virtual void appendDependentData(CUndoData & undoData, const CCore::Framework & framework);

  static void sanitizeObjectName(std::string & name);

  CDataObject(const CDataObject & src,
              const CDataContainer * pParent);

  virtual ~CDataObject();

  /**
   * Calculate the objects value.
   */
  virtual void calculateValue();

  /**
   * Retrieve the CN of the object
   * @return CCommonName
   */
  virtual CCommonName getCN() const;

  /**
   * Retrieve a descendant object by its CN.
   * @param const CCommonName & cn
   * @return const CObjectInterface * pObject
   */
  virtual const CObjectInterface * getObject(const CCommonName & cn) const;

  /**
   * Retrieve the prerequisites, i.e., the objects which need to be evaluated
   * before this.
   * @return const CObjectInterface::ObjectSet & prerequisites
   */
  virtual const CObjectInterface::ObjectSet & getPrerequisites() const;

  /**
   * Check whether a given object is a prerequisite for a context.
   * @param const CObjectInterface * pObject
   * @param const CCore::SimulationContextFlag & context
   * @param const CObjectInterface::ObjectSet & changedObjects
   * @return bool isPrerequisiteForContext
   */
  virtual bool isPrerequisiteForContext(const CObjectInterface * pObject,
                                        const CCore::SimulationContextFlag & context,
                                        const CObjectInterface::ObjectSet & changedObjects) const;

  /**
   * This is the output method for any object. The default implementation
   * provided with CDataObject uses the ostream operator<< of the object
   * to print the object.To override this default behavior one needs to
   * reimplement the virtual print function.
   * @param std::ostream * ostream
   */
  virtual void print(std::ostream * ostream) const;

  /**
   * Retrieve a pointer to the value of the object
   */
  virtual void * getValuePointer() const;

  /**
   * Retrieve a pointer to the data object
   * @return const DATA_OBJECT * dataObject
   */
  virtual const CDataObject * getDataObject() const;

  /**
   * Retrieve the display name of the object
   * @param bool regular (default: true)
   * @param bool richtext (default: false)
   * @return std::string objectDisplayName
   */
  virtual std::string getObjectDisplayName() const;

  /**
   * Get the aggregation of any issues associated with this object
   * @return const CValidity & validity
   */
  virtual const CValidity & getValidity() const;

  /**
   * This method is called whenever the validity of the object or a contained object changes.
   * @param const CValidity & changedValidity
   */
  void validityChanged(const CValidity & changedValidity);

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
  bool setObjectName(const std::string & name);

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

  CFlags< Flag > mObjectFlag;

  std::set< CDataContainer * > mReferences;

  std::set< const CValidity * > mReferencedValidities;
  CValidity mAggregateValidity;

protected:
  ObjectSet mPrerequisits;
};

#endif // COPASI_CDataObject
