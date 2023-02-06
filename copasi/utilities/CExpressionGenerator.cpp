// Copyright (C) 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "CExpressionGenerator.h"

#include <sstream>

#include <copasi/model/CModel.h>

// static
const CEnumAnnotation< std::string, CExpressionGenerator::Operation > CExpressionGenerator::OperationNames(
{
  "Sum",
  "Sum of Squares",
  "Sum of Absolutes",
  "Product"
}
);

// static
const CEnumAnnotation< CExpressionGenerator::sOperation, CExpressionGenerator::Operation > CExpressionGenerator::OperationParts(
{
  sOperation(" + ", "", "", "", ""),
  sOperation(" + ", "", "", "", "^2"),
  sOperation(" + ", "", "", "ABS(", ")"),
  sOperation(" * ", "", "", "", "")
}
);

// static
std::vector< std::string > CExpressionGenerator::mSupportedTypes =
{
  "Global Quantities",
  "Species",
  "Reactions",
  "Compartments",
};

// static
std::string CExpressionGenerator::escapeDisplayName(const CDataObject * pObject)
{
  std::string name = pObject->getObjectDisplayName();
  // We need to escape >
  std::string::size_type pos = name.find_first_of("}");

  while (pos != std::string::npos)
    {
      name.insert(pos, "\\");
      pos += 2;
      pos = name.find_first_of("}", pos);
    }

  return name;
}

CExpressionGenerator::CExpressionGenerator(
  const std::string & type,
  const std::string & selection,
  const std::string & operation)
  : CDataObject("ExpressionGenerator")
  , mType(type)
  , mSelection(selection)
  , mOperation(OperationNames.toEnum(operation))
{}

// static
std::vector< std::string > CExpressionGenerator::getSupportedOperations()
{
  return OperationNames.annotations();
}

bool CExpressionGenerator::isTypeSupported(const std::string & type)
{
  return std::find(mSupportedTypes.begin(), mSupportedTypes.end(), type) != mSupportedTypes.end();
}

std::vector< const CDataObject * > CExpressionGenerator::getObjectsForSelection(const CModel * pModel) const
{
  std::vector< const CDataObject * > result;

  if (!pModel)
    return result;

  if (mType == "Species")
    {
      for (auto & metab : pModel->getMetabolites())
        {
          if (mSelection == "Rates (Particle Numbers)")
            result.push_back(metab.getRateReference());

          if (mSelection == "Rates (Concentrations)")
            result.push_back(metab.getConcentrationRateReference());

          if (mSelection == "Transient Particle Numbers")
            result.push_back(metab.getValueReference());

          if (mSelection == "Transient Concentrations")
            result.push_back(metab.getConcentrationReference());

          if (mSelection == "Initial Particle Numbers")
            result.push_back(metab.getInitialValueReference());

          if (mSelection == "Initial Concentrations")
            result.push_back(metab.getInitialConcentrationReference());
        }
    }

  if (mType == "Global Quantities")
    {
      for (auto & mv : pModel->getModelValues())
        {
          if (mSelection == "Rates")
            result.push_back(mv.getRateReference());

          if (mSelection == "Transient Values")
            result.push_back(mv.getValueReference());

          if (mSelection == "Initial Values")
            result.push_back(mv.getInitialValueReference());
        }
    }

  if (mType == "Compartments")
    {
      for (auto & comp : pModel->getCompartments())
        {
          if (mSelection == "Rates")
            result.push_back(comp.getRateReference());

          if (mSelection == "Transient Volumes")
            result.push_back(comp.getValueReference());

          if (mSelection == "Initial Volumes")
            result.push_back(comp.getInitialValueReference());
        }
    }

  if (mType == "Reactions")
    {
      for (auto & reaction : pModel->getReactions())
        {
          if (mSelection == "Fluxes (Particle Numbers)")
            result.push_back(reaction.getParticleFluxReference());

          if (mSelection == "Fluxes (Amount)")
            result.push_back(reaction.getFluxReference());
        }
    }

  return result;
}

std::string CExpressionGenerator::generateExpressionFor(const CModel * pModel, bool useCn) const
{
  if (!pModel)
    return std::string();

  return generate(mOperation, getObjectsForSelection(pModel), useCn);
}

std::string CExpressionGenerator::generate(Operation operation, const std::vector< const CDataObject * > & objects, bool useCn)
{
  const sOperation & parts = OperationParts[operation];

  if (objects.empty())
    return std::string();

  const CDataObject * entry = *objects.begin();

  std::stringstream result;
  result << parts.surroundStart;

  result << parts.entryStart;

  if (useCn)
    result << "<" << entry->getCN() << ">";
  else
    result << "{" << escapeDisplayName(entry) << "}";

  result << parts.entryEnd;

  for (int i = 1; i < objects.size(); ++i)
    {
      entry = objects[i];

      result << parts.join;
      result << parts.entryStart;

      if (useCn)
        result << "<" << entry->getCN() << ">";
      else
        result << "{" << escapeDisplayName(entry) << "}";

      result << parts.entryEnd;
    }

  result << parts.surroundEnd;

  return result.str();
}

void CExpressionGenerator::setType(const std::string & type)
{
  mType = type;
}

void CExpressionGenerator::setSelection(const std::string & selection)
{
  mSelection = selection;
}

void CExpressionGenerator::setOperation(const std::string & operation)
{
  mOperation = OperationNames.toEnum(operation);
}
