// Copyright (C) 2011 - 2012 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CModelParameter
#define COPASI_CModelParameter

#include <set>

#include "copasi/report/CCopasiObjectName.h"

class CModelParameterSet;
class CModelParameterGroup;
class CCopasiObject;
class CExpression;
class CModel;

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
  void setParent(CModelParameterGroup* pParent);
  CModelParameterGroup* getParent() const;
  const Type& getType() const;
  virtual void setCN(const CCopasiObjectName& cn);
  const CCopasiObjectName& getCN() const;
#ifndef SWIG
  virtual void setValue(const double& value, const Framework& framework =
                          ParticleNumbers);
  const virtual double& getValue(
    const Framework& framework = ParticleNumbers) const;
#endif
  void setInitialExpression(const std::string& initialExpression);
  std::string getInitialExpression() const;
  void setCompareResult(const CompareResult& compareResult);
  const CompareResult& getCompareResult() const;
  size_t getIndex() const;
  bool isReadOnly() const;
  CCopasiObject* getObject() const;
  CModelParameterSet * getSet() const;
  CModel* getModel() const;
  bool isInitialExpressionValid() const;
  virtual std::string getName() const;
  virtual void compile();
#ifndef SWIG
  const virtual CompareResult& diff(const CModelParameter& other);
#endif
  virtual bool updateModel();

protected:
  static std::string nameFromCN(const CCopasiObjectName& cn);

protected:
  CModelParameterGroup* mpParent;
  Type mType;
  CRegisteredObjectName mCN;
  double mValue;

  CExpression * mpInitialExpression;

  CompareResult mCompareResult;

  CCopasiObject * mpObject;

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

  virtual void setValue(const C_FLOAT64 & value, const Framework & framework = ParticleNumbers);

  void addSpecies(CModelParameterSpecies * pSpecies);

  void removeSpecies(CModelParameterSpecies * pSpecies);

private:
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

  virtual void compile();

  virtual void setCN(const CCopasiObjectName & cn);

  virtual void setValue(const C_FLOAT64 & value, const Framework & framework = ParticleNumbers);

  virtual const C_FLOAT64 & getValue(const Framework & framework = ParticleNumbers) const;

private:
  CCopasiObjectName getCompartmentCN() const;

  CRegisteredObjectName mCompartmentCN;

  CModelParameterCompartment * mpCompartment;

  C_FLOAT64 mConcentration;
};
#endif // COPASI_CModelParameter
