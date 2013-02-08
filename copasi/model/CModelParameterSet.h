// Copyright (C) 2011 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CModelParameterSet
#define COPASI_CModelParameterSet

#include <string>

#include "copasi/report/CCopasiContainer.h"
#include "copasi/model/CModelParameterGroup.h"
#include "copasi/model/CAnnotation.h"

class CModel;

class CModelParameterSet: public CCopasiContainer, public CModelParameterGroup, public CAnnotation
{
public:
  /**
   * Constructor
   * @param const std::string & name
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CModelParameterSet(const std::string & name,
                     const CCopasiContainer * pParent = NULL);

  /**
   * Copy constructor
   * @param const CModelParameterSet & src
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CModelParameterSet(const CModelParameterSet & src,
                     const CCopasiContainer * pParent = NULL);

  /**
   * Destructor
   */
  virtual ~CModelParameterSet();

  /**
   * Retrieve the unique key of the set.
   * @return const std::string & key
   */
  virtual const std::string & getKey() const;

  /**
   * Set the object parent
   * @param const CCopasiContainer * pParent
   * @return bool success
   */
  virtual bool setObjectParent(const CCopasiContainer * pParent);

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
  bool compareWithModel();

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
   * Determine whether this is parameter set is currently active, i.e., it is synchronized
   * with the model.
   * @return bool isActive
   */
  bool isActive() const;

  /**
   * Assign the content of the source set to this, i.e., copy all
   * contained parameters and groups.
   * @param const CModelParameterSet & src
   */
  void assignSetContent(const CModelParameterSet & src);

  /**
   * Save the parameter set to a stream
   * @param std::ostream & os
   * @param const std::string & mode (report or table)
   * @param const std::string & separator
   */
  bool saveToStream(std::ostream & os, const std::string & mode, const std::string & separator);

private:
  /**
   * The unique key of the set
   */
  std::string mKey;

  /**
   * A pointer to the model the parameter set is storing values for
   */
  CModel * mpModel;
};

#endif // COPASI_CModelParameterSet
