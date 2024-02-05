// Copyright (C) 2019 - 2024 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

//

#include <sstream>
#include <string>
#include <vector>
#include <limits>
#include <cmath>
#include <algorithm>
#include <chrono>

#include "copasi/copasi.h"

// #define DEBUG_MATRIX

#include "CCompartment.h"
#include "CMetab.h"
#include "CModel.h"
#include "CState.h"
#include "CModelValue.h"
#include "CObjectLists.h"
#include "copasi/function/CFunctionDB.h"
#include "copasi/core/CDataObjectReference.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/utilities/CCopasiException.h"
#include "copasi/utilities/CCopasiMessage.h"
#include "copasi/core/CDataVector.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/core/CVector.h"
#include "copasi/utilities/CluX.h"
#include "copasi/utilities/utility.h"
#include "copasi/utilities/CProcessReport.h"
#include "CReactionInterface.h"
#include "copasi/core/CDataArray.h"
#include "CMetabNameInterface.h"

#include "copasi/math/CMathContainer.h"

#include "copasi/lapack/blaswrap.h"
#include "copasi/lapack/lapackwrap.h"

#define MNumMetabolitesReactionDependent (mNumMetabolitesReaction - mNumMetabolitesReactionIndependent)

//static
const CEnumAnnotation< std::string, CModel::ModelType > CModel::ModelTypeNames(
{
  "deterministic",
  "stochastic"
});

// static
CModel * CModel::fromData(const CData & data, CUndoObjectInterface * pParent)
{
  CModel * pModel = new CModel(NO_PARENT);
  pModel->setObjectName(data.getProperty(CData::OBJECT_NAME).toString());

  return pModel;
}

// virtual
CData CModel::toData() const
{
  CData Data = CModelEntity::toData();

  Data.addProperty(CData::VOLUME_UNIT, mVolumeUnit);
  Data.addProperty(CData::AREA_UNIT, mAreaUnit);
  Data.addProperty(CData::LENGTH_UNIT, mLengthUnit);
  Data.addProperty(CData::TIME_UNIT, mTimeUnit);

  CData QuantityUnitData;
  QuantityUnitData.addProperty(CData::VALUE, mQuantityUnit);
  QuantityUnitData.addProperty(CData::FRAMEWORK, CCore::FrameworkNames[CCore::Framework::ParticleNumbers]);
  Data.addProperty(CData::QUANTITY_UNIT, QuantityUnitData);

  Data.addProperty(CData::MODEL_TYPE, ModelTypeNames[this->mType]);

  CData AvogadroData;
  AvogadroData.addProperty(CData::VALUE, mAvogadro);
  AvogadroData.addProperty(CData::FRAMEWORK, CCore::FrameworkNames[CCore::Framework::ParticleNumbers]);
  Data.addProperty(CData::AVOGADRO_NUMBER, AvogadroData);

  return Data;
}

// virtual
bool CModel::applyData(const CData & data, CUndoData::CChangeSet & changes)
{
  bool success = CModelEntity::applyData(data, changes);
  bool compileModel = false;

  if (data.isSetProperty(CData::VOLUME_UNIT))
    {
      success &= setVolumeUnit(data.getProperty(CData::VOLUME_UNIT).toString());
    }

  if (data.isSetProperty(CData::AREA_UNIT))
    {
      success &= setAreaUnit(data.getProperty(CData::AREA_UNIT).toString());
    }

  if (data.isSetProperty(CData::LENGTH_UNIT))
    {
      success &= setLengthUnit(data.getProperty(CData::LENGTH_UNIT).toString());
    }

  if (data.isSetProperty(CData::TIME_UNIT))
    {
      success &= setTimeUnit(data.getProperty(CData::TIME_UNIT).toString());
    }

  if (data.isSetProperty(CData::QUANTITY_UNIT))
    {
      const CData & Data = data.getProperty(CData::QUANTITY_UNIT).toData();
      success &= setQuantityUnit(Data.getProperty(CData::VALUE).toString(),
                                 CCore::FrameworkNames.toEnum(Data.getProperty(CData::FRAMEWORK).toString(), CCore::Framework::ParticleNumbers));
    }

  if (data.isSetProperty(CData::MODEL_TYPE))
    {
      setModelType(ModelTypeNames.toEnum(data.getProperty(CData::MODEL_TYPE).toString(), ModelType::deterministic));
      compileModel = true;
    }

  if (data.isSetProperty(CData::AVOGADRO_NUMBER))
    {
      const CData & Data = data.getProperty(CData::AVOGADRO_NUMBER).toData();
      setAvogadro(data.getProperty(CData::VALUE).toDouble(),
                  CCore::FrameworkNames.toEnum(Data.getProperty(CData::FRAMEWORK).toString(), CCore::Framework::ParticleNumbers));
      compileModel = true;
    }

  if (compileModel)
    {
      compileModel = true;
    }

  return success;
}

// virtual
void CModel::createUndoData(CUndoData & undoData,
                            const CUndoData::Type & type,
                            const CData & oldData,
                            const CCore::Framework & framework) const
{
  CModelEntity::createUndoData(undoData, type, oldData, framework);

  if (type != CUndoData::Type::CHANGE)
    {
      return;
    }

  undoData.addProperty(CData::VOLUME_UNIT, oldData.getProperty(CData::VOLUME_UNIT), mVolumeUnit);
  undoData.addProperty(CData::AREA_UNIT, oldData.getProperty(CData::AREA_UNIT), mAreaUnit);
  undoData.addProperty(CData::LENGTH_UNIT, oldData.getProperty(CData::LENGTH_UNIT), mLengthUnit);
  undoData.addProperty(CData::TIME_UNIT, oldData.getProperty(CData::TIME_UNIT), mTimeUnit);

  CData OldQuantityUnitData;
  OldQuantityUnitData.addProperty(CData::VALUE, oldData.getProperty(CData::QUANTITY_UNIT).toData().getProperty(CData::VALUE));
  OldQuantityUnitData.addProperty(CData::FRAMEWORK, CCore::FrameworkNames[framework]);
  CData NewQuantityUnitData;
  NewQuantityUnitData.addProperty(CData::VALUE, mQuantityUnit);
  NewQuantityUnitData.addProperty(CData::FRAMEWORK, CCore::FrameworkNames[framework]);

  undoData.addProperty(CData::QUANTITY_UNIT, OldQuantityUnitData, NewQuantityUnitData);
  undoData.addProperty(CData::MODEL_TYPE, oldData.getProperty(CData::MODEL_TYPE), ModelTypeNames[this->mType]);

  CData OldAvogadroData;
  OldAvogadroData.addProperty(CData::VALUE, oldData.getProperty(CData::AVOGADRO_NUMBER).toData().getProperty(CData::VALUE));
  OldAvogadroData.addProperty(CData::FRAMEWORK, CCore::FrameworkNames[framework]);
  CData NewAvogadroData;
  NewAvogadroData.addProperty(CData::VALUE, mAvogadro);
  NewAvogadroData.addProperty(CData::FRAMEWORK, CCore::FrameworkNames[framework]);

  undoData.addProperty(CData::AVOGADRO_NUMBER, OldAvogadroData, NewAvogadroData);
}

CModel::CModel(CDataContainer* pParent):
  CModelEntity("New Model", pParent, "Model"),
  mStateTemplate(*this),
  mStructuralDependencies(),
  mVolumeUnit("l"),
  mAreaUnit("m\xc2\xb2"),
  mLengthUnit("m"),
  mTimeUnit("s"),
  mQuantityUnit("mol"),
  mType(CModel::ModelType::deterministic),
  mCompartments("Compartments", this),
  mMetabolites("Metabolites", this),
  mMetabolitesX("Reduced Model Metabolites", this),
  mSteps("Reactions", this),
  mEvents("Events", this),
  mParticleFluxes(),
  mReactionsPerSpecies(),
  mValues("Values", this),
  mParameterSet("Initial State", this),
  mParameterSets("ParameterSets", this),
  mActiveParameterSetKey(""),
  mMoieties("Moieties", this),
  mpStoiAnnotation(NULL),
  mStoi(),
  mRedStoi(),
  mpRedStoiAnnotation(NULL),
  mNumMetabolitesUnused(0),
  mNumMetabolitesODE(0),
  mNumMetabolitesReaction(0),
  mNumMetabolitesAssignment(0),
  mNumMetabolitesReactionIndependent(0),
  mL(),
  mpLinkMatrixAnnotation(NULL),
  mLView(mL),
  mAvogadro(CUnit::Avogadro),
  mpAvogadroReference(new CDataObjectReference< C_FLOAT64 >("Avogadro Constant", this, mAvogadro, CDataObject::ValueDbl)),
  mQuantity2NumberFactor(std::numeric_limits< C_FLOAT64 >::quiet_NaN()),
  mpQuantity2NumberFactorReference(new CDataObjectReference< C_FLOAT64 >("Quantity Conversion Factor", this, mQuantity2NumberFactor, CDataObject::ValueDbl)),
  mNumber2QuantityFactor(std::numeric_limits< C_FLOAT64 >::quiet_NaN()),
  mpProcessReport(),
  mReorderNeeded(false),
  mIsAutonomous(true),
  mBuildInitialSequence(true),
  mpMathContainer(NULL)
{
  initObjects();

  setStatus(Status::TIME);
  setUsed(true);
  mIValue = 0.0;

  setQuantityUnit(mQuantityUnit, CCore::Framework::ParticleNumbers);

  initializeMetabolites();

  forceCompile(NULL);
}

// CModel::CModel(const CModel & src):
//     CModelEntity(src),
//     mInitialState(),
//     mCurrentState(),
//     mStateTemplate(*this, this->mInitialState, this->mCurrentState),
//     mComments(src.mComments),
//     mVolumeUnit(src.mVolumeUnit),
//     mTimeUnit(src.mTimeUnit),
//     mQuantityUnit(src.mQuantityUnit),
//     mType(src.mType),
//     mCompartments(src.mCompartments, this),
//     mMetabolites(src.mMetabolites, this),
//     mMetabolitesX(src.mMetabolitesX, this),
//     mSteps(src.mSteps, this),
//     mEvents(src.mEvents,this),
//     mParticleFluxes(src.mParticleFluxes),
//     mValues(src.mValues, this),
//     mParameterSets(src.mParameterSets, this),
//     mActiveParameterSetKey(src.mActiveParameterSetKey),
//     mMoieties(src.mMoieties, this),
//     mStoi(src.mStoi),
//     mpStoiAnnotation(NULL),
//     mStoi(src.mStoi),
//     mRedStoi(src.mRedStoi),
//     mpRedStoiAnnotation(NULL),
//     mNumMetabolitesUnused(src.mNumMetabolitesUnused),
//     mNumMetabolitesODE(src.mNumMetabolitesODE),
//     mNumMetabolitesReaction(src.mNumMetabolitesReaction),
//     mNumMetabolitesAssignment(src.mNumMetabolitesAssignment),
//     mNumMetabolitesIndependent(src.mNumMetabolitesIndependent),
//     mL(src.mL),
//     mpLinkMatrixAnnotation(NULL),
//     mLView(mL, mNumMetabolitesIndependent),
//     mQuantity2NumberFactor(src.mQuantity2NumberFactor),
//     mNumber2QuantityFactor(src.mNumber2QuantityFactor),
//     mpCompileHandler(NULL),
//     mInitialRefreshes(),
//     mSimulatedRefreshes(),
//     mConstantRefreshes(),
//     mNonSimulatedRefreshes(),
//     mReorderNeeded(false),
//     mIsAutonomous(false)
// {
//   CONSTRUCTOR_TRACE;
//   initObjects();
//
//   size_t i, imax = mSteps.size();
//
//   for (i = 0; i < imax; i++)
//     mSteps[i].compile(/*mCompartments*/);
//
//   initializeMetabolites();
//
//   forceCompile(NULL);
//}

CModel::~CModel()
{
  mpModel = NULL;

  pdelete(mpStoiAnnotation);
  pdelete(mpRedStoiAnnotation);
  pdelete(mpLinkMatrixAnnotation);

  pdelete(mpMathContainer);

  CRootContainer::getKeyFactory()->remove(mKey);

  DESTRUCTOR_TRACE;
}

// virtual
bool CModel::setObjectParent(const CDataContainer * pParent)
{
  return CDataContainer::setObjectParent(pParent);
}

// virtual
std::string CModel::getChildObjectUnits(const CDataObject * pObject) const
{
  if (pObject == mpAvogadroReference)
    {
      return "1";
    }

  if (pObject == mpQuantity2NumberFactorReference)
    {
      return "#/(" + mQuantityUnit + ")";
    }

  return CModelEntity::getChildObjectUnits(pObject);
}

C_INT32 CModel::load(CReadConfig & configBuffer)
{
  C_INT32 Size = 0;
  C_INT32 Fail = 0;
  size_t i;
  std::string tmp;

  // For old Versions we must read the list of Metabolites beforehand
  if ((Fail = configBuffer.getVariable("TotalMetabolites", "C_INT32",
                                       &Size, CReadConfig::LOOP)))
    return Fail;

  // :TODO: Remove OldMetabolites as part of the data model.
  CDataModel* pDataModel = getObjectDataModel();
  assert(pDataModel != NULL);
  pDataModel->pOldMetabolites->load(configBuffer, Size);

  if ((Fail = configBuffer.getVariable("Title", "string", &tmp,
                                       CReadConfig::LOOP)))
    return Fail;

  setObjectName(tmp);

  std::string Notes;

  try
    {
      Fail = configBuffer.getVariable("Comments", "multiline", &Notes,
                                      CReadConfig::SEARCH);
    }

  catch (CCopasiException & Exception)
    {
      if ((MCReadConfig + 1) == Exception.getMessage().getNumber())
        Notes = "";
      else
        throw Exception;
    }

  setNotes(Notes);

  try
    {
      Fail = configBuffer.getVariable("TimeUnit", "string", &tmp,
                                      CReadConfig::LOOP);
    }
  catch (CCopasiException & Exception)
    {
      if ((MCReadConfig + 1) == Exception.getMessage().getNumber())
        tmp = ""; //unknown?
      else
        throw Exception;
    }

  setTimeUnit(tmp); // set the factors

  try
    {
      Fail = configBuffer.getVariable("ConcentrationUnit", "string", &tmp,
                                      CReadConfig::LOOP);
    }
  catch (CCopasiException & Exception)
    {
      if ((MCReadConfig + 1) == Exception.getMessage().getNumber())
        tmp = "";  //unknown?
      else
        throw Exception;
    }

  // We suppress all errors and warnings
  size_t MessageSize = CCopasiMessage::size();

  if (!setQuantityUnit(tmp, CCore::Framework::ParticleNumbers) &&
      !setQuantityUnit(tmp.substr(0, 1) + "mol", CCore::Framework::ParticleNumbers))
    {
      setQuantityUnit("mmol", CCore::Framework::ParticleNumbers);
    }

  // Remove error messages created by the task initialization as this may fail
  // due to incomplete task specification at this time.
  while (CCopasiMessage::size() > MessageSize)
    CCopasiMessage::getLastMessage();

  try
    {
      Fail = configBuffer.getVariable("VolumeUnit", "string", &tmp,
                                      CReadConfig::LOOP);
    }
  catch (CCopasiException & Exception)
    {
      if ((MCReadConfig + 1) == Exception.getMessage().getNumber())
        tmp = ""; //unknown?
      else
        throw Exception;
    }

  setVolumeUnit(tmp); // set the factors

  mIValue = 0;

  if ((Fail = configBuffer.getVariable("TotalCompartments", "C_INT32", &Size,
                                       CReadConfig::LOOP)))
    return Fail;

  mCompartments.load(configBuffer, Size);

  // Create the correct compartment / metabolite relationships
  CMetab *pMetabolite;

  for (i = 0; i < pDataModel->pOldMetabolites->size(); i++)
    {
      pMetabolite = new CMetab;
      mCompartments[pDataModel->pOldMetabolites->operator[](i).getIndex()].addMetabolite(pMetabolite);

      // The assignment operator requires the metabolite to be in a compartment.
      (*pMetabolite) = pDataModel->pOldMetabolites->operator[](i);
      mMetabolites.add(pMetabolite, false);
    }

  initializeMetabolites();

  if ((Fail = CRootContainer::getFunctionList()->load(configBuffer))) // slow
    return Fail;

  if ((Fail = configBuffer.getVariable("TotalSteps", "C_INT32", &Size,
                                       CReadConfig::LOOP)))
    return Fail;

  mSteps.load(configBuffer, Size); // slow

  for (i = 0; i < mSteps.size(); i++)
    mSteps[i].compile(/*mCompartments*/);

  pDataModel->pOldMetabolites->cleanup();

  setCompileFlag();
  return Fail;
}

CIssue CModel::compile()
{
  //bool success = true;
  CIssue firstWorstIssue;
  bool RenameHandlerEnabled = CRegisteredCommonName::isEnabled();

  CRegisteredCommonName::setEnabled(false);

  unsigned C_INT32 CompileStep = 0;
  size_t hCompileStep;

  // std::chr::time_point<std::chrono::steady_clock> // Start = std::chrono::steady_clock::now();

  if (mpProcessReport != NULL)
    {
      mpProcessReport->setName("Compiling model...");
      unsigned C_INT32 totalSteps = 12;
      hCompileStep = mpProcessReport->addItem("Compile Process",
                                              CompileStep,
                                              &totalSteps);
    }

  CompileStep = 0;

  if (mpProcessReport && !mpProcessReport->progressItem(hCompileStep))
    {
      firstWorstIssue = CIssue::Error;
      goto finish;
    }

  buildStoi();

  // std::cout << "CModel::compile(buildStoi): duration = '" << std::chrono::nanoseconds(std::chrono::steady_clock::now() - Start).count()  << "' ns." << std::endl;
  // Start = std::chrono::steady_clock::now();

  CompileStep = 1;

  if (mpProcessReport && !mpProcessReport->progressItem(hCompileStep))
    {
      firstWorstIssue = CIssue::Error;
      goto finish;
    }

  buildLinkZero();

  // std::cout << "CModel::compile(buildLinkZero): duration = '" << std::chrono::nanoseconds(std::chrono::steady_clock::now() - Start).count()  << "' ns." << std::endl;
  // Start = std::chrono::steady_clock::now();

  CompileStep = 2;

  if (mpProcessReport && !mpProcessReport->progressItem(hCompileStep))
    {
      firstWorstIssue = CIssue::Error;
      goto finish;
    }

  buildRedStoi();

  // std::cout << "CModel::compile(buildRedStoi): duration = '" << std::chrono::nanoseconds(std::chrono::steady_clock::now() - Start).count()  << "' ns." << std::endl;
  // Start = std::chrono::steady_clock::now();

  CompileStep = 3;

  if (mpProcessReport && !mpProcessReport->progressItem(hCompileStep))
    {
      firstWorstIssue = CIssue::Error;
      goto finish;
    }

  buildMoieties();

  // std::cout << "CModel::compile(buildMoieties): duration = '" << std::chrono::nanoseconds(std::chrono::steady_clock::now() - Start).count()  << "' ns." << std::endl;
  // Start = std::chrono::steady_clock::now();

  CompileStep = 4;

  if (mpProcessReport && !mpProcessReport->progressItem(hCompileStep))
    {
      firstWorstIssue = CIssue::Error;
      goto finish;
    }

  buildStateTemplate();

  // std::cout << "CModel::compile(buildStateTemplate): duration = '" << std::chrono::nanoseconds(std::chrono::steady_clock::now() - Start).count()  << "' ns." << std::endl;
  // Start = std::chrono::steady_clock::now();

  CompileStep = 5;

  if (mpProcessReport && !mpProcessReport->progressItem(hCompileStep))
    {
      firstWorstIssue = CIssue::Error;
      goto finish;
    }

  buildUserOrder();

  // std::cout << "CModel::compile(buildUserOrder): duration = '" << std::chrono::nanoseconds(std::chrono::steady_clock::now() - Start).count()  << "' ns." << std::endl;
  // Start = std::chrono::steady_clock::now();

  CompileStep = 6;

  if (mpProcessReport && !mpProcessReport->progressItem(hCompileStep))
    {
      firstWorstIssue = CIssue::Error;
      goto finish;
    }

  //update annotations
  updateMatrixAnnotations();

  firstWorstIssue &= compileEvents();
  // success &= mpMathModel->compile(this);

  if (!firstWorstIssue)
    {
      mIsAutonomous = false;
    }
  else
    {
      mCompileIsNecessary = false;
    }

  // writeDependenciesToDotFile();

  CompileStep = 7;

  if (mpProcessReport && !mpProcessReport->progressItem(hCompileStep))
    {
      firstWorstIssue = CIssue::Error;
      goto finish;
    }

  // std::cout << "CModel::compile(updateMatrixAnnotations): duration = '" << std::chrono::nanoseconds(std::chrono::steady_clock::now() - Start).count()  << "' ns." << std::endl;
  // Start = std::chrono::steady_clock::now();

  buildDependencyGraphs();

  CompileStep = 8;

  if (mpProcessReport && !mpProcessReport->progressItem(hCompileStep))
    {
      firstWorstIssue = CIssue::Error;
      goto finish;
    }

  // std::cout << "CModel::compile(buildDependencyGraphs): duration = '" << std::chrono::nanoseconds(std::chrono::steady_clock::now() - Start).count()  << "' ns." << std::endl;
  // Start = std::chrono::steady_clock::now();

  mpMathContainer->compile();

  CompileStep = 9;

  if (mpProcessReport && !mpProcessReport->progressItem(hCompileStep))
    {
      firstWorstIssue = CIssue::Error;
      goto finish;
    }

  // std::cout << "CModel::compile(mpMathContainer->compile): duration = '" << std::chrono::nanoseconds(std::chrono::steady_clock::now() - Start).count()  << "' ns." << std::endl;
  // Start = std::chrono::steady_clock::now();

  mpMathContainer->fetchInitialState();
  mpMathContainer->updateInitialValues(CCore::Framework::ParticleNumbers);
  mpMathContainer->pushInitialState();

  CompileStep = 10;

  if (mpProcessReport && !mpProcessReport->progressItem(hCompileStep))
    {
      firstWorstIssue = CIssue::Error;
      goto finish;
    }

  // std::cout << "CModel::compile(mpMathContainer->updateInitialValues): duration = '" << std::chrono::nanoseconds(std::chrono::steady_clock::now() - Start).count()  << "' ns." << std::endl;
  // Start = std::chrono::steady_clock::now();

  mIsAutonomous = mpMathContainer->isAutonomous();

  {
    CDataVector< CMetab >::iterator itSpecies = mMetabolitesX.begin();
    CDataVector< CMetab >::iterator endSpecies = mMetabolitesX.end();

    for (; itSpecies != endSpecies; ++itSpecies)
      {
        itSpecies->compileIsInitialValueChangeAllowed();
      }
  }

  CompileStep = 11;

  if (mpProcessReport && !mpProcessReport->progressItem(hCompileStep))
    {
      firstWorstIssue = CIssue::Error;
      goto finish;
    }

  // std::cout << "CModel::compile(itSpecies->compileIsInitialValueChangeAllowed): duration = '" << std::chrono::nanoseconds(std::chrono::steady_clock::now() - Start).count()  << "' ns." << std::endl;
  // Start = std::chrono::steady_clock::now();
  // CMathContainer CopyModel(MathModel);

  // Update the parameter set
  mParameterSet.createFromModel();

  CompileStep = 12;

  if (mpProcessReport && !mpProcessReport->progressItem(hCompileStep))
    {
      firstWorstIssue = CIssue::Error;
      goto finish;
    }

  // std::cout << "CModel::compile(mParameterSet.createFromModel): duration = '" << std::chrono::nanoseconds(std::chrono::steady_clock::now() - Start).count()  << "' ns." << std::endl;
finish:

  // Since we have applied the pivot to the stoichiometry matrix and the species
  // we do not need them any longer. In fact it is detrimental if other functions rely
  // on consistency between the stoichiometry matrix, reduced stoichiometry matrix and the Link matrix..
  mL.clearPivoting();

  if (RenameHandlerEnabled)
    {
      CRegisteredCommonName::setEnabled(true);
    }

  mCompileIsNecessary = !firstWorstIssue;

  if (mpProcessReport != NULL) mpProcessReport->finishItem(hCompileStep);

  return firstWorstIssue;
}

bool CModel::buildDependencyGraphs()
{
  mStructuralDependencies.clear();

  // We need to add all compartment, species, global quantities, reactions, events, and event assignments
  CDataVector< CCompartment >::const_iterator itCompartment = mCompartments.begin();
  CDataVector< CCompartment >::const_iterator endCompartment = mCompartments.end();

  for (; itCompartment != endCompartment; ++itCompartment)
    {
      mStructuralDependencies.addObject(&*itCompartment);
    }

  CDataVector< CMetab >::const_iterator itMetab = mMetabolites.begin();
  CDataVector< CMetab >::const_iterator endMetab = mMetabolites.end();

  for (; itMetab != endMetab; ++itMetab)
    {
      mStructuralDependencies.addObject(&*itMetab);
    }

  CDataVector< CModelValue >::const_iterator itModelValue = mValues.begin();
  CDataVector< CModelValue >::const_iterator endModelValue = mValues.end();

  for (; itModelValue != endModelValue; ++itModelValue)
    {
      mStructuralDependencies.addObject(&*itModelValue);
    }

  CDataVector< CReaction >::const_iterator itReaction = mSteps.begin();
  CDataVector< CReaction >::const_iterator endReaction = mSteps.end();

  for (; itReaction != endReaction; ++itReaction)
    {
      mStructuralDependencies.addObject(&*itReaction);
    }

  CDataVector< CEvent >::const_iterator itEvent = mEvents.begin();
  CDataVector< CEvent >::const_iterator endEvent = mEvents.end();

  for (; itEvent != endEvent; ++itEvent)
    {
      mStructuralDependencies.addObject(&*itEvent);

      CDataVector< CEventAssignment >::const_iterator itAssignment = itEvent->getAssignments().begin();
      CDataVector< CEventAssignment >::const_iterator endAssignment = itEvent->getAssignments().end();

      for (; itAssignment != endAssignment; ++itAssignment)
        {
          mStructuralDependencies.addObject(&*itAssignment);
        }
    }

#ifdef COPASI_DEBUG_TRACE
  std::ofstream StructuralDependencies("StructuralDependencies.dot");
  mStructuralDependencies.exportDOTFormat(StructuralDependencies, "StructuralDependencies");
#endif // COPASI_DEBUG_TRACE

  return true;
}

void CModel::functionDefinitionChanged(const CFunction * pFunction)
{
  CObjectInterface::ObjectSet ChangedObjects;
  ChangedObjects.insert(pFunction);
  CObjectInterface::ObjectSet DependentObjects;

  if (mStructuralDependencies.appendDirectDependents(ChangedObjects, DependentObjects))
    {
      setCompileFlag(true);
    }
}

void CModel::setCompileFlag(bool flag)
{
  mCompileIsNecessary = flag;
}

const bool & CModel::isCompileNecessary() const
{
  return mCompileIsNecessary;
}

bool CModel::compileIfNecessary(CProcessReport * pProcessReport)
{
  bool success = true;

  if (mCompileIsNecessary)
    {
      mpProcessReport = pProcessReport;

      try
        {
          success &= compile();
        }

      catch (...)
        {
          success = false;
        }

      mpProcessReport = NULL;
    }

  return success;
}

bool CModel::forceCompile(CProcessReport * pProcessReport)
{
  setCompileFlag();
  return compileIfNecessary(pProcessReport);
}

void CModel::buildStoi()
{
  unsigned C_INT32 i, numCols;

  initializeMetabolites();

  mReactionsPerSpecies.clear();

  size_t numRows;
  numRows = mNumMetabolitesReaction;
  numCols = (unsigned C_INT32) mSteps.size();

  mParticleFluxes.resize(numCols);
  mStoi.resize(numRows, numCols);
  mStoi = 0.0;

  size_t hProcess;

  if (mpProcessReport != NULL)
    {
      i = 0;
      hProcess = mpProcessReport->addItem("Building Stoichiometry", i, &numCols);
    }

  C_FLOAT64 * pCol, *pColEnd;
  pCol = mStoi.array();
  pColEnd = mStoi.array() + numCols;

  C_FLOAT64 * pRow, *pRowEnd;
  pRowEnd = mStoi.array() + numRows * numCols;

  CDataVector< CReaction >::iterator itStep = mSteps.begin();
  CDataVector< CMetab >::const_iterator itMetab;
  size_t reactionNum = 0, speciesNum = 0;

  for (; pCol < pColEnd; ++pCol, ++itStep, ++reactionNum)
    {
      if (mpProcessReport && !mpProcessReport->progressItem(hProcess)) return;

      // Since we are stepping through the reactions we can check whether
      // the kinetic functions are usable.
      CIssue issue = itStep->getFunction()->getValidity().getFirstWorstIssue();

      if (!issue)
        CCopasiMessage(CCopasiMessage::ERROR, MCReaction + 11,
                       itStep->getObjectName().c_str(),
                       itStep->getFunction()->getObjectName().c_str());

      const CDataVector< CChemEqElement > & Balance = itStep->getChemEq().getBalances();
      CDataVector< CChemEqElement >::const_iterator itBalance = Balance.begin();
      CDataVector< CChemEqElement >::const_iterator endBalance = Balance.end();

      for (; itBalance != endBalance; ++itBalance)
        {
          const std::string & key = itBalance->getMetaboliteKey();
          speciesNum = 0;

          for (pRow = pCol, itMetab = CDataVector< CMetab >::const_iterator(mMetabolitesX.begin()) + mNumMetabolitesODE;
               pRow < pRowEnd;
               pRow += numCols, ++itMetab, ++speciesNum)
            if (itMetab->getKey() == key)
              {
                *pRow = itBalance->getMultiplicity();
                mReactionsPerSpecies[&*itMetab].insert(std::make_pair(&*itStep, *pRow));
                break;
              }
        }
    }

  // We need to have all unused and fixed metabolites at the end of mMetabolites.
  // However we can only detect unused metabolites after building the
  // stoichiometry matrix.
  handleUnusedMetabolites();

#ifdef DEBUG_MATRIX
  DebugFile << "Stoichiometry Matrix" << std::endl;
  DebugFile << mStoi << std::endl;
#endif

  if (mpProcessReport != NULL)
    mpProcessReport->finishItem(hProcess);

  return;
}

bool CModel::handleUnusedMetabolites()
{
  size_t numRows, numCols;
  numRows = mStoi.numRows();
  numCols = mStoi.numCols();

  C_FLOAT64 * pStoi, *pStoiEnd, *pRowEnd;
  pStoi = mStoi.array();
  pStoiEnd = mStoi.array() + numRows * numCols;

  size_t i, NumUnused;
  C_FLOAT64 tmp;
  std::vector< size_t > Unused;

  for (i = 0; i < numRows; i++)
    {
      tmp = 0;

      for (pRowEnd = pStoi + numCols; pStoi < pRowEnd; ++pStoi)
        tmp += fabs(*pStoi);

      if (tmp < std::numeric_limits< C_FLOAT64 >::min()) Unused.push_back(i);
    }

  NumUnused = Unused.size();

  if (NumUnused == 0) return false;

  // We treat unused variables in the same way as fixed, i.e.
  // they will be sorted to the end of the metabolite list.

  numRows -= NumUnused;

  CMatrix< C_FLOAT64 > NewStoi(numRows, numCols);
  C_FLOAT64 * pNewStoi = NewStoi.array();
  std::vector< CMetab * > UsedMetabolites(numRows);
  std::vector< CMetab * >::iterator itUsedMetabolites = UsedMetabolites.begin();
  std::vector< CMetab * > UnusedMetabolites(NumUnused);
  std::vector< CMetab * >::iterator itUnusedMetabolites = UnusedMetabolites.begin();
  std::vector< size_t >::const_iterator itUnused = Unused.begin();
  std::vector< size_t >::const_iterator endUnused = Unused.end();

  CDataVector< CMetab >::iterator itMetab = mMetabolitesX.begin() + mNumMetabolitesODE;
  CDataVector< CMetab >::iterator endMetab = itMetab + mNumMetabolitesReaction;

  // Build new stoichiometry Matrix
  pStoi = mStoi.array();

  for (i = 0; itMetab != endMetab; ++itMetab, i++, pStoi += numCols)
    {
      if (itUnused != endUnused && i == *itUnused)
        {
          itMetab->setUsed(false);
          *itUnusedMetabolites = itMetab;

          ++itUnusedMetabolites;
          ++itUnused;
        }
      else
        {
          itMetab->setUsed(true);
          *itUsedMetabolites = itMetab;
          ++itUsedMetabolites;

          // The row needs to be copied to the new stoichiometry matrix
          memcpy(pNewStoi, pStoi, sizeof(C_FLOAT64) * numCols);
          pNewStoi += numCols;
        }
    }

  // Reorder metabolites
  // Skip the metabolites determined by ODE
  itMetab = mMetabolitesX.begin() + mNumMetabolitesODE;

  // Handle the metabolites determined by actually determined by reactions
  itUsedMetabolites = UsedMetabolites.begin();
  std::vector< CMetab * >::iterator itMetabolitesEnd = UsedMetabolites.end();

  for (; itUsedMetabolites != itMetabolitesEnd; ++itUsedMetabolites, ++itMetab)
    itMetab = *itUsedMetabolites;

  // Handle metabolites determined by assignment and marked as fixed
  // This is just a shift of NumUnused.
  endMetab = itMetab + mNumMetabolitesAssignment + mNumMetabolitesUnused;

  for (; itMetab != endMetab; ++itMetab)
    itMetab = static_cast< CMetab * >(itMetab + NumUnused);

  // Handle newly marked unused metabolites
  itUnusedMetabolites = UnusedMetabolites.begin();
  itMetabolitesEnd = UnusedMetabolites.end();

  for (; itUnusedMetabolites != itMetabolitesEnd; ++itUnusedMetabolites, ++itMetab)
    itMetab = *itUnusedMetabolites;

  // Now its time to update the number of metabolites determined by reactions
  // and the one being unused.
  mNumMetabolitesReaction -= NumUnused;
  mNumMetabolitesUnused += NumUnused;

  // Update stoichiometry matrix
  mStoi = NewStoi;

  return true;
}

void CModel::buildRedStoi()
{
  mRedStoi = mStoi;
  mRedStoi.resize(mNumMetabolitesReactionIndependent, mRedStoi.numCols(), true);

  // The first metabolites are determined by ODEs we therefore cannot simply
  // apply the pivot.

  // Create a temporary copy of metabolites determined by reactions.
  CVector< CMetab * > ReactionMetabolites(mNumMetabolitesReaction);
  CMetab ** ppMetab = ReactionMetabolites.array();
  CMetab ** ppMetabEnd = ppMetab + mNumMetabolitesReaction;
  CDataVector< CMetab >::iterator itMetabX = mMetabolitesX.begin() + mNumMetabolitesODE;

  for (; ppMetab != ppMetabEnd; ++ppMetab, ++itMetabX)
    {
      *ppMetab = itMetabX;
    }

  // Apply the pivot on the temporary copy
  mL.applyRowPivot(ReactionMetabolites);

  // Map the result on the actual metabolites
  ppMetab = ReactionMetabolites.array();
  itMetabX = mMetabolitesX.begin() + mNumMetabolitesODE;

  for (; ppMetab != ppMetabEnd; ++ppMetab, ++itMetabX)
    {
      itMetabX = *ppMetab;
    }

  return;
}

void CModel::updateMatrixAnnotations()
{
  mpLinkMatrixAnnotation->resize();
  mpStoiAnnotation->resize();
  mpRedStoiAnnotation->resize();

  CDataVector< CMetab >::const_iterator it = CDataVector< CMetab >::const_iterator(mMetabolitesX.begin()) + mNumMetabolitesODE;
  CDataVector< CMetab >::const_iterator end = it + mNumMetabolitesReactionIndependent;

  CCommonName CN;
  size_t j;

  for (j = 0; it != end; ++it, j++)
    {
      mpStoiAnnotation->setAnnotation(0, j, &*it);
      mpLinkMatrixAnnotation->setAnnotation(0, j, &*it);
      mpLinkMatrixAnnotation->setAnnotation(1, j, &*it);
      mpRedStoiAnnotation->setAnnotation(0, j, &*it);
    }

  end += MNumMetabolitesReactionDependent;

  for (; it != end; ++it, j++)
    {
      mpStoiAnnotation->setAnnotation(0, j, &*it);
      mpLinkMatrixAnnotation->setAnnotation(0, j, &*it);
    }

  mpStoiAnnotation->setCopasiVector(1, mSteps);
  mpRedStoiAnnotation->setCopasiVector(1, mSteps);
}

void CModel::updateMoietyValues()
{
  CDataVector< CMoiety >::iterator it = mMoieties.begin();
  CDataVector< CMoiety >::iterator end = mMoieties.end();

  for (; it != end; ++it)
    it->refreshInitialValue();
}

void CModel::buildMoieties()
{
  // Independent metabs
  CDataVector< CMetab >::iterator itIndependent = mMetabolitesX.begin() + mNumMetabolitesODE;
  CDataVector< CMetab >::iterator endIndependent = itIndependent + mNumMetabolitesReactionIndependent;

  // Dependent metabs
  CDataVector< CMetab >::iterator itDependent = endIndependent;
  CDataVector< CMetab >::iterator endDependent = itDependent + MNumMetabolitesReactionDependent;

  C_FLOAT64 * pFactor = mL.array();

  CMoiety *pMoiety;
  mMoieties.cleanup();

  for (; itDependent != endDependent; ++itDependent)
    {
      pMoiety = new CMoiety(itDependent->getObjectName());
      pMoiety->add(1.0, itDependent);

      if (pFactor != NULL)
        {
          for (itIndependent = mMetabolitesX.begin() + mNumMetabolitesODE; itIndependent != endIndependent; ++itIndependent, ++pFactor)
            if (fabs(*pFactor) > std::numeric_limits< C_FLOAT64 >::epsilon())
              pMoiety->add(- *pFactor, itIndependent);
        }

      mMoieties.add(pMoiety, true);
    }

  updateMoietyValues();
  return;
}

void CModel::clearSbmlIds()
{
  for (auto & comp : getCompartments())
    comp.setSBMLId("");

  for (auto & metab : getMetabolites())
    metab.setSBMLId("");

  for (auto & param : getModelValues())
    param.setSBMLId("");

  for (auto & reaction : getReactions())
    reaction.setSBMLId("");

  for (auto & c_event : getEvents())
    c_event.setSBMLId("");
}

//this is supposed to be so fast it can be called often to be kept up to date
//all the time. At the moment it creates the mMetabolites and sorts the fixed
//metabs to the end
void CModel::initializeMetabolites()
{
  // Create a vector of pointers to all metabolites.
  // Note, the metabolites physically exist in the compartments.
  mMetabolitesX.clear();

  CDataVector< CCompartment >::iterator itCompartment = mCompartments.begin();
  CDataVector< CCompartment >::iterator endCompartment = mCompartments.end();
  CDataVector< CMetab >::iterator itMetab;
  CDataVector< CMetab >::iterator endMetab;

  std::vector< CMetab * > ODEMetabs;
  std::vector< CMetab * > ReactionMetabs;
  std::vector< CMetab * > AssignmentMetabs;
  std::vector< CMetab * > FixedMetabs;

  for (; itCompartment != endCompartment; ++itCompartment)
    {
      itMetab = itCompartment->getMetabolites().begin();
      endMetab = itCompartment->getMetabolites().end();

      for (; itMetab != endMetab; ++itMetab)
        {
          // Reset all moieties
          itMetab->setDependsOnMoiety(NULL);

          switch (itMetab->getStatus())
            {
              case Status::FIXED:
                FixedMetabs.push_back(itMetab);
                itMetab->setUsed(false);
                break;

              case Status::ASSIGNMENT:
                AssignmentMetabs.push_back(itMetab);
                itMetab->setUsed(true);
                break;

              case Status::ODE:
                ODEMetabs.push_back(itMetab);
                itMetab->setUsed(true);
                break;

              case Status::REACTIONS:
                ReactionMetabs.push_back(itMetab);
                itMetab->setUsed(true);
                break;

              default:
                fatalError();
                break;
            }
        }
    }

  mNumMetabolitesODE = ODEMetabs.size();
  mNumMetabolitesReaction = ReactionMetabs.size();
  mNumMetabolitesAssignment = AssignmentMetabs.size();
  mNumMetabolitesUnused = FixedMetabs.size();

  std::vector< CMetab *>::const_iterator itSorted = ODEMetabs.begin();
  std::vector< CMetab *>::const_iterator endSorted = ODEMetabs.end();

  for (; itSorted != endSorted; ++itSorted)
    {
      mMetabolitesX.add(*itSorted, false);
    }

  itSorted = ReactionMetabs.begin();
  endSorted = ReactionMetabs.end();

  for (; itSorted != endSorted; ++itSorted)
    {
      mMetabolitesX.add(*itSorted, false);
    }

  itSorted = AssignmentMetabs.begin();
  endSorted = AssignmentMetabs.end();

  for (; itSorted != endSorted; ++itSorted)
    {
      mMetabolitesX.add(*itSorted, false);
    }

  itSorted = FixedMetabs.begin();
  endSorted = FixedMetabs.end();

  for (; itSorted != endSorted; ++itSorted)
    {
      mMetabolitesX.add(*itSorted, false);
    }

  // mMetabolitesX = mMetabolites;
}

const std::set< std::pair< const CReaction *, C_FLOAT64 > > & CModel::getReactionsPerSpecies(const CMetab * pSpecies) const
{
  static std::set< std::pair< const CReaction *, C_FLOAT64 > > EmptySet;

  std::map < const CMetab *, std::set< std::pair< const CReaction *, C_FLOAT64 > > >::const_iterator found = mReactionsPerSpecies.find(pSpecies);

  if (found != mReactionsPerSpecies.end())
    {
      return found->second;
    }

  return EmptySet;
}

CDataVectorNS < CReaction > & CModel::getReactions()
{return mSteps;}

const CDataVectorNS < CReaction > & CModel::getReactions() const
{return mSteps;}

const CVector< C_FLOAT64 > & CModel::getParticleFlux() const
{return mParticleFluxes;}

CDataVector< CMetab > & CModel::getMetabolites()
{return mMetabolites;}

const CDataVector< CMetab > & CModel::getMetabolites() const
{return mMetabolites;}

CDataVector< CMetab > & CModel::getMetabolitesX()
{return mMetabolitesX;}

const CDataVector< CMetab > & CModel::getMetabolitesX() const
{return mMetabolitesX;}

const CDataVectorN< CModelValue > & CModel::getModelValues() const
{return mValues;}

CDataVectorN< CModelValue > & CModel::getModelValues()
{return mValues;}

const CDataVectorN< CModelParameterSet > & CModel::getModelParameterSets() const
{return mParameterSets;}

CDataVectorN< CModelParameterSet > & CModel::getModelParameterSets()
{return mParameterSets;}

const CModelParameterSet & CModel::getActiveModelParameterSet() const
{
  return mParameterSet;
}

CModelParameterSet & CModel::getActiveModelParameterSet()
{
  return mParameterSet;
}

void CModel::applyActiveParameterSet()
{
  CModelParameterSet * pParameterSet =
    dynamic_cast< CModelParameterSet * >(CRootContainer::getKeyFactory()->get(mActiveParameterSetKey));

  if (pParameterSet != NULL)
    {
      pParameterSet->updateModel();
    }
  else
    {
      /*
      CModelParameterSet * pParameterSet = new CModelParameterSet(UTCTimeStamp());
      mParameterSets.add(pParameterSet, true);
      mActiveParameterSetKey = pParameterSet->getKey();
      pParameterSet->createFromModel();
      */
    }

  mParameterSet.createFromModel();
  mActiveParameterSetKey = mParameterSet.getKey();
}

void CModel::refreshActiveParameterSet()
{
  mParameterSet.refreshFromModel(false);
}

CDataVectorN < CEvent > & CModel::getEvents()
{return mEvents;}

const CDataVectorN < CEvent > & CModel::getEvents() const
{return mEvents;}

//********

size_t CModel::getNumMetabs() const
{return mMetabolitesX.size();}

size_t CModel::getNumVariableMetabs() const
{return mNumMetabolitesODE + mNumMetabolitesReaction + mNumMetabolitesAssignment;}

size_t CModel::getNumODEMetabs() const
{return mNumMetabolitesODE;}

size_t CModel::getNumAssignmentMetabs() const
{return mNumMetabolitesAssignment;}

size_t CModel::getNumIndependentReactionMetabs() const
{return mNumMetabolitesReactionIndependent;}

size_t CModel::getNumDependentReactionMetabs() const
{return mNumMetabolitesReaction - mNumMetabolitesReactionIndependent;}

size_t CModel::getTotSteps() const
{return mSteps.size();}

size_t CModel::getNumModelValues() const
{return mValues.size();}

const std::string & CModel::getKey() const
{return mKey;}

CDataVectorNS < CCompartment > & CModel::getCompartments()
{return mCompartments;}

const CDataVectorNS < CCompartment > & CModel::getCompartments() const
{return mCompartments;}

/**
 *  Get the Reduced Stoichiometry Matrix of this Model
 */
const CMatrix < C_FLOAT64 >& CModel::getRedStoi() const
{return mRedStoi;}

const CDataArray *
CModel::getRedStoiAnnotation() const
{
  return mpRedStoiAnnotation;
}

/**
 *  Get the reordered stoichiometry matrix of this model
 */
const CMatrix < C_FLOAT64 >& CModel::getStoi() const
{return mStoi;}

const CDataArray *
CModel::getStoiAnnotation() const
{
  return mpStoiAnnotation;
}

const CDataVector < CMoiety > & CModel::getMoieties() const
{return mMoieties;}

const CLinkMatrixView & CModel::getL() const
{return mLView;}

const CDataArray * CModel::getLAnnotation() const
{
  return mpLinkMatrixAnnotation;
}

const CLinkMatrix & CModel::getL0() const
{return mL;}

const CStateTemplate & CModel::getStateTemplate() const
{return mStateTemplate;}

void CModel::addModelEntity(const CModelEntity * pModelEntity)
{
  mStateTemplate.add(pModelEntity);
}

void CModel::removeModelEntity(const CModelEntity * pModelEntity)
{
  mStateTemplate.remove(pModelEntity);
}

void CModel::setInitialTime(const C_FLOAT64 & time)
{mIValue = time;}

const C_FLOAT64 & CModel::getInitialTime() const
{return mIValue;}

void CModel::setTime(const C_FLOAT64 & time)
{mValue = time;}

const C_FLOAT64 & CModel::getTime() const
{return mValue;}

//**********************************************************************

/**
 *        Returns the index of the metab
 */
CMetab * CModel::findMetabByName(const std::string & name) const
{
  objectMap::range Range = mMetabolites.getObjects().equal_range(unQuote(name));
  CMetab * pSpecies = NULL;

  for (; Range.first != Range.second; ++Range.first)
    if ((pSpecies = dynamic_cast< CMetab * >(*Range.first)) != NULL)
      {
        return pSpecies;
      }

  Range = mMetabolites.getObjects().equal_range(name);

  for (; Range.first != Range.second; ++Range.first)
    if ((pSpecies = dynamic_cast< CMetab * >(*Range.first)) != NULL)
      {
        return pSpecies;
      }

  return pSpecies;
}

/**
 *        Returns the index of the Moiety
 */
size_t CModel::findMoiety(const std::string &Target) const
{
  size_t i, s;
  std::string name;

  s = mMoieties.size();

  for (i = 0; i < s; i++)
    {
      name = mMoieties[i].getObjectName();

      if (name == Target)
        return i;
    }

  return C_INVALID_INDEX;
}

//**********************************************************************

void CModel::applyInitialValues()
{
  mpMathContainer->fetchInitialState();
  mpMathContainer->updateInitialValues(CCore::Framework::ParticleNumbers);
  mpMathContainer->applyInitialValues();
  mpMathContainer->updateSimulatedValues(false);
  mpMathContainer->updateTransientDataValues();
  mpMathContainer->pushAllTransientValues();
}

void CModel::clearMoieties()
{
  mMoieties.clear();
}

bool CModel::buildStateTemplate()
{
  CVector< CModelEntity * > Entities(mMetabolitesX.size() + mCompartments.size() + mValues.size());
  CModelEntity ** ppEntity = Entities.array();

  CDataVector< CModelValue >::iterator itValue = mValues.begin();
  CDataVector< CModelValue >::iterator endValue = mValues.end();

  for (; itValue != endValue; ++itValue)
    if (itValue->getStatus() == Status::ODE)
      {
        itValue->setUsed(true);
        *ppEntity++ = itValue;
      }

  CDataVector< CCompartment >::iterator itCompartment = mCompartments.begin();
  CDataVector< CCompartment >::iterator endCompartment = mCompartments.end();

  for (; itCompartment != endCompartment; ++itCompartment)
    if (itCompartment->getStatus() == Status::ODE)
      {
        itCompartment->setUsed(true);
        *ppEntity++ = itCompartment;
      }

  CDataVector< CMetab >::iterator itMetab = mMetabolitesX.begin();
  CDataVector< CMetab >::iterator endMetab = mMetabolitesX.end();

  for (; itMetab != endMetab; ++itMetab)
    {
      if (!itMetab->isUsed()) break;

      *ppEntity++ = itMetab;
    }

  itCompartment = mCompartments.begin();

  for (; itCompartment != endCompartment; ++itCompartment)
    if (itCompartment->getStatus() == Status::ASSIGNMENT)
      {
        itCompartment->setUsed(true);
        *ppEntity++ = itCompartment;
      }

  itValue = mValues.begin();

  for (; itValue != endValue; ++itValue)
    if (itValue->getStatus() == Status::ASSIGNMENT)
      {
        itValue->setUsed(true);
        *ppEntity++ = itValue;
      }

  for (; itMetab != endMetab; ++itMetab)
    *ppEntity++ = itMetab;

  itCompartment = mCompartments.begin();

  for (; itCompartment != endCompartment; ++itCompartment)
    if (itCompartment->isFixed())
      *ppEntity++ = itCompartment;

  itValue = mValues.begin();

  for (; itValue != endValue; ++itValue)
    if (itValue->isFixed())
      *ppEntity++ = itValue;

  mStateTemplate.reorder(Entities);
  mReorderNeeded = false;

  // Now all entities and reactions can be compiled
  ppEntity = Entities.array();
  CModelEntity ** ppEntityEnd = ppEntity + Entities.size();

  for (; ppEntity != ppEntityEnd; ++ppEntity)
    (*ppEntity)->compile();

  CDataVector< CReaction >::iterator itReaction = mSteps.begin();
  CDataVector< CReaction >::iterator endReaction = mSteps.end();

  for (; itReaction != endReaction; ++itReaction)
    itReaction->compile();

  return true;
}

bool CModel::buildUserOrder()
{
  assert(mMetabolites.size() == mMetabolitesX.size());

  CVector< const CModelEntity * > UserEntities(mMetabolites.size() + mCompartments.size() + mValues.size());
  const CModelEntity ** ppEntity = UserEntities.array();

  CDataVector< CMetab >::iterator itMetab = mMetabolites.begin();
  CDataVector< CMetab >::iterator endMetab = mMetabolites.end();

  for (; itMetab != endMetab; ++itMetab)
    *ppEntity++ = itMetab;;

  CDataVector< CCompartment >::iterator itCompartment = mCompartments.begin();
  CDataVector< CCompartment >::iterator endCompartment = mCompartments.end();

  for (; itCompartment != endCompartment; ++itCompartment)
    *ppEntity++ = itCompartment;

  CDataVector< CModelValue >::iterator itValue = mValues.begin();
  CDataVector< CModelValue >::iterator endValue = mValues.end();

  for (; itValue != endValue; ++itValue)
    *ppEntity++ = itValue;

  mStateTemplate.setUserOrder(UserEntities);

  mJacobianPivot.resize(mStateTemplate.getNumIndependent() + MNumMetabolitesReactionDependent);
  //now sized to the number of entities with ODEs + all metabolites dependent on reactions

  const size_t * pUserOrder = mStateTemplate.getUserOrder().array();
  const size_t * pUserOrderEnd = pUserOrder + mStateTemplate.getUserOrder().size();
  const CVector< const CModelEntity *> & Entities = mStateTemplate.getEntities();

  size_t i;

  for (i = 0; pUserOrder != pUserOrderEnd; ++pUserOrder)
    {
      const Status & status = Entities[*pUserOrder]->getStatus();

      if (status == Status::ODE ||
          (status == Status::REACTIONS && Entities[*pUserOrder]->isUsed()))
        mJacobianPivot[i++] = *pUserOrder - 1;
    }

  return true;
}

bool CModel::updateInitialValues(const CCore::Framework & framework, bool refreshParameterSet)
{
  bool success = compileIfNecessary(NULL);

  mpMathContainer->fetchInitialState();
  mpMathContainer->updateInitialValues(framework);
  mpMathContainer->pushInitialState();

  if (refreshParameterSet)
    refreshActiveParameterSet();

  return success;
}

void CModel::stateToIntialState()
{
  mpMathContainer->fetchState();
  mpMathContainer->setInitialState(mpMathContainer->getState(false));
  mpMathContainer->updateInitialValues(CCore::Framework::ParticleNumbers);
  mpMathContainer->pushInitialState();
  refreshActiveParameterSet();
}

// virtual
const std::string CModel::getUnits() const
{
  return mTimeUnit;
}

bool CModel::setVolumeUnit(const std::string & name)
{
  mVolumeUnit = name;

  if (CUnit(mVolumeUnit).isDimensionless())
    mVolumeUnit = CUnit::prettyPrint(name);

  return true;
}

const std::string & CModel::getVolumeUnit() const
{
  return mVolumeUnit;
}

std::string CModel::getVolumeUnitName() const
{
  return mVolumeUnit;
}

//****

bool CModel::setAreaUnit(const std::string & name)
{
  mAreaUnit = name;

  if (CUnit(mAreaUnit).isDimensionless())
    mAreaUnit = CUnit::prettyPrint(name);

  return true;
}

const std::string & CModel::getAreaUnit() const
{
  return mAreaUnit;
}

std::string CModel::getAreaUnitName() const
{
  return mAreaUnit;
}

//****
bool CModel::setLengthUnit(const std::string & name)
{
  mLengthUnit = name;

  if (CUnit(mLengthUnit).isDimensionless())
    mLengthUnit = CUnit::prettyPrint(name);

  return true;
}

const std::string & CModel::getLengthUnit() const
{
  return mLengthUnit;
}

std::string CModel::getLengthUnitName() const
{
  return mLengthUnit;
}

//****

bool CModel::setTimeUnit(const std::string & name)
{
  mTimeUnit = name;

  if (CUnit(mTimeUnit).isDimensionless())
    mTimeUnit = CUnit::prettyPrint(name);

  return true;
}

const std::string & CModel::getTimeUnit() const
{
  return mTimeUnit;
}

std::string CModel::getTimeUnitName() const
{
  return mTimeUnit;
}

//****

bool CModel::setQuantityUnit(const std::string & name,
                             const CCore::Framework & framework)
{
  mQuantityUnit = name;

  CUnit QuantityUnit(mQuantityUnit);

  if (QuantityUnit.isDimensionless())
    mQuantityUnit = CUnit::prettyPrint(name);

  if (QuantityUnit.isUndefined()) return false;

  std::set< CUnitComponent >::const_iterator dimensionless = QuantityUnit.getComponents().find(CBaseUnit::dimensionless);
  mQuantity2NumberFactor = dimensionless->getMultiplier() * pow(10.0, dimensionless->getScale());

  // Avogadro is no longer stored in the multiplier it has its own component:
  std::set< CUnitComponent >::const_iterator avogadro = QuantityUnit.getComponents().find(CBaseUnit::avogadro);

  if (avogadro != QuantityUnit.getComponents().end())
    {
      mQuantity2NumberFactor *= pow(mAvogadro, avogadro->getExponent());
    }

  mNumber2QuantityFactor = 1.0 / mQuantity2NumberFactor;

  updateInitialValues(framework);

  return true;
}

const std::string CModel::getQuantityUnit() const
{
  return mQuantityUnit;
}

std::string CModel::getQuantityUnitName() const
{
  return mQuantityUnit;
}

void CModel::setModelType(const CModel::ModelType & modelType)
{mType = modelType;}

const CModel::ModelType & CModel::getModelType() const
{return mType;}

void CModel::setAvogadro(const C_FLOAT64 & avogadro, const CCore::Framework & frameWork)
{
  mAvogadro = avogadro;

  setQuantityUnit(mQuantityUnit, frameWork);
}

const C_FLOAT64 & CModel::getAvogadro() const
{
  return mAvogadro;
}

const C_FLOAT64 & CModel::getQuantity2NumberFactor() const
{return mQuantity2NumberFactor;}

const C_FLOAT64 & CModel::getNumber2QuantityFactor() const
{return mNumber2QuantityFactor;}

//*****

bool CModel::appendDirectDependents(const CDataContainer & container,
                                    CDataObject::DataObjectSet & dependentReactions,
                                    CDataObject::DataObjectSet & dependentMetabolites,
                                    CDataObject::DataObjectSet & dependentCompartments,
                                    CDataObject::DataObjectSet & dependentModelValues,
                                    CDataObject::DataObjectSet & dependentEvents,
                                    CDataObject::DataObjectSet & dependentEventAssignments,
                                    const bool & onlyStructural) const
{
  ObjectSet Objects;
  Objects.insert(&container);

  return appendDirectDependents(Objects, dependentReactions, dependentMetabolites, dependentCompartments, dependentModelValues, dependentEvents, dependentEventAssignments, onlyStructural);
}

bool CModel::appendDirectDependents(const CDataObject::ObjectSet & objects,
                                    CDataObject::DataObjectSet & dependentReactions,
                                    CDataObject::DataObjectSet & dependentMetabolites,
                                    CDataObject::DataObjectSet & dependentCompartments,
                                    CDataObject::DataObjectSet & dependentModelValues,
                                    CDataObject::DataObjectSet & dependentEvents,
                                    CDataObject::DataObjectSet & dependentEventAssignments,
                                    const bool & onlyStructural) const
{
  size_t Size = dependentReactions.size() +
                dependentMetabolites.size() +
                dependentCompartments.size() +
                dependentModelValues.size() +
                dependentEvents.size() +
                dependentEventAssignments.size();

  ObjectSet Dependents;

  mStructuralDependencies.appendDirectDependents(objects, Dependents);

  if (!onlyStructural)
    {
      ObjectSet::const_iterator itObject = objects.begin();
      ObjectSet::const_iterator endObject = objects.end();

      // Map the descendants to math objects
      ObjectSet Candidates;
      DataObjectSet Descendants;

      for (; itObject != endObject; ++itObject)
        {
          if (dynamic_cast< const CDataContainer * >(*itObject) != NULL)
            {
              static_cast< const CDataContainer * >(*itObject)->getDescendants(Descendants);
            }

          // We need to directly add the event targets since they do not appear in any dependency graph
          if (dynamic_cast< const CEvent * >(*itObject) != NULL)
            {
              CDataVectorN< CEventAssignment >::const_iterator itAssignment = static_cast< const CEvent * >(*itObject)->getAssignments().begin();
              CDataVectorN< CEventAssignment >::const_iterator endAssignment = static_cast< const CEvent * >(*itObject)->getAssignments().end();

              for (; itAssignment != endAssignment; ++itAssignment)
                {
                  Dependents.insert(itAssignment->getTargetObject());
                }
            }
        }

      std::set< const CDataObject * >::const_iterator it = Descendants.begin();
      std::set< const CDataObject * >::const_iterator end = Descendants.end();

      for (; it != end; ++it)
        {
          Candidates.insert(mpMathContainer->getMathObject(*it));
          Dependents.insert(*it);
        }

      Candidates.erase(NULL);

      // Retrieve dependent math object
      mpMathContainer->getInitialDependencies().appendDirectDependents(Candidates, Dependents);
      mpMathContainer->getTransientDependencies().appendDirectDependents(Candidates, Dependents);
    }

  // Map objects to compartments, species, model values, reactions, events, and event assignments
  CObjectInterface::ObjectSet::const_iterator itDependent = Dependents.begin();
  CObjectInterface::ObjectSet::const_iterator endDependent = Dependents.end();

  for (; itDependent != endDependent; ++itDependent)
    {
      const CDataObject * pDataObject = (*itDependent)->getDataObject();

      // We need to  map to the correct model appropriate containers:
      // Compartments, Species, Model Values, Reactions, Event Assignments, and Events
      if (pDataObject == NULL) continue;

      const CDataContainer * pContainer = NULL;

      if (((pContainer = dynamic_cast< const CReaction * >(pDataObject)) != NULL ||
           (pContainer = pDataObject->getObjectAncestor("Reaction")) != NULL) &&
          objects.find(pContainer) == objects.end())
        {
          dependentReactions.insert(pContainer);
        }
      else if (((pContainer = dynamic_cast< const CMetab * >(pDataObject)) != NULL ||
                (pContainer = pDataObject->getObjectAncestor("Metabolite")) != NULL) &&
               objects.find(pContainer) == objects.end())
        {
          dependentMetabolites.insert(pContainer);
        }
      else if (((pContainer = dynamic_cast< const CCompartment * >(pDataObject)) != NULL ||
                (pContainer = pDataObject->getObjectAncestor("Compartment")) != NULL) &&
               objects.find(pContainer) == objects.end())
        {
          dependentCompartments.insert(pContainer);
        }
      else if (((pContainer = dynamic_cast< const CModelValue * >(pDataObject)) != NULL ||
                (pContainer = pDataObject->getObjectAncestor("ModelValue")) != NULL) &&
               objects.find(pContainer) == objects.end())
        {
          dependentModelValues.insert(pContainer);
        }
      else if (((pContainer = dynamic_cast< const CEventAssignment * >(pDataObject)) != NULL ||
                (pContainer = pDataObject->getObjectAncestor("EventAssignment")) != NULL) &&
               objects.find(pContainer) == objects.end())
        {
          dependentEventAssignments.insert(pContainer);
        }
      else if (((pContainer = dynamic_cast< const CEvent * >(pDataObject)) != NULL ||
                (pContainer = pDataObject->getObjectAncestor("Event")) != NULL) &&
               objects.find(pContainer) == objects.end())
        {
          dependentEvents.insert(pContainer);
        }
    }

  return Size < dependentReactions.size() +
         dependentMetabolites.size() +
         dependentCompartments.size() +
         dependentModelValues.size() +
         dependentEvents.size() +
         dependentEventAssignments.size();
}

bool CModel::appendAllDependents(const CDataContainer & container,
                                 DataObjectSet & dependentReactions,
                                 DataObjectSet & dependentMetabolites,
                                 DataObjectSet & dependentCompartments,
                                 DataObjectSet & dependentModelValues,
                                 DataObjectSet & dependentEvents,
                                 DataObjectSet & dependentEventAssignments,
                                 const bool & onlyStructural) const
{
  ObjectSet Objects;
  Objects.insert(&container);

  return appendAllDependents(Objects, dependentReactions, dependentMetabolites, dependentCompartments, dependentModelValues, dependentEvents, dependentEventAssignments, onlyStructural);
}

bool CModel::appendAllDependents(const ObjectSet & objects,
                                 DataObjectSet & dependentReactions,
                                 DataObjectSet & dependentMetabolites,
                                 DataObjectSet & dependentCompartments,
                                 DataObjectSet & dependentModelValues,
                                 DataObjectSet & dependentEvents,
                                 DataObjectSet & dependentEventAssignments,
                                 const bool & onlyStructural) const
{
  const CReaction * pIgnoreReaction = NULL;
  ObjectSet Ignored;

  if (objects.size() == 1)
    {
      if (dynamic_cast< const CCopasiParameter * >(*objects.begin()))
        {
          pIgnoreReaction = dynamic_cast< const CReaction * >(static_cast<  const CCopasiParameter * >(*objects.begin())->getObjectAncestor("Reaction"));
        }
      else if (dynamic_cast< const CReaction * >(*objects.begin()))
        {
          const CChemEq & Equation = static_cast< const CReaction * >(*objects.begin())->getChemEq();
          CDataVector < CChemEqElement >::const_iterator it = Equation.getBalances().begin();
          CDataVector < CChemEqElement >::const_iterator end = Equation.getBalances().end();

          for (; it != end; ++it)
            {
              const CMetab * pMetab = it->getMetabolite();

              if (pMetab != NULL &&
                  pMetab->getStatus() == CModelEntity::Status::REACTIONS)
                {
                  CMathObject * pMathObject = mpMathContainer->getMathObject(pMetab->getRateReference());
                  CMathObject * pInitialMathObject = mpMathContainer->getInitialValueObject(pMathObject);

                  Ignored.insert(pMathObject);

                  if (pInitialMathObject != pMathObject)
                    {
                      Ignored.insert(pInitialMathObject);
                    }

                  Ignored.insert(mpMathContainer->getMathObject(pMetab->getTransitionTimeReference()));
                }
            }
        }
    }

  dependentReactions.erase(pIgnoreReaction);

  size_t Size = dependentReactions.size() +
                dependentMetabolites.size() +
                dependentCompartments.size() +
                dependentModelValues.size() +
                dependentEvents.size() +
                dependentEventAssignments.size();

  ObjectSet Dependents;

  mStructuralDependencies.appendAllDependents(objects, Dependents);

  if (!onlyStructural)
    {
      // Map the descendants to math objects
      ObjectSet Candidates;
      DataObjectSet Descendants;
      ObjectSet::const_iterator itObject = objects.begin();
      ObjectSet::const_iterator endObject = objects.end();

      for (; itObject != endObject; ++itObject)
        if (dynamic_cast< const CDataContainer * >(*itObject) != NULL)
          {
            static_cast< const CDataContainer * >(*itObject)->getDescendants(Descendants);
          }

      std::set< const CDataObject * >::const_iterator it = Descendants.begin();
      std::set< const CDataObject * >::const_iterator end = Descendants.end();

      for (; it != end; ++it)
        {
          // We are missing initial values associated with the object that only exist in the math container
          CMathObject * pMathObject = mpMathContainer->getMathObject(*it);
          CMathObject * pInitialMathObject = mpMathContainer->getInitialValueObject(pMathObject);

          Candidates.insert(pMathObject);

          if (pInitialMathObject != pMathObject)
            {
              Candidates.insert(pInitialMathObject);
            }

          Dependents.insert(*it);
        }

      Candidates.erase(NULL);
      Ignored.erase(NULL);

      // Retrieve dependent math object
      mpMathContainer->getInitialDependencies().appendAllDependents(Candidates, Dependents, Ignored);
      mpMathContainer->getTransientDependencies().appendAllDependents(Candidates, Dependents, Ignored);
    }

  // Map objects to compartments, species, model values, reactions, events, and event assignments
  CObjectInterface::ObjectSet::const_iterator itDependent = Dependents.begin();
  CObjectInterface::ObjectSet::const_iterator endDependent = Dependents.end();

  for (; itDependent != endDependent; ++itDependent)
    {
      const CDataObject * pDataObject = (*itDependent)->getDataObject();

      // We need to  map to the correct model appropriate containers:
      // Compartments, Species, Model Values, Reactions, Event Assignments, and Events
      if (pDataObject == NULL) continue;

      const CDataContainer * pContainer = NULL;

      if (((pContainer = dynamic_cast< const CReaction * >(pDataObject)) != NULL ||
           (pContainer = dynamic_cast< const CReaction * >(pDataObject->getObjectParent())) != NULL) &&
          objects.find(pContainer) == objects.end())
        {
          dependentReactions.insert(pContainer);
        }
      else if (((pContainer = dynamic_cast< const CMetab * >(pDataObject)) != NULL ||
                (pContainer = dynamic_cast< const CMetab * >(pDataObject->getObjectParent())) != NULL) &&
               (static_cast< const CMetab * >(pContainer)->getStatus() != CModelEntity::Status::REACTIONS ||
                (pDataObject->getObjectName() != "ParticleNumberRate" &&
                 pDataObject->getObjectName() != "Rate" &&
                 pDataObject->getObjectName() != "Noise" &&
                 pDataObject->getObjectName() != "IntensiveNoise" &&
                 pDataObject->getObjectName() != "TransitionTime")) &&
               objects.find(pContainer) == objects.end())
        {
          dependentMetabolites.insert(pContainer);
        }
      else if (((pContainer = dynamic_cast< const CCompartment * >(pDataObject)) != NULL ||
                (pContainer = dynamic_cast< const CCompartment * >(pDataObject->getObjectParent())) != NULL) &&
               objects.find(pContainer) == objects.end())
        {
          dependentCompartments.insert(pContainer);
        }
      else if (((pContainer = dynamic_cast< const CModelValue * >(pDataObject)) != NULL ||
                (pContainer = dynamic_cast< const CModelValue * >(pDataObject->getObjectParent())) != NULL) &&
               objects.find(pContainer) == objects.end())
        {
          dependentModelValues.insert(pContainer);
        }
      else if (((pContainer = dynamic_cast< const CEventAssignment * >(pDataObject)) != NULL ||
                (pContainer = dynamic_cast< const CEventAssignment * >(pDataObject->getObjectParent())) != NULL) &&
               objects.find(pContainer) == objects.end())
        {
          dependentEventAssignments.insert(pContainer);
        }
      else if (((pContainer = dynamic_cast< const CEvent * >(pDataObject)) != NULL ||
                (pContainer = dynamic_cast< const CEvent * >(pDataObject->getObjectParent())) != NULL) &&
               objects.find(pContainer) == objects.end())
        {
          dependentEvents.insert(pContainer);
        }
    }

  return Size < dependentReactions.size() +
         dependentMetabolites.size() +
         dependentCompartments.size() +
         dependentModelValues.size() +
         dependentEvents.size() +
         dependentEventAssignments.size();
}

//**********************************************************************

CMetab* CModel::createMetabolite(const std::string & name,
                                 const std::string & compartment,
                                 const C_FLOAT64 & iconc,
                                 const CMetab::Status & status)
{
  size_t Index;

  if (mCompartments.size() == 0)
    return NULL;

  if (compartment == "")
    Index = 0;
  else if ((Index = mCompartments.getIndex(compartment)) == C_INVALID_INDEX)
    return NULL;

  if (mCompartments[Index].getMetabolites().getIndex(name) != C_INVALID_INDEX)
    return NULL;

  CMetab * pMetab = new CMetab(name);

  if (!mCompartments[Index].addMetabolite(pMetab))
    {
      delete pMetab;
      return NULL;
    }

  pMetab->setStatus(status);
  pMetab->setInitialConcentration(iconc);
  pMetab->setInitialValue(iconc * mCompartments[Index].getInitialValue() * mpModel->getQuantity2NumberFactor());

  if (!mMetabolites.add(pMetab, false))
    return NULL;

  mCompileIsNecessary = true;

  return pMetab;
}

bool CModel::removeMetabolite(const size_t index,
                              const bool & recursive)
{
  const CMetab* pMetabolite = &getMetabolites()[index];
  return removeMetabolite(pMetabolite, recursive);
}

bool CModel::removeMetabolite(const std::string & key,
                              const bool & recursive)
{
  CMetab* pMetabolite =
    dynamic_cast< CMetab * >(CRootContainer::getKeyFactory()->get(key));
  return removeMetabolite(pMetabolite, recursive);
}

bool CModel::removeMetabolite(const CMetab* pMetabolite,
                              const bool & recursive)
{
  if (!pMetabolite)
    return false;

  if (recursive)
    {
      std::string key = pMetabolite->getKey();

      ObjectSet Deleted;
      Deleted.insert(pMetabolite);
      removeDependentModelObjects(Deleted);

      // the metabolite might have been deleted above, need to aquire the pointer
      pMetabolite =
        dynamic_cast< CMetab * >(CRootContainer::getKeyFactory()->get(key));
    }

  if (pMetabolite != NULL)
    {
      /* Assure that all references are removed */
      mMetabolites.remove(const_cast< CMetab * >(pMetabolite));
      mMetabolitesX.remove(const_cast< CMetab * >(pMetabolite));
      removeDataObject(pMetabolite);
      pdelete(pMetabolite);
    }

  clearMoieties();
  mCompileIsNecessary = true;

  return true;
}

CCompartment* CModel::createCompartment(const std::string & name,
                                        const C_FLOAT64 & volume)
{
  // check if there is already a volume with this name
  if (mCompartments.getIndex(name) != C_INVALID_INDEX)
    return NULL;

  CCompartment * cpt = new CCompartment(name);

  cpt->setInitialValue(volume);
  //cpt->setVolume(volume);

  if (!mCompartments.add(cpt, true))
    {
      delete cpt;
      return NULL;
    }

  mCompileIsNecessary = true;
  return cpt;
}

bool CModel::removeCompartment(const size_t index,
                               const bool & recursive)
{
  const CCompartment * pCompartment = &getCompartments()[index];
  return removeCompartment(pCompartment, recursive);
}

bool CModel::removeCompartment(const std::string & key,
                               const bool & recursive)
{
  CCompartment *pCompartment =
    dynamic_cast< CCompartment * >(CRootContainer::getKeyFactory()->get(key));
  return removeCompartment(pCompartment, recursive);
}

bool CModel::removeCompartment(const CCompartment * pCompartment,
                               const bool & recursive)
{
  if (!pCompartment)
    return false;

  if (recursive)
    {
      ObjectSet Deleted;
      Deleted.insert(pCompartment);
      removeDependentModelObjects(Deleted);
    }

  //Check if Compartment with that name exists
  size_t index =
    mCompartments.CDataVector< CCompartment >::getIndex(pCompartment);

  if (index == C_INVALID_INDEX)
    return false;

  removeDataObject(pCompartment);
  mCompartments.CDataVector< CCompartment >::remove(index);

  mCompileIsNecessary = true;

  return true;
}

CReaction* CModel::createReaction(const std::string & name)
{
  if (mSteps.getIndex(name) != C_INVALID_INDEX)
    return NULL;

  CReaction * pReaction = new CReaction(name);

  if (!mSteps.add(pReaction, true))
    {
      delete pReaction;
      return NULL;
    }

  mCompileIsNecessary = true;
  return pReaction;
}

bool CModel::removeReaction(const std::string & key,
                            const bool & recursive)
{
  CReaction * pReaction =
    dynamic_cast< CReaction * >(CRootContainer::getKeyFactory()->get(key));
  return removeReaction(pReaction, recursive);
}

bool CModel::removeReaction(const size_t index,
                            const bool & recursive)
{
  const CReaction * pReaction = &getReactions()[index];
  return removeReaction(pReaction, recursive);
}

bool CModel::removeReaction(const CReaction * pReaction,
                            const bool & recursive)
{
  if (!pReaction)
    return false;

  if (recursive)
    {
      ObjectSet Deleted;
      Deleted.insert(pReaction);
      removeDependentModelObjects(Deleted);
    }

  //Check if Reaction exists
  size_t index =
    mSteps.CDataVector< CReaction >::getIndex(pReaction);

  if (index == C_INVALID_INDEX)
    return false;

  removeDataObject(pReaction);
  mSteps.CDataVector< CReaction >::remove(index);

  clearMoieties();
  mCompileIsNecessary = true;

  return true;
}

bool CModel::removeLocalReactionParameter(const std::string & key,
    const bool & recursive)
{
  CCopasiParameter * pParameter =
    dynamic_cast< CCopasiParameter * >(CRootContainer::getKeyFactory()->get(key));

  if (pParameter == NULL)
    return false;

  if (recursive)
    {
      ObjectSet Deleted;
      Deleted.insert(pParameter);
      removeDependentModelObjects(Deleted);
    }

  return true;
}

CModelValue* CModel::createModelValue(const std::string & name,
                                      const C_FLOAT64 & value)
{
  // check if there is already a value with this name
  if (mValues.getIndex(name) != C_INVALID_INDEX)
    return NULL;

  CModelValue * cmv = new CModelValue(name);

  cmv->setInitialValue(value);

  if (!mValues.add(cmv, true))
    {
      delete cmv;
      return NULL;
    }

  mCompileIsNecessary = true;
  return cmv;
}

void CModel::removeDependentModelObjects(const CDataObject::ObjectSet & deletedObjects,
    const bool & onlyStructural)
{
  DataObjectSet Reactions;
  DataObjectSet Metabolites;
  DataObjectSet Values;
  DataObjectSet Compartments;
  DataObjectSet Events;
  DataObjectSet EventAssignments;

  appendAllDependents(deletedObjects, Reactions, Metabolites, Compartments, Values, Events, EventAssignments, onlyStructural);

  std::set<const CDataObject*>::const_iterator it, end;

  for (it = Reactions.begin(), end = Reactions.end(); it != end; ++it)
    {
      removeDataObject(*it);
      removeReaction((*it)->getKey(), false);
    }

  for (it = Metabolites.begin(), end = Metabolites.end(); it != end; ++it)
    {
      removeDataObject(*it);
      removeMetabolite((*it)->getKey(), false);
    }

  for (it = Compartments.begin(), end = Compartments.end(); it != end; ++it)
    {
      removeDataObject(*it);
      removeCompartment((*it)->getKey(), false);
    }

  for (it = Values.begin(), end = Values.end(); it != end; ++it)
    {
      removeDataObject(*it);
      removeModelValue((*it)->getKey(), false);
    }

  // Event Assignments mut be deleted before events as else we may have an invalid pointer
  for (it = EventAssignments.begin(), end = EventAssignments.end(); it != end; ++it)
    if (*it)
      {
        removeDataObject(*it);
        delete *it;
      }

  for (it = Events.begin(), end = Events.end(); it != end; ++it)
    {
      removeDataObject(*it);
      removeEvent((*it)->getKey(), false);
    }

  return;
}

bool CModel::removeModelValue(const size_t index,
                              const bool & recursive)
{
  const CModelValue * pMV = &getModelValues()[index];
  return removeModelValue(pMV, recursive);
}
bool CModel::removeModelValue(const std::string & key,
                              const bool & recursive)
{
  CModelValue *pModelValue =
    dynamic_cast< CModelValue * >(CRootContainer::getKeyFactory()->get(key));
  return removeModelValue(pModelValue, recursive);
}

bool CModel::removeModelValue(const CModelValue * pModelValue,
                              const bool & recursive)
{
  if (!pModelValue)
    return false;

  if (recursive)
    {
      ObjectSet Deleted;
      Deleted.insert(pModelValue);
      removeDependentModelObjects(Deleted);
    }

  //Check if Value with that name exists
  size_t index =
    mValues.CDataVector< CModelValue >::getIndex(pModelValue);

  if (index == C_INVALID_INDEX)
    return false;

  removeDataObject(pModelValue);
  mValues.CDataVector< CModelValue >::remove(index);

  mCompileIsNecessary = true;

  return true;
}

bool CModel::removeFunction(const CFunction * pFunction,
                            const bool & recursive)
{
  if (pFunction == NULL)
    return false;

  if (recursive)
    {
      ObjectSet Deleted;
      Deleted.insert(pFunction);
      removeDependentModelObjects(Deleted);
    }

  removeDataObject(pFunction);

  mCompileIsNecessary = true;

  return true;
}

CEvent* CModel::createEvent(const std::string & name)
{
  if (mEvents.getIndex(name) != C_INVALID_INDEX)
    return NULL;

  CEvent * pEvent = new CEvent(name, this);

  if (!mEvents.add(pEvent, true))
    {
      delete pEvent;
      return NULL;
    }

  mCompileIsNecessary = true;
  return pEvent;
}

bool CModel::removeEvent(const size_t index,
                         const bool & recursive)
{
  const CEvent * pEvent = &mEvents[index];

  return removeEvent(pEvent, recursive);
}

bool CModel::removeEvent(const std::string & key,
                         const bool & recursive)
{
  CEvent * pEvent = dynamic_cast< CEvent * >(CRootContainer::getKeyFactory()->get(key));

  return removeEvent(pEvent, recursive);
}

bool CModel::removeEvent(const CEvent * pEvent,
                         const bool & /* recursive */)
{
  if (!pEvent)
    return false;

  //Check if Event exists
  size_t index =
    mEvents.CDataVector< CEvent >::getIndex(pEvent);

  if (index == C_INVALID_INDEX)
    return false;

  removeDataObject(pEvent);
  mEvents.CDataVector< CEvent >::remove(index);

  clearMoieties();

  mCompileIsNecessary = true;

  return true;
}

#include <copasi/parameterFitting/CExperiment.h>
#include <copasi/parameterFitting/CExperimentSet.h>
#include <copasi/parameterFitting/CExperimentObjectMap.h>

#include <copasi/parameterFitting/CFitTask.h>
#include <copasi/parameterFitting/CFitProblem.h>

#include <copasi/trajectory/CTrajectoryTask.h>
#include <copasi/trajectory/CTrajectoryProblem.h>

#include <copasi/commandline/CLocaleString.h>

std::string getNextId(const std::string& base, int count)
{
  std::stringstream str;
  str << base << count;
  return str.str();
}

const CObjectInterface * getDependentOrNull(const std::map< const CObjectInterface *, size_t > &  dependentMap, int index)
{

  std::map< const CObjectInterface *, size_t >::const_iterator it = dependentMap.begin();

  while (it != dependentMap.end())
    {
      if (it->second == index) return it->first;

      ++it;
    }

  return NULL;
}

bool
CModel::createEventsForTimeseries(CExperiment* experiment/* = NULL*/)
{

#pragma region   //find_experiment

  if (experiment == NULL)
    {
      // find experiment and invoke with it
      const CExperiment* theExperiment = NULL;

      const CDataModel* dataModel = getObjectDataModel();
      const CFitTask* task = dynamic_cast<const CFitTask*>(&dataModel->getTaskList()->operator[]("Parameter Estimation"));

      if (task == NULL)
        {
          CCopasiMessage(CCopasiMessage::ERROR,
                         "The parameter estimation was not correctly setup.");
          return false;
        }

      const CFitProblem *problem = static_cast<const CFitProblem*>(task->getProblem());

      const CExperimentSet& experiments = problem->getExperimentSet();

      // find first time course experiment
      for (size_t i = 0; i < experiments.size(); ++i)
        {
          const CExperiment* exp = experiments.getExperiment(i);

          if (exp->getExperimentType() == CTaskEnum::Task::timeCourse)
            {
              theExperiment = exp;
              break;
            }
        }

      // if still not found, bail
      if (theExperiment == NULL)
        {
          CCopasiMessage(CCopasiMessage::ERROR,
                         "No suitable experiment could be found, please first define a time course experiment and map the data.");
          return false;
        }

      if (experiments.size() > 1)
        {
          CCopasiMessage(CCopasiMessage::WARNING,
                         "You have defined multiple experiments, this function will only create events for the first time course experiment, unless another is specified.");
        }

      return createEventsForTimeseries(const_cast<CExperiment*>(theExperiment));
    }

#pragma endregion //find_experiment

  if (experiment->getExperimentType() != CTaskEnum::Task::timeCourse)
    {
      CCopasiMessage(CCopasiMessage::ERROR,
                     "The selected experiment, is not a time series experiment.");
      return false;
    }

  // need to get at the time course data

  std::ifstream File;
  File.open(CLocaleString::fromUtf8(experiment->getFileName()).c_str());

  size_t CurrentLine = 1;

  if (!experiment->read(File, CurrentLine))
    {
      CCopasiMessage(CCopasiMessage::ERROR,
                     "The data file could not be read.");
      return false;
    }

  if (!experiment->compile(mpMathContainer))
    {
      CCopasiMessage(CCopasiMessage::ERROR,
                     "The experiment could not be compiled.");
      return false;
    }

  // grab time column
  const CVector<double>& time = experiment->getTimeData();
  size_t numRows = experiment->getNumDataRows();

  if (numRows <= 1)
    {
      CCopasiMessage(CCopasiMessage::ERROR,
                     "Need at least 2 data rows in the experiment.");
      return false;
    }

  //size_t numCols = experiment->getNumColumns();
  const std::map< const CObjectInterface *, size_t > &  dependentMap = experiment->getDependentObjectsMap();

  // then go through each time point
  for (size_t i = 0; i < numRows; ++i)
    {
      double current = time[i];

      // skip initial time
      if (current == 0) continue;

      CEvent* pEvent = createEvent(getNextId("pe_event_", i));

      if (pEvent == NULL)
        {
          CCopasiMessage(CCopasiMessage::ERROR,
                         "Could not create event, please verify that the events have not been created before.");
          return false;
        }

      std::stringstream trigger; trigger
          << "<"  << getObject(CRegisteredCommonName("Reference=Time"))->getCN()
          << ">" << " > " << current;
      pEvent->setTriggerExpression(trigger.str());
      pEvent->getTriggerExpressionPtr()->compile();

      const CMatrix<double>& data = experiment->getDependentData();

      // create event and assignment for each mapping with its value
      for (size_t j = 0; j < data.numCols(); ++j)
        {

          const CObjectInterface * currentObject = getDependentOrNull(dependentMap, j);  //objects[j + 1];

          if (currentObject == NULL ||
              currentObject->getDataObject() ==  NULL ||
              currentObject->getDataObject()->getObjectParent() == NULL) continue;

          double value = data(i, j);

          // don't include missing data points
          if (value != value)
            {
              std::string displayName = currentObject->getDataObject()->getObjectParent()->getObjectDisplayName();
              CCopasiMessage(CCopasiMessage::WARNING,
                             "At time %.2f: a missing data point was encountered for '%s', the value has been ignored."
                             , current, displayName.c_str());
              continue;
            }

          CEventAssignment * pNewAssignment =
            new CEventAssignment(currentObject->getDataObject()->getObjectParent()->getCN());
          std::stringstream assignmentStr; assignmentStr << value;
          pNewAssignment->setExpression(assignmentStr.str());
          pNewAssignment->getExpressionPtr()->compile();
          pEvent->getAssignments().add(pNewAssignment, true);
        }
    }

  return true;
}

//*****************************************************************

bool CModel::convert2NonReversible()
{
  // TODO check if there are any reversible reactions
  // TODO warn the user
  // TODO tell the GUI about changes -> not from here
  // TODO generate report ?
  // TODO check if newly generated reaction names are valid
  // TODO map, so that the same function is split only once

  bool success = true;

  std::vector< CReaction * > reactionsToDelete;

  CReaction *reac0, *reac1, *reac2;
  std::string fn, rn1, rn2;

  //CModel* model = dynamic_cast< CModel * >(CRootContainer::getKeyFactory()->get(objKey));
  //if (!model) return false;

  CDataVectorN< CReaction > & steps = this->getReactions();

  size_t i, imax = steps.size();

  for (i = 0; i < imax; ++i)
    if (steps[i].isReversible())
      {
        std::vector< std::pair< const CDataObject *, const CDataObject * > > ParameterMap;

        reac0 = &steps[i];
        rn1 = reac0->getObjectName() + " (forward)";
        rn2 = reac0->getObjectName() + " (backward)";

        fn = reac0->getFunction()->getObjectName();

        const CFunction* pFunc = reac0->getFunction();

        bool massaction = (fn == "Mass action (reversible)");

        std::pair<CFunction *, CFunction *> tmp;

        if (massaction)
          {
            //set functions to mass action (irrev)
            tmp.first = dynamic_cast<CFunction*>
                        (CRootContainer::getFunctionList()-> findFunction("Mass action (irreversible)"));
            assert(tmp.first);
            tmp.second = tmp.first;
          }
        else //not mass action
          {
            //try splitting
            tmp = pFunc->splitFunction(NULL, pFunc->getObjectName() + " (forward part)",
                                       pFunc->getObjectName() + " (backward part)");

            if ((tmp.first == NULL) || (tmp.second == NULL))
              {
                // Create a message that the conversion for this reaction failed.
                CCopasiMessage(CCopasiMessage::ERROR, MCReaction + 12,
                               reac0->getObjectName().c_str(), fn.c_str());
                success = false;

                pdelete(tmp.first);
                pdelete(tmp.second);
                continue;
              }

            tmp.first = CRootContainer::getFunctionList()->addAndAdaptName(tmp.first);

            tmp.second = CRootContainer::getFunctionList()->addAndAdaptName(tmp.second);
          }

        size_t i, imax;

        //**** create 1st reaction.
        reac1 = createReaction(rn1);
        reac1->setReversible(false);
        //substrates
        imax = reac0->getChemEq().getSubstrates().size();

        for (i = 0; i < imax; ++i)
          reac1->addSubstrate(reac0->getChemEq().getSubstrates()[i].getMetaboliteKey(),
                              reac0->getChemEq().getSubstrates()[i].getMultiplicity());

        //products
        imax = reac0->getChemEq().getProducts().size();

        for (i = 0; i < imax; ++i)
          reac1->addProduct(reac0->getChemEq().getProducts()[i].getMetaboliteKey(),
                            reac0->getChemEq().getProducts()[i].getMultiplicity());

        //function
        reac1->setFunction(tmp.first);

        //**** create 2nd reaction.
        reac2 = createReaction(rn2);
        reac2->setReversible(false);
        //substrates -> products
        imax = reac0->getChemEq().getSubstrates().size();

        for (i = 0; i < imax; ++i)
          reac2->addProduct(reac0->getChemEq().getSubstrates()[i].getMetaboliteKey(),
                            reac0->getChemEq().getSubstrates()[i].getMultiplicity());

        //products -> substrates
        imax = reac0->getChemEq().getProducts().size();

        for (i = 0; i < imax; ++i)
          reac2->addSubstrate(reac0->getChemEq().getProducts()[i].getMetaboliteKey(),
                              reac0->getChemEq().getProducts()[i].getMultiplicity());

        //function
        reac2->setFunction(tmp.second);

        //mapping for both reactions
        if (massaction)
          {
            // the parameter names of the massaction kinetics are hardcoded here.
            if (reac0->isLocalParameter("k1"))
              reac1->setParameterValue("k1", reac0->getParameterValue("k1"));
            else
              reac1->setParameterCNs("k1", reac0->getParameterCNs("k1"));

            reac1->setParameterCNs("substrate", reac0->getParameterCNs("substrate"));

            if (reac0->isLocalParameter("k2"))
              reac2->setParameterValue("k1", reac0->getParameterValue("k2"));
            else
              reac2->setParameterCNs("k1", reac0->getParameterCNs("k2"));

            reac2->setParameterCNs("substrate", reac0->getParameterCNs("product"));

            // Bug 2143: We need to replace any occurrence of the reaction parameter of the
            // reversible reaction with its replacement in the forward or backwards reaction
            ParameterMap.push_back(std::make_pair(reac0->getParameters().getParameter("k1")->getValueReference(),
                                                  reac1->getParameters().getParameter("k1")->getValueReference()));
            ParameterMap.push_back(std::make_pair(reac0->getParameters().getParameter("k2")->getValueReference(),
                                                  reac2->getParameters().getParameter("k1")->getValueReference()));
          }
        else //not mass action
          {
            const CFunctionParameters & fps = reac0->getFunctionParameters();
            imax = fps.size();

            for (i = 0; i < imax; ++i)
              {
                const CFunctionParameter * fp = fps[i];
                assert(fp);
                assert(fp->getType() == CFunctionParameter::DataType::FLOAT64);

                switch (fp->getUsage())
                  {
                    case CFunctionParameter::Role::SUBSTRATE:
                      reac1->setParameterCNs(fp->getObjectName(),
                                             reac0->getParameterCNs(fp->getObjectName()));

                      // It is possible (see Bug 1830) that the split function may have additional modifier.
                      // This will happen e.g. if the product is referenced in the forward part of the reaction.
                      if (reac2->setParameterCNs(fp->getObjectName(),
                                                 reac0->getParameterCNs(fp->getObjectName())))
                        {
                          reac2->addModifier(reac0->getParameterObjects(fp->getObjectName())[0]->getKey());
                        }

                      break;

                    case CFunctionParameter::Role::PRODUCT:

                      // It is possible (see Bug 1830) that the split function may have additional modifier.
                      // This will happen e.g. if the product is referenced in the forward part of the reaction.
                      if (reac1->setParameterCNs(fp->getObjectName(),
                                                 reac0->getParameterCNs(fp->getObjectName())))
                        {
                          reac1->addModifier(reac0->getParameterObjects(fp->getObjectName())[0]->getKey());
                        }

                      reac2->setParameterCNs(fp->getObjectName(),
                                             reac0->getParameterCNs(fp->getObjectName()));
                      break;

                    case CFunctionParameter::Role::MODIFIER:

                      if (reac1->setParameterCNs(fp->getObjectName(),
                                                 reac0->getParameterCNs(fp->getObjectName())))
                        {
                          // Add the modifier
                          reac1->addModifier(reac0->getParameterObjects(fp->getObjectName())[0]->getKey());
                        }

                      if (reac2->setParameterCNs(fp->getObjectName(),
                                                 reac0->getParameterCNs(fp->getObjectName())))
                        {
                          // Add the modifier
                          reac2->addModifier(reac0->getParameterObjects(fp->getObjectName())[0]->getKey());
                        }

                      break;

                    case CFunctionParameter::Role::PARAMETER:

                      if (reac0->isLocalParameter(fp->getObjectName()))
                        {

                          reac1->setParameterValue(fp->getObjectName(),
                                                   reac0->getParameterValue(fp->getObjectName()));
                          reac2->setParameterValue(fp->getObjectName(),
                                                   reac0->getParameterValue(fp->getObjectName()));
                        }
                      else
                        {
                          reac1->setParameterCNs(fp->getObjectName(),
                                                 reac0->getParameterCNs(fp->getObjectName()));
                          reac2->setParameterCNs(fp->getObjectName(),
                                                 reac0->getParameterCNs(fp->getObjectName()));
                        }

                      // Bug 2143: We need to replace any occurrence of the reaction parameter of the
                      // reversible reaction with its replacement in the forward or backwards reaction
                      {
                        CCopasiParameter * pOldParameter = reac0->getParameters().getParameter(fp->getObjectName());
                        CCopasiParameter * pNewParameter = reac1->getParameters().getParameter(fp->getObjectName());

                        if (pNewParameter == NULL)
                          {
                            pNewParameter = reac2->getParameters().getParameter(fp->getObjectName());
                          }

                        ParameterMap.push_back(std::make_pair(pOldParameter->getValueReference(), pNewParameter->getValueReference()));
                      }

                      break;

                    default:
                      reac1->setParameterCNs(fp->getObjectName(),
                                             reac0->getParameterCNs(fp->getObjectName()));
                      reac2->setParameterCNs(fp->getObjectName(),
                                             reac0->getParameterCNs(fp->getObjectName()));
                      break;
                  }
              }
          }

        reac1->compile();
        reac2->compile();

        std::string Old;
        std::string New;
        std::string Infix;

        // Bug 2143: We need to replace any occurrence of the reaction parameter of the
        // reversible reaction with its replacement in the forward or backwards reaction

        std::vector< std::pair< const CDataObject *, const CDataObject * > >::const_iterator itParameter = ParameterMap.begin();
        std::vector< std::pair< const CDataObject *, const CDataObject * > >::const_iterator endParameter = ParameterMap.end();

        for (; itParameter != endParameter; ++itParameter)
          {
            Old = "<" + itParameter->first->getCN() + ">";
            New = "<" + itParameter->second->getCN() + ">";
            replaceInExpressions(Old, New);
          }

        // BUG 1848. We need to replace all references to the flux and particle flux
        // with the difference of the forward and backward reaction fluxes and particle fluxes, i.e,
        // flux = forward.flux - backward.flux

        Old = "<" + reac0->getFluxReference()->getCN() + ">";
        New = "(<" + reac1->getFluxReference()->getCN() + "> - <" + reac2->getFluxReference()->getCN() + ">)";
        replaceInExpressions(Old, New);

        // particleFlux = forward.particleFlux - backward.particleFlux
        Old = "<" + reac0->getParticleFluxReference()->getCN() + ">";
        New = "(<" + reac1->getParticleFluxReference()->getCN() + "> - <" + reac2->getParticleFluxReference()->getCN() + ">)";
        replaceInExpressions(Old, New);

        // Schedule the old reaction for removal.
        reactionsToDelete.push_back(reac0);
      }

  imax = reactionsToDelete.size();

  for (i = 0; i < imax; ++i)
    {
      delete reactionsToDelete[i];
    }

  if (imax != 0)
    {
      setCompileFlag(true);
    }

  return success;
}

void CModel::replaceInExpressions(const std::string & oldStr,
                                  const std::string & New)
{
  std::string Infix;

  // We need to find all expressions which reference the old parameter (first value of the itParameter)
  // Compartments (expression, initial expression)
  CDataVector< CCompartment >::iterator itComp = mCompartments.begin();
  CDataVector< CCompartment >::iterator endComp = mCompartments.end();

  for (; itComp != endComp; ++itComp)
    {
      Infix = itComp->getExpression();

      if (stringReplace(Infix, oldStr, New)) itComp->setExpression(Infix);

      Infix = itComp->getInitialExpression();

      if (stringReplace(Infix, oldStr, New)) itComp->setInitialExpression(Infix);

      Infix = itComp->getNoiseExpression();

      if (stringReplace(Infix, oldStr, New)) itComp->setNoiseExpression(Infix);
    }

  // Species (expression, initial expression)
  CDataVector< CMetab >::iterator itMetab = mMetabolitesX.begin();
  CDataVector< CMetab >::iterator endMetab = mMetabolitesX.end();

  for (; itMetab != endMetab; ++itMetab)
    {
      Infix = itMetab->getExpression();

      if (stringReplace(Infix, oldStr, New)) itMetab->setExpression(Infix);

      Infix = itMetab->getInitialExpression();

      if (stringReplace(Infix, oldStr, New)) itMetab->setInitialExpression(Infix);

      Infix = itMetab->getNoiseExpression();

      if (stringReplace(Infix, oldStr, New)) itMetab->setNoiseExpression(Infix);
    }

  // Model Quantities (expression, initial expression)
  CDataVector< CModelValue >::iterator itValue = mValues.begin();
  CDataVector< CModelValue >::iterator endValue = mValues.end();

  for (; itValue != endValue; ++itValue)
    {
      Infix = itValue->getExpression();

      if (stringReplace(Infix, oldStr, New)) itValue->setExpression(Infix);

      Infix = itValue->getInitialExpression();

      if (stringReplace(Infix, oldStr, New)) itValue->setInitialExpression(Infix);

      Infix = itValue->getNoiseExpression();

      if (stringReplace(Infix, oldStr, New)) itValue->setNoiseExpression(Infix);
    }

  // Events (trigger, delay, assignments)
  CDataVector< CEvent >::iterator itEvent = mEvents.begin();
  CDataVector< CEvent >::iterator endEvent = mEvents.end();

  for (; itEvent != endEvent; ++itEvent)
    {
      Infix = itEvent->getTriggerExpression();

      if (stringReplace(Infix, oldStr, New)) itEvent->setTriggerExpression(Infix);

      Infix = itEvent->getDelayExpression();

      if (stringReplace(Infix, oldStr, New)) itEvent->setDelayExpression(Infix);

      Infix = itEvent->getPriorityExpression();

      if (stringReplace(Infix, oldStr, New)) itEvent->setPriorityExpression(Infix);

      CDataVector< CEventAssignment >::iterator itAssignment = itEvent->getAssignments().begin();
      CDataVector< CEventAssignment >::iterator endAssignment = itEvent->getAssignments().end();

      for (; itAssignment != endAssignment; ++itAssignment)
        {
          Infix = itAssignment->getExpression();

          if (stringReplace(Infix, oldStr, New)) itAssignment->setExpression(Infix);
        }
    }
}
//**********************************************************************

void CModel::removeDataObject(const CDataObject * pObject)
{
  mStructuralDependencies.removeObject(pObject);
  mpMathContainer->removeDataObject(pObject);
}

void CModel::initObjects()
{
  mpModel = this;

  //mKey = CRootContainer::getKeyFactory()->add("Model", this);

  // The regular CModelEntity mechanism does not work since
  // CModel is created before mStateTemplate :(
  mStateTemplate.add(this);

  // units

  mpIValueReference->setObjectName("Initial Time");
  mpValueReference->setObjectName("Time");

  mRate = 1.0;

  addObjectReference("Comments", *const_cast<std::string *>(&getNotes()));

  // These are broken since they contain pointers to values :(
  //  addVectorReference("Fluxes", mFluxes, CDataObject::ValueDbl);
  //  addVectorReference("Particle Fluxes", mParticleFluxes, CDataObject::ValueDbl);

  addMatrixReference("Stoichiometry", mStoi, CDataObject::ValueDbl);
  addMatrixReference("Reduced Model Stoichiometry", mRedStoi, CDataObject::ValueDbl);
  addMatrixReference("Link Matrix", mLView, CDataObject::ValueDbl);

  mpStoiAnnotation = new CDataArray("Stoichiometry(ann)", this, new CMatrixInterface<CMatrix<C_FLOAT64> >(&mStoi), true);
  mpStoiAnnotation->setDescription("Stoichiometry Matrix");
  mpStoiAnnotation->setMode(0, CDataArray::Mode::Objects);
  mpStoiAnnotation->setDimensionDescription(0, "Species that are controlled by reactions");
  mpStoiAnnotation->setMode(1, CDataArray::Mode::VectorOnTheFly);
  mpStoiAnnotation->setDimensionDescription(1, "Reactions");
  mpStoiAnnotation->setCopasiVector(1, mSteps);

  mpRedStoiAnnotation = new CDataArray("Reduced stoichiometry(ann)", this, new CMatrixInterface<CMatrix<C_FLOAT64> >(&mRedStoi), true);
  mpRedStoiAnnotation->setDescription("Reduced stoichiometry Matrix");
  mpRedStoiAnnotation->setMode(0, CDataArray::Mode::Objects);
  mpRedStoiAnnotation->setDimensionDescription(0, "Species (reduced system)");
  mpRedStoiAnnotation->setMode(1, CDataArray::Mode::VectorOnTheFly);
  mpRedStoiAnnotation->setDimensionDescription(1, "Reactions");
  mpRedStoiAnnotation->setCopasiVector(1, mSteps);

  mpLinkMatrixAnnotation = new CDataArray("Link matrix(ann)", this, new CMatrixInterface<CLinkMatrixView>(&mLView), true);
  mpLinkMatrixAnnotation->setDescription("Link matrix");
  mpLinkMatrixAnnotation->setMode(0, CDataArray::Mode::Objects);
  mpLinkMatrixAnnotation->setDimensionDescription(0, "Species that are controlled by reactions (full system)");
  mpLinkMatrixAnnotation->setMode(1, CDataArray::Mode::Objects);
  mpLinkMatrixAnnotation->setDimensionDescription(1, "Species (reduced system)");

  mpMathContainer = new CMathContainer(*this);
}

bool CModel::hasReversibleReaction() const
{
  size_t i, imax = mSteps.size();

  for (i = 0; i < imax; ++i) if (mSteps[i].isReversible()) return true;

  return false;
}

std::string CModel::suitableForStochasticSimulation() const
{
  size_t i, reactSize = mSteps.size();
  C_INT32 multInt;
  size_t j;
  C_FLOAT64 multFloat;
  //  C_INT32 metabSize = mMetabolites->size();

  for (i = 0; i < reactSize; i++) // for every reaction
    {
      // TEST getCompartmentNumber() == 1
      //if (mSteps[i].getCompartmentNumber() != 1) return - 1;

      // TEST isReversible() == 0
      if (mSteps[i].isReversible() != 0)
        return "At least one reaction is reversible. That means stochastic simulation is not possible. \nYou can use \"Tools|Convert to irreversible\" which will split the reversible reactions \n into two irreversible reactions. However you should check the kinetics afterwards.";

      // TEST integer stoichiometry
      // Iterate through each the metabolites
      // Juergen: the number of rows of mStoi equals the number of non-fixed metabs!
      //  for (j=0; i<metabSize; j++)
      for (j = 0; j < mStoi.numRows(); j++)
        {
          multFloat = mStoi(j, i);
          multInt = static_cast<C_INT32>(floor(multFloat + 0.5)); // +0.5 to get a rounding out of the static_cast to int!

          if ((multFloat - multInt) > 0.01)
            return "Not all stoichiometries are integer numbers. \nThat means that discrete simulation is not possible.";
        }
    }

  for (i = 0; i < mMetabolites.size(); ++i)
    {
      if (mMetabolites[i].getInitialValue() > std::numeric_limits< C_INT64 >::max())
        return "At least one particle number in the initial state is too big.";
    }

  return ""; // Model is appropriate for hybrid simulation
}

void CModel::buildLinkZero()
{
  mL.build(mStoi);
  mNumMetabolitesReactionIndependent = mL.getNumIndependent();
  mL.doRowPivot(mStoi);

  return;
}

const bool & CModel::isAutonomous() const
{return mIsAutonomous;}

bool CModel::isStateVariable(const CDataObject * pObject) const
{
  if (pObject == NULL)
    {
      return false;
    }

  // We check whether the object itself or the parent object is a state variable
  // A state variable is an independent model entity, a dependent species, or
  // a fixed entity, which is an event target.

  const CModelEntity * pEntity = dynamic_cast< const CModelEntity * >(pObject);

  if (pEntity == NULL)
    {
      pEntity = dynamic_cast< const CModelEntity * >(pObject->getObjectParent());
    }

  if (pEntity == NULL)
    {
      return false;
    }

  const CModelEntity * const* it = mStateTemplate.beginIndependent();
  const CModelEntity * const* end = mStateTemplate.endDependent();

  for (; it != end; ++it)
    {
      if (*it == pEntity)
        {
          return true;
        }
    }

  std::set< const CModelEntity * > EventTargets = CObjectLists::getEventTargets(this);
  std::set< const CModelEntity * >::const_iterator itSet = EventTargets.begin();
  std::set< const CModelEntity * >::const_iterator endSet = EventTargets.end();

  for (; itSet != endSet; ++itSet)
    {
      if (*itSet == pEntity)
        {
          return true;
        }
    }

  return false;
}

CDataObject * CModel::getCorrespondingTransientObject(const CDataObject * pObject) const
{
  // CModelEntities and derived classes are the only object which have initial and transient values
  // Note, for species we have distinguish between particle number and concentration.

  const CModelEntity * pEntity = dynamic_cast< const CModelEntity * >(pObject);

  if (pEntity == NULL)
    {
      pEntity = dynamic_cast< const CModelEntity * >(pObject->getObjectParent());
    }

  if (pEntity == NULL)
    {
      return const_cast< CDataObject * >(pObject);
    }

  const CMetab * pMetab = dynamic_cast< const CMetab * >(pEntity);

  if (pMetab != NULL && pMetab->getInitialConcentrationReference() == pObject)
    {
      return pMetab->getConcentrationReference();
    }

  return pEntity->getValueReference();
}

std::vector< const CEvaluationTree * > CModel::getTreesWithDiscontinuities() const
{
  std::vector< const CEvaluationTree * > TreesWithDiscontinuities;

  // Check all expressions for entities of type ASSIGNMENT and ODE
  const CModelEntity *const* ppEntity = mStateTemplate.getEntities().array();
  const CModelEntity *const* ppEntityEnd = ppEntity + mStateTemplate.size();

  for (; ppEntity != ppEntityEnd; ++ppEntity)
    {
      switch ((*ppEntity)->getStatus())
        {
          case Status::ODE:

            if ((*ppEntity)->getNoiseExpressionPtr() &&
                (*ppEntity)->getNoiseExpressionPtr()->hasDiscontinuity())
              {
                TreesWithDiscontinuities.push_back((*ppEntity)->getNoiseExpressionPtr());
              }

          // Intentionally no break statement!

          case Status::ASSIGNMENT:

            if ((*ppEntity)->getExpressionPtr() &&
                (*ppEntity)->getExpressionPtr()->hasDiscontinuity())
              {
                TreesWithDiscontinuities.push_back((*ppEntity)->getExpressionPtr());
              }

            break;

          default:
            break;
        }
    }

  // Check all kinetic functions.
  CDataVector< CReaction >::const_iterator itReaction = mSteps.begin();
  CDataVector< CReaction >::const_iterator endReaction = mSteps.end();

  for (; itReaction != endReaction; ++itReaction)
    {
      if (itReaction->getFunction() &&
          itReaction->getFunction()->hasDiscontinuity())
        {
          TreesWithDiscontinuities.push_back(itReaction->getFunction());
        }

      if (itReaction->getNoiseExpressionPtr() &&
          itReaction->getNoiseExpressionPtr()->hasDiscontinuity())
        {
          TreesWithDiscontinuities.push_back(itReaction->getNoiseExpressionPtr());
        }
    }

  // Check all event triggers
  CDataVector< CEvent >::const_iterator itEvent = mEvents.begin();
  CDataVector< CEvent >::const_iterator endEvent = mEvents.end();

  for (; itEvent != endEvent; ++itEvent)
    {
      if (itEvent->getTriggerExpressionPtr() &&
          itEvent->getTriggerExpressionPtr()->hasDiscontinuity())
        {
          TreesWithDiscontinuities.push_back(itEvent->getTriggerExpressionPtr());
        }
    }

  return TreesWithDiscontinuities;
}

CIssue CModel::compileEvents()
{
  CIssue issue; //Default: Success

  CObjectInterface::ContainerList ListOfContainer;

  CDataVectorN< CEvent >::iterator it = mEvents.begin();
  CDataVectorN< CEvent >::iterator end = mEvents.end();

  for (; it != end; ++ it)
    {
      issue &= it->compile(ListOfContainer);
    }

  return issue;
}

void CModel::updateInitialValues(std::set< const CDataObject * > & changedObjects, bool refreshParameterSet)
{
  bool success = compileIfNecessary(NULL);

  CCore::CUpdateSequence UpdateSequence = buildInitialRefreshSequence(changedObjects);

  mpMathContainer->fetchInitialState();
  mpMathContainer->applyUpdateSequence(UpdateSequence);
  mpMathContainer->pushInitialState();

  if (refreshParameterSet)
    refreshActiveParameterSet();
}

void CModel::updateInitialValues(const CDataObject* changedObject, bool refreshParameterSet)
{
  std::set< const CDataObject * > changedObjects;
  changedObjects.insert(changedObject);
  updateInitialValues(changedObjects, refreshParameterSet);
}

CCore::CUpdateSequence
CModel::buildInitialRefreshSequence(std::set< const CDataObject * > & changedObjects)
{
  // Map the changed objects to their math equivalents;
  std::set< const CDataObject * >::const_iterator it = changedObjects.begin();
  std::set< const CDataObject * >::const_iterator end = changedObjects.end();

  CObjectInterface::ObjectSet ChangedObjects;

  for (; it != end; ++it)
    {
      CMathObject * pObject = mpMathContainer->getMathObject(*it);

      if (pObject != NULL)
        {
          ChangedObjects.insert(pObject);
        }
      else
        {
          // Issue 1170: We need to add elements of the stoichiometry, reduced stoichiometry,
          // and link matrices.
          ChangedObjects.insert(*it);
        }
    }

  CCore::CUpdateSequence UpdateSequence;
  mpMathContainer->getInitialDependencies().getUpdateSequence(UpdateSequence,
      CCore::SimulationContext::UpdateMoieties,
      ChangedObjects,
      mpMathContainer->getInitialStateObjects());

  return UpdateSequence;
}

CVector< C_FLOAT64 > CModel::initializeAtolVector(const C_FLOAT64 & atol, const bool & reducedModel) const
{
  CVector< C_FLOAT64 > Atol;

  if (reducedModel)
    Atol.resize(mStateTemplate.getNumIndependent());
  else
    Atol.resize(mStateTemplate.getNumIndependent() + getNumDependentReactionMetabs());

  C_FLOAT64 * pAtol = Atol.array();
  C_FLOAT64 * pEnd = pAtol + Atol.size();

  C_FLOAT64 InitialValue;
  C_FLOAT64 Limit;

  const CModelEntity *const* ppEntity = mStateTemplate.beginIndependent();
  const CMetab * pMetab;

  for (; pAtol != pEnd; ++pAtol, ++ppEntity)
    {
      *pAtol = atol;

      InitialValue = fabs((*ppEntity)->getInitialValue());

      if ((pMetab = dynamic_cast< const CMetab * >(*ppEntity)) != NULL)
        {
          Limit =
            fabs(pMetab->getCompartment()->getInitialValue()) * mQuantity2NumberFactor;

          if (InitialValue != 0.0)
            *pAtol *= std::min(Limit, InitialValue);
          else
            *pAtol *= std::max(1.0, Limit);
        }
      else if (InitialValue != 0.0)
        *pAtol *= std::min(1.0, InitialValue);
    }

  return Atol;
}

const CMathContainer & CModel::getMathContainer() const
{return *mpMathContainer;}

CMathContainer & CModel::getMathContainer()
{return *mpMathContainer;}

#include "copasi/function/CDerive.h"

CEvaluationNode* CModel::prepareElasticity(const CReaction * pReaction, const CModelEntity* pVar, bool simplify)
{
  //TODO check: pVar should be a pointer to a variable (ODE or REACTION), a local parameter, an initial value, or a fixed entity
  //it should not be an entity with an assignment.

  //here we select the actual derivation variable: concentration, or value, or volume, etc. TODO
  const CDataObject * pVarObj = pVar->CModelEntity::getValueObject();
  //const CDataObject * pVarObj = pVar->getValueObject();

  CEvaluationNode* tmp;
  CExpression * derivExp = new CExpression("derivative expression", this);

  //first handle mass action
  if (dynamic_cast<const CMassAction*>(pReaction->getFunction()))
    {
      //create the explicit kinetic law, so that we can calculate the derivative
      //we use the metabs in the object nodes. These are automatically converted to concentration references
      //during compile later
      CEvaluationNode* tmp_ma;

      //forward part
      std::vector<const CDataObject*> prod;
      size_t j;

      for (j = 0; j < pReaction->getMap().getObjects()[1].vector->size(); ++j)
        {
          prod.push_back((*(pReaction->getMap().getObjects()[1].vector))[j].value); //substrates
        }

      prod.push_back(pReaction->getMap().getObjects()[0].value); //k1

      std::vector<const CEvaluationNode*> env;
      CDerive der(env, derivExp, simplify);

      if (prod.size() == 1)
        tmp_ma = new CEvaluationNodeObject(CEvaluationNode::SubType::CN, "<" + prod[0]->getCN() + ">");
      else
        {
          tmp_ma = der.multiply(new CEvaluationNodeObject(CEvaluationNode::SubType::CN, "<" + prod[0]->getCN() + ">"),
                                new CEvaluationNodeObject(CEvaluationNode::SubType::CN, "<" + prod[1]->getCN() + ">"));

          for (j = 2; j < prod.size(); ++j)
            tmp_ma = der.multiply(tmp_ma, new CEvaluationNodeObject(CEvaluationNode::SubType::CN, "<" + prod[j]->getCN() + ">"));
        }

      //backwards part
      if (pReaction->isReversible())
        {
          CEvaluationNode * ttt = tmp_ma; //store the forward part
          CEvaluationNode * tt2; //for the backwards part
          prod.clear();

          for (j = 0; j < pReaction->getMap().getObjects()[3].vector->size(); ++j)
            {
              prod.push_back((*(pReaction->getMap().getObjects()[3].vector))[j].value); //products
            }

          prod.push_back(pReaction->getMap().getObjects()[2].value); //k2

          if (prod.size() == 1)
            tt2 = new CEvaluationNodeObject(CEvaluationNode::SubType::CN, "<" + prod[0]->getCN() + ">");
          else
            {
              tt2 = der.multiply(new CEvaluationNodeObject(CEvaluationNode::SubType::CN, "<" + prod[0]->getCN() + ">"),
                                 new CEvaluationNodeObject(CEvaluationNode::SubType::CN, "<" + prod[1]->getCN() + ">"));

              for (j = 2; j < prod.size(); ++j)
                tt2 = der.multiply(tt2, new CEvaluationNodeObject(CEvaluationNode::SubType::CN, "<" + prod[j]->getCN() + ">"));
            }

          tmp_ma = new CEvaluationNodeOperator(CEvaluationNode::SubType::MINUS, "-");
          tmp_ma->addChild(ttt);
          tmp_ma->addChild(tt2);
        }

      CExpression * tmpExp = new CExpression("Mass action expression", this);
      der.compileTree(tmp_ma);

      tmpExp->setRoot(tmp_ma);
      tmpExp->compile(); //this converts references from model entities to value references

      tmp = der.deriveBranch(tmp_ma, pVarObj);

      CDerive::deleteBranch(tmp_ma);
    }
  else //not mass action
    {
      //create call environment for the kinetic function
      //do we have to call something on CReaction to make sure that the map is uptodate?
      std::vector<const CEvaluationNode*> env;
      size_t i, imax = pReaction->getMap().getObjects().size();
      env.resize(imax);

      for (i = 0; i < imax; ++i)
        {
          const CDataObject* tmpObj = pReaction->getMap().getObjects()[i].value;
          //if we have a metab, its always the concentration
          const CMetab* tmpMetab = dynamic_cast<const CMetab*>(tmpObj);

          if (tmpMetab)
            tmpObj = tmpMetab->getConcentrationReference();

          std::string tmpstr = tmpObj ? "<" + tmpObj->getCN() + ">" : "<>";
          CEvaluationNodeObject* tmpENO = new CEvaluationNodeObject(CEvaluationNode::SubType::CN, tmpstr);
          env[i] = tmpENO;
          tmpENO->compile(); //this uses derivExp as a dummy expression (so that the node has a context for the compile()
        }

      CDerive derive(env, derivExp, simplify);
      tmp = derive.deriveBranch(pReaction->getFunction()->getRoot(), pVarObj);

      for (int l = (int)env.size() - 1; l >= 0; l--)
        {
          delete const_cast<CEvaluationNode*>(env[l]);
        }

      env.clear();
    }

  derivExp->setRoot(tmp);
  derivExp->compile();

  //tmp->printRecursively(std::cout);
  return tmp;
}

size_t getUsedSymbolCount(const std::string& unit, const std::string& symbol)
{
  CUnit Unit(unit);

  return Unit.getUsedSymbols().count(symbol);
}

// Return a set of any COPASI object using this symbol.
CDataObject::DataObjectSet CModel::getUnitSymbolUsage(std::string symbol) const
{
  DataObjectSet usages;

  //Is it used in the Model Values?
  CDataVector< CModelValue >::const_iterator it = getModelValues().begin();
  CDataVector< CModelValue >::const_iterator end = getModelValues().end();
  CUnit unit;

  for (; it != end; ++it)
    {
      unit.setExpression(it->getUnitExpression());

      if (unit.getUsedSymbols().count(symbol))
        usages.insert(it);
    }

  //Is it used for any of the default model units?
  if (getUsedSymbolCount(mVolumeUnit, symbol) ||
      getUsedSymbolCount(mAreaUnit, symbol) ||
      getUsedSymbolCount(mLengthUnit, symbol) ||
      getUsedSymbolCount(mTimeUnit, symbol) ||
      getUsedSymbolCount(mQuantityUnit, symbol))
    usages.insert(this);

  return usages;
}

// Return a set of any Copasi object using this symbol.
void CModel::changeUnitExpressionSymbols(std::string oldSymbol, std::string newSymbol)
{
  //Model Values
  CDataVector< CModelValue >::iterator it = getModelValues().begin();
  CDataVector< CModelValue >::iterator end = getModelValues().end();

  for (; it != end; ++it)
    {
      it->setUnitExpression(CUnit::replaceSymbol(it->getUnitExpression(), oldSymbol, newSymbol));
    }

  mVolumeUnit = CUnit::replaceSymbol(mVolumeUnit, oldSymbol, newSymbol);
  mAreaUnit = CUnit::replaceSymbol(mAreaUnit, oldSymbol, newSymbol);
  mLengthUnit = CUnit::replaceSymbol(mLengthUnit, oldSymbol, newSymbol);
  mTimeUnit = CUnit::replaceSymbol(mTimeUnit, oldSymbol, newSymbol);
  mQuantityUnit = CUnit::replaceSymbol(mQuantityUnit, oldSymbol, newSymbol);

  return;
}

std::map< std::string, CUnit > CModel::getUsedUnits() const
{
  std::map< std::string, CUnit > UsedUnits;

  //Model Values
  CDataVector< CModelValue >::const_iterator it = getModelValues().begin();
  CDataVector< CModelValue >::const_iterator end = getModelValues().end();

  for (; it != end; ++it)
    {
      UsedUnits[it->getUnitExpression()] = CUnit(it->getUnits());
    }

  UsedUnits[mVolumeUnit] = CUnit(mVolumeUnit);
  UsedUnits[mAreaUnit] = CUnit(mAreaUnit);
  UsedUnits[mLengthUnit] = CUnit(mLengthUnit);
  UsedUnits[mTimeUnit] = CUnit(mTimeUnit);
  UsedUnits[mQuantityUnit] = CUnit(mQuantityUnit);

  return UsedUnits;
}
