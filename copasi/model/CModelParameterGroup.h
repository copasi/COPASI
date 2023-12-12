// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and University of 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

#ifndef COPASI_CModelParameterGroup
#define COPASI_CModelParameterGroup

#include <vector>

#include "copasi/copasi.h"

#include "copasi/model/CModelParameter.h"
#include "copasi/utilities/CValidatedUnit.h"

class CModel;

class CModelParameterGroup: public CModelParameter
{
public:
  typedef std::vector< CModelParameter * >::iterator iterator;
  typedef std::vector< CModelParameter * >::const_iterator const_iterator;

public:
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
   * Retrieve the data describing the object
   * @return CData data
   */
  virtual CData toData() const;

  /**
   * Apply the provided data to the object
   * @param const CData & data
   * @return bool success
   */
  virtual bool applyData(const CData & data, CUndoData::CChangeSet & changes);

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
                              const CCore::Framework & framework = CCore::Framework::ParticleNumbers) const;

  /**
   * Constructor
   * @param CModelParameterGroup * pParent
   * @param const CModelParameter::Type & type (default: CModelParameter::Group)
   */
  CModelParameterGroup(CModelParameterGroup * pParent, const CModelParameter::Type & type = CModelParameter::Type::Group);

  /**
   * Copy constructor
   * @param const CModelParameterGroup & src
   * @param CModelParameterGroup * pParent
   * @param const bool & createMissing
   */
  CModelParameterGroup(const CModelParameterGroup & src,
                       CModelParameterGroup * pParent,
                       const bool & createMissing);

  /**
   * Destructor
   */
  virtual ~CModelParameterGroup();

  /**
   * Add parameter of the given type to the group and return a pointer to it
   * @param const CModelParameter::Type & type
   * @return CModelParameter * pParameter
   */
  CModelParameter * add(const CModelParameter::Type & type);

  /**
   * Add the given parameter to the group.
   * Note, the parent of the parameter is not updated
   * @param CModelParameter * pModelParameter
   */
  virtual void add(CModelParameter * pModelParameter);

  /**
   * Remove the given parameter from the group.
   * Note, the parameter is not deleted.
   * @param CModelParameter * pModelParameter
   */
  void remove(CModelParameter * pModelParameter);

  /**
   * Remove the indexed parameter from the group and delete it
   * @param const size_t & index
   */
  void remove(const size_t & index);

  /**
   * Retrieve the size of the group
   * @return size_t size
   */
  size_t size() const;

  /**
   * Retrieve the iterator pointing to the first contained parameter.
   * @return iterator begin
   */
  iterator begin();

  /**
   * Retrieve the iterator pointing past the last contained parameter.
   * @return iterator end
   */
  iterator end();

  /**
   * Retrieve the const_iterator pointing to the first contained parameter.
   * @return const_iterator begin
   */
  const_iterator begin() const;

  /**
   * Retrieve the const_iterator pointing past the last contained parameter.
   * @return const_iterator end
   */
  const_iterator end() const;

  /**
   * Compile the parameter
   */
  virtual void compile();

  /**
   * Clear the contained parameters and delete them.
   */
  void clear();

#ifndef SWIG
  /**
   * Compare the parameter to an other
   * @param const CModelParameter & other
   * @param const CCore::Framework & framework
   * @param const bool & createMissing = false
   */
  const virtual CompareResult & diff(const CModelParameter& other,
                                     const CCore::Framework & framework,
                                     const bool & createMissing = false);
#endif //SWIG

  /**
   * Update the corresponding model object with the current parameter settings
   */
  virtual bool updateModel();

  /**
   * Refresh the parameter from the corresponding model object
   * @param const bool & modifyExistence
   */
  virtual bool refreshFromModel(const bool & modifyExistence);

  /**
   * Retrieve a pointer to the parameter with the given CN
   * @param const std::string & cn
   * @return CModelParameter * pModelParameter
   */
  CModelParameter * getModelParameter(const std::string & cn) const;

  /**
    * Retrieve a pointer to the parameter with the given name and type
    * @param const std::string & name
    * @param const CModelParameter::Type & type
    * @return CModelParameter * pModelParameter
    */
  CModelParameter * getModelParameter(const std::string & name,
                                      const CModelParameter::Type & type) const;

  // These methods are only here so that we can use CNodeIterator to traverse the tree.
  virtual size_t getNumChildren() const;
  virtual const CModelParameter * getChild(const size_t & index) const;

  /**
   * Retrieve the validated unit of the object units
   * @param const CModelParameter * pModelParameter
   * @return const CValidatedUnit & objectUnit
   */
  const CValidatedUnit & getObjectUnit(const CModelParameter * pModelParameter) const;

  /**
   * Assign the content of the source group to this, i.e., copy all
   * contained parameters.
   * @param const CModelParameterGroup & src
   * @param const bool & createMissing
   */
  void assignGroupContent(const CModelParameterGroup & src,
                          const bool & createMissing);

protected:
  /**
   * Copy the existing parameter and add it to the group
   * @param const CModelParameter & src
   * @param const bool & createMissing
   * @return CModelParameter * pCopy
   */
  CModelParameter * copy(const CModelParameter & src,
                         const bool & createMissing);

private:
  /**
   * A vector of pointer to the contained parameters.
   */
  std::vector< CModelParameter * > mModelParameters;

  /**
   * A map of model objects and their validated units
   */
  mutable std::map< CObjectInterface *, CValidatedUnit > mValidatedUnits;
};

#endif // COPASI_CModelParameterGroup
