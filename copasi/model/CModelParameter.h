// Copyright (C) 2019 - 2024 by Pedro Mendes, Rector and Visitors of the
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

#ifndef COPASI_CModelParameter
#define COPASI_CModelParameter

#include <set>

#include "copasi/core/CRegisteredCommonName.h"
#include "copasi/model/CModelValue.h"
#include "copasi/undo/CUndoObjectInterface.h"

class CModelParameterSet;
class CModelParameterGroup;
class CDataObject;
class CExpression;
class CModel;
class CReaction;
class CValidatedUnit;

class CModelParameter : public CUndoObjectInterface
{
  friend std::ostream &operator<<(std::ostream &os, const CModelParameter & o);

public:
  enum struct Type
  {
    Model,
    Compartment,
    Species,
    ModelValue,
    ReactionParameter,
    Reaction,
    Group,
    Set,
    unknown,
    __SIZE
  };

  static const CEnumAnnotation< std::string, Type > TypeNames;

  enum struct CompareResult
  {
    Obsolete,
    Missing,
    Modified,
    Conflict,
    Identical,
    __SIZE
  };

  static const CEnumAnnotation< std::string, CompareResult > CompareResultNames;

  /**
   * Static method to create a CDataObject based on the provided data
   * @param const CData & data
   * @return CModelParameter * pDataObject
   */
  static CModelParameter * fromData(const CData & data, CUndoObjectInterface * pParent);

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

private:
  /**
   * The default constructor is hidden.
   */
  CModelParameter();

public:
  /**
   * Constructor
   */
  CModelParameter(CModelParameterGroup* pParent,
                  const CModelParameter::Type& type);
  /**
   * Copy constructor
   */
  CModelParameter(const CModelParameter& src, CModelParameterGroup* pParent);

public:
  /**
   * Destructor
   */
  virtual ~CModelParameter();

  virtual CModelParameterSet * toSet();

  virtual const CModelParameterSet * toSet() const;

  bool operator < (const CModelParameter & rhs) const;

  /**
   * Set the parent, i.e., containing group, of the parameter.
   * Note, it is the responsibility of the user to remove the parameter
   * from the old part.
   * @param CModelParameterGroup * pParent
   */
  void setParent(CModelParameterGroup * pParent);

  /**
   * Retrieve the parent, i.e., containing group, of the parameter.
   * @return CModelParameterGroup * pParent
   */
  CModelParameterGroup* getParent() const;

  /**
   * Retrieve the type of the parameter
   * @return const Type & type
   */
  const Type & getType() const;

  /**
   * Retrieve the unit of the parameter based on the current framework
   * @param const Framework & framework (default: ParticleNumbers)
   * @return CValidatedUnit unit
   */
  CValidatedUnit getUnit(const CCore::Framework & framework) const;

  /**
   * Set the CN of the object represented by the parameter
   * @param const CCommonName & cn
   */
  virtual void setCN(const CCommonName & cn);

  /**
   * Retrieve the CN of the object represented by the parameter
   * @return const CCommonName & cn
   */
  const CCommonName & getCN() const;

  /**
   * Set the role the parameters object plays in the simulation.
   * Note, REACTION is only valid for species.
   * @param const CModelEntity::Status & simulationType
   * @return bool success
   */
  bool setSimulationType(const CModelEntity::Status & simulationType);

  /**
   * Retrieve the role the parameters object plays in the simulation
   * @return const CModelEntity::Status & simulationType
   */
  const CModelEntity::Status & getSimulationType() const;

#ifndef SWIG
  /**
   * Set the value of the parameter based on the current framework
   * @param const double & value
   * @param const Framework & framework
   * @param updateModelIfActive if this is the active parameter set,
   *        write the changes back to the model
   */
  virtual void setValue(const C_FLOAT64 & value, const CCore::Framework & framework, bool updateModelIfActive = true);

  /**
   * Retrieve the value of the parameter based on the current framework
   * @param const Framework & framework
   * @return const double & value
   */
  const virtual double& getValue(const CCore::Framework & framework) const;
#endif

  /**
   * Set the initial expression infix.
   * @param const std::string & initialExpression
   */
  void setInitialExpression(const std::string & initialExpression);

  /**
   * Retrieve the initial expression infix.
   * @return std::string initialExpression
   */
  std::string getInitialExpression() const;

  /**
   * Retrieve the actual initial expression.
   * @return const CExpression* initialExpression
   */
  const CExpression* getInitialExpressionPtr() const;

  /**
   * The the compare result.
   * @param const CompareResult & compareResult
   */
  void setCompareResult(const CompareResult & compareResult);

  /**
   * Retrieve the compare result.
   * @return const CompareResult & compareResult
   */
  const CompareResult & getCompareResult() const;

  /**
   * Retrieve the index of the parameter in the vector of children in the parent
   * @return size_t index
   */
  virtual size_t getIndex() const;

  /**
   * Check whether the value is read only.
   * @return bool isReadOnly
   */
  bool isReadOnly() const;

  /**
   * Retrieve the pointer to the corresponding model object
   * @return CDataObject * pObject
   */
  CDataObject * getObject() const;

  /**
   * Retrieve a pointer to the parameter set the parameter belongs to
   * @return CModelParameterSet * set
   */
  CModelParameterSet * getSet() const;

  /**
   * Retrieve a pointer to the model the parameter is part of
   * @return CModel * pModel
   */
  CModel * getModel() const;

  /**
   * Check whether the initial expression is valid, i.e., it compiled
   * @return bool isInitialExpressionValid
   */
  bool isInitialExpressionValid() const;

  /**
   * Retrieve the name of the parameter.
   * @return std::string name
   */
  virtual std::string getName() const;

  /**
   * Compile the parameter
   */
  virtual void compile();

#ifndef SWIG
  /**
   * Compare the parameter to an other
   * @param const CModelParameter & other
   * @param const CCore::Framework & framework (default: ParticleNumbers)
   * @param const bool & createMissing = false
   */
  const virtual CompareResult & diff(const CModelParameter& other,
                                     const CCore::Framework & framework = CCore::Framework::ParticleNumbers,
                                     const bool & createMissing = false);
#endif

  /**
   * Update the corresponding model object with the current parameter settings
   */
  virtual bool updateModel();

  /**
   * Refresh the parameter from the corresponding model object
   * @param const bool & modifyExistence
   */
  virtual bool refreshFromModel(const bool & modifyExistence);

  // These methods are only here so that we can use CNodeIterator to traverse the tree.
  virtual size_t getNumChildren() const;
  virtual const CModelParameter * getChild(const size_t & index) const;

protected:
  /**
   * The parent group
   */
  CModelParameterGroup* mpParent;

  /**
   * The type
   */
  Type mType;

  /**
   * The CN of the corresponding model object
   */
  CRegisteredCommonName mCN;

  /**
   * The role the parameter object is used in the simulation.
   */
  CModelEntity::Status mSimulationType;

  /**
   * The value of the parameter
   */
  double mValue;

  /**
   * A pointer to the initial expression
   */
  CExpression * mpInitialExpression;

  /**
   * The result of the last compare
   */
  CompareResult mCompareResult;

  /**
   * A pointer to the corresponding model object. NULL if no object exists.
   */
  CDataObject * mpObject;

  /**
   * The result of the last compile of the initial expression. Note an empty or
   * missing expression is valid.
   */
  bool mIsInitialExpressionValid;
};

class CModelParameterSpecies;

class CModelParameterCompartment : public CModelParameter
{
public:
  /**
   * Constructor
   */
  CModelParameterCompartment(CModelParameterGroup * pParent, const CModelParameter::Type & type = CModelParameter::Type::Compartment);

  /**
   * Copy constructor
   */
  CModelParameterCompartment(const CModelParameterCompartment & src, CModelParameterGroup * pParent);

public:
  /**
   * Destructor
   */
  virtual ~CModelParameterCompartment();

  /**
   * Set the value of the parameter based on the current framework
   * @param const double & value
   * @param const Framework & framework
   * @param updateModelIfActive if this is the active parameter set,
   *        write the changes back to the model
   */
  virtual void setValue(const C_FLOAT64 & value, const CCore::Framework & framework, bool updateModelIfActive = true);

  /**
   * Add a pointer to a species parameter to the compartment
   */
  void addSpecies(CModelParameterSpecies * pSpecies);

  /**
   * Remove a pointer to a species parameter from the compartment
   */
  void removeSpecies(CModelParameterSpecies * pSpecies);

private:
  /**
   * The set of species parameters which are contained in the compartment
   */
  std::set< CModelParameterSpecies * > mSpecies;
};

class CModelParameterSpecies : public CModelParameter
{
#ifndef SWIG
  friend CModelParameterCompartment::~CModelParameterCompartment();
#endif

public:
  /**
   * Retrieve the data describing the object
   * @return CData data
   */
  virtual CData toData() const;

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
   */
  CModelParameterSpecies(CModelParameterGroup * pParent, const CModelParameter::Type & type = CModelParameter::Type::Species);

  /**
   * Copy constructor
   */
  CModelParameterSpecies(const CModelParameterSpecies & src, CModelParameterGroup * pParent);

public:
  /**
   * Destructor
   */
  virtual ~CModelParameterSpecies();

  /**
   * Retrieve the name.
   * @return std::string name
   */
  virtual std::string getName() const;

  /**
   * Compile the parameter
   */
  virtual void compile();

  /**
   * Set the CN of the object represented by the parameter
   * @param const CCommonName & cn
   */
  virtual void setCN(const CCommonName & cn);

  /**
   * Set the value of the parameter based on the current framework
   * @param const double & value
   * @param const Framework & framework
   * @param updateModelIfActive if this is the active parameter set,
   *        write the changes back to the model
   */
  virtual void setValue(const C_FLOAT64 & value, const CCore::Framework & framework, bool updateModelIfActive = true);

  /**
   * Retrieve the value of the parameter based on the current framework
   * @param const Framework & framework
   * @return const double & value
   */
  virtual const C_FLOAT64 & getValue(const CCore::Framework & framework) const;

  /**
   * Update the corresponding model object with the current parameter settings
   */
  virtual bool updateModel();

private:
  /**
   * Retrieve the CN of the compartment the species is contained in.
   * @return CCommonName compartmentCN
   */
  CCommonName getCompartmentCN() const;

  /**
   * The CN of the compartment the species is contained in.
   */
  CRegisteredCommonName mCompartmentCN;

  /**
   * A pointer to the parameter representing the compartment the species is contained in.
   */
  CModelParameterCompartment * mpCompartment;

  /**
   * The concentration value of the species.
   */
  C_FLOAT64 mConcentration;
};

class CModelParameterReactionParameter: public CModelParameter
{
public:

  /**
   * Retrieve the CN of the reaction the parameter belongs to
   * @param const CCommonName & reactionParameterCN
   * @return CCommonName reationCN
   */
  static CCommonName getReactionCN(const CCommonName & reactionParameterCN);

  /**
   * Constructor
   */
  CModelParameterReactionParameter(CModelParameterGroup * pParent, const CModelParameter::Type & type = CModelParameter::Type::ReactionParameter);

  /**
   * Copy constructor
   */
  CModelParameterReactionParameter(const CModelParameterReactionParameter & src, CModelParameterGroup * pParent);

  /**
   * Destructor
   */
  virtual ~CModelParameterReactionParameter();

  /**
   * Compile the parameter
   */
  virtual void compile();

  /**
   * Retrieve a pointer to the reaction the parameter belongs to.
   * @return const CReaction * reaction
   */
  const CReaction * getReaction() const;

  /**
   * Set the CN of the assigned global quantity. If the CN is empty
   * the assignment is removed.
   * @param const std::string & globalQuantityCN
   */
  void setGlobalQuantityCN(const std::string & globalQuantityCN);

  /**
   * Retrieve the CN of the assigned global quantity
   * @return const CRegisteredCommonName & globalQuantityCN
   */
  const CRegisteredCommonName & getGlobalQuantityCN() const;

private:
  /**
   * A pointer to the reaction the parameter belongs to.
   */
  CReaction * mpReaction;

  /**
   * The CN of the assigned global quantity.
   */
  CRegisteredCommonName mGlobalQuantityCN;

  /**
   * A pointer to the parameter representing the assigned global quantity.
   */
  CModelParameter * mpGlobalQuantity;
};
#endif // COPASI_CModelParameter
