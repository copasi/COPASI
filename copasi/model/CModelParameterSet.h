// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
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

#ifndef COPASI_CModelParameterSet
#define COPASI_CModelParameterSet

#include <string>

#include "copasi/core/CDataContainer.h"
#include "copasi/model/CModelParameterGroup.h"
#include "copasi/model/CAnnotation.h"

class CModel;

class CModelParameterSet: public CDataContainer, public CModelParameterGroup, public CAnnotation
{
public:
  /**
   * Static method to create a CDataObject based on the provided data
   * @param const CData & data
   * @return CModelParameterSet * pDataObject
   */
  static CModelParameterSet * fromData(const CData & data, CUndoObjectInterface * pParent);

  /**
   * Destruct the object
   */
  virtual void destruct();

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
   * Constructor
   * @param const std::string & name
   * @param const CDataContainer * pParent (default: NULL)
   */
  CModelParameterSet(const std::string & name,
                     const CDataContainer * pParent = NO_PARENT);

  /**
   * Copy constructor
   * @param const CModelParameterSet & src
   * @param const CDataContainer * pParent
   * @param const bool & createMissing (default: false)
   */
  CModelParameterSet(const CModelParameterSet & src,
                     const CDataContainer * pParent,
                     const bool & createMissing = false);

  /**
   * Destructor
   */
  virtual ~CModelParameterSet();

  /**
   * Retrieve the CN of the object
   * @return CCommonName
   */
  virtual CCommonName getCN() const;

  CModelParameterGroup * toGroup();

  const CModelParameterGroup * toGroup() const;

  virtual CModelParameterSet * toSet();

  virtual const CModelParameterSet * toSet() const;

  /**
   * Add the given parameter to the group.
   * Note, the parent of the parameter is not updated
   * @param CModelParameter * pModelParameter
   */
  virtual void add(CModelParameter * pModelParameter);

  /**
   * Retrieve the unique key of the set.
   * @return const std::string & key
   */
  virtual const std::string & getKey() const;

  /**
   * Set the object parent
   * @param const CDataContainer * pParent
   * @return bool success
   */
  virtual bool setObjectParent(const CDataContainer * pParent);

  /**
   * Retrieve the index of the parameter in the vector of children in the parent
   * @return size_t index
   */
  virtual size_t getIndex() const;

  /**
   * Set the model the parameter set is storing values for
   * @param const CModel * pModel
   */
  void setModel(const CModel * pModel);

  /**
   * Retrieve the model the parameter set is storing values for
   * @return CModel * pModel
   */
  CModel * getModel() const;

  /**
   * Create the parameter set from the assigned model
   */
  void createFromModel();

  /**
   * Compare the parameter set with the assigned model
   */
  bool compareWithModel(const CCore::Framework & framework);

  /**
   * Retrieve the name of the parameter set
   * @return std::string name
   */
  virtual std::string getName() const;

  /**
   * Update the corresponding model object with the current parameter settings
   */
  virtual bool updateModel();

  /**
   * Compile the parameter
   */
  virtual void compile();

  /**
   * Compare the parameter to an other
   * @param const CModelParameterSet & other
   * @param const CCore::Framework & framework
   * @param const bool & createMissing = false
   */
  const CompareResult & diff(const CModelParameterSet & other,
                             const CCore::Framework & framework,
                             const bool & createMissing = false);

  /**
   * Retrieve a pointer to the parameter with the given CN
   * @param const std::string & cn
   * @return const CModelParameter * pModelParameter
   */
  const CModelParameter * getModelParameter(const std::string & cn) const;

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
   * Refresh the parameter from the corresponding model object
   * @param const bool & modifyExistence
   */
  virtual bool refreshFromModel(const bool & modifyExistence);

  /**
   * Determine whether this is parameter set is currently active, i.e., it is synchronized
   * with the model.
   * @return bool isActive
   */
  bool isActive() const;

  /**
   * Assign the content of the source set to this, i.e., copy all
   * contained parameters and groups.
   * @param const CModelParameterSet & src
   * @param const bool & createMissing
   */
  void assignSetContent(const CModelParameterSet & src,
                        const bool & createMissing);

  /**
   * Save the parameter set to a stream
   * @param std::ostream & os
   * @param const CCore::Framework & framework
   * @param const std::string & mode (report, ini or table)
   * @param const std::string & separator
   */
  bool saveToStream(std::ostream & os,
                    const CCore::Framework & framework,
                    const std::string & mode,
                    const std::string & separator);

private:
  void init();

  /**
   * The unique key of the set
   */
  std::string mKey;

  /**
   * A pointer to the model the parameter set is storing values for
   */
  CModel * mpModel;

  CModelParameterGroup * mpTimes;
  CModelParameterGroup * mpCompartments;
  CModelParameterGroup * mpSpecies;
  CModelParameterGroup * mpModelValues;
  CModelParameterGroup * mpReactions;
};

#endif // COPASI_CModelParameterSet
