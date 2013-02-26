// Copyright (C) 2011 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CModelParameterGroup
#define COPASI_CModelParameterGroup

#include <vector>

#include "copasi.h"

#include "copasi/model/CModelParameter.h"

class CModel;

class CModelParameterGroup: public CModelParameter
{
public:
  typedef std::vector< CModelParameter * >::iterator iterator;
  typedef std::vector< CModelParameter * >::const_iterator const_iterator;

public:
  /**
   * Constructor
   * @param CModelParameterGroup * pParent
   * @param const CModelParameter::Type & type (default: CModelParameter::Group)
   */
  CModelParameterGroup(CModelParameterGroup * pParent, const CModelParameter::Type & type = CModelParameter::Group);

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
  void add(CModelParameter * pModelParameter);

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
   * @param const CModelParameter::Framework & framework
   * @param const bool & createMissing = false
   */
  const virtual CompareResult & diff(const CModelParameter& other,
                                     const CModelParameter::Framework & framework,
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

protected:
  /**
   * Assign the content of the source group to this, i.e., copy all
   * contained parameters.
   * @param const CModelParameterGroup & src
   * @param const bool & createMissing
   */
  void assignGroupContent(const CModelParameterGroup & src,
                          const bool & createMissing);

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
};

#endif // COPASI_CModelParameterGroup
