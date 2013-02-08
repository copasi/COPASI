// Copyright (C) 2011 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CModelParameter
#define COPASI_CModelParameter

#include <set>

#include "copasi/report/CCopasiObjectName.h"
#include "copasi/model/CModelValue.h"

class CModelParameterSet;
class CModelParameterGroup;
class CCopasiObject;
class CExpression;
class CModel;
class CReaction;

class CModelParameter
{
  friend std::ostream &operator<<(std::ostream &os, const CModelParameter & o);

public:
  enum Type
  {
    Model,
    Compartment,
    Species,
    ModelValue,
    ReactionParameter,
    Group,
    Set,
    unknown
  };

  static const char * TypeNames[];

  enum CompareResult
  {
    Obsolete,
    Missing,
    Modified,
    Identical
  };

  enum Framework
  {
    Concentration = 0,
    ParticleNumbers
  };

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
   * @return const std::string unit
   */
  const std::string getUnit(const Framework & framework = ParticleNumbers) const;

  /**
   * Set the CN of the object represented by the parameter
   * @param const CCopasiObjectName & cn
   */
  virtual void setCN(const CCopasiObjectName & cn);

  /**
   * Retrieve the CN of the object represented by the parameter
   * @return const CCopasiObjectName & cn
   */
  const CCopasiObjectName & getCN() const;

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
   * @param const Framework & framework (default: ParticleNumbers)
   */
  virtual void setValue(const double & value, const Framework& framework = ParticleNumbers);

  /**
   * Retrieve the value of the parameter based on the current framework
   * @param const Framework & framework (default: ParticleNumbers)
   * @return const double & value
   */
  const virtual double& getValue(const Framework & framework = ParticleNumbers) const;
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
  size_t getIndex() const;

  /**
   * Check whether the value is read only.
   * @return bool isReadOnly
   */
  bool isReadOnly() const;

  /**
   * Retrieve the pointer to the corresponding model object
   * @return CCopasiObject * pObject
   */
  CCopasiObject * getObject() const;

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
   */
  const virtual CompareResult & diff(const CModelParameter& other);
#endif

  /**
   * Update the corresponding model object with the current parameter settings
   */
  virtual bool updateModel();

  /**
   * Refresh the parameter from the corresponding model object
   */
  virtual bool refreshFromModel();

  // These methods are only here so that we can use CNodeIterator to traverse the tree.
  virtual size_t getNumChildren() const;
  virtual const CModelParameter * getChild(const size_t & index) const;

protected:
  /**
   * Determine the parameter name based on the CN of the corresponding object
   * @param const CCopasiObjectName & cn
   * @return std::string name
   */
  static std::string nameFromCN(const CCopasiObjectName & cn);

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
  CRegisteredObjectName mCN;

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
  CCopasiObject * mpObject;

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
  CModelParameterCompartment(CModelParameterGroup * pParent, const CModelParameter::Type & type = CModelParameter::Compartment);

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
   * @param const Framework & framework (default: ParticleNumbers)
   */
  virtual void setValue(const C_FLOAT64 & value, const Framework & framework = ParticleNumbers);

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
  friend CModelParameterCompartment::~CModelParameterCompartment();

public:
  /**
   * Constructor
   */
  CModelParameterSpecies(CModelParameterGroup * pParent, const CModelParameter::Type & type = CModelParameter::Species);

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
   * @param const CCopasiObjectName & cn
   */
  virtual void setCN(const CCopasiObjectName & cn);

  /**
   * Set the value of the parameter based on the current framework
   * @param const double & value
   * @param const Framework & framework (default: ParticleNumbers)
   */
  virtual void setValue(const C_FLOAT64 & value, const Framework & framework = ParticleNumbers);

  /**
   * Retrieve the value of the parameter based on the current framework
   * @param const Framework & framework (default: ParticleNumbers)
   * @return const double & value
   */
  virtual const C_FLOAT64 & getValue(const Framework & framework = ParticleNumbers) const;

private:
  /**
   * Retrieve the CN of the compartment the species is contained in.
   * @return CCopasiObjectName compartmentCN
   */
  CCopasiObjectName getCompartmentCN() const;

  /**
   * The CN of the compartment the species is contained in.
   */
  CRegisteredObjectName mCompartmentCN;

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
   * Constructor
   */
  CModelParameterReactionParameter(CModelParameterGroup * pParent, const CModelParameter::Type & type = CModelParameter::ReactionParameter);

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
   * Retrieve the CN of the assigned global quantity
   * @return const CRegisteredObjectName & globalQuantityCN
   */
  const CRegisteredObjectName & getGlobalQuantityCN() const;

private:
  /**
   * A pointer to the reaction the parameter belongs to.
   */
  CReaction * mpReaction;

  /**
   * The CN of the assigned global quantity.
   */
  CRegisteredObjectName mGlobalQuantityCN;

  /**
   * A pointer to the parameter representing the assigned global quantity.
   */
  CModelParameter * mpGlobalQuantity;
};
#endif // COPASI_CModelParameter
