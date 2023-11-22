// Copyright (C) 2022 - 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include <sbml/Model.h>
#include <sbml/Compartment.h>
#include <sbml/Species.h>
#include <sbml/SpeciesReference.h>
#include <sbml/Reaction.h>

#include "copasi/sbml/SBMLUnitSupport.h"
#include "copasi/model/CModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/sbml/SBMLIncompatibility.h"

#define SBML_AVOGADRO 6.02214179e23

bool areApproximatelyEqual(double x, double y)
{
  double maxXYOne = std::max({1.0, std::fabs(x), std::fabs(y)});

  return std::fabs(x - y) <= maxXYOne * std::numeric_limits< double >::epsilon();
}

// static
std::string SBMLUnitSupport::unitKindToString(UnitKind_t kind)
{
  switch (kind)
    {
      case UNIT_KIND_AMPERE:
        return "A";

      case UNIT_KIND_AVOGADRO:
        return "Avogadro";

      case UNIT_KIND_BECQUEREL:
        return "Bq";

      case UNIT_KIND_CANDELA:
        return "cd";

      case UNIT_KIND_COULOMB:
        return "C";

      case UNIT_KIND_DIMENSIONLESS:
        return "1";

      case UNIT_KIND_FARAD:
        return "F";

      case UNIT_KIND_GRAM:
        return "g";

      case UNIT_KIND_GRAY:
        return "Gy";

      case UNIT_KIND_HENRY:
        return "H";

      case UNIT_KIND_HERTZ:
        return "Hz";

      case UNIT_KIND_ITEM:
        return "#";

      case UNIT_KIND_JOULE:
        return "J";

      case UNIT_KIND_KATAL:
        return "kat";

      case UNIT_KIND_KELVIN:
        return "K";

      case UNIT_KIND_KILOGRAM:
        return "kg";

      case UNIT_KIND_LITER:
      case UNIT_KIND_LITRE:
        return "l";

      case UNIT_KIND_LUMEN:
        return "lm";

      case UNIT_KIND_LUX:
        return "lx";

      case UNIT_KIND_METER:
      case UNIT_KIND_METRE:
        return "m";

      case UNIT_KIND_MOLE:
        return "mol";

      case UNIT_KIND_NEWTON:
        return "N";

      case UNIT_KIND_OHM:
        return "\xCE\xA9";

      case UNIT_KIND_PASCAL:
        return "Pa";

      case UNIT_KIND_RADIAN:
        return "rad";

      case UNIT_KIND_SECOND:
        return "s";

      case UNIT_KIND_SIEMENS:
        return "S";

      case UNIT_KIND_SIEVERT:
        return "Sv";

      case UNIT_KIND_STERADIAN:
        return "sr";

      case UNIT_KIND_TESLA:
        return "T";

      case UNIT_KIND_VOLT:
        return "V";

      case UNIT_KIND_WATT:
        return "W";

      case UNIT_KIND_WEBER:
        return "Wb";

      case UNIT_KIND_INVALID:
      default:
        return "";
    }
}

SBMLUnitSupport::~SBMLUnitSupport()
{
  for (std::pair< const std::string, SUnitInfo > & UnitInfo : mImportedUnits)
    if (UnitInfo.second.allocated)
      pdelete(UnitInfo.second.pSBML);
}

void SBMLUnitSupport::setLevelAndVersion(int level, int version)
{
  mLevel = level;
  mVersion = version;
}

void SBMLUnitSupport::importUnitsFromSBMLDocument(Model * sbmlModel,
    CModel * pCopasiModel)
{
  mpSubstanceUnit = nullptr;
  mpTimeUnit = nullptr;
  mpVolumeUnit = nullptr;
  mpAreaUnit = nullptr;
  mpLengthUnit = nullptr;

  /* Set standard units to match the standard units of SBML files. */

  // for SBML L3 files the default units are defined on the model
  if (mLevel > 2)
    {
      pCopasiModel->setAvogadro(SBML_AVOGADRO, CCore::Framework::Concentration);
      mAvogadroSet = true;

      // we make copies of the unit definitions so that we do not have to remember
      // if we created them or not
      std::string units;
      UnitDefinition * pUDef = NULL;
      Unit unit(sbmlModel->getLevel(), sbmlModel->getVersion());
      unit.initDefaults();

      if (sbmlModel->isSetSubstanceUnits())
        {
          units = sbmlModel->getSubstanceUnits();
          mpSubstanceUnit = &importUnit(units, sbmlModel);

          if (!mpSubstanceUnit->valid)
            {
              std::string message = "COPASI can't handle substance unit \"" + units + "\". Setting unit for substances to dimensionless.";
              CCopasiMessage(CCopasiMessage::WARNING, message.c_str());

              UnitDefinition * pUnitDefintion = new UnitDefinition(sbmlModel->getLevel(), sbmlModel->getVersion());
              pUnitDefintion->setId("dimensionless");
              unit.setKind(UNIT_KIND_DIMENSIONLESS);
              unit.setExponent(1);
              unit.setMultiplier(1.0);
              unit.setScale(0);
              pUnitDefintion->addUnit(&unit);
              mpSubstanceUnit = &importUnit(pUnitDefintion, true);
            }
        }

      if (sbmlModel->isSetTimeUnits())
        {
          units = sbmlModel->getTimeUnits();
          mpTimeUnit = &importUnit(units, sbmlModel);

          if (!mpTimeUnit->valid)
            {
              std::string message = "COPASI can't handle time unit \"" + units + "\". Setting unit for time to dimensionless.";
              CCopasiMessage(CCopasiMessage::WARNING, message.c_str());

              UnitDefinition * pUnitDefintion = new UnitDefinition(sbmlModel->getLevel(), sbmlModel->getVersion());
              pUnitDefintion->setId("dimensionless");
              unit.setKind(UNIT_KIND_DIMENSIONLESS);
              unit.setExponent(1);
              unit.setMultiplier(1.0);
              unit.setScale(0);
              pUnitDefintion->addUnit(&unit);
              mpTimeUnit = &importUnit(pUnitDefintion, true);
            }
        }

      if (sbmlModel->isSetVolumeUnits())
        {
          units = sbmlModel->getVolumeUnits();
          mpVolumeUnit = &importUnit(units, sbmlModel);

          if (!mpVolumeUnit->valid)
            {
              std::string message = "COPASI can't handle volume unit \"" + units + "\". Setting unit for volume to dimensionless.";
              CCopasiMessage(CCopasiMessage::WARNING, message.c_str());

              UnitDefinition * pUnitDefintion = new UnitDefinition(sbmlModel->getLevel(), sbmlModel->getVersion());
              pUnitDefintion->setId("dimensionless");
              unit.setKind(UNIT_KIND_DIMENSIONLESS);
              unit.setExponent(1);
              unit.setMultiplier(1.0);
              unit.setScale(0);
              pUnitDefintion->addUnit(&unit);
              mpVolumeUnit = &importUnit(pUnitDefintion, true);
            }
        }

      if (sbmlModel->isSetAreaUnits())
        {
          units = sbmlModel->getAreaUnits();
          mpAreaUnit = &importUnit(units, sbmlModel);

          if (!mpAreaUnit->valid)
            {
              std::string message = "COPASI can't handle area unit \"" + units + "\". Setting unit for area to dimensionless.";
              CCopasiMessage(CCopasiMessage::WARNING, message.c_str());

              UnitDefinition * pUnitDefintion = new UnitDefinition(sbmlModel->getLevel(), sbmlModel->getVersion());
              pUnitDefintion->setId("dimensionless");
              unit.setKind(UNIT_KIND_DIMENSIONLESS);
              unit.setExponent(1);
              unit.setMultiplier(1.0);
              unit.setScale(0);
              pUnitDefintion->addUnit(&unit);
              mpAreaUnit = &importUnit(pUnitDefintion, true);
            }
        }

      if (sbmlModel->isSetLengthUnits())
        {
          units = sbmlModel->getLengthUnits();
          mpLengthUnit = &importUnit(units, sbmlModel);

          if (!mpLengthUnit->valid)
            {
              std::string message = "COPASI can't handle length unit \"" + units + "\". Setting unit for length to dimensionless.";
              CCopasiMessage(CCopasiMessage::WARNING, message.c_str());

              UnitDefinition * pUnitDefintion = new UnitDefinition(sbmlModel->getLevel(), sbmlModel->getVersion());
              pUnitDefintion->setId("dimensionless");
              unit.setKind(UNIT_KIND_DIMENSIONLESS);
              unit.setExponent(1);
              unit.setMultiplier(1.0);
              unit.setScale(0);
              pUnitDefintion->addUnit(&unit);
              mpAreaUnit = &importUnit(pUnitDefintion, true);
            }
        }
    }
  else
    {
      if (sbmlModel->getNumUnitDefinitions() != 0)
        {
          unsigned int counter;

          for (counter = 0; counter < sbmlModel->getNumUnitDefinitions(); counter++)
            {
              UnitDefinition * uDef = sbmlModel->getUnitDefinition(counter);
              std::string unitId = uDef->getId();

              if (unitId == "substance")
                {
                  mpSubstanceUnit = &importUnit(uDef, false);
                }
              else if (unitId == "time")
                {
                  mpTimeUnit = &importUnit(uDef, false);
                }
              else if (unitId == "volume")
                {
                  mpVolumeUnit = &importUnit(uDef, false);
                }
              else if ((unitId == "area"))
                {
                  mpAreaUnit = &importUnit(uDef, false);
                }
              else if ((unitId == "length"))
                {
                  mpLengthUnit = &importUnit(uDef, false);
                }
            }
        }
    }

  // create the default units if some unit has not been specified
  if (mpSubstanceUnit == nullptr
      || !mpSubstanceUnit->valid)
    {
      if (mLevel > 2)
        {
          // issue a warning
          CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 91, "substance", "mole", "substance");
        }

      // create the default units
      UnitDefinition * pUnitDefintion = new UnitDefinition(sbmlModel->getLevel(), sbmlModel->getVersion());
      pUnitDefintion->setId("dummy_substance");
      pUnitDefintion->setName("dummy_substance");
      Unit * pUnit = pUnitDefintion->createUnit();
      pUnit->setKind(UNIT_KIND_MOLE);
      pUnit->setExponent(1);
      pUnit->setMultiplier(1.0);
      pUnit->setScale(0);

      mpSubstanceUnit = &importUnit(pUnitDefintion, true);
    }

  if (mpTimeUnit == nullptr
      || !mpTimeUnit->valid)
    {
      if (mLevel > 2)
        {
          // issue a warning
          CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 91, "time", "second", "time");
        }

      // create the default units
      UnitDefinition * pUnitDefintion = new UnitDefinition(sbmlModel->getLevel(), sbmlModel->getVersion());
      pUnitDefintion->setId("dummy_time");
      pUnitDefintion->setName("dummy_time");
      Unit * pUnit = pUnitDefintion->createUnit();
      pUnit->setKind(UNIT_KIND_SECOND);
      pUnit->setExponent(1);
      pUnit->setMultiplier(1.0);
      pUnit->setScale(0);

      mpTimeUnit = &importUnit(pUnitDefintion, true);
    }

  if (mpVolumeUnit == nullptr
      || !mpVolumeUnit->valid)
    {
      if (mLevel > 2)
        {
          // issue a warning
          CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 91, "volume", "litre", "volume");
        }

      // create the default units
      UnitDefinition * pUnitDefintion = new UnitDefinition(sbmlModel->getLevel(), sbmlModel->getVersion());
      pUnitDefintion->setId("dummy_volume");
      pUnitDefintion->setName("dummy_volume");
      Unit * pUnit = pUnitDefintion->createUnit();
      pUnit->setKind(UNIT_KIND_LITRE);
      pUnit->setExponent(1);
      pUnit->setMultiplier(1.0);
      pUnit->setScale(0);

      mpVolumeUnit = &importUnit(pUnitDefintion, true);
    }

  if (mpAreaUnit == nullptr
      || !mpAreaUnit->valid)
    {
      if (mLevel > 2)
        {
          // issue a warning
          CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 91, "area", "m^2", "area");
        }

      // create the default units
      UnitDefinition * pUnitDefintion = new UnitDefinition(sbmlModel->getLevel(), sbmlModel->getVersion());
      pUnitDefintion->setId("dummy_area");
      pUnitDefintion->setName("dummy_area");
      Unit * pUnit = pUnitDefintion->createUnit();
      pUnit->setKind(UNIT_KIND_METRE);
      pUnit->setExponent(2);
      pUnit->setMultiplier(1.0);
      pUnit->setScale(0);

      mpAreaUnit = &importUnit(pUnitDefintion, true);
    }

  if (mpLengthUnit == nullptr
      || !mpLengthUnit->valid)
    {
      if (mLevel > 2)
        {
          // issue a warning
          CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 91, "length", "m", "length");
        }

      // create the default units
      UnitDefinition * pUnitDefintion = new UnitDefinition(sbmlModel->getLevel(), sbmlModel->getVersion());
      pUnitDefintion->setId("dummy_length");
      pUnitDefintion->setName("dummy_length");
      Unit * pUnit = pUnitDefintion->createUnit();
      pUnit->setKind(UNIT_KIND_METRE);
      pUnit->setExponent(1);
      pUnit->setMultiplier(1.0);
      pUnit->setScale(0);

      mpLengthUnit = &importUnit(pUnitDefintion, true);
    }

  // now we have some common code to actually import the units

  if (mpSubstanceUnit != nullptr
      && mpSubstanceUnit->valid
      && mpSubstanceUnit->type.isSet(UnitType::substance))
    {
      pCopasiModel->setQuantityUnit(mpSubstanceUnit->expression, CCore::Framework::Concentration);

      // check if the extent units are set and if they are equal to the substance units
      // otherwise issue a warning
      if (mLevel > 2)
        {
          if (!sbmlModel->isSetExtentUnits())
            {
              CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 92);
            }
          else
            {
              const SUnitInfo & ExtentUnits = importUnit(sbmlModel->getExtentUnits(), sbmlModel);

              if (ExtentUnits.valid)
                {
                  if (!areSBMLUnitDefinitionsIdentical(*mpSubstanceUnit, ExtentUnits))
                    {
                      CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 92);
                    }
                }
              else
                {
                  // only issue warning if the extent units are actual different
                  if (sbmlModel->getExtentUnits() != sbmlModel->getSubstanceUnits())
                    {
                      CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 66, "extent", "the same units as the substances");
                    }
                }
            }
        }
    }
  else
    {
      // the unit could not be handled, give an error message and
      // set the units to mole
      CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 66, "substance", "Mole");
      pCopasiModel->setQuantityUnit("mol", CCore::Framework::Concentration);
    }

  // handle the time units
  if (mpTimeUnit != nullptr
      && mpTimeUnit->valid
      && mpTimeUnit->type.isSet(UnitType::time))
    {
      pCopasiModel->setTimeUnit(mpTimeUnit->expression);
    }
  else
    {
      // the unit could not be handled, give an error message and
      // set the units to mole
      CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 66, "time", "second");
      pCopasiModel->setTimeUnit("s");
    }

  // handle the volume units
  if (mpVolumeUnit != nullptr
      && mpVolumeUnit->valid
      && mpVolumeUnit->type.isSet(UnitType::volume))
    {
      pCopasiModel->setVolumeUnit(mpVolumeUnit->expression);
    }
  else
    {
      // the unit could not be handled, give an error message and
      // set the units to mole
      CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 66, "volume", "liter");
      pCopasiModel->setVolumeUnit("l");
    }

  // handle the area units
  if (mpAreaUnit != nullptr
      && mpAreaUnit->valid
      && mpAreaUnit->type.isSet(UnitType::area))
    {
      pCopasiModel->setAreaUnit(mpAreaUnit->expression);
    }
  else
    {
      // the unit could not be handled, give an error message and
      // set the units to mole
      CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 66, "area", "meter^2");
      pCopasiModel->setAreaUnit("m^2");
    }

  // handle the length units
  if (mpLengthUnit != nullptr
      && mpLengthUnit->valid
      && mpLengthUnit->type.isSet(UnitType::length))
    {
      pCopasiModel->setLengthUnit(mpLengthUnit->expression);
    }
  else
    {
      // the unit could not be handled, give an error message and
      // set the units to mole
      CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 66, "length", "meter");
      pCopasiModel->setLengthUnit("m");
    }

  // go through all compartments and species and check if the units are
  // consistent
  checkElementUnits(sbmlModel, pCopasiModel);
}

const SBMLUnitSupport::SUnitInfo & SBMLUnitSupport::importUnit(const std::string unitId, const Model * pSBMLModel)
{
  static const SUnitInfo Invalid;

  if (unitId.empty()
      || pSBMLModel == nullptr)
    return Invalid;

  const UnitDefinition * pExistingUnitDefinition = pSBMLModel->getUnitDefinition(unitId);

  if (pExistingUnitDefinition != nullptr)
    return importUnit(pExistingUnitDefinition, false);

  UnitDefinition * pUnitDefinition = nullptr;

  UnitKind_t UnitKind = UnitKind_forName(unitId.c_str());
  C_INT32 Dimension = 1;

  // Handle special cases
  if (UnitKind == UNIT_KIND_INVALID)
    {
      if (unitId == "volume")
        UnitKind = UNIT_KIND_LITER;
      else if (unitId == "substance")
        UnitKind = UNIT_KIND_MOLE;
      else if (unitId == "time")
        UnitKind = UNIT_KIND_SECOND;
      else if (unitId == "area")
        {
          UnitKind = UNIT_KIND_METER;
          Dimension = 2;
        }
      else if (unitId == "length")
        {
          UnitKind = UNIT_KIND_METER;
          Dimension = 1;
        }
    }

  pUnitDefinition = new UnitDefinition(pSBMLModel->getLevel(), pSBMLModel->getVersion());
  Unit * pUnit = nullptr;

  switch (UnitKind)
    {
      case UNIT_KIND_AMPERE:
        pUnitDefinition->setId("dummy_ampere");
        pUnitDefinition->setName("dummy_ampere");
        pUnit = pUnitDefinition->createUnit();
        pUnit->setKind(UNIT_KIND_AMPERE);
        pUnit->setExponent(1);
        pUnit->setMultiplier(1.0);
        pUnit->setScale(0);
        break;

      case UNIT_KIND_AVOGADRO:
        pUnitDefinition->setId("dummy_avogadro");
        pUnitDefinition->setName("dummy_avogadro");
        pUnit = pUnitDefinition->createUnit();
        pUnit->setKind(UNIT_KIND_AVOGADRO);
        pUnit->setExponent(1);
        pUnit->setMultiplier(1.0);
        pUnit->setScale(0);
        break;

      case UNIT_KIND_BECQUEREL:
        pUnitDefinition->setId("dummy_becquerel");
        pUnitDefinition->setName("dummy_becquerel");
        pUnit = pUnitDefinition->createUnit();
        pUnit->setKind(UNIT_KIND_BECQUEREL);
        pUnit->setExponent(1);
        pUnit->setMultiplier(1.0);
        pUnit->setScale(0);
        break;

      case UNIT_KIND_CANDELA:
        pUnitDefinition->setId("dummy_candela");
        pUnitDefinition->setName("dummy_candela");
        pUnit = pUnitDefinition->createUnit();
        pUnit->setKind(UNIT_KIND_CANDELA);
        pUnit->setExponent(1);
        pUnit->setMultiplier(1.0);
        pUnit->setScale(0);
        break;

      case UNIT_KIND_CELSIUS:
        pUnitDefinition->setId("dummy_celsius");
        pUnitDefinition->setName("dummy_celsius");
        pUnit = pUnitDefinition->createUnit();
        pUnit->setKind(UNIT_KIND_CELSIUS);
        pUnit->setExponent(1);
        pUnit->setMultiplier(1.0);
        pUnit->setScale(0);
        break;

      case UNIT_KIND_COULOMB:
        pUnitDefinition->setId("dummy_coulomb");
        pUnitDefinition->setName("dummy_coulomb");
        pUnit = pUnitDefinition->createUnit();
        pUnit->setKind(UNIT_KIND_COULOMB);
        pUnit->setExponent(1);
        pUnit->setMultiplier(1.0);
        pUnit->setScale(0);
        break;

      case UNIT_KIND_DIMENSIONLESS:
        pUnitDefinition->setId("dummy_dimensionless");
        pUnitDefinition->setName("dummy_dimensionless");
        pUnit = pUnitDefinition->createUnit();
        pUnit->setKind(UNIT_KIND_DIMENSIONLESS);
        pUnit->setExponent(1);
        pUnit->setMultiplier(1.0);
        pUnit->setScale(0);
        break;

      case UNIT_KIND_FARAD:
        pUnitDefinition->setId("dummy_farad");
        pUnitDefinition->setName("dummy_farad");
        pUnit = pUnitDefinition->createUnit();
        pUnit->setKind(UNIT_KIND_FARAD);
        pUnit->setExponent(1);
        pUnit->setMultiplier(1.0);
        pUnit->setScale(0);
        break;

      case UNIT_KIND_GRAM:
        pUnitDefinition->setId("dummy_gram");
        pUnitDefinition->setName("dummy_gram");
        pUnit = pUnitDefinition->createUnit();
        pUnit->setKind(UNIT_KIND_GRAM);
        pUnit->setExponent(1);
        pUnit->setMultiplier(1.0);
        pUnit->setScale(0);
        break;

      case UNIT_KIND_GRAY:
        pUnitDefinition->setId("dummy_gray");
        pUnitDefinition->setName("dummy_gray");
        pUnit = pUnitDefinition->createUnit();
        pUnit->setKind(UNIT_KIND_GRAY);
        pUnit->setExponent(1);
        pUnit->setMultiplier(1.0);
        pUnit->setScale(0);
        break;

      case UNIT_KIND_HENRY:
        pUnitDefinition->setId("dummy_henry");
        pUnitDefinition->setName("dummy_henry");
        pUnit = pUnitDefinition->createUnit();
        pUnit->setKind(UNIT_KIND_HENRY);
        pUnit->setExponent(1);
        pUnit->setMultiplier(1.0);
        pUnit->setScale(0);
        break;

      case UNIT_KIND_HERTZ:
        pUnitDefinition->setId("dummy_hertz");
        pUnitDefinition->setName("dummy_hertz");
        pUnit = pUnitDefinition->createUnit();
        pUnit->setKind(UNIT_KIND_HERTZ);
        pUnit->setExponent(1);
        pUnit->setMultiplier(1.0);
        pUnit->setScale(0);
        break;

      case UNIT_KIND_ITEM:
        pUnitDefinition->setId("dummy_item");
        pUnitDefinition->setName("dummy_item");
        pUnit = pUnitDefinition->createUnit();
        pUnit->setKind(UNIT_KIND_ITEM);
        pUnit->setExponent(1);
        pUnit->setMultiplier(1.0);
        pUnit->setScale(0);
        break;

      case UNIT_KIND_JOULE:
        pUnitDefinition->setId("dummy_joule");
        pUnitDefinition->setName("dummy_joule");
        pUnit = pUnitDefinition->createUnit();
        pUnit->setKind(UNIT_KIND_JOULE);
        pUnit->setExponent(1);
        pUnit->setMultiplier(1.0);
        pUnit->setScale(0);
        break;

      case UNIT_KIND_KATAL:
        pUnitDefinition->setId("dummy_katal");
        pUnitDefinition->setName("dummy_katal");
        pUnit = pUnitDefinition->createUnit();
        pUnit->setKind(UNIT_KIND_KATAL);
        pUnit->setExponent(1);
        pUnit->setMultiplier(1.0);
        pUnit->setScale(0);
        break;

      case UNIT_KIND_KELVIN:
        pUnitDefinition->setId("dummy_kelvin");
        pUnitDefinition->setName("dummy_kelvin");
        pUnit = pUnitDefinition->createUnit();
        pUnit->setKind(UNIT_KIND_KELVIN);
        pUnit->setExponent(1);
        pUnit->setMultiplier(1.0);
        pUnit->setScale(0);
        break;

      case UNIT_KIND_KILOGRAM:
        pUnitDefinition->setId("dummy_kilogram");
        pUnitDefinition->setName("dummy_kilogram");
        pUnit = pUnitDefinition->createUnit();
        pUnit->setKind(UNIT_KIND_KILOGRAM);
        pUnit->setExponent(1);
        pUnit->setMultiplier(1.0);
        pUnit->setScale(0);
        break;

      case UNIT_KIND_LITER:
      case UNIT_KIND_LITRE:
        pUnitDefinition->setId("dummy_volume");
        pUnitDefinition->setName("dummy_volume");
        pUnit = pUnitDefinition->createUnit();
        pUnit->setKind(UNIT_KIND_LITRE);
        pUnit->setExponent(1);
        pUnit->setMultiplier(1.0);
        pUnit->setScale(0);
        break;

      case UNIT_KIND_LUMEN:
        pUnitDefinition->setId("dummy_lumen");
        pUnitDefinition->setName("dummy_lumen");
        pUnit = pUnitDefinition->createUnit();
        pUnit->setKind(UNIT_KIND_LUMEN);
        pUnit->setExponent(1);
        pUnit->setMultiplier(1.0);
        pUnit->setScale(0);
        break;

      case UNIT_KIND_LUX:
        pUnitDefinition->setId("dummy_lux");
        pUnitDefinition->setName("dummy_lux");
        pUnit = pUnitDefinition->createUnit();
        pUnit->setKind(UNIT_KIND_LUX);
        pUnit->setExponent(1);
        pUnit->setMultiplier(1.0);
        pUnit->setScale(0);
        break;

      case UNIT_KIND_METER:
      case UNIT_KIND_METRE:
        switch (Dimension)
          {
            case 1:
              pUnitDefinition->setId("dummy_length");
              pUnitDefinition->setName("dummy_length");
              pUnit = pUnitDefinition->createUnit();
              pUnit->setKind(UNIT_KIND_METRE);
              pUnit->setExponent(1);
              pUnit->setMultiplier(1.0);
              pUnit->setScale(0);
              break;

            case 2:
              pUnitDefinition->setId("dummy_area");
              pUnitDefinition->setName("dummy_area");
              pUnit = pUnitDefinition->createUnit();
              pUnit->setKind(UNIT_KIND_METRE);
              pUnit->setExponent(2);
              pUnit->setMultiplier(1.0);
              pUnit->setScale(0);
              break;

            case 3:
              pUnitDefinition->setId("dummy_volume");
              pUnitDefinition->setName("dummy_volume");
              pUnit = pUnitDefinition->createUnit();
              pUnit->setKind(UNIT_KIND_METRE);
              pUnit->setExponent(3);
              pUnit->setMultiplier(1.0);
              pUnit->setScale(0);
              break;

            default:
              break;
          }

        break;

      case UNIT_KIND_MOLE:
        pUnitDefinition->setId("dummy_substance");
        pUnitDefinition->setName("dummy_substance");
        pUnit = pUnitDefinition->createUnit();
        pUnit->setKind(UNIT_KIND_MOLE);
        pUnit->setExponent(1);
        pUnit->setMultiplier(1.0);
        pUnit->setScale(0);
        break;

      case UNIT_KIND_NEWTON:
        pUnitDefinition->setId("dummy_newton");
        pUnitDefinition->setName("dummy_newton");
        pUnit = pUnitDefinition->createUnit();
        pUnit->setKind(UNIT_KIND_NEWTON);
        pUnit->setExponent(1);
        pUnit->setMultiplier(1.0);
        pUnit->setScale(0);
        break;

      case UNIT_KIND_OHM:
        pUnitDefinition->setId("dummy_ohm");
        pUnitDefinition->setName("dummy_ohm");
        pUnit = pUnitDefinition->createUnit();
        pUnit->setKind(UNIT_KIND_OHM);
        pUnit->setExponent(1);
        pUnit->setMultiplier(1.0);
        pUnit->setScale(0);
        break;

      case UNIT_KIND_PASCAL:
        pUnitDefinition->setId("dummy_pascal");
        pUnitDefinition->setName("dummy_pascal");
        pUnit = pUnitDefinition->createUnit();
        pUnit->setKind(UNIT_KIND_PASCAL);
        pUnit->setExponent(1);
        pUnit->setMultiplier(1.0);
        pUnit->setScale(0);
        break;

      case UNIT_KIND_RADIAN:
        pUnitDefinition->setId("dummy_radian");
        pUnitDefinition->setName("dummy_radian");
        pUnit = pUnitDefinition->createUnit();
        pUnit->setKind(UNIT_KIND_RADIAN);
        pUnit->setExponent(1);
        pUnit->setMultiplier(1.0);
        pUnit->setScale(0);
        break;

      case UNIT_KIND_SECOND:
        pUnitDefinition->setId("dummy_time");
        pUnitDefinition->setName("dummy_time");
        pUnit = pUnitDefinition->createUnit();
        pUnit->setKind(UNIT_KIND_SECOND);
        pUnit->setExponent(1);
        pUnit->setMultiplier(1.0);
        pUnit->setScale(0);
        break;

      case UNIT_KIND_SIEMENS:
        pUnitDefinition->setId("dummy_siemens");
        pUnitDefinition->setName("dummy_siemens");
        pUnit = pUnitDefinition->createUnit();
        pUnit->setKind(UNIT_KIND_SIEMENS);
        pUnit->setExponent(1);
        pUnit->setMultiplier(1.0);
        pUnit->setScale(0);
        break;

      case UNIT_KIND_SIEVERT:
        pUnitDefinition->setId("dummy_sievert");
        pUnitDefinition->setName("dummy_sievert");
        pUnit = pUnitDefinition->createUnit();
        pUnit->setKind(UNIT_KIND_SIEVERT);
        pUnit->setExponent(1);
        pUnit->setMultiplier(1.0);
        pUnit->setScale(0);
        break;

      case UNIT_KIND_STERADIAN:
        pUnitDefinition->setId("dummy_steradian");
        pUnitDefinition->setName("dummy_steradian");
        pUnit = pUnitDefinition->createUnit();
        pUnit->setKind(UNIT_KIND_STERADIAN);
        pUnit->setExponent(1);
        pUnit->setMultiplier(1.0);
        pUnit->setScale(0);
        break;

      case UNIT_KIND_TESLA:
        pUnitDefinition->setId("dummy_tesla");
        pUnitDefinition->setName("dummy_tesla");
        pUnit = pUnitDefinition->createUnit();
        pUnit->setKind(UNIT_KIND_TESLA);
        pUnit->setExponent(1);
        pUnit->setMultiplier(1.0);
        pUnit->setScale(0);
        break;

      case UNIT_KIND_VOLT:
        pUnitDefinition->setId("dummy_volt");
        pUnitDefinition->setName("dummy_volt");
        pUnit = pUnitDefinition->createUnit();
        pUnit->setKind(UNIT_KIND_VOLT);
        pUnit->setExponent(1);
        pUnit->setMultiplier(1.0);
        pUnit->setScale(0);
        break;

      case UNIT_KIND_WATT:
        pUnitDefinition->setId("dummy_watt");
        pUnitDefinition->setName("dummy_watt");
        pUnit = pUnitDefinition->createUnit();
        pUnit->setKind(UNIT_KIND_WATT);
        pUnit->setExponent(1);
        pUnit->setMultiplier(1.0);
        pUnit->setScale(0);
        break;

      case UNIT_KIND_WEBER:
        pUnitDefinition->setId("dummy_weber");
        pUnitDefinition->setName("dummy_weber");
        pUnit = pUnitDefinition->createUnit();
        pUnit->setKind(UNIT_KIND_WEBER);
        pUnit->setExponent(1);
        pUnit->setMultiplier(1.0);
        pUnit->setScale(0);
        break;

      case UNIT_KIND_INVALID:
        break;
    }

  return importUnit(pUnitDefinition, true);
}

const SBMLUnitSupport::SUnitInfo & SBMLUnitSupport::importUnit(const UnitDefinition * pUnitDefinition, const bool & allocated)
{
  static const SUnitInfo Invalid;

  if (pUnitDefinition == nullptr)
    return Invalid;

  SUnitInfo & UnitInfo = mImportedUnits[pUnitDefinition->getId()];

  // Check whther we already imported the unit;
  if (UnitInfo.pSBML != nullptr)
    return UnitInfo;

  UnitInfo.pSBML = pUnitDefinition;
  UnitInfo.valid = createUnitExpressionFor(UnitInfo);

  if (UnitInfo.valid)
    {
      if (validateUnit(UnitInfo, "#"))
        UnitInfo.type |= UnitType::substance;

      if (validateUnit(UnitInfo, "s"))
        UnitInfo.type |= UnitType::time;

      if (validateUnit(UnitInfo, "m"))
        UnitInfo.type |= UnitType::length;

      if (validateUnit(UnitInfo, "m^2"))
        UnitInfo.type |= UnitType::area;

      if (validateUnit(UnitInfo, "m^3"))
        UnitInfo.type |= UnitType::volume;

      if (CUnit(UnitInfo.expression).isDimensionless())
        UnitInfo.type |= UnitType::dimensionless;
    }

  return UnitInfo;
}

bool SBMLUnitSupport::validateUnit(SBMLUnitSupport::SUnitInfo & unitInfo, const std::string & constraint) const
{
  if (createUnitExpressionFor(unitInfo))
    {
      CUnit Unit(unitInfo.expression);
      CUnit Constraint(constraint);

      if (Constraint.isEquivalent(Unit) || Unit.isDimensionless())
        return true;
    }

  return false;
}

void SBMLUnitSupport::checkElementUnits(const Model * pSBMLModel, CModel * pCopasiModel)
{
  unsigned int i, iMax = pSBMLModel->getNumCompartments();
  const SUnitInfo * pSubstanceUnit = nullptr;
  const SUnitInfo * pTimeUnit = nullptr;
  const SUnitInfo * pVolumeUnit = nullptr;
  const SUnitInfo * pAreaUnit = nullptr;
  const SUnitInfo * pLengthUnit = nullptr;
  const SUnitInfo * pDimensionlessUnit = nullptr;
  std::vector< std::string > nonDefaultCompartmentsVolume;
  std::vector< std::string > nonDefaultCompartmentsArea;
  std::vector< std::string > nonDefaultCompartmentsLength;
  std::vector< std::string > nonDefaultCompartmentsDimensionless;
  std::vector< std::string > nonDefaultSpecies;
  std::vector< std::string > nonDefaultKineticTime;
  std::vector< std::string > nonDefaultKineticSubstance;
  std::vector< std::string > nonDefaultEventTime;
  const Compartment * pCompartment;
  const Species * pSpecies;
  const Reaction * pReaction;
  const KineticLaw * pKineticLaw;
  std::string lastVolumeUnit;
  std::string lastAreaUnit;
  std::string lastLengthUnit;
  std::string lastDimensionlessUnit;
  bool inconsistentVolumeUnits = false;
  bool inconsistentAreaUnits = false;
  bool inconsistentLengthUnits = false;
  bool inconsistentDimensionlessUnits = false;
  bool defaultVolumeUsed = false;
  bool defaultAreaUsed = false;
  bool defaultLengthUsed = false;

  for (i = 0; i < iMax; ++i)
    {
      pCompartment = pSBMLModel->getCompartment(i);

      if (areApproximatelyEqual(pCompartment->getSpatialDimensionsAsDouble(), 3.0))
        {
          if (pCompartment->isSetUnits())
            {
              std::string unitId = pCompartment->getUnits();
              const SUnitInfo & UnitInfo = importUnit(unitId, pSBMLModel);

              if (UnitInfo.type.isSet(UnitType::volume))
                {
                  if (pVolumeUnit == nullptr)
                    pVolumeUnit = &UnitInfo;

                  if (mpVolumeUnit == nullptr
                      || !mpVolumeUnit->valid)
                    {
                      mpVolumeUnit = &UnitInfo;
                      pCopasiModel->setVolumeUnit(UnitInfo.expression);
                    }

                  if (mpVolumeUnit && !areSBMLUnitDefinitionsIdentical(*mpVolumeUnit, UnitInfo))
                    {
                      nonDefaultCompartmentsVolume.push_back(pCompartment->getId());
                    }

                  if (pVolumeUnit && !areSBMLUnitDefinitionsIdentical(*pVolumeUnit, UnitInfo))
                    {
                      inconsistentVolumeUnits = true;
                    }
                }
              else
                {
                  // warning message
                  CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 103, pCompartment->getId().c_str(), pCompartment->getSpatialDimensionsAsDouble(), UnitInfo.expression.c_str());
                }
            }
        }
      else if (areApproximatelyEqual(pCompartment->getSpatialDimensionsAsDouble(), 2.0))
        {
          if (pCompartment->isSetUnits())
            {
              std::string unitId = pCompartment->getUnits();
              const SUnitInfo & UnitInfo = importUnit(unitId, pSBMLModel);

              if (UnitInfo.type.isSet(UnitType::area))
                {
                  if (pAreaUnit == nullptr)
                    pAreaUnit = &UnitInfo;

                  if (mpAreaUnit == nullptr
                      || !mpAreaUnit->valid)
                    {
                      mpAreaUnit = &UnitInfo;
                      pCopasiModel->setAreaUnit(UnitInfo.expression);
                    }

                  if (mpAreaUnit && !areSBMLUnitDefinitionsIdentical(*mpAreaUnit, UnitInfo))
                    {
                      nonDefaultCompartmentsArea.push_back(pCompartment->getId());
                    }

                  if (pAreaUnit && !areSBMLUnitDefinitionsIdentical(*pAreaUnit, UnitInfo))
                    {
                      inconsistentAreaUnits = true;
                    }
                }
              else
                {
                  // warning message
                  CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 103, pCompartment->getId().c_str(), pCompartment->getSpatialDimensionsAsDouble(), UnitInfo.expression.c_str());
                }
            }
        }
      else if (areApproximatelyEqual(pCompartment->getSpatialDimensionsAsDouble(), 1.0))
        {
          if (pCompartment->isSetUnits())
            {
              std::string unitId = pCompartment->getUnits();
              const SUnitInfo & UnitInfo = importUnit(unitId, pSBMLModel);

              if (UnitInfo.type.isSet(UnitType::length))
                {
                  if (pLengthUnit == nullptr)
                    pLengthUnit = &UnitInfo;

                  if (mpLengthUnit == nullptr
                      || !mpLengthUnit->valid)
                    {
                      mpLengthUnit = &UnitInfo;
                      pCopasiModel->setLengthUnit(UnitInfo.expression);
                    }

                  if (mpLengthUnit  && !areSBMLUnitDefinitionsIdentical(*mpLengthUnit, UnitInfo))
                    {
                      nonDefaultCompartmentsLength.push_back(pCompartment->getId());
                    }

                  if (pLengthUnit && !areSBMLUnitDefinitionsIdentical(*pLengthUnit, UnitInfo))
                    {
                      inconsistentLengthUnits = true;
                    }
                }
              else
                {
                  // warning message
                  CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 103, pCompartment->getId().c_str(), pCompartment->getSpatialDimensionsAsDouble(), UnitInfo.expression.c_str());
                }
            }
        }
      else
        {
          if (pCompartment->isSetUnits())
            {
              std::string unitId = pCompartment->getUnits();
              const SUnitInfo & UnitInfo = importUnit(unitId, pSBMLModel);

              if (UnitInfo.type.isSet(UnitType::dimensionless))
                {
                  if (pDimensionlessUnit == nullptr)
                    pDimensionlessUnit = &UnitInfo;

                  if (pDimensionlessUnit != nullptr
                      && !areSBMLUnitDefinitionsIdentical(*pDimensionlessUnit, UnitInfo))
                    {
                      inconsistentDimensionlessUnits = true;
                    }
                }
              else
                {
                  // warning message
                  CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 103, pCompartment->getId().c_str(), pCompartment->getSpatialDimensionsAsDouble(), UnitInfo.expression.c_str());
                }
            }
        }
    }

  if (!inconsistentVolumeUnits
      && pVolumeUnit != nullptr
      && !nonDefaultCompartmentsVolume.empty())
    {
      mpVolumeUnit = pVolumeUnit;
      pCopasiModel->setVolumeUnit(pVolumeUnit->expression);
      nonDefaultCompartmentsVolume.clear();
    }

  if (!inconsistentAreaUnits
      && pAreaUnit != nullptr
      && !nonDefaultCompartmentsArea.empty())
    {
      mpAreaUnit = pAreaUnit;
      pCopasiModel->setAreaUnit(pAreaUnit->expression);
      nonDefaultCompartmentsArea.clear();
    }

  if (!inconsistentLengthUnits
      && pLengthUnit != nullptr
      && !nonDefaultCompartmentsLength.empty())
    {
      mpLengthUnit = pLengthUnit;
      pCopasiModel->setLengthUnit(pLengthUnit->expression);
      nonDefaultCompartmentsLength.clear();
    }

  // warn about inconsistent units and that they have been ignored and
  // report the actual units used
  // one warning for every entry in nonDefaultCompartment
  {
    std::ostringstream os;

    for (const std::string & entity : nonDefaultCompartmentsVolume)
      {
        os << entity << ", ";
      }

    for (const std::string & entity : nonDefaultCompartmentsArea)
      {
        os << entity << ", ";
      }

    for (const std::string & entity : nonDefaultCompartmentsLength)
      {
        os << entity << ", ";
      }

    std::string message = os.str();

    if (!message.empty())
      {
        CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 24, message.substr(0, message.size() - 2).c_str());
      }
  }

  bool inconsistentUnits = false;
  std::string lastUnit;

  iMax = pSBMLModel->getNumSpecies();

  for (i = 0; i < iMax; ++i)
    {
      pSpecies = pSBMLModel->getSpecies(i);

      if (mLevel < 2 || (mLevel == 2 && mVersion < 3))
        {
          // check the isSetSpatialSizeUnits flag for models prior to L2V3.
          if (pSpecies->isSetSpatialSizeUnits() == true)
            {
              // check if the spatialSizeUnits is consistent with the
              // pVolumeUnits, pAreaUnits, pLengthUnits or pDimensionlessUnits
              // first we need to find the entity
              pCompartment = pSBMLModel->getCompartment(pSpecies->getCompartment());
              std::string spatialSizeUnits = pSpecies->getSpatialSizeUnits();
              const SUnitInfo & UnitInfo = importUnit(spatialSizeUnits, pSBMLModel);

              if (!UnitInfo.valid)
                {
                  CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 104, "species", pSpecies->getId().c_str(), "spatial size", spatialSizeUnits.c_str());
                }

              if (areApproximatelyEqual(pCompartment->getSpatialDimensionsAsDouble(), 3.0))
                {
                  if (mpVolumeUnit != nullptr
                      && !areSBMLUnitDefinitionsIdentical(*mpVolumeUnit, UnitInfo))
                    CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 19, pSpecies->getId().c_str());
                }
              else if (areApproximatelyEqual(pCompartment->getSpatialDimensionsAsDouble(), 2.0))
                {
                  if (mpAreaUnit != nullptr
                      && !areSBMLUnitDefinitionsIdentical(*mpAreaUnit, UnitInfo))
                    CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 19, pSpecies->getId().c_str());
                }
              else if (areApproximatelyEqual(pCompartment->getSpatialDimensionsAsDouble(), 1.0))
                {
                  if (mpLengthUnit != nullptr
                      && !areSBMLUnitDefinitionsIdentical(*mpLengthUnit, UnitInfo))
                    CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 19, pSpecies->getId().c_str());
                }
              else
                {
                  if (pDimensionlessUnit != nullptr
                      && !areSBMLUnitDefinitionsIdentical(*pDimensionlessUnit, UnitInfo))
                    CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 19, pSpecies->getId().c_str());
                }
            }
        }

      if (pSpecies->isSetUnits())
        {
          std::string unitId = pSpecies->getUnits();
          const SUnitInfo & UnitInfo = importUnit(unitId, pSBMLModel);

          if (UnitInfo.type.isSet(UnitType::substance))
            {
              if (pSubstanceUnit == nullptr)
                pSubstanceUnit = &UnitInfo;

              if (mpSubstanceUnit == nullptr
                  || !mpSubstanceUnit->valid)
                {
                  mpSubstanceUnit = &UnitInfo;
                  pCopasiModel->setQuantityUnit(UnitInfo.expression, CCore::Framework::Concentration);
                }

              if (mpSubstanceUnit != nullptr
                  && !areSBMLUnitDefinitionsIdentical(*mpSubstanceUnit, UnitInfo))
                {
                  nonDefaultSpecies.push_back(pSpecies->getId());
                }

              if (pSubstanceUnit != nullptr
                  && !areSBMLUnitDefinitionsIdentical(*pSubstanceUnit, UnitInfo))
                {
                  inconsistentUnits = true;
                }
            }
        }
    }

  if (!inconsistentUnits && pSubstanceUnit != nullptr
      && !nonDefaultSpecies.empty())
    {
      mpSubstanceUnit = pSubstanceUnit;
      pCopasiModel->setQuantityUnit(pSubstanceUnit->expression, CCore::Framework::Concentration);
      nonDefaultSpecies.clear();
    }

  // warn about inconsistent units and that they have been ignored and
  // report the actual units used
  // one warning for every entry in nonDefaultCompartment
  {
    std::ostringstream os;

    for (const std::string & entity : nonDefaultSpecies)
      {
        os << entity << ", ";
      }

    std::string message = os.str();

    if (!message.empty())
      {
        CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 25, message.substr(0, message.size() - 2).c_str());
      }
  }

  inconsistentUnits = false;
  bool inconsistentTimeUnits = false;
  std::string lastTimeUnits;
  iMax = pSBMLModel->getNumReactions();

  for (i = 0; i < iMax; ++i)
    {
      pReaction = pSBMLModel->getReaction(i);
      pKineticLaw = pReaction->getKineticLaw();

      if (pKineticLaw != nullptr)
        {
          std::string unitId;

          if (pKineticLaw->isSetSubstanceUnits())
            {
              unitId = pKineticLaw->getSubstanceUnits();
              const SUnitInfo & UnitInfo = importUnit(unitId, pSBMLModel);

              if (UnitInfo.type.isSet(UnitType::substance))
                {
                  if (pSubstanceUnit == nullptr)
                    pSubstanceUnit = &UnitInfo;

                  if (mpSubstanceUnit == nullptr
                      || !mpSubstanceUnit->valid)
                    {
                      mpSubstanceUnit = &UnitInfo;
                      pCopasiModel->setQuantityUnit(UnitInfo.expression, CCore::Framework::Concentration);
                    }

                  if (!areSBMLUnitDefinitionsIdentical(*mpSubstanceUnit, UnitInfo))
                    {
                      nonDefaultKineticSubstance.push_back(pReaction->getId());
                    }

                  if (!areSBMLUnitDefinitionsIdentical(*pSubstanceUnit, UnitInfo))
                    {
                      inconsistentUnits = true;
                    }
                }
              else
                {
                  // error message
                  CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 104, "kinetic law of the reaction", pReaction->getId().c_str(), "substance", unitId.c_str());
                }
            }

          if (pKineticLaw->isSetTimeUnits())
            {
              unitId = pKineticLaw->getTimeUnits();
              const SUnitInfo & UnitInfo = importUnit(unitId, pSBMLModel);

              if (UnitInfo.type.isSet(UnitType::time))
                {
                  if (pTimeUnit == nullptr)
                    pTimeUnit = &UnitInfo;

                  if (mpTimeUnit == nullptr
                      || !mpTimeUnit->valid)
                    {
                      mpTimeUnit = &UnitInfo;
                      pCopasiModel->setTimeUnit(UnitInfo.expression);
                    }

                  if (mpTimeUnit != nullptr
                      && !areSBMLUnitDefinitionsIdentical(*mpTimeUnit, UnitInfo))
                    {
                      nonDefaultKineticTime.push_back(pReaction->getId());
                    }

                  if (pTimeUnit != nullptr
                      && !areSBMLUnitDefinitionsIdentical(*pTimeUnit, UnitInfo))
                    {
                      inconsistentTimeUnits = true;
                    }
                }
              else
                {
                  // error message
                  CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 104, "kinetic law of the reaction", pReaction->getId().c_str(), "time", unitId.c_str());
                }
            }
        }
    }

  if (!inconsistentUnits && pSubstanceUnit != nullptr
      && !nonDefaultKineticSubstance.empty())
    {
      mpSubstanceUnit = pSubstanceUnit;
      pCopasiModel->setQuantityUnit(pSubstanceUnit->expression, CCore::Framework::Concentration);
      nonDefaultKineticSubstance.clear();
    }

  // warn about inconsistent units and that they have been ignored and
  // report the actual units used
  // one warning for every entry in nonDefaultCompartment
  {
    std::ostringstream os;

    for (const std::string & entity : nonDefaultKineticSubstance)
      {
        os << entity << ", ";
      }

    std::string message = os.str();

    if (!message.empty())
      {
        CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 44, message.substr(0, message.size() - 2).c_str());
      }
  }

  if (!inconsistentTimeUnits && pTimeUnit != nullptr
      && !nonDefaultKineticTime.empty())
    {
      mpTimeUnit = pTimeUnit;
      pCopasiModel->setTimeUnit(pTimeUnit->expression);
      nonDefaultKineticTime.clear();
    }

  // warn about inconsistent units and that they have been ignored and
  // report the actual units used
  // one warning for every entry in nonDefaultCompartment
  {
    std::ostringstream os;

    for (const std::string & entity : nonDefaultKineticTime)
      {
        os << entity << ", ";
      }

    std::string message = os.str();

    if (!message.empty())
      {
        CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 53, message.substr(0, message.size() - 2).c_str());
      }
  }

  const Event * pEvent = NULL;
  inconsistentTimeUnits = false;
  iMax = pSBMLModel->getNumEvents();

  for (i = 0; i < iMax; ++i)
    {
      pEvent = pSBMLModel->getEvent(i);
      std::string unitId;

      if (pEvent->isSetTimeUnits())
        {
          unitId = pEvent->getTimeUnits();
          const SUnitInfo & UnitInfo = importUnit(unitId, pSBMLModel);

          if (UnitInfo.type.isSet(UnitType::time))
            {
              if (pTimeUnit == nullptr)
                pTimeUnit = &UnitInfo;

              if (mpTimeUnit == nullptr
                  || !mpTimeUnit->valid)
                {
                  mpTimeUnit = &UnitInfo;
                  pCopasiModel->setTimeUnit(UnitInfo.expression);
                }

              if (mpTimeUnit != nullptr
                  && !areSBMLUnitDefinitionsIdentical(*mpTimeUnit, UnitInfo))
                {
                  nonDefaultEventTime.push_back(pEvent->getId());
                }

              if (pTimeUnit != nullptr
                  && !areSBMLUnitDefinitionsIdentical(*pTimeUnit, UnitInfo))
                {
                  inconsistentTimeUnits = true;
                }
            }
          else if (!unitId.empty())
            {
              // error message
              CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 104, "event", pEvent->getId().c_str(), "time", unitId.c_str());
            }
        }
    }

  if (!inconsistentTimeUnits && pTimeUnit != nullptr
      && !nonDefaultEventTime.empty())
    {
      mpTimeUnit = pTimeUnit;
      pCopasiModel->setTimeUnit(pTimeUnit->expression);
      nonDefaultEventTime.clear();
    }

  // warn about inconsistent units and that they have been ignored and
  // report the actual units used
  // one warning for every entry in nonDefaultCompartment
  {
    std::ostringstream os;

    for (const std::string & entity : nonDefaultEventTime)
      {
        os << entity << ", ";
      }

    std::string message = os.str();

    if (!message.empty())
      {
        CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 53, message.substr(0, message.size() - 2).c_str());
      }
  }
}

bool SBMLUnitSupport::createUnitExpressionFor(SUnitInfo & unitInfo) const
{
  if (unitInfo.pSBML == nullptr)
    return false;

  // otherwise
  CUnit copasiUnit("1");

  for (unsigned int i = 0; i < unitInfo.pSBML->getNumUnits(); ++i)
    {
      const Unit * current = unitInfo.pSBML->getUnit(i);
      std::string symbol = unitKindToString(current->getKind());

      // skip invalid / unsupported
      if (symbol.empty())
        continue;

      double multiplier = current->getMultiplier();
      double exponent = current->getExponentAsDouble();
      double scale = current->getScale();

      if (symbol == "1" && i == 0)
        {
          copasiUnit.setDimensionLess(multiplier, scale, exponent);
          continue;
        }

      if (symbol == "s" && multiplier == 86400)
        {
          symbol = "d";
          multiplier = 1;
        }
      else if (symbol == "s" && multiplier == 3600)
        {
          symbol = "h";
          multiplier = 1;
        }
      else if (symbol == "s" && multiplier == 60)
        {
          symbol = "min";
          multiplier = 1;
        }

      CUnit tmp = CUnit(symbol).exponentiate(current->getExponentAsDouble());

      tmp.addComponent(
        CUnitComponent(
          CBaseUnit::dimensionless,
          areApproximatelyEqual(exponent, 0.0) ? 1.0 : pow(multiplier, exponent),
          areApproximatelyEqual(exponent, 0.0) ? 0.0 : current->getScale() * exponent));

      tmp.buildExpression();
      tmp.compile();

      copasiUnit = copasiUnit * tmp;
    }

  copasiUnit.buildExpression();
  unitInfo.expression = copasiUnit.getExpression();

  // return whether the expression is valid
  return unitInfo.expression != "?";
}

/**
 * Enhanced method to identify identical sbml unit definitions.
 * The method first converts the unit definitions to SI units and simplifies
 * them, only then they are compared.
 */
bool SBMLUnitSupport::areSBMLUnitDefinitionsIdentical(const SBMLUnitSupport::SUnitInfo & unitInfo1, const SBMLUnitSupport::SUnitInfo & unitInfo2)
{
  if (unitInfo1.valid != unitInfo2.valid
      || unitInfo1.type != unitInfo2.type)
    return false;

  // We have two invalid units which are equal.
  if (unitInfo1.valid == false)
    return true;

  if (unitInfo1.pSBML == unitInfo2.pSBML)
    return true;

  UnitDefinition * pTmpUdef1 = UnitDefinition::convertToSI(unitInfo1.pSBML);
  UnitDefinition::simplify(pTmpUdef1);
  UnitDefinition * pTmpUdef2 = UnitDefinition::convertToSI(unitInfo2.pSBML);
  UnitDefinition::simplify(pTmpUdef2);

  bool result = UnitDefinition::areIdentical(pTmpUdef1, pTmpUdef2);

  if (result == false)
    {
      // check if maybe everything is the same, only the multipliers are
      // somewhat off due to rounding errors
      bool newResult = true;

      if (pTmpUdef1->getNumUnits() == pTmpUdef2->getNumUnits())
        {
          UnitDefinition::reorder(pTmpUdef1);
          UnitDefinition::reorder(pTmpUdef2);
          unsigned int i = 0, iMax = pTmpUdef1->getNumUnits();

          // we have to reset i to 0
          i = 0;
          const Unit *pU1, *pU2;

          while (newResult == true && i != iMax)
            {
              pU1 = pTmpUdef1->getUnit(i);
              pU2 = pTmpUdef2->getUnit(i);

              if (pU1->getKind() != pU2->getKind() || pU1->getExponent() != pU2->getExponent() || pU1->getScale() != pU2->getScale() || !areApproximatelyEqual(pU2->getMultiplier(), pU1->getMultiplier()))
                {
                  newResult = false;
                }

              ++i;
            }

          result = newResult;
        }
    }

  delete pTmpUdef1;
  delete pTmpUdef2;
  return result;
}

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
// static
void SBMLUnitSupport::checkForSpatialSizeUnits(const CDataModel & dataModel, std::vector< SBMLIncompatibility > & result)
{
  const SBMLDocument * pSBMLDocument = const_cast< CDataModel & >(dataModel).getCurrentSBMLDocument();

  if (pSBMLDocument != nullptr)
    {
      // check all species in the model if they have a spatial size attribute set
      // and if it is identical to the unit of the compartment the species is in
      const CModel * pModel = dataModel.getModel();

      if (pModel != nullptr)
        {
          CDataVector< CMetab >::const_iterator it = pModel->getMetabolites().begin(), endit = pModel->getMetabolites().end();
          std::set< std::string > badSpecies;
          const std::map< const CDataObject *, SBase * > & copasi2sbmlmap = const_cast< CDataModel & >(dataModel).getCopasi2SBMLMap();
          std::map< const CDataObject *, SBase * >::const_iterator pos;
          const Species * pSBMLSpecies = NULL;
          std::string spatialSizeUnits;

          SBMLUnitSupport UnitImporter;
          UnitImporter.setLevelAndVersion(pSBMLDocument->getLevel(), pSBMLDocument->getVersion());

          while (it != endit)
            {
              pos = copasi2sbmlmap.find(it);

              if (pos != copasi2sbmlmap.end())
                {
                  // check for the spatial size units attribute
                  pSBMLSpecies = dynamic_cast< const Species * >(pos->second);
                  assert(pSBMLSpecies != nullptr);

                  if (pSBMLSpecies == NULL)
                    continue;

                  if (pSBMLSpecies->isSetSpatialSizeUnits())
                    {
                      spatialSizeUnits = pSBMLSpecies->getSpatialSizeUnits();
                      const SBMLUnitSupport::SUnitInfo * pSpeciesUnitInfo = &UnitImporter.importUnit(spatialSizeUnits, pSBMLDocument->getModel());

                      // check if the units are the same as the one on the species
                      // compartment
                      const Compartment * pCompartment = pSBMLDocument->getModel()->getCompartment(pSBMLSpecies->getCompartment());
                      const SBMLUnitSupport::SUnitInfo * pCompartmentUnitInfo = NULL;

                      if (pCompartment != nullptr)
                        {
                          if (pCompartment->isSetUnits())
                            {
                              assert(pSBMLDocument->getModel() != nullptr);

                              if (pSBMLDocument->getModel() != nullptr)
                                {
                                  pCompartmentUnitInfo = &UnitImporter.importUnit(pCompartment->getUnits(), pSBMLDocument->getModel());
                                }
                            }
                          else
                            {
                              // the compartment has the default units associated with the
                              // symbol length , area or volume depending on the spatial size
                              // of the compartment
                              assert(pSBMLDocument->getModel() != nullptr);

                              if (pSBMLDocument->getModel() != nullptr)
                                {
                                  switch (pCompartment->getSpatialDimensions())
                                    {
                                      case 0:
                                        // the species is not allowed to have a
                                        // spatialDimensionsUnit attribute
                                        CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 83, pSBMLSpecies->getId().c_str());
                                        break;

                                      case 1:
                                        pCompartmentUnitInfo = &UnitImporter.importUnit("length", pSBMLDocument->getModel());
                                        break;

                                      case 2:
                                        pCompartmentUnitInfo = &UnitImporter.importUnit("area", pSBMLDocument->getModel());
                                        break;

                                      case 3:
                                        pCompartmentUnitInfo = &UnitImporter.importUnit("volume", pSBMLDocument->getModel());
                                        break;

                                      default:
                                        CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 82, pCompartment->getId().c_str());
                                        break;
                                    }
                                }
                            }

                          if (pCompartmentUnitInfo->valid && pSpeciesUnitInfo->valid)
                            {
                              // compare the two unit definitions
                              if (!UnitImporter.areSBMLUnitDefinitionsIdentical(*pCompartmentUnitInfo, *pSpeciesUnitInfo))
                                {
                                  // add the species to bad species
                                  badSpecies.insert(pSBMLSpecies->getId());
                                }
                            }
                        }
                    }
                }

              ++it;
            }

          if (!badSpecies.empty())
            {
              // create the incompatibility message
              std::ostringstream os;
              std::set< std::string >::const_iterator sit = badSpecies.begin(), sendit = badSpecies.end();

              while (sit != sendit)
                {
                  os << *sit << ", ";
                  ++sit;
                }

              result.push_back(SBMLIncompatibility(2, os.str().substr(0, os.str().size() - 2).c_str()));
            }
        }
    }
}
