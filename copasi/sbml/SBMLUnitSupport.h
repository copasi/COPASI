// Copyright (C) 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef SBMLUNITIMPORTER_H__
#define SBMLUNITIMPORTER_H__

LIBSBML_CPP_NAMESPACE_BEGIN
class Model;
class UnitDefinition;
LIBSBML_CPP_NAMESPACE_END

#include "copasi/core/CFlags.h"

class CModel;
class CDataModel;
class SBMLIncompatibility;

class SBMLUnitSupport
{
public:
  enum struct UnitType
  {
    dimensionless,
    substance,
    time,
    volume,
    area,
    length,
    other,
    __SIZE
  };

  struct SUnitInfo
  {
    const UnitDefinition * pSBML = nullptr;
    bool allocated = false;
    std::string expression = "";
    CFlags< UnitType > type = UnitType::other;
    bool valid = false;
  };

  ~SBMLUnitSupport();

  void setLevelAndVersion(int level, int version);

  /**
   * @brief imports the units from the given sbml model
   * @param sbmlModel
   */
  void importUnitsFromSBMLDocument(Model* sbmlModel,
                                   CModel* pCopasiModel);

  const SUnitInfo & importUnit(const std::string unitId, const Model * pSBMLModel);

  const SUnitInfo & importUnit(const UnitDefinition * pUnitDefinition, const bool & allocated);

  /**
   * Validates whether SBML unit definition is derived from constraint.
   * If valid the equivalent COPASI unit expression is returned otherwise an empty string;
   *
   * @param SUnitInfo & unitInfo
   * @param const std::string & constraint
   * @return std::string copasiUnitExpression
   */
  bool validateUnit(SUnitInfo & unitInfo, const std::string & constraint) const;

  /**
   * Converts the given SBML unit to a COPASI Unit
   * @param SUnitInfo & unitInfo
   * @return bool success
   */
  bool createUnitExpressionFor(SUnitInfo & unitInfo) const;

  void checkElementUnits(const Model* pSBMLModel,
                         CModel* pCopasiModel);

  /**
   * Enhanced method to identify identical SBML unit definitions.
   * This method uses the areIdentical method from libSBML, but if the method
   * return false, it does some extra checks.
   * Right now it check for example if two volumes, one given in litre and one
   * given in cubic meters are identical.
   */
  static bool areSBMLUnitDefinitionsIdentical(const SUnitInfo & unitInfo1, const SUnitInfo & unitInfo2);

  static std::string unitKindToString(UnitKind_t kind);

  /**
   * Go through all species in the model and check if the corresponding species
   * in the SBML model has the spatialSizeUnits attribute set.
   * This attribute is not supported in SBML L2V3 and above, so we have to get
   * rid of this attribute when we export to a level equal to or higher than
   * L2V3.
   * If the attribute has the same value as the compartments units, we can just
   * delete it without changing the model, otherwise we have to give a
   * corresponding warning.
   */
  static void checkForSpatialSizeUnits(const CDataModel& dataModel, std::vector<SBMLIncompatibility>& result);

protected:
  unsigned int mLevel = 0;
  unsigned int mVersion = 0;
  bool mAvogadroSet = false;

private:
  std::map< std::string, SUnitInfo > mImportedUnits;
  const SUnitInfo * mpSubstanceUnit = nullptr;
  const SUnitInfo * mpTimeUnit = nullptr;
  const SUnitInfo * mpVolumeUnit = nullptr;
  const SUnitInfo * mpAreaUnit = nullptr;
  const SUnitInfo * mpLengthUnit = nullptr;
};

#endif // SBMLUNITIMPORTER_H__
