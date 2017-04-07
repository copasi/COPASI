// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2002 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * Class CCopasiObject
 *
 * This class is the base class for all global accessible objects in COPASI.
 *
 * Copyright Stefan Hoops 2002
 */

#ifndef COPASI_CCopasiObject
#define COPASI_CCopasiObject

#define NO_PARENT static_cast< CCopasiContainer * >((void *) 0)
#define INHERIT_PARENT static_cast< CCopasiContainer * >((void *) -1)

#include <string>
#include <list>

#include "copasi/report/CObjectInterface.h"
#include "copasi/utilities/CValidity.h"

class CCopasiObject;
class CModel;
class CCopasiDataModel;
class CCopasiStaticString;
class CUnit;   //This will also work-around having a circular dependency
class CData;

template <class CType> class CCopasiObjectReference;
template <class CType> class CCopasiVectorReference;
template <class CType> class CCopasiMatrixReference;

#ifdef WIN32
template <class CType> class CCopasiVector;
#endif // WIN32

class CRenameHandler;
class CMathUpdateSequence;

//********************************************************************************

class CCopasiObject: public CObjectInterface
{
#ifdef WIN32
  friend CCopasiVector< CCopasiObject >;
#endif // WIN32

public:
  typedef std::set< const CCopasiObject * > DataObjectSet;

  //Attributes
protected:
  enum Flag
  {
    Container = 0x1,
    Vector = 0x2,
    Matrix = 0x4,
    NameVector = 0x8,
    Reference = 0x10,
    ValueBool = 0x20,
    ValueInt = 0x40,
    ValueInt64 = 0x80,
    ValueDbl = 0x100,
    NonUniqueName = 0x200,
    StaticString = 0x400,
    ValueString = 0x800,
    Separator = 0x1000,
    ModelEntity = 0x2000,
    Array = 0x4000,
    DataModel = 0x8000,
    Root = 0x10000,
    Gui = 0x20000
  };

private:
  std::string mObjectName;

  std::string mObjectType;

  CCopasiContainer * mpObjectParent;

  mutable CCopasiStaticString * mpObjectDisplayName;

  unsigned C_INT32 mObjectFlag;

  /**
   * A list of all objects the object depends on directly, i.e, the
   * objects which are used to calculate the object.
   */
  DataObjectSet mDependencies;

  std::set< CCopasiContainer * > mReferences;

protected:
  ObjectSet mPrerequisits;

  CValidity mValidity;

  static C_FLOAT64 DummyValue;

  static CRenameHandler * smpRenameHandler;

  //Operations
  CCopasiObject();

  CCopasiObject(const std::string & name,
                const CCopasiContainer * pParent = NO_PARENT,
                const std::string & type = "CN",
                const unsigned C_INT32 & flag = 0);

  CCopasiObject(const CCopasiObject & src);

public:
  static CCopasiObject * fromData(const CData & data);

  CCopasiObject(const CCopasiObject & src,
                const CCopasiContainer * pParent);

  virtual ~CCopasiObject();

  /**
   * Calculate the objects value.
   */
  virtual void calculateValue() {};

  /**
   * This is the output method for any object. The default implementation
   * provided with CCopasiObject uses the ostream operator<< of the object
   * to print the object.To override this default behavior one needs to
   * reimplement the virtual print function.
   * @param std::ostream * ostream
   */
  virtual void print(std::ostream * ostream) const;

  /**
   * Set the name of the object.
   * Note: An attempt set the name to "" results in the name
   *       being set to "No Name".
   * @param const std::string & name
   * @return success
   */
  bool setObjectName(const std::string & name);

  const std::string & getObjectName() const;

  /**
   * Retrieve the display name of the object
   * @param bool regular (default: true)
   * @param bool richtext (default: false)
   * @return std::string objectDisplayName
   */
  virtual std::string getObjectDisplayName() const;

  const std::string & getObjectType() const;

  virtual bool setObjectParent(const CCopasiContainer * pParent);

  CCopasiContainer * getObjectParent() const;

  void addReference(const CCopasiContainer * pReference);

  void removeReference(const CCopasiContainer * pReference);

  /**
   * Returns a pointer to the CCopasiDataModel the element belongs to.
   * If there is no instance of CCopasiDataModel in the ancestor tree, NULL
   * is returned.
   */
  CCopasiDataModel* getObjectDataModel() const;

  CCopasiContainer * getObjectAncestor(const std::string & type) const;

  virtual CCopasiObjectName getCN() const;

  virtual const CObjectInterface * getObject(const CCopasiObjectName & cn) const;

  /**
   * Retrieve a object by its full CN.
   * @param const CCopasiObjectName & cn
   * @return const CObjectInterface * pObject
   */
  virtual const CObjectInterface * getObjectFromCN(const CCopasiObjectName & cn) const;

  /**
   * Set the direct dependencies
   * @param const Set & directDependencies
   */
  void setDirectDependencies(const DataObjectSet & directDependencies);

  /**
   * Retrieve the list of direct dependencies
   * @param const DataObjectSet & context (default empty set)
   * @return const DataObjectSet & directDependencies
   */
  virtual const DataObjectSet &
  getDirectDependencies(const DataObjectSet & context = DataObjectSet()) const;

  /**
   * Clear the list of direct dependencies.
   */
  void clearDirectDependencies();

  /**
   * Add a the object to the direct dependencies
   * @param const CCopasiObject * pObject
   */
  void addDirectDependency(const CCopasiObject * pObject);

  /**
   * Remove an object from the direct dependencies
   * @param const CCopasiObject * pObject
   */
  void removeDirectDependency(const CCopasiObject * pObject);

  /**
   * Retrieve the prerequisites, i.e., the objects which need to be evaluated
   * before this.
   * @return const CObjectInterface::ObjectSet & prerequisites
   */
  virtual const CObjectInterface::ObjectSet & getPrerequisites() const;

  /**
   * Check whether a given object is a prerequisite for a context.
   * @param const CObjectInterface * pObject
   * @param const CMath::SimulationContextFlag & context
   * @param const CObjectInterface::ObjectSet & changedObjects
   * @return bool isPrerequisiteForContext
   */
  virtual bool isPrerequisiteForContext(const CObjectInterface * pObject,
                                        const CMath::SimulationContextFlag & context,
                                        const CObjectInterface::ObjectSet & changedObjects) const;

  /**
   * If called with an empty set of dependencies it retrieves the complete list
   * of all dependencies (including all indirect) of the current object.
   * If called with a non empty set it will only add any dependency and all its
   * dependencies to the list if the dependency is not already among the dependencies
   * @param DataObjectSet & dependencies
   * @param const DataObjectSet & context
   */
  void getAllDependencies(DataObjectSet & dependencies,
                          const DataObjectSet & context) const;

  /**
   * Check whether an object must be deleted because its prerequisites can
   * no longer be fulfilled due to the given deleted objects
   * @param const DataObjectSet & deletedObjects
   * @return bool mustBeDeleted
   */
  virtual bool mustBeDeleted(const DataObjectSet & deletedObjects) const;

  /**
   * Check whether the current object depends on any objects in the candidates.
   * @param DataObjectSet candidates
   * @param const DataObjectSet & context (default: empty set)
   * @return bool dependsOn
   */
  bool dependsOn(DataObjectSet candidates,
                 const DataObjectSet & context = DataObjectSet()) const;

  /**
   * If called with an empty set it will check whether the current object and all its
   * dependencies (including all indirect) form a circular dependency.
   * If called with a non empty set it check whether the candidates plus the current object
   * and all its dependencies form a circular dependency.
   * @param DataObjectSet & dependencies
   * @param DataObjectSet & verified
   * @param const DataObjectSet & context
   * @return bool hasCircularDependencies
   */
  bool hasCircularDependencies(DataObjectSet & candidates,
                               DataObjectSet & verified,
                               const DataObjectSet & context) const;

  /**
   * Retrieve the units of the object.
   * @return std::string units
   */
  virtual const std::string getUnits() const;

  /**
   * Comparison operator which can be used to sort objects based on their dependencies
   * If the object *lhs is a dependency of *rhs and must be evaluated first the operator
   * return true.
   * @param const CCopasiObject * lhs
   * @param const CCopasiObject * rhs
   * @return bool isLess
   */
  // static
  // bool compare(const CCopasiObject * lhs, const CCopasiObject * rhs);

  bool isContainer() const;

  bool isVector() const;

  bool isMatrix() const;

  bool isNameVector() const;

  bool isReference() const;

  bool isValueBool() const;
  bool isValueInt() const;
  bool isValueInt64() const;
  bool isValueDbl() const;
  bool isNonUniqueName() const;
  bool isStaticString() const;
  bool isValueString() const;
  bool isSeparator() const;
  bool isArray() const;
  bool isDataModel() const;
  bool isRoot() const;

  virtual void * getValuePointer() const;

  /**
   * Retrieve a pointer to the data object
   * @return const CCopasiObject * dataObject
   */
  virtual const CCopasiObject * getDataObject() const;

  virtual const CCopasiObject * getValueObject() const;

  /**
   * Get the aggregation of any issues associated with this object
   * @return CValidity & validity
   */
  virtual CValidity & getValidity();

  /**
   * Get the aggregation of any issues associated with this object
   * @return const CValidity & validity
   */
  virtual const CValidity & getValidity() const;

  virtual CData toData() const;
  virtual bool applyData(const CData & data);

  friend std::ostream &operator<<(std::ostream &os, const CCopasiObject & o);

  virtual const std::string & getKey() const;

  static void setRenameHandler(CRenameHandler* rh)
  {smpRenameHandler = rh;}
};

template <class CType> CCopasiObjectReference< CType > *
createReference(const std::string & name,
                const CCopasiContainer * pParent,
                CType & reference,
                const unsigned C_INT32 & flag = 0)
{return new CCopasiObjectReference< CType >(name, pParent, reference, flag);}

template <class CType> CCopasiVectorReference< CType > *
createVectorReference(const std::string & name,
                      const CCopasiContainer * pParent,
                      CType & reference,
                      const unsigned C_INT32 & flag = 0)
{return new CCopasiVectorReference< CType >(name, pParent, reference, flag);}

template <class CType> CCopasiMatrixReference< CType > *
createMatrixReference(const std::string & name,
                      const CCopasiContainer * pParent,
                      CType & reference,
                      const unsigned C_INT32 & flag = 0)
{return new CCopasiMatrixReference< CType >(name, pParent, reference, flag);}

/**
 * Sort the CCopasiObjects in the interval [begin, end) according to
 * their dependencies
 * @param ForwardAccessIterator begin
 * @param ForwardAccessIterator end
 * @param const DataObjectSet & context
 * @return std::list< const CCopasiObject * >
 */
template <typename ForwardAccessIterator>
std::list< const CCopasiObject * > sortObjectsByDependency(ForwardAccessIterator begin,
    ForwardAccessIterator end,
    const CCopasiObject::DataObjectSet & context)
{
  std::list< const CCopasiObject * > SortedList;
  std::list< const CCopasiObject * >::iterator itList;
  std::list< const CCopasiObject * >::iterator endList;

  CCopasiObject::DataObjectSet AllDependencies;
  std::list< CCopasiObject::DataObjectSet > DependencySet;
  std::list< CCopasiObject::DataObjectSet >::iterator itDependencies;

  for (; begin != end; ++begin)
    {
      AllDependencies.clear();
      (*begin)->getAllDependencies(AllDependencies, context);

      itList = SortedList.begin();
      endList = SortedList.end();
      itDependencies = DependencySet.begin();

      for (; itList != endList; ++itList, ++itDependencies)
        if (itDependencies->count(*begin)) break;

      SortedList.insert(itList, *begin);
      DependencySet.insert(itDependencies, AllDependencies);
    }

  return SortedList;
}

#endif // COPASI_CCopasiObject
