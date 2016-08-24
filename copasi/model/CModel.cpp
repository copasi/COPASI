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

#include "copasi.h"

// #define DEBUG_MATRIX

#include "CCompartment.h"
#include "CMetab.h"
#include "CModel.h"
#include "CState.h"
#include "CModelValue.h"
#include "CObjectLists.h"
#include "function/CFunctionDB.h"
#include "report/CCopasiObjectReference.h"
#include "report/CKeyFactory.h"
#include "utilities/CCopasiException.h"
#include "utilities/CCopasiMessage.h"
#include "utilities/CCopasiVector.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "utilities/CVector.h"
#include "utilities/CluX.h"
#include "utilities/utility.h"
#include "utilities/CProcessReport.h"
#include "CReactionInterface.h"
#include "utilities/CAnnotatedMatrix.h"
#include "CMetabNameInterface.h"

#include "math/CMathContainer.h"

#include "lapack/blaswrap.h"
#include "lapack/lapackwrap.h"

#define MNumMetabolitesReactionDependent (mNumMetabolitesReaction - mNumMetabolitesReactionIndependent)

const char * CModel::ModelTypeNames[] =
{"deterministic", "stochastic", NULL};

CModel::CModel(CCopasiContainer* pParent):
  CModelEntity("New Model", pParent, "Model"),
  mStateTemplate(*this),
  mPhysicalDependencies(),
  mVolumeUnit("ml"),
  mAreaUnit("m\xc2\xb2"),
  mLengthUnit("m"),
  mTimeUnit("s"),
  mQuantityUnit("mmol"),
  mDimensionlessUnits(5),
  mType(deterministic),
  mCompartments("Compartments", this),
  mMetabolites("Metabolites", this),
  mMetabolitesX("Reduced Model Metabolites", this),
  mSteps("Reactions", this),
  mEvents("Events", this),
  mParticleFluxes(),
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
  mpAvogadroReference(new CCopasiObjectReference< C_FLOAT64 >("Avogadro Constant", this, mAvogadro, CCopasiObject::ValueDbl)),
  mQuantity2NumberFactor(std::numeric_limits< C_FLOAT64 >::quiet_NaN()),
  mpQuantity2NumberFactorReference(new CCopasiObjectReference< C_FLOAT64 >("Quantity Conversion Factor", this, mQuantity2NumberFactor, CCopasiObject::ValueDbl)),
  mNumber2QuantityFactor(std::numeric_limits< C_FLOAT64 >::quiet_NaN()),
  mpCompileHandler(NULL),
  mReorderNeeded(false),
  mIsAutonomous(true),
  mBuildInitialSequence(true),
  mpMathContainer(NULL)
{
  initObjects();

  setStatus(TIME);
  setUsed(true);
  mIValue = 0.0;

  setQuantityUnit(mQuantityUnit, CModelParameter::ParticleNumbers);

  initializeMetabolites();

  mpMathContainer = new CMathContainer(*this);

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

  CCopasiRootContainer::getKeyFactory()->remove(mKey);

  DESTRUCTOR_TRACE;
}

// virtual
bool CModel::setObjectParent(const CCopasiContainer * pParent)
{
  return CCopasiContainer::setObjectParent(pParent);
}

// virtual
std::string CModel::getChildObjectUnits(const CCopasiObject * pObject) const
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
  CCopasiDataModel* pDataModel = getObjectDataModel();
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

  try
    {
      setQuantityUnit(tmp, CModelParameter::Concentration); // set the factors
    }

  catch (CCopasiException &)
    {
      try
        {
          setQuantityUnit(tmp.substr(0, 1) + "mol", CModelParameter::Concentration);
        }

      catch (CCopasiException &)
        {
          setQuantityUnit("mmol", CModelParameter::Concentration);
        }
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

      (*pMetabolite) = pDataModel->pOldMetabolites->operator[](i);
    }

  initializeMetabolites();

  if ((Fail = CCopasiRootContainer::getFunctionList()->load(configBuffer))) // slow
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

bool CModel::compile()
{
  bool success = true;
  bool RenameHandlerEnabled = false;

  if (CCopasiObject::smpRenameHandler != NULL)
    {
      RenameHandlerEnabled = CCopasiObject::smpRenameHandler->isEnabled();
      CCopasiObject::smpRenameHandler->setEnabled(false);
    }

  mpValueReference->addDirectDependency(this);

  unsigned C_INT32 CompileStep = 0;
  size_t hCompileStep;

  if (mpCompileHandler)
    {
      mpCompileHandler->setName("Compiling model...");
      unsigned C_INT32 totalSteps = 7;
      hCompileStep = mpCompileHandler->addItem("Compile Process",
                     CompileStep,
                     &totalSteps);
    }

  CompileStep = 0;

  if (mpCompileHandler && !mpCompileHandler->progressItem(hCompileStep))
    {
      success = false;
      goto finish;
    }

  buildStoi();
  CompileStep = 1;

  if (mpCompileHandler && !mpCompileHandler->progressItem(hCompileStep))
    {
      success = false;
      goto finish;
    }

  buildLinkZero();
  CompileStep = 2;

  if (mpCompileHandler && !mpCompileHandler->progressItem(hCompileStep))
    {
      success = false;
      goto finish;
    }

  buildRedStoi();
  CompileStep = 3;

  if (mpCompileHandler && !mpCompileHandler->progressItem(hCompileStep))
    {
      success = false;
      goto finish;
    }

  buildMoieties();
  CompileStep = 4;

  if (mpCompileHandler && !mpCompileHandler->progressItem(hCompileStep))
    {
      success = false;
      goto finish;
    }

  buildStateTemplate();
  CompileStep = 5;

  if (mpCompileHandler && !mpCompileHandler->progressItem(hCompileStep))
    {
      success = false;
      goto finish;
    }

  CompileStep = 6;

  if (mpCompileHandler && !mpCompileHandler->progressItem(hCompileStep))
    {
      success = false;
      goto finish;
    }

  buildUserOrder();

  if (mpCompileHandler) mpCompileHandler->finishItem(hCompileStep);

  {
    CCopasiVector< CMetab >::iterator itSpecies = mMetabolitesX.begin();
    CCopasiVector< CMetab >::iterator endSpecies = mMetabolitesX.end();

    for (; itSpecies != endSpecies; ++itSpecies)
      {
        itSpecies->compileIsInitialConcentrationChangeAllowed();
      }
  }

  //update annotations
  updateMatrixAnnotations();

  success &= compileEvents();
  // success &= mpMathModel->compile(this);

  if (!success)
    {
      mIsAutonomous = false;
    }
  else
    {
      mCompileIsNecessary = false;
    }

  // writeDependenciesToDotFile();

  buildDependencyGraphs();

  mpMathContainer->compile();
  mpMathContainer->fetchInitialState();
  mpMathContainer->updateInitialValues(CModelParameterSet::ParticleNumbers);
  mpMathContainer->pushInitialState();

  mIsAutonomous = mpMathContainer->isAutonomous();

  // CMathContainer CopyModel(MathModel);

  // Update the parameter set
  mParameterSet.createFromModel();

finish:

  // Since we have applied the pivot to the stoichiometry matrix and the species
  // we do not need them any longer. In fact it is detrimental if other functions rely
  // on consistency between the stoichiometry matrix, reduced stoichiometry matrix and the Link matrix..
  mL.clearPivoting();

  if (RenameHandlerEnabled)
    {
      CCopasiObject::smpRenameHandler->setEnabled(true);
    }

  mCompileIsNecessary = !success;

  return success;
}

bool CModel::buildDependencyGraphs()
{
  mPhysicalDependencies.clear();

  // The initial values of the model entities
  // We need to add the time for non-autonomous models.
  const CModelEntity *const* ppEntity = mStateTemplate.beginIndependent() - 1;
  const CModelEntity *const* ppEntityEnd = mStateTemplate.endFixed();

  for (; ppEntity != ppEntityEnd; ++ppEntity)
    {
      const CMetab * pSpecies = dynamic_cast< const CMetab * >(*ppEntity);

      // TODO CRITICAL Create support for physical dependencies.
    }

  return true;
}

void CModel::setCompileFlag(bool flag)
{
  mCompileIsNecessary = flag;
}

const bool & CModel::isCompileNecessary() const
{
  return mCompileIsNecessary;
}

bool CModel::compileIfNecessary(CProcessReport* pProcessReport)
{
  bool success = true;

  if (mCompileIsNecessary)
    {
      mpCompileHandler = pProcessReport;

      try
        {
          success &= compile();
        }

      catch (...)
        {
          success = false;
        }

      mpCompileHandler = NULL;
    }

  return success;
}

bool CModel::forceCompile(CProcessReport* pProcessReport)
{
  setCompileFlag();
  return compileIfNecessary(pProcessReport);
}

void CModel::buildStoi()
{
  unsigned C_INT32 i, numCols;

  initializeMetabolites();

  size_t numRows;
  numRows = mNumMetabolitesReaction;
  numCols = (unsigned C_INT32) mSteps.size();

  mParticleFluxes.resize(numCols);
  mStoi.resize(numRows, numCols);
  mStoi = 0.0;

  size_t hProcess;

  if (mpCompileHandler)
    {
      i = 0;
      hProcess = mpCompileHandler->addItem("Building Stoichiometry", i, &numCols);
    }

  C_FLOAT64 * pCol, *pColEnd;
  pCol = mStoi.array();
  pColEnd = mStoi.array() + numCols;

  C_FLOAT64 * pRow, *pRowEnd;
  pRowEnd = mStoi.array() + numRows * numCols;

  CCopasiVector< CReaction >::iterator itStep = mSteps.begin();
  CCopasiVector< CMetab >::const_iterator itMetab;

  for (; pCol < pColEnd; ++pCol, ++itStep)
    {
      if (mpCompileHandler && !mpCompileHandler->progressItem(hProcess)) return;

      // Since we are stepping through the reactions we can check whether
      // the kinetic functions are usable.
      if (!itStep->getFunction()->isUsable())
        CCopasiMessage(CCopasiMessage::ERROR, MCReaction + 11,
                       itStep->getObjectName().c_str(),
                       itStep->getFunction()->getObjectName().c_str());

      const CCopasiVector< CChemEqElement > & Balance = itStep->getChemEq().getBalances();
      CCopasiVector< CChemEqElement >::const_iterator itBalance = Balance.begin();
      CCopasiVector< CChemEqElement >::const_iterator endBalance = Balance.end();

      for (; itBalance != endBalance; ++itBalance)
        {
          const std::string & key = itBalance->getMetaboliteKey();

          for (pRow = pCol, itMetab = CCopasiVector< CMetab >::const_iterator(mMetabolitesX.begin()) + mNumMetabolitesODE;
               pRow < pRowEnd;
               pRow += numCols, ++itMetab)
            if (itMetab->getKey() == key)
              {
                *pRow = itBalance->getMultiplicity();
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

  if (mpCompileHandler)
    mpCompileHandler->finishItem(hProcess);

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

  CCopasiVector< CMetab >::iterator itMetab = mMetabolitesX.begin() + mNumMetabolitesODE;
  CCopasiVector< CMetab >::iterator endMetab = itMetab + mNumMetabolitesReaction;

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
  CCopasiVector< CMetab >::iterator itMetabX = mMetabolitesX.begin() + mNumMetabolitesODE;

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

  CCopasiVector< CMetab >::const_iterator it = CCopasiVector< CMetab >::const_iterator(mMetabolitesX.begin()) + mNumMetabolitesODE;
  CCopasiVector< CMetab >::const_iterator end = it + mNumMetabolitesReactionIndependent;

  CCopasiObjectName CN;
  size_t j;

  for (j = 0; it != end; ++it, j++)
    {
      CN = it->getCN();

      mpStoiAnnotation->setAnnotationCN(0, j, CN);
      mpLinkMatrixAnnotation->setAnnotationCN(0, j, CN);
      mpLinkMatrixAnnotation->setAnnotationCN(1, j, CN);
      mpRedStoiAnnotation->setAnnotationCN(0, j, CN);
    }

  end += MNumMetabolitesReactionDependent;

  for (; it != end; ++it, j++)
    {
      CN = it->getCN();

      mpStoiAnnotation->setAnnotationCN(0, j, CN);
      mpLinkMatrixAnnotation->setAnnotationCN(0, j, CN);
    }

  mpStoiAnnotation->setCopasiVector(1, mSteps);
  mpRedStoiAnnotation->setCopasiVector(1, mSteps);
}

void CModel::updateMoietyValues()
{
  CCopasiVector< CMoiety >::iterator it = mMoieties.begin();
  CCopasiVector< CMoiety >::iterator end = mMoieties.end();

  for (; it != end; ++it)
    it->refreshInitialValue();
}

void CModel::buildMoieties()
{
  // Independent metabs
  CCopasiVector< CMetab >::iterator itIndependent = mMetabolitesX.begin() + mNumMetabolitesODE;
  CCopasiVector< CMetab >::iterator endIndependent = itIndependent + mNumMetabolitesReactionIndependent;

  // Dependent metabs
  CCopasiVector< CMetab >::iterator itDependent = endIndependent;
  CCopasiVector< CMetab >::iterator endDependent = itDependent + MNumMetabolitesReactionDependent;

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

//this is supposed to be so fast it can be called often to be kept up to date
//all the time. At the moment it creates the mMetabolites and sorts the fixed
//metabs to the end
void CModel::initializeMetabolites()
{
  // Create a vector of pointers to all metabolites.
  // Note, the metabolites physically exist in the compartments.
  mMetabolitesX.clear();

  CCopasiVector< CCompartment >::iterator itCompartment = mCompartments.begin();
  CCopasiVector< CCompartment >::iterator endCompartment = mCompartments.end();
  CCopasiVector< CMetab >::iterator itMetab;
  CCopasiVector< CMetab >::iterator endMetab;

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
              case FIXED:
                FixedMetabs.push_back(itMetab);
                itMetab->setUsed(false);
                break;

              case ASSIGNMENT:
                AssignmentMetabs.push_back(itMetab);
                itMetab->setUsed(true);
                break;

              case ODE:
                ODEMetabs.push_back(itMetab);
                itMetab->setUsed(true);
                break;

              case REACTIONS:
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

  mMetabolitesX.resize(mNumMetabolitesODE + mNumMetabolitesReaction + mNumMetabolitesAssignment + mNumMetabolitesUnused);
  itMetab = mMetabolitesX.begin();
  std::vector< CMetab *>::const_iterator itSorted = ODEMetabs.begin();
  std::vector< CMetab *>::const_iterator endSorted = ODEMetabs.end();

  for (; itSorted != endSorted; ++itSorted, ++itMetab)
    itMetab = *itSorted;

  itSorted = ReactionMetabs.begin();
  endSorted = ReactionMetabs.end();

  for (; itSorted != endSorted; ++itSorted, ++itMetab)
    itMetab = *itSorted;

  itSorted = AssignmentMetabs.begin();
  endSorted = AssignmentMetabs.end();

  for (; itSorted != endSorted; ++itSorted, ++itMetab)
    itMetab = *itSorted;

  itSorted = FixedMetabs.begin();
  endSorted = FixedMetabs.end();

  for (; itSorted != endSorted; ++itSorted, ++itMetab)
    itMetab = *itSorted;

  // mMetabolitesX = mMetabolites;
}

//**********************************************************************

CCopasiVectorNS < CReaction > & CModel::getReactions()
{return mSteps;}

const CCopasiVectorNS < CReaction > & CModel::getReactions() const
{return mSteps;}

const CVector< C_FLOAT64 > & CModel::getParticleFlux() const
{return mParticleFluxes;}

CCopasiVector< CMetab > & CModel::getMetabolites()
{return mMetabolites;}

const CCopasiVector< CMetab > & CModel::getMetabolites() const
{return mMetabolites;}

CCopasiVector< CMetab > & CModel::getMetabolitesX()
{return mMetabolitesX;}

const CCopasiVector< CMetab > & CModel::getMetabolitesX() const
{return mMetabolitesX;}

const CCopasiVectorN< CModelValue > & CModel::getModelValues() const
{return mValues;}

CCopasiVectorN< CModelValue > & CModel::getModelValues()
{return mValues;}

const CCopasiVectorN< CModelParameterSet > & CModel::getModelParameterSets() const
{return mParameterSets;}

CCopasiVectorN< CModelParameterSet > & CModel::getModelParameterSets()
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
    dynamic_cast< CModelParameterSet * >(CCopasiRootContainer::getKeyFactory()->get(mActiveParameterSetKey));

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

CCopasiVectorN < CEvent > & CModel::getEvents()
{return mEvents;}

const CCopasiVectorN < CEvent > & CModel::getEvents() const
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

CCopasiVectorNS < CCompartment > & CModel::getCompartments()
{return mCompartments;}

const CCopasiVectorNS < CCompartment > & CModel::getCompartments() const
{return mCompartments;}

/**
 *  Get the Reduced Stoichiometry Matrix of this Model
 */
const CMatrix < C_FLOAT64 >& CModel::getRedStoi() const
{return mRedStoi;}

/**
 *  Get the reordered stoichiometry matrix of this model
 */
const CMatrix < C_FLOAT64 >& CModel::getStoi() const
{return mStoi;}

const CArrayAnnotation *
CModel::getStoiAnnotation() const
{
  return mpStoiAnnotation;
}

const CCopasiVector < CMoiety > & CModel::getMoieties() const
{return mMoieties;}

const CLinkMatrixView & CModel::getL() const
{return mLView;}

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
  mpMathContainer->updateInitialValues(CModelParameter::ParticleNumbers);
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

  CCopasiVector< CModelValue >::iterator itValue = mValues.begin();
  CCopasiVector< CModelValue >::iterator endValue = mValues.end();

  for (; itValue != endValue; ++itValue)
    if (itValue->getStatus() == ODE)
      {
        itValue->setUsed(true);
        *ppEntity++ = itValue;
      }

  CCopasiVector< CCompartment >::iterator itCompartment = mCompartments.begin();
  CCopasiVector< CCompartment >::iterator endCompartment = mCompartments.end();

  for (; itCompartment != endCompartment; ++itCompartment)
    if (itCompartment->getStatus() == ODE)
      {
        itCompartment->setUsed(true);
        *ppEntity++ = itCompartment;
      }

  CCopasiVector< CMetab >::iterator itMetab = mMetabolitesX.begin();
  CCopasiVector< CMetab >::iterator endMetab = mMetabolitesX.end();

  for (; itMetab != endMetab; ++itMetab)
    {
      if (!itMetab->isUsed()) break;

      *ppEntity++ = itMetab;
    }

  itCompartment = mCompartments.begin();

  for (; itCompartment != endCompartment; ++itCompartment)
    if (itCompartment->getStatus() == ASSIGNMENT)
      {
        itCompartment->setUsed(true);
        *ppEntity++ = itCompartment;
      }

  itValue = mValues.begin();

  for (; itValue != endValue; ++itValue)
    if (itValue->getStatus() == ASSIGNMENT)
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

  CCopasiVector< CReaction >::iterator itReaction = mSteps.begin();
  CCopasiVector< CReaction >::iterator endReaction = mSteps.end();

  for (; itReaction != endReaction; ++itReaction)
    itReaction->compile();

  return true;
}

bool CModel::buildUserOrder()
{
  assert(mMetabolites.size() == mMetabolitesX.size());

  CVector< const CModelEntity * > UserEntities(mMetabolites.size() + mCompartments.size() + mValues.size());
  const CModelEntity ** ppEntity = UserEntities.array();

  CCopasiVector< CMetab >::iterator itMetab = mMetabolites.begin();
  CCopasiVector< CMetab >::iterator endMetab = mMetabolites.end();

  for (; itMetab != endMetab; ++itMetab)
    *ppEntity++ = itMetab;;

  CCopasiVector< CCompartment >::iterator itCompartment = mCompartments.begin();
  CCopasiVector< CCompartment >::iterator endCompartment = mCompartments.end();

  for (; itCompartment != endCompartment; ++itCompartment)
    *ppEntity++ = itCompartment;

  CCopasiVector< CModelValue >::iterator itValue = mValues.begin();
  CCopasiVector< CModelValue >::iterator endValue = mValues.end();

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
      const Status & Status = Entities[*pUserOrder]->getStatus();

      if (Status == ODE ||
          (Status == REACTIONS && Entities[*pUserOrder]->isUsed()))
        mJacobianPivot[i++] = *pUserOrder - 1;
    }

  return true;
}

bool CModel::updateInitialValues(const CModelParameter::Framework & framework)
{
  bool success = compileIfNecessary(NULL);

  mpMathContainer->fetchInitialState();
  mpMathContainer->updateInitialValues(framework);
  mpMathContainer->pushInitialState();
  refreshActiveParameterSet();

  return success;
}

void CModel::stateToIntialState()
{
  mpMathContainer->fetchState();
  mpMathContainer->setInitialState(mpMathContainer->getState(false));
  mpMathContainer->updateInitialValues(CModelParameter::ParticleNumbers);
  mpMathContainer->pushInitialState();
}

// virtual
const std::string CModel::getUnits() const
{
  return mTimeUnit;
}

bool CModel::setVolumeUnit(const std::string & name)
{
  mVolumeUnit = name;
  mDimensionlessUnits[volume] = CUnit(mVolumeUnit).isDimensionless();
  return true;
}

bool CModel::setVolumeUnit(const CUnit::VolumeUnit & unitEnum)
{
  return setVolumeUnit(CUnit::VolumeUnitNames[unitEnum]);
}

const std::string & CModel::getVolumeUnit() const
{
  return mVolumeUnit;
}

std::string CModel::getVolumeUnitName() const
{
  return mVolumeUnit;
}

CUnit::VolumeUnit CModel::getVolumeUnitEnum() const
{
  return toEnum(mVolumeUnit.c_str(), CUnit::VolumeUnitNames, CUnit::ml);
}

//****

bool CModel::setAreaUnit(const std::string & name)
{
  mAreaUnit = name;
  mDimensionlessUnits[area] = CUnit(mAreaUnit).isDimensionless();
  return true;
}

bool CModel::setAreaUnit(const CUnit::AreaUnit & unitEnum)
{
  return setAreaUnit(CUnit::AreaUnitNames[unitEnum]);
}

const std::string & CModel::getAreaUnit() const
{
  return mAreaUnit;
}

std::string CModel::getAreaUnitName() const
{
  return mAreaUnit;
}

CUnit::AreaUnit CModel::getAreaUnitEnum() const
{
  return toEnum(mAreaUnit.c_str(), CUnit::AreaUnitNames, CUnit::m2);
}

//****
bool CModel::setLengthUnit(const std::string & name)
{
  mLengthUnit = name;
  mDimensionlessUnits[length] = CUnit(mLengthUnit).isDimensionless();
  return true;
}

bool CModel::setLengthUnit(const CUnit::LengthUnit & unitEnum)
{
  return setLengthUnit(CUnit::LengthUnitNames[unitEnum]);
}

const std::string & CModel::getLengthUnit() const
{
  return mLengthUnit;
}

std::string CModel::getLengthUnitName() const
{
  return mLengthUnit;
}

CUnit::LengthUnit CModel::getLengthUnitEnum() const
{
  return toEnum(mLengthUnit.c_str(), CUnit::LengthUnitNames, CUnit::m);
}

//****

bool CModel::setTimeUnit(const std::string & name)
{
  mTimeUnit = name;
  mDimensionlessUnits[time] = CUnit(mTimeUnit).isDimensionless();
  return true;
}

bool CModel::setTimeUnit(const CUnit::TimeUnit & unitEnum)
{
  return setTimeUnit(CUnit::TimeUnitNames[unitEnum]);
}

const std::string & CModel::getTimeUnit() const
{
  return mTimeUnit;
}

std::string CModel::getTimeUnitName() const
{
  return mTimeUnit;
}

CUnit::TimeUnit CModel::getTimeUnitEnum() const
{
  return toEnum(mTimeUnit.c_str(), CUnit::TimeUnitNames, CUnit::s);
}

//****

bool CModel::setQuantityUnit(const std::string & name,
                             const CModelParameter::Framework & frameWork)
{
  mQuantityUnit = name;
  mDimensionlessUnits[quantity] = CUnit(mQuantityUnit).isDimensionless();

  CUnit QuantityUnit(mQuantityUnit);

  // The dimensionless, component will have all the scale and multiplier information
  std::set< CUnitComponent >::const_iterator dimensionless = QuantityUnit.getComponents().find(CBaseUnit::dimensionless);
  mQuantity2NumberFactor = dimensionless->getMultiplier() * pow(10.0, dimensionless->getScale());

  // Avogadro is no longer stored in the multiplier it has its own component:
  std::set< CUnitComponent >::const_iterator avogadro = QuantityUnit.getComponents().find(CBaseUnit::avogadro);

  if (avogadro != QuantityUnit.getComponents().end())
    {
      mQuantity2NumberFactor *= pow(mAvogadro, avogadro->getExponent());
    }

  mNumber2QuantityFactor = 1.0 / mQuantity2NumberFactor;

  //adapt particle numbers
  size_t i, imax = mMetabolitesX.size();

  switch (frameWork)
    {
      case CModelParameter::Concentration:
        for (i = 0; i < imax; ++i)
          {
            //update particle numbers
            mMetabolitesX[i].refreshInitialValue();
            mMetabolitesX[i].refreshNumber();
          }

        break;

      case CModelParameter::ParticleNumbers:
        for (i = 0; i < imax; ++i)
          {
            //update particle numbers
            mMetabolitesX[i].refreshInitialConcentration();
            mMetabolitesX[i].refreshConcentration();
          }

        break;
    }

  return true;
}

bool CModel::setQuantityUnit(const CUnit::QuantityUnit & unitEnum,
                             const CModelParameter::Framework & frameWork)
{
  return setQuantityUnit(CUnit::QuantityUnitNames[unitEnum],
                         frameWork);
}

const std::string CModel::getQuantityUnit() const
{
  return mQuantityUnit;
}

std::string CModel::getQuantityUnitName() const
{
  return mQuantityUnit;
}

std::string CModel::getQuantityUnitOldXMLName() const
{
  return mQuantityUnit;
}

CUnit::QuantityUnit CModel::getQuantityUnitEnum() const
{
  return toEnum(mQuantityUnit.c_str(), CUnit::QuantityUnitNames, CUnit::mMol);
}

void CModel::setModelType(const CModel::ModelType & modelType)
{mType = modelType;}

const CModel::ModelType & CModel::getModelType() const
{return mType;}

void CModel::setAvogadro(const C_FLOAT64 & avogadro, const CModelParameter::Framework & frameWork)
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

//**********************************************************************

bool CModel::appendDependentModelObjects(const std::set< const CCopasiObject * > & deletedObjects,
    std::set< const CCopasiObject * > & dependentReactions,
    std::set< const CCopasiObject * > & dependentMetabolites,
    std::set< const CCopasiObject * > & dependentCompartments,
    std::set< const CCopasiObject * > & dependentModelValues,
    std::set< const CCopasiObject * > & dependentEvents) const
{
  // We need a local copy since we recursively add deleted objects.
  std::set< const CCopasiObject * > DeletedObjects = deletedObjects;

  bool ObjectsAppended = false;
  bool DeleteObjects = DeletedObjects.size() > 0;

  // This is this implemented recursively. Since deleting a container may result
  // in the deletion of objects not dependent on the original set of deleted objects.

  while (DeleteObjects)
    {
      DeleteObjects = false;

      DeleteObjects |= appendDependentReactions(DeletedObjects, dependentReactions);

      if (dependentReactions.size() > 0)
        {
          std::set< const CCopasiObject * >::const_iterator it, itEnd = dependentReactions.end();

          for (it = dependentReactions.begin(); it != itEnd; ++it)
            if (DeletedObjects.find(*it) == DeletedObjects.end())
              {
                CCopasiObject::DataObjectSet AdditionalObjects =
                  static_cast< const CReaction * >(*it)->getDeletedObjects();

                std::set< const CCopasiObject * >::const_iterator itDeleted = AdditionalObjects.begin();
                std::set< const CCopasiObject * >::const_iterator endDeleted = AdditionalObjects.end();

                for (; itDeleted != endDeleted; ++itDeleted)
                  DeletedObjects.insert(*itDeleted);
              }
        }

      DeleteObjects |= appendDependentMetabolites(DeletedObjects, dependentMetabolites);

      if (dependentMetabolites.size() > 0)
        {
          std::set< const CCopasiObject * >::const_iterator it, itEnd = dependentMetabolites.end();

          for (it = dependentMetabolites.begin(); it != itEnd; ++it)
            if (DeletedObjects.find(*it) == DeletedObjects.end())
              {
                CCopasiObject::DataObjectSet AdditionalObjects =
                  static_cast< const CMetab * >(*it)->getDeletedObjects();

                std::set< const CCopasiObject * >::const_iterator itDeleted = AdditionalObjects.begin();
                std::set< const CCopasiObject * >::const_iterator endDeleted = AdditionalObjects.end();

                for (; itDeleted != endDeleted; ++itDeleted)
                  DeletedObjects.insert(*itDeleted);
              }
        }

      DeleteObjects |= appendDependentModelValues(DeletedObjects, dependentModelValues);

      if (dependentModelValues.size() > 0)
        {
          std::set< const CCopasiObject * >::const_iterator it, itEnd = dependentModelValues.end();

          for (it = dependentModelValues.begin(); it != itEnd; ++it)
            if (DeletedObjects.find(*it) == DeletedObjects.end())
              {
                CCopasiObject::DataObjectSet AdditionalObjects =
                  static_cast< const CModelValue * >(*it)->getDeletedObjects();

                std::set< const CCopasiObject * >::const_iterator itDeleted = AdditionalObjects.begin();
                std::set< const CCopasiObject * >::const_iterator endDeleted = AdditionalObjects.end();

                for (; itDeleted != endDeleted; ++itDeleted)
                  DeletedObjects.insert(*itDeleted);
              }
        }

      DeleteObjects |= appendDependentCompartments(DeletedObjects, dependentCompartments);

      if (dependentCompartments.size() > 0)
        {
          std::set< const CCopasiObject * >::const_iterator it, itEnd = dependentCompartments.end();

          for (it = dependentCompartments.begin(); it != itEnd; ++it)
            if (DeletedObjects.find(*it) == DeletedObjects.end())
              {
                CCopasiObject::DataObjectSet AdditionalObjects =
                  static_cast< const CCompartment * >(*it)->getDeletedObjects();

                std::set< const CCopasiObject * >::const_iterator itDeleted = AdditionalObjects.begin();
                std::set< const CCopasiObject * >::const_iterator endDeleted = AdditionalObjects.end();

                for (; itDeleted != endDeleted; ++itDeleted)
                  DeletedObjects.insert(*itDeleted);
              }
        }

      DeleteObjects |= appendDependentEvents(DeletedObjects, dependentEvents);

      ObjectsAppended |= DeleteObjects;
    }

  return ObjectsAppended;
}

bool CModel::appendDependentReactions(std::set< const CCopasiObject * > candidates,
                                      std::set< const CCopasiObject * > & dependents) const
{
  const_cast< CModel * >(this)->compileIfNecessary(NULL);

  size_t Size = dependents.size();

  CCopasiVectorN< CReaction >::const_iterator it = mSteps.begin();
  CCopasiVectorN< CReaction >::const_iterator end = mSteps.end();

  CCopasiObject::DataObjectSet::const_iterator itSet;
  CCopasiObject::DataObjectSet::const_iterator endSet;

  for (; it != end; ++it)
    if (candidates.find(it) == candidates.end())
      {
        // Check whether the reaction is already in the list of deleted objects
        if (candidates.find(it) == candidates.end())
          {
            if (it->mustBeDeleted(candidates))
              {
                dependents.insert(it);
              }
          }
      }

  return Size < dependents.size();
}

bool CModel::appendDependentMetabolites(std::set< const CCopasiObject * > candidates,
                                        std::set< const CCopasiObject * > & dependents) const
{
  const_cast< CModel * >(this)->compileIfNecessary(NULL);

  size_t Size = dependents.size();

  CCopasiVectorN< CCompartment >::const_iterator itComp = mCompartments.begin();
  CCopasiVectorN< CCompartment >::const_iterator endComp = mCompartments.end();

  CCopasiVectorN< CMetab >::const_iterator it;
  CCopasiVectorN< CMetab >::const_iterator end;

  CCopasiObject::DataObjectSet::const_iterator itSet;
  CCopasiObject::DataObjectSet::const_iterator endSet;

  for (; itComp != endComp; ++itComp)
    {
      it = itComp->getMetabolites().begin();
      end = itComp->getMetabolites().end();

      for (; it != end; ++it)
        {
          // Check whether the species is already in the list of deleted objects
          if (candidates.find(it) == candidates.end())
            {
              if (it->mustBeDeleted(candidates))
                {
                  dependents.insert(it);
                }
            }
        }
    }

  return Size < dependents.size();
}

bool CModel::appendDependentCompartments(std::set< const CCopasiObject * > candidates,
    std::set< const CCopasiObject * > & dependents) const
{
  const_cast< CModel * >(this)->compileIfNecessary(NULL);

  size_t Size = dependents.size();

  CCopasiVectorN< CCompartment >::const_iterator it = mCompartments.begin();
  CCopasiVectorN< CCompartment >::const_iterator end = mCompartments.end();

  std::set< const CCopasiObject * >::const_iterator itSet;
  std::set< const CCopasiObject * >::const_iterator endSet;

  for (; it != end; ++it)
    {
      // Check whether the compartment is already in the list of deleted objects
      if (candidates.find(it) == candidates.end())
        {
          if (it->mustBeDeleted(candidates))
            {
              dependents.insert(it);
            }
        }
    }

  return Size < dependents.size();
}

bool CModel::appendDependentModelValues(std::set< const CCopasiObject * > candidates,
                                        std::set< const CCopasiObject * > & dependents) const
{
  const_cast< CModel * >(this)->compileIfNecessary(NULL);

  size_t Size = dependents.size();

  CCopasiVectorN< CModelValue >::const_iterator it = mValues.begin();
  CCopasiVectorN< CModelValue >::const_iterator end = mValues.end();

  std::set< const CCopasiObject * >::const_iterator itSet;
  std::set< const CCopasiObject * >::const_iterator endSet;

  for (; it != end; ++it)

    // Check whether the model value is already in the list of deleted objects
    if (candidates.find(it) == candidates.end())
      {
        if (it->mustBeDeleted(candidates))
          {
            dependents.insert(it);
          }
      }

  return Size < dependents.size();
}

bool CModel::appendDependentEvents(std::set< const CCopasiObject * > candidates,
                                   std::set< const CCopasiObject * > & dependents) const
{
  const_cast< CModel * >(this)->compileIfNecessary(NULL);

  size_t Size = dependents.size();

  CCopasiVectorN< CEvent >::const_iterator it = mEvents.begin();
  CCopasiVectorN< CEvent >::const_iterator end = mEvents.end();

  std::set< const CCopasiObject * >::const_iterator itSet;
  std::set< const CCopasiObject * >::const_iterator endSet;

  for (; it != end; ++it)

    // Check whether the model value is already in the list of deleted objects
    if (candidates.find(it) == candidates.end())
      {
        if (it->mustBeDeleted(candidates))
          {
            dependents.insert(it);
          }
      }

  return Size < dependents.size();
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
  pMetab->refreshInitialValue();

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
    dynamic_cast< CMetab * >(CCopasiRootContainer::getKeyFactory()->get(key));
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
      removeDependentModelObjects(pMetabolite->getDeletedObjects());

      // the metabolite might have been deleted above, need to reaquire the pointer
      pMetabolite =
        dynamic_cast< CMetab * >(CCopasiRootContainer::getKeyFactory()->get(key));
    }

  if (pMetabolite != NULL)
    {
      /* Assure that all references are removed */
      mMetabolites.remove((CMetab *)pMetabolite);
      mMetabolitesX.remove((CMetab *)pMetabolite);

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
    dynamic_cast< CCompartment * >(CCopasiRootContainer::getKeyFactory()->get(key));
  return removeCompartment(pCompartment, recursive);
}

bool CModel::removeCompartment(const CCompartment * pCompartment,
                               const bool & recursive)
{
  if (!pCompartment)
    return false;

  if (recursive)
    {
      removeDependentModelObjects(pCompartment->getDeletedObjects());
    }

  //Check if Compartment with that name exists
  size_t index =
    mCompartments.CCopasiVector< CCompartment >::getIndex(pCompartment);

  if (index == C_INVALID_INDEX)
    return false;

  mCompartments.CCopasiVector< CCompartment >::remove(index);

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
    dynamic_cast< CReaction * >(CCopasiRootContainer::getKeyFactory()->get(key));
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
      removeDependentModelObjects(pReaction->getDeletedObjects());
    }

  //Check if Reaction exists
  size_t index =
    mSteps.CCopasiVector< CReaction >::getIndex(pReaction);

  if (index == C_INVALID_INDEX)
    return false;

  mSteps.CCopasiVector< CReaction >::remove(index);

  clearMoieties();
  mCompileIsNecessary = true;

  return true;
}

bool CModel::removeLocalReactionParameter(const std::string & key,
    const bool & recursive)
{
  CCopasiParameter * pParameter =
    dynamic_cast< CCopasiParameter * >(CCopasiRootContainer::getKeyFactory()->get(key));

  if (pParameter == NULL)
    return false;

  if (recursive)
    {
      std::set< const CCopasiObject * > DeletedObjects;
      DeletedObjects.insert(pParameter->getValueReference());

      removeDependentModelObjects(DeletedObjects);
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

void CModel::removeDependentModelObjects(const std::set<const CCopasiObject*> & deletedObjects)
{
  std::set<const CCopasiObject*> Reactions;
  std::set<const CCopasiObject*> Metabolites;
  std::set<const CCopasiObject*> Values;
  std::set<const CCopasiObject*> Compartments;
  std::set<const CCopasiObject*> Events;

  appendDependentModelObjects(deletedObjects, Reactions, Metabolites, Compartments, Values, Events);

  std::set<const CCopasiObject*>::const_iterator it, end;

  for (it = Reactions.begin(), end = Reactions.end(); it != end; ++it)
    removeReaction((*it)->getKey(), false);

  for (it = Metabolites.begin(), end = Metabolites.end(); it != end; ++it)
    removeMetabolite((*it)->getKey(), false);

  for (it = Compartments.begin(), end = Compartments.end(); it != end; ++it)
    removeCompartment((*it)->getKey(), false);

  for (it = Values.begin(), end = Values.end(); it != end; ++it)
    removeModelValue((*it)->getKey(), false);

  for (it = Events.begin(), end = Events.end(); it != end; ++it)
    removeEvent((*it)->getKey(), false);

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
    dynamic_cast< CModelValue * >(CCopasiRootContainer::getKeyFactory()->get(key));
  return removeModelValue(pModelValue, recursive);
}

bool CModel::removeModelValue(const CModelValue * pModelValue,
                              const bool & recursive)
{
  if (!pModelValue)
    return false;

  if (recursive)
    {
      removeDependentModelObjects(pModelValue->getDeletedObjects());
    }

  //Check if Value with that name exists
  size_t index =
    mValues.CCopasiVector< CModelValue >::getIndex(pModelValue);

  if (index == C_INVALID_INDEX)
    return false;

  mValues.CCopasiVector< CModelValue >::remove(index);

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
  CEvent * pEvent = dynamic_cast< CEvent * >(CCopasiRootContainer::getKeyFactory()->get(key));

  return removeEvent(pEvent, recursive);
}

bool CModel::removeEvent(const CEvent * pEvent,
                         const bool & /* recursive */)
{
  if (!pEvent)
    return false;

  //Check if Event exists
  size_t index =
    mEvents.CCopasiVector< CEvent >::getIndex(pEvent);

  if (index == C_INVALID_INDEX)
    return false;

  mEvents.CCopasiVector< CEvent >::remove(index);

  clearMoieties();

  mCompileIsNecessary = true;

  return true;
}

#ifdef WITH_PE_EVENT_CREATION

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

      const CCopasiDataModel* dataModel = getObjectDataModel();
      const CFitTask* task = dynamic_cast<const CFitTask*>(&dataModel->getTaskList()->operator[]("Parameter Estimation"));

      if (task == NULL)
        {
          CCopasiMessage(CCopasiMessage::ERROR,
                         "The parameter estimation was not correctly setup.");
          return false;
        }

      const CFitProblem *problem = static_cast<const CFitProblem*>(task->getProblem());

      const CExperimentSet& experiments = problem->getExperiementSet();

      // find first time course experiment
      for (size_t i = 0; i < experiments.size(); ++i)
        {
          const CExperiment* exp = experiments.getExperiment(i);

          if (exp->getExperimentType() == CTaskEnum::timeCourse)
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

  if (experiment->getExperimentType() != CTaskEnum::timeCourse)
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

  // remember whether we had events before, if so it could be that
  // we have two events triggering at the same time
  bool hadEvents = getEvents().size() > 0;

  size_t numCols = experiment->getNumColumns();
  const std::map< const CObjectInterface *, size_t > &  dependentMap = experiment->getDependentObjects();

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
          << "<"  << getObject(CRegisteredObjectName("Reference=Time"))->getCN()
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
            new CEventAssignment(currentObject->getDataObject()->getObjectParent()->getKey());
          std::stringstream assignmentStr; assignmentStr << value;
          pNewAssignment->setExpression(assignmentStr.str());
          pNewAssignment->getExpressionPtr()->compile();
          pEvent->getAssignments().add(pNewAssignment, true);
        }
    }

  // ensure that the 'continue on simultaneous events' option is enabled
  // for time course simulations, this needs to happen whenever we already
  // have events in the model, as then there is a chance that two events trigger at the same time

  if (!hadEvents) return true;

  CTrajectoryTask* task = dynamic_cast<CTrajectoryTask*>(&getObjectDataModel()->getTaskList()->operator[]("Time-Course"));

  if (task != NULL)
    {
      CTrajectoryProblem* problem = dynamic_cast<CTrajectoryProblem*>(task->getProblem());

      if (!problem->getContinueSimultaneousEvents())
        {
          problem->setContinueSimultaneousEvents(true);
          CCopasiMessage(CCopasiMessage::WARNING,
                         "Since the model contained events, the option 'Continue on Simultaneous Events' "
                         "has been enabled in the 'Time 'Course' task to ensure that simulation continues "
                         "if multiple events trigger at the same time.");
        }
    }

  return true;
}
#endif

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

  //CModel* model = dynamic_cast< CModel * >(CCopasiRootContainer::getKeyFactory()->get(objKey));
  //if (!model) return false;

  CCopasiVectorN< CReaction > & steps = this->getReactions();

  size_t i, imax = steps.size();

  for (i = 0; i < imax; ++i)
    if (steps[i].isReversible())
      {
        std::vector< std::pair< const CCopasiObject * , const CCopasiObject * > > ParameterMap;

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
                        (CCopasiRootContainer::getFunctionList()-> findFunction("Mass action (irreversible)"));
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

            tmp.first = CCopasiRootContainer::getFunctionList()->addAndAdaptName(tmp.first);

            tmp.second = CCopasiRootContainer::getFunctionList()->addAndAdaptName(tmp.second);
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
              reac1->setParameterMapping("k1", reac0->getParameterMapping("k1")[0]);

            reac1->setParameterMappingVector("substrate", reac0->getParameterMapping("substrate"));

            if (reac0->isLocalParameter("k2"))
              reac2->setParameterValue("k1", reac0->getParameterValue("k2"));
            else
              reac2->setParameterMapping("k1", reac0->getParameterMapping("k2")[0]);

            reac2->setParameterMappingVector("substrate", reac0->getParameterMapping("product"));

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
                assert(fp->getType() == CFunctionParameter::FLOAT64);

                switch (fp->getUsage())
                  {
                    case CFunctionParameter::SUBSTRATE:
                      reac1->setParameterMapping(fp->getObjectName(),
                                                 reac0->getParameterMapping(fp->getObjectName())[0]);

                      // It is possible (see Bug 1830) that the split function may have additional modifier.
                      // This will happen e.g. if the product is referenced in the forward part of the reaction.
                      if (reac2->setParameterMapping(fp->getObjectName(),
                                                     reac0->getParameterMapping(fp->getObjectName())[0]))
                        {
                          reac2->addModifier(reac0->getParameterMapping(fp->getObjectName())[0]);
                        }

                      break;

                    case CFunctionParameter::PRODUCT:

                      // It is possible (see Bug 1830) that the split function may have additional modifier.
                      // This will happen e.g. if the product is referenced in the forward part of the reaction.
                      if (reac1->setParameterMapping(fp->getObjectName(),
                                                     reac0->getParameterMapping(fp->getObjectName())[0]))
                        {
                          reac1->addModifier(reac0->getParameterMapping(fp->getObjectName())[0]);
                        }

                      reac2->setParameterMapping(fp->getObjectName(),
                                                 reac0->getParameterMapping(fp->getObjectName())[0]);
                      break;

                    case CFunctionParameter::MODIFIER:

                      if (reac1->setParameterMapping(fp->getObjectName(),
                                                     reac0->getParameterMapping(fp->getObjectName())[0]))
                        {
                          // Add the modifier
                          reac1->addModifier(reac0->getParameterMapping(fp->getObjectName())[0]);
                        }

                      if (reac2->setParameterMapping(fp->getObjectName(),
                                                     reac0->getParameterMapping(fp->getObjectName())[0]))
                        {
                          // Add the modifier
                          reac2->addModifier(reac0->getParameterMapping(fp->getObjectName())[0]);
                        }

                      break;

                    case CFunctionParameter::PARAMETER:

                      if (reac0->isLocalParameter(fp->getObjectName()))
                        {

                          reac1->setParameterValue(fp->getObjectName(),
                                                   reac0->getParameterValue(fp->getObjectName()));
                          reac2->setParameterValue(fp->getObjectName(),
                                                   reac0->getParameterValue(fp->getObjectName()));
                        }
                      else
                        {
                          reac1->setParameterMapping(fp->getObjectName(),
                                                     reac0->getParameterMapping(fp->getObjectName())[0]);
                          reac2->setParameterMapping(fp->getObjectName(),
                                                     reac0->getParameterMapping(fp->getObjectName())[0]);
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
                      reac1->setParameterMapping(fp->getObjectName(),
                                                 reac0->getParameterMapping(fp->getObjectName())[0]);
                      reac2->setParameterMapping(fp->getObjectName(),
                                                 reac0->getParameterMapping(fp->getObjectName())[0]);
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
        std::vector< std::pair< const CCopasiObject *, const CCopasiObject * > >::const_iterator itParameter = ParameterMap.begin();
        std::vector< std::pair< const CCopasiObject *, const CCopasiObject * > >::const_iterator endParameter = ParameterMap.end();

        for (; itParameter != endParameter; ++itParameter)
          {
            Old = "<" + itParameter->first->getCN() + ">";
            New = "<" + itParameter->second->getCN() + ">";

            // We need to find all expressions which reference the old parameter (first value of the itParameter)
            // Compartments (expression, initial expression)
            CCopasiVector< CCompartment >::iterator itComp = mCompartments.begin();
            CCopasiVector< CCompartment >::iterator endComp = mCompartments.end();

            for (; itComp != endComp; ++itComp)
              {
                const CExpression * pExpression = itComp->getExpressionPtr();

                if (pExpression != NULL)
                  {
                    const CCopasiObject::DataObjectSet & Dependencies = pExpression->getDirectDependencies();

                    if (Dependencies.find(itParameter->first) != Dependencies.end())
                      {
                        Infix = itComp->getExpression();
                        stringReplace(Infix, Old, New);
                        itComp->setExpression(Infix);
                      }
                  }

                pExpression = itComp->getInitialExpressionPtr();

                if (pExpression != NULL)
                  {
                    const CCopasiObject::DataObjectSet & Dependencies = pExpression->getDirectDependencies();

                    if (Dependencies.find(itParameter->first) != Dependencies.end())
                      {
                        Infix = itComp->getInitialExpression();
                        stringReplace(Infix, Old, New);
                        itComp->setInitialExpression(Infix);
                      }
                  }
              }

            // Species (expression, initial expression)
            CCopasiVector< CMetab >::iterator itMetab = mMetabolitesX.begin();
            CCopasiVector< CMetab >::iterator endMetab = mMetabolitesX.end();

            for (; itMetab != endMetab; ++itMetab)
              {
                const CExpression * pExpression = itMetab->getExpressionPtr();

                if (pExpression != NULL)
                  {
                    const CCopasiObject::DataObjectSet & Dependencies = pExpression->getDirectDependencies();

                    if (Dependencies.find(itParameter->first) != Dependencies.end())
                      {
                        Infix = itMetab->getExpression();
                        stringReplace(Infix, Old, New);
                        itMetab->setExpression(Infix);
                      }
                  }

                pExpression = itMetab->getInitialExpressionPtr();

                if (pExpression != NULL)
                  {
                    const CCopasiObject::DataObjectSet & Dependencies = pExpression->getDirectDependencies();

                    if (Dependencies.find(itParameter->first) != Dependencies.end())
                      {
                        Infix = itMetab->getInitialExpression();
                        stringReplace(Infix, Old, New);
                        itMetab->setInitialExpression(Infix);
                      }
                  }
              }

            // Model Quantities (expression, initial expression)
            CCopasiVector< CModelValue >::iterator itValue = mValues.begin();
            CCopasiVector< CModelValue >::iterator endValue = mValues.end();

            for (; itValue != endValue; ++itValue)
              {
                const CExpression * pExpression = itValue->getExpressionPtr();

                if (pExpression != NULL)
                  {
                    const CCopasiObject::DataObjectSet & Dependencies = pExpression->getDirectDependencies();

                    if (Dependencies.find(itParameter->first) != Dependencies.end())
                      {
                        Infix = itValue->getExpression();
                        stringReplace(Infix, Old, New);
                        itValue->setExpression(Infix);
                      }
                  }

                pExpression = itValue->getInitialExpressionPtr();

                if (pExpression != NULL)
                  {
                    const CCopasiObject::DataObjectSet & Dependencies = pExpression->getDirectDependencies();

                    if (Dependencies.find(itParameter->first) != Dependencies.end())
                      {
                        Infix = itValue->getInitialExpression();
                        stringReplace(Infix, Old, New);
                        itValue->setInitialExpression(Infix);
                      }
                  }
              }

            // Events (trigger, delay, assignments)
            CCopasiVector< CEvent >::iterator itEvent = mEvents.begin();
            CCopasiVector< CEvent >::iterator endEvent = mEvents.end();

            for (; itEvent != endEvent; ++itEvent)
              {
                const CExpression * pExpression = itEvent->getTriggerExpressionPtr();

                if (pExpression != NULL)
                  {
                    const CCopasiObject::DataObjectSet & Dependencies = pExpression->getDirectDependencies();

                    if (Dependencies.find(itParameter->first) != Dependencies.end())
                      {
                        Infix = itEvent->getTriggerExpression();
                        stringReplace(Infix, Old, New);
                        itEvent->setTriggerExpression(Infix);
                      }
                  }

                pExpression = itEvent->getDelayExpressionPtr();

                if (pExpression != NULL)
                  {
                    const CCopasiObject::DataObjectSet & Dependencies = pExpression->getDirectDependencies();

                    if (Dependencies.find(itParameter->first) != Dependencies.end())
                      {
                        Infix = itEvent->getDelayExpression();
                        stringReplace(Infix, Old, New);
                        itEvent->setDelayExpression(Infix);
                      }
                  }

                CCopasiVector< CEventAssignment >::iterator itAssignment = itEvent->getAssignments().begin();
                CCopasiVector< CEventAssignment >::iterator endAssignment = itEvent->getAssignments().end();

                for (; itAssignment != endAssignment; ++itAssignment)
                  {
                    pExpression = itAssignment->getExpressionPtr();

                    if (pExpression != NULL)
                      {
                        const CCopasiObject::DataObjectSet & Dependencies = pExpression->getDirectDependencies();

                        if (Dependencies.find(itParameter->first) != Dependencies.end())
                          {
                            Infix = itAssignment->getExpression();
                            stringReplace(Infix, Old, New);
                            itAssignment->setExpression(Infix);
                          }
                      }
                  }
              }
          }

        // BUG 1848. We need to replace all references to the flux and particle flux
        // with the difference of the forward and backward reaction fluxes and particle fluxes, i.e,
        // flux = forward.flux - backward.flux

        Old = "<" + reac0->getFluxReference()->getCN() + ">";
        New = "(<" + reac1->getFluxReference()->getCN() + "> - <" + reac2->getFluxReference()->getCN() + ">)";

        // Find all objects which directly depend on the flux or particle flux.
        std::set< const CCopasiObject * > Flux;
        Flux.insert(reac0->getFluxReference());
        std::set< const CCopasiObject * > FluxDependents;

        // Initial Expression and Expression
        appendDependentCompartments(Flux, FluxDependents);
        appendDependentModelValues(Flux, FluxDependents);
        appendDependentMetabolites(Flux, FluxDependents);

        std::set< const CCopasiObject * >::iterator it = FluxDependents.begin();
        std::set< const CCopasiObject * >::iterator end = FluxDependents.end();

        for (; it != end; ++it)
          {
            CModelEntity * pEntity = static_cast< CModelEntity * >(const_cast< CCopasiObject * >(*it));

            // Expression
            Infix = pEntity->getExpression();

            if (stringReplace(Infix, Old, New))
              {
                pEntity->setExpression(Infix);
              }

            // Initial Expression
            if (pEntity->getStatus() != CModelEntity::ASSIGNMENT)
              {
                Infix = pEntity->getInitialExpression();

                if (stringReplace(Infix, Old, New))
                  {
                    pEntity->setInitialExpression(Infix);
                  }
              }
          }

        FluxDependents.clear();

        // Trigger and Assignments
        appendDependentEvents(Flux, FluxDependents);

        it = FluxDependents.begin();
        end = FluxDependents.end();

        for (; it != end; ++it)
          {
            CEvent * pEvent = static_cast< CEvent * >(const_cast< CCopasiObject * >(*it));

            // Trigger Expression
            Infix = pEvent->getTriggerExpression();

            if (stringReplace(Infix, Old, New))
              {
                pEvent->setTriggerExpression(Infix);
              }

            // Delay Expression
            Infix = pEvent->getDelayExpression();

            if (stringReplace(Infix, Old, New))
              {
                pEvent->setDelayExpression(Infix);
              }

            // Priority Expression
            Infix = pEvent->getPriorityExpression();

            if (stringReplace(Infix, Old, New))
              {
                pEvent->setPriorityExpression(Infix);
              }

            // Assignments
            CCopasiVector< CEventAssignment >::iterator itAssignment = pEvent->getAssignments().begin();
            CCopasiVector< CEventAssignment >::iterator endAssignment = pEvent->getAssignments().end();

            for (; itAssignment != endAssignment; ++itAssignment)
              {
                Infix = itAssignment->getExpression();

                if (stringReplace(Infix, Old, New))
                  {
                    itAssignment->setExpression(Infix);
                  }
              }
          }

        FluxDependents.clear();
        Flux.clear();

        // particleFlux = forward.particleFlux - backward.particleFlux
        Old = "<" + reac0->getParticleFluxReference()->getCN() + ">";
        New = "(<" + reac1->getParticleFluxReference()->getCN() + "> - <" + reac2->getParticleFluxReference()->getCN() + ">)";

        Flux.insert(reac0->getParticleFluxReference());

        // Initial Expression and Expression
        appendDependentCompartments(Flux, FluxDependents);
        appendDependentModelValues(Flux, FluxDependents);
        appendDependentMetabolites(Flux, FluxDependents);

        it = FluxDependents.begin();
        end = FluxDependents.end();

        for (; it != end; ++it)
          {
            CModelEntity * pEntity = static_cast< CModelEntity * >(const_cast< CCopasiObject * >(*it));

            // Expression
            Infix = pEntity->getExpression();

            if (stringReplace(Infix, Old, New))
              {
                pEntity->setExpression(Infix);
              }

            // Initial Expression
            if (pEntity->getStatus() != CModelEntity::ASSIGNMENT)
              {
                Infix = pEntity->getInitialExpression();

                if (stringReplace(Infix, Old, New))
                  {
                    pEntity->setInitialExpression(Infix);
                  }
              }
          }

        FluxDependents.clear();

        // Trigger and Assignments
        appendDependentEvents(Flux, FluxDependents);

        it = FluxDependents.begin();
        end = FluxDependents.end();

        for (; it != end; ++it)
          {
            CEvent * pEvent = static_cast< CEvent * >(const_cast< CCopasiObject * >(*it));

            // Trigger Expression
            Infix = pEvent->getTriggerExpression();

            if (stringReplace(Infix, Old, New))
              {
                pEvent->setTriggerExpression(Infix);
              }

            // Delay Expression
            Infix = pEvent->getDelayExpression();

            if (stringReplace(Infix, Old, New))
              {
                pEvent->setDelayExpression(Infix);
              }

            // Priority Expression
            Infix = pEvent->getPriorityExpression();

            if (stringReplace(Infix, Old, New))
              {
                pEvent->setPriorityExpression(Infix);
              }

            // Assignments
            CCopasiVector< CEventAssignment >::iterator itAssignment = pEvent->getAssignments().begin();
            CCopasiVector< CEventAssignment >::iterator endAssignment = pEvent->getAssignments().end();

            for (; itAssignment != endAssignment; ++itAssignment)
              {
                Infix = itAssignment->getExpression();

                if (stringReplace(Infix, Old, New))
                  {
                    itAssignment->setExpression(Infix);
                  }
              }
          }

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

//**********************************************************************

void CModel::initObjects()
{
  mpModel = this;

  mKey = CCopasiRootContainer::getKeyFactory()->add("Model", this);

  // The regular CModelEntity mechanism does not work since
  // CModel is created before mStateTemplate :(
  mStateTemplate.add(this);

  // units

  mpIValueReference->setObjectName("Initial Time");
  mpValueReference->setObjectName("Time");

  mRate = 1.0;

  addObjectReference("Comments", *const_cast<std::string *>(&getNotes()));

  // These are broken since they contain pointers to values :(
  //  addVectorReference("Fluxes", mFluxes, CCopasiObject::ValueDbl);
  //  addVectorReference("Particle Fluxes", mParticleFluxes, CCopasiObject::ValueDbl);

  addMatrixReference("Stoichiometry", mStoi, CCopasiObject::ValueDbl);
  addMatrixReference("Reduced Model Stoichiometry", mRedStoi, CCopasiObject::ValueDbl);
  addMatrixReference("Link Matrix"   , mLView, CCopasiObject::ValueDbl);

  mpStoiAnnotation = new CArrayAnnotation("Stoichiometry(ann)", this, new CCopasiMatrixInterface<CMatrix<C_FLOAT64> >(&mStoi), true);
  mpStoiAnnotation->setDescription("Stoichiometry Matrix");
  mpStoiAnnotation->setMode(0, CArrayAnnotation::OBJECTS);
  mpStoiAnnotation->setDimensionDescription(0, "Species that are controlled by reactions");
  mpStoiAnnotation->setMode(1, CArrayAnnotation::VECTOR_ON_THE_FLY);
  mpStoiAnnotation->setDimensionDescription(1, "Reactions");
  mpStoiAnnotation->setCopasiVector(1, mSteps);

  mpRedStoiAnnotation = new CArrayAnnotation("Reduced stoichiometry(ann)", this, new CCopasiMatrixInterface<CMatrix<C_FLOAT64> >(&mRedStoi), true);
  mpRedStoiAnnotation->setDescription("Reduced stoichiometry Matrix");
  mpRedStoiAnnotation->setMode(0, CArrayAnnotation::OBJECTS);
  mpRedStoiAnnotation->setDimensionDescription(0, "Species (reduced system)");
  mpRedStoiAnnotation->setMode(1, CArrayAnnotation::VECTOR_ON_THE_FLY);
  mpRedStoiAnnotation->setDimensionDescription(1, "Reactions");
  mpRedStoiAnnotation->setCopasiVector(1, mSteps);

  mpLinkMatrixAnnotation = new CArrayAnnotation("Link matrix(ann)", this, new CCopasiMatrixInterface<CLinkMatrixView>(&mLView), true);
  mpLinkMatrixAnnotation->setDescription("Link matrix");
  mpLinkMatrixAnnotation->setMode(0, CArrayAnnotation::OBJECTS);
  mpLinkMatrixAnnotation->setDimensionDescription(0, "Species that are controlled by reactions (full system)");
  mpLinkMatrixAnnotation->setMode(1, CArrayAnnotation::OBJECTS);
  mpLinkMatrixAnnotation->setDimensionDescription(1, "Species (reduced system)");

  mDimensionlessUnits[volume] = CUnit(mVolumeUnit).isDimensionless();
  mDimensionlessUnits[area] = CUnit(mAreaUnit).isDimensionless();
  mDimensionlessUnits[length] = CUnit(mLengthUnit).isDimensionless();
  mDimensionlessUnits[time] = CUnit(mTimeUnit).isDimensionless();
  mDimensionlessUnits[quantity] = CUnit(mQuantityUnit).isDimensionless();

  // mpMathModel = new CMathModel(this);
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

bool CModel::isStateVariable(const CCopasiObject * pObject) const
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

CCopasiObject * CModel::getCorrespondingTransientObject(const CCopasiObject * pObject) const
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
      return const_cast< CCopasiObject * >(pObject);
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
          case ODE:
          case ASSIGNMENT:

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
  CCopasiVector< CReaction >::const_iterator itReaction = mSteps.begin();
  CCopasiVector< CReaction >::const_iterator endReaction = mSteps.end();

  for (; itReaction != endReaction; ++itReaction)
    {
      if (itReaction->getFunction() &&
          itReaction->getFunction()->hasDiscontinuity())
        {
          TreesWithDiscontinuities.push_back(itReaction->getFunction());
        }
    }

  // Check all event triggers
  CCopasiVector< CEvent >::const_iterator itEvent = mEvents.begin();
  CCopasiVector< CEvent >::const_iterator endEvent = mEvents.end();

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

bool CModel::compileEvents()
{
  bool success = true;

  CObjectInterface::ContainerList ListOfContainer;

  CCopasiVectorN< CEvent >::iterator it = mEvents.begin();
  CCopasiVectorN< CEvent >::iterator end = mEvents.end();

  for (; it != end; ++ it)
    {
      success &= it->compile(ListOfContainer);
    }

  return success;
}

void CModel::updateInitialValues(std::set< const CCopasiObject * > & changedObjects)
{
  CObjectInterface::UpdateSequence UpdateSequence = buildInitialRefreshSequence(changedObjects);

  mpMathContainer->fetchInitialState();
  mpMathContainer->applyUpdateSequence(UpdateSequence);
  mpMathContainer->pushInitialState();

  refreshActiveParameterSet();
}

void CModel::updateInitialValues(const CCopasiObject* changedObject)
{
  std::set< const CCopasiObject * > changedObjects;
  changedObjects.insert(changedObject);
  updateInitialValues(changedObjects);
}

CObjectInterface::UpdateSequence
CModel::buildInitialRefreshSequence(std::set< const CCopasiObject * > & changedObjects)
{
  // Map the changed objects to their math equivalents;
  std::set< const CCopasiObject * >::const_iterator it = changedObjects.begin();
  std::set< const CCopasiObject * >::const_iterator end = changedObjects.end();

  CObjectInterface::ObjectSet ChangedObjects;

  for (; it != end; ++it)
    {
      CObjectInterface * pObject = mpMathContainer->getMathObject(*it);

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

  CObjectInterface::UpdateSequence UpdateSequence;
  mpMathContainer->getInitialDependencies().getUpdateSequence(UpdateSequence,
      CMath::UpdateMoieties,
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

#include "function/CDerive.h"

CEvaluationNode* CModel::prepareElasticity(const CReaction * pReaction, const CModelEntity* pVar, bool simplify)
{
  //TODO check: pVar should be a pointer to a variable (ODE or REACTION), a local parameter, an initial value, or a fixed entity
  //it should not be an entity with an assignment.

  //here we select the actual derivation variable: concentration, or value, or volume, etc. TODO
  const CCopasiObject * pVarObj = pVar->CModelEntity::getValueObject();
  //const CCopasiObject * pVarObj = pVar->getValueObject();

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
      std::vector<const CCopasiObject*> prod;
      size_t j;

      for (j = 0; j < pReaction->getMap().getObjects()[1].vector->size(); ++j)
        {
          prod.push_back((*(pReaction->getMap().getObjects()[1].vector))[j].value); //substrates
        }

      prod.push_back(pReaction->getMap().getObjects()[0].value); //k1

      if (prod.size() == 1)
        tmp_ma = new CEvaluationNodeObject(CEvaluationNodeObject::CN, "<" + prod[0]->getCN() + ">");
      else
        {
          tmp_ma = CDerive::multiply(new CEvaluationNodeObject(CEvaluationNodeObject::CN, "<" + prod[0]->getCN() + ">"),
                                     new CEvaluationNodeObject(CEvaluationNodeObject::CN, "<" + prod[1]->getCN() + ">"), simplify);

          for (j = 2; j < prod.size(); ++j)
            tmp_ma = CDerive::multiply(tmp_ma,
                                       new CEvaluationNodeObject(CEvaluationNodeObject::CN, "<" + prod[j]->getCN() + ">"), simplify);
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
            tt2 = new CEvaluationNodeObject(CEvaluationNodeObject::CN, "<" + prod[0]->getCN() + ">");
          else
            {
              tt2 = CDerive::multiply(new CEvaluationNodeObject(CEvaluationNodeObject::CN, "<" + prod[0]->getCN() + ">"),
                                      new CEvaluationNodeObject(CEvaluationNodeObject::CN, "<" + prod[1]->getCN() + ">"), simplify);

              for (j = 2; j < prod.size(); ++j)
                tt2 = CDerive::multiply(tt2,
                                        new CEvaluationNodeObject(CEvaluationNodeObject::CN, "<" + prod[j]->getCN() + ">"), simplify);
            }

          tmp_ma = new CEvaluationNodeOperator(CEvaluationNodeOperator::MINUS, "-");
          tmp_ma->addChild(ttt);
          tmp_ma->addChild(tt2);
        }

      CDerive::compileTree(tmp_ma, NULL);

      CExpression * tmpExp = new CExpression("Mass action expression", this);
      tmpExp->setRoot(tmp_ma);
      tmpExp->compile(); //this converts references from model entities to value references

      std::vector<const CEvaluationNode*> env;
      tmp = CDerive::deriveBranch(tmp_ma, pVarObj, env, derivExp, simplify);

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
          const CCopasiObject* tmpObj = pReaction->getMap().getObjects()[i].value;
          //if we have a metab, its always the concentration
          const CMetab* tmpMetab = dynamic_cast<const CMetab*>(tmpObj);

          if (tmpMetab)
            tmpObj = tmpMetab->getConcentrationReference();

          std::string tmpstr = tmpObj ? "<" + tmpObj->getCN() + ">" : "<>";
          CEvaluationNodeObject* tmpENO = new CEvaluationNodeObject(CEvaluationNodeObject::CN, tmpstr);
          env[i] = tmpENO;
          tmpENO->compile(derivExp); //this uses derivExp as a dummy expression (so that the node has a context for the compile()
        }

      tmp = CDerive::deriveBranch(pReaction->getFunction()->getRoot(), pVarObj, env, derivExp, simplify);

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
  const CUnitDefinition * unitDef = CCopasiRootContainer::getUnitDefFromSymbol(unit);

  if (unitDef == NULL) return 0;

  return unitDef->getUsedSymbols().count(symbol);
}

// Return a set of any COPASI object using this symbol.
CCopasiObject::DataObjectSet CModel::getUnitSymbolUsage(std::string symbol) const
{
  DataObjectSet usages;

  //Is it used in the Model Values?
  CCopasiVector< CModelValue >::const_iterator it = getModelValues().begin();
  CCopasiVector< CModelValue >::const_iterator end = getModelValues().end();
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
  CCopasiVector< CModelValue >::iterator it = getModelValues().begin();
  CCopasiVector< CModelValue >::iterator end = getModelValues().end();

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
  CCopasiVector< CModelValue >::const_iterator it = getModelValues().begin();
  CCopasiVector< CModelValue >::const_iterator end = getModelValues().end();

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

bool CModel::isDimensionless(UnitType type) const
{
  return mDimensionlessUnits[type];
}
