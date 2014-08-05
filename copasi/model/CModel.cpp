// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
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
#include "CMathModel.h"

#ifdef USE_MATH_CONTAINER
# include "math/CMathContainer.h"
#endif //USE_MATH_CONTAINER

#include "lapack/blaswrap.h"
#include "lapack/lapackwrap.h"

#ifdef COPASI_DEBUG
#define CCHECK {check();}
#else
#define CCHECK
#endif

#define MNumMetabolitesReactionDependent (mNumMetabolitesReaction - mNumMetabolitesReactionIndependent)

const char * CModel::ModelTypeNames[] =
{"deterministic", "stochastic", NULL};

CModel::CModel(CCopasiContainer* pParent):
  CModelEntity("New Model", pParent, "Model"),
  mInitialState(),
  mCurrentState(),
  mStateTemplate(*this, this->mInitialState, this->mCurrentState),
  mSimulatedUpToDateObjects(),
  mInitialDependencies(),
  mTransientDependencies(),
  mPhysicalDependencies(),
#ifdef USE_MATH_CONTAINER
  mpMathContainer(NULL),
#endif // USE_MATH_CONTAINER
  mListOfUnits("Units", this),
  mpVolumeUnit(NULL),
  mpAreaUnit(NULL),
  mpLengthUnit(NULL),
  mpTimeUnit(NULL),
  mpQuantityUnit(NULL),
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
  mStoiInternal(),
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
  mQuantity2NumberFactor(1.0),
  mNumber2QuantityFactor(1.0),
  mpCompileHandler(NULL),
  mInitialRefreshes(),
  mSimulatedRefreshes(),
  mApplyInitialValuesRefreshes(),
  mNonSimulatedRefreshes(),
  mReorderNeeded(false),
  mIsAutonomous(true),
  mBuildInitialSequence(true),
  mpMathModel(NULL)
{
  initObjects();

  setStatus(TIME);
  setUsed(true);

  *mpIValue = 0.0;
  *mpValue = std::numeric_limits<C_FLOAT64>::quiet_NaN();

  size_t i, imax = mSteps.size();

  for (i = 0; i < imax; i++)
    mSteps[i]->compile(/*mCompartments*/);

  initializeMetabolites();

  forceCompile(NULL);

  /* This following 2 lines added by Liang Xu
  Because of the failure to initialize the parameter when creating a new models
  */
//  setQuantityUnit(mpQuantityUnit->getSymbol()); // set the factors
//  setVolumeUnit(mpVolumeUnit->getSymbol()); // set the factors
  setQuantityUnit("mol");
  setVolumeUnit("ml");

  CONSTRUCTOR_TRACE;
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
//     mStoiInternal(src.mStoiInternal),
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
//     mSteps[i]->compile(/*mCompartments*/);
//
//   initializeMetabolites();
//
//   forceCompile(NULL);
//}

CModel::~CModel()
{
  mpIValue = NULL;
  mpValue = NULL;

  pdelete(mpStoiAnnotation);
  pdelete(mpRedStoiAnnotation);
  pdelete(mpLinkMatrixAnnotation);

#ifdef USE_MATH_CONTAINER
  pdelete(mpMathContainer);
#endif // USE_MATH_CONTAINER

  CCopasiRootContainer::getKeyFactory()->remove(mKey);

  DESTRUCTOR_TRACE;
}

// virtual
std::string CModel::getChildObjectUnits(const CCopasiObject * pObject) const
{
  if (pObject->getObjectName() == "Initial Time" ||
      pObject->getObjectName() == "Time")
    return getTimeUnitName();

  return "";
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

  setQuantityUnit(tmp); // set the factors

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

  *mpIValue = 0;

  if ((Fail = configBuffer.getVariable("TotalCompartments", "C_INT32", &Size,
                                       CReadConfig::LOOP)))
    return Fail;

  mCompartments.load(configBuffer, Size);

  // Create the correct compartment / metabolite relationships
  CMetab *pMetabolite;

  for (i = 0; i < pDataModel->pOldMetabolites->size(); i++)
    {
      pMetabolite = new CMetab;
      mCompartments[(*pDataModel->pOldMetabolites)[i]->getIndex()]->
      addMetabolite(pMetabolite);

      (*pMetabolite) = *(*pDataModel->pOldMetabolites)[i];
    }

  initializeMetabolites();

  if ((Fail = CCopasiRootContainer::getFunctionList()->load(configBuffer))) // slow
    return Fail;

  if ((Fail = configBuffer.getVariable("TotalSteps", "C_INT32", &Size,
                                       CReadConfig::LOOP)))
    return Fail;

  mSteps.load(configBuffer, Size); // slow

  for (i = 0; i < mSteps.size(); i++)
    mSteps[i]->compile(/*mCompartments*/);

  pDataModel->pOldMetabolites->cleanup();

  setCompileFlag();
  return Fail;
}

bool CModel::compile()
{
  bool success = true;

  if (CCopasiObject::smpRenameHandler != NULL)
    {
      CCopasiObject::smpRenameHandler->setEnabled(false);
    }

  mpValueReference->addDirectDependency(this);

  CMatrix< C_FLOAT64 > LU;

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

  // To assure that we do not produce access violations we clear the refresh sequences
  // first
  mInitialRefreshes.clear();
  mSimulatedRefreshes.clear();
  mApplyInitialValuesRefreshes.clear();
  mNonSimulatedRefreshes.clear();

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

  try
    {
      success &= buildInitialSequence();
      success &= buildApplyInitialValuesSequence();
      success &= buildSimulatedSequence();
      success &= buildNonSimulatedSequence();
    }
  catch (...)
    {
      success = false;
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
        (*itSpecies)->compileIsInitialConcentrationChangeAllowed();
      }
  }

  //update annotations
  updateMatrixAnnotations();

  success &= compileEvents();
  success &= mpMathModel->compile(this);

  if (!success)
    {
      mIsAutonomous = false;
    }
  else
    {
      mCompileIsNecessary = false;
      determineIsAutonomous();
    }

  //writeDependenciesToDotFile();

  buildDependencyGraphs();

#ifdef USE_MATH_CONTAINER
  pdelete(mpMathContainer);
  mpMathContainer = new CMathContainer(*this);

  // CMathContainer CopyModel(MathModel);
#endif // USE_MATH_CONTAINER

  // Update the parameter set
  mParameterSet.createFromModel();

finish:

  if (CCopasiObject::smpRenameHandler != NULL)
    {
      CCopasiObject::smpRenameHandler->setEnabled(true);
    }

  mCompileIsNecessary = !success;

  return success;
}

bool CModel::buildDependencyGraphs()
{
  mInitialDependencies.clear();
  mTransientDependencies.clear();
  mPhysicalDependencies.clear();

  // The initial values of the model entities
  // We need to add the time for non-autonomous models.
  CModelEntity **ppEntity = mStateTemplate.beginIndependent() - 1;
  CModelEntity **ppEntityEnd = mStateTemplate.endFixed();

  for (; ppEntity != ppEntityEnd; ++ppEntity)
    {
      CMetab * pSpecies = dynamic_cast< CMetab * >(*ppEntity);

      mInitialDependencies.addObject((*ppEntity)->getInitialValueReference());
      mTransientDependencies.addObject((*ppEntity)->getValueReference());

      if (pSpecies != NULL)
        {
          mInitialDependencies.addObject(pSpecies->getInitialConcentrationReference());
          mTransientDependencies.addObject(pSpecies->getConcentrationReference());
        }

      switch ((*ppEntity)->getStatus())
        {
          case CModelEntity::ODE:
          case CModelEntity::REACTIONS:
            mTransientDependencies.addObject((*ppEntity)->getRateReference());
            break;

          default:
            break;
        }
    }

  CCopasiVector< CMoiety >::iterator itMoiety = mMoieties.begin();
  CCopasiVector< CMoiety >::iterator endMoiety = mMoieties.end();

  for (; itMoiety != endMoiety; ++itMoiety)
    {
      mInitialDependencies.addObject((*itMoiety)->getInitialValueReference());
      mTransientDependencies.addObject((*itMoiety)->getTotalNumberReference());
      mTransientDependencies.addObject((*itMoiety)->getDependentNumberReference());
    }

#ifdef COPASI_DEBUG_TRACE
  std::ofstream File;

  File.open("InitialDependencies.dot");
  mInitialDependencies.exportDOTFormat(File, "InitialDependencies");
  File.close();

  File.open("SimulationDependencies.dot");
  mTransientDependencies.exportDOTFormat(File, "SimulationDependencies");
  File.close();
#endif //COPASI_DEBUG_TRACE
  return true;
}

void CModel::setCompileFlag(bool flag)
{
  mCompileIsNecessary = flag;
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
  mStoiInternal.resize(numRows, numCols);
  mStoiInternal = 0.0;

  size_t hProcess;

  if (mpCompileHandler)
    {
      i = 0;
      hProcess = mpCompileHandler->addItem("Building Stoichiometry",
                                           i,
                                           &numCols);
    }

  C_FLOAT64 * pCol, *pColEnd;
  pCol = mStoiInternal.array();
  pColEnd = mStoiInternal.array() + numCols;

  C_FLOAT64 * pRow, *pRowEnd;
  pRowEnd = mStoiInternal.array() + numRows * numCols;

  CCopasiVector< CReaction >::iterator itStep = mSteps.begin();
  CCopasiVector< CMetab >::const_iterator itMetab;

  for (; pCol < pColEnd; ++pCol, ++itStep)
    {
      if (mpCompileHandler && !mpCompileHandler->progressItem(hProcess)) return;

      // Since we are stepping through the reactions we can check whether
      // the kinetic functions are usable.
      if (!(*itStep)->getFunction()->isUsable())
        CCopasiMessage(CCopasiMessage::ERROR, MCReaction + 11,
                       (*itStep)->getObjectName().c_str(),
                       (*itStep)->getFunction()->getObjectName().c_str());

      const CCopasiVector< CChemEqElement > & Balance =
        (*itStep)->getChemEq().getBalances();
      CCopasiVector< CChemEqElement >::const_iterator itBalance = Balance.begin();
      CCopasiVector< CChemEqElement >::const_iterator endBalance = Balance.end();

      for (; itBalance != endBalance; ++itBalance)
        {
          const std::string & key = (*itBalance)->getMetaboliteKey();

          for (pRow = pCol, itMetab = mMetabolitesX.begin() + mNumMetabolitesODE;
               pRow < pRowEnd;
               pRow += numCols, ++itMetab)
            if ((*itMetab)->getKey() == key)
              {
                *pRow = (*itBalance)->getMultiplicity();
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
  DebugFile << mStoiInternal << std::endl;
#endif

  if (mpCompileHandler)
    mpCompileHandler->finishItem(hProcess);

  return;
}

bool CModel::handleUnusedMetabolites()
{
  size_t numRows, numCols;
  numRows = mStoiInternal.numRows();
  numCols = mStoiInternal.numCols();

  C_FLOAT64 * pStoi, *pStoiEnd, *pRowEnd;
  pStoi = mStoiInternal.array();
  pStoiEnd = mStoiInternal.array() + numRows * numCols;

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
  pStoi = mStoiInternal.array();

  for (i = 0; itMetab != endMetab; ++itMetab, i++, pStoi += numCols)
    {
      if (itUnused != endUnused && i == *itUnused)
        {
          (*itMetab)->setUsed(false);
          *itUnusedMetabolites = (*itMetab);

          ++itUnusedMetabolites;
          ++itUnused;
        }
      else
        {
          (*itMetab)->setUsed(true);
          *itUsedMetabolites = (*itMetab);
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
    *itMetab = *itUsedMetabolites;

  // Handle metabolites determined by assignment and marked as fixed
  // This is just a shift of NumUnused.
  endMetab = itMetab + mNumMetabolitesAssignment + mNumMetabolitesUnused;

  for (; itMetab != endMetab; ++itMetab)
    *itMetab = *(itMetab + NumUnused);

  // Handle newly marked unused metabolites
  itUnusedMetabolites = UnusedMetabolites.begin();
  itMetabolitesEnd = UnusedMetabolites.end();

  for (; itUnusedMetabolites != itMetabolitesEnd; ++itUnusedMetabolites, ++itMetab)
    *itMetab = *itUnusedMetabolites;

  // Now its time to update the number of metabolites determined by reactions
  // and the one being unused.
  mNumMetabolitesReaction -= NumUnused;
  mNumMetabolitesUnused += NumUnused;

  // Update stoichiometry matrix
  mStoiInternal = NewStoi;

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
      *ppMetab = *itMetabX;
    }

  // Apply the pivot on the temporary copy
  mL.applyRowPivot(ReactionMetabolites);

  // Map the result on the actual metabolites
  ppMetab = ReactionMetabolites.array();
  itMetabX = mMetabolitesX.begin() + mNumMetabolitesODE;

  for (; ppMetab != ppMetabEnd; ++ppMetab, ++itMetabX)
    {
      *itMetabX = *ppMetab;
    }

  return;
}

void CModel::updateMatrixAnnotations()
{
  mpLinkMatrixAnnotation->resize();
  mpStoiAnnotation->resize();
  mpRedStoiAnnotation->resize();

  CCopasiVector< CMetab >::const_iterator it = mMetabolitesX.begin() + mNumMetabolitesODE;
  CCopasiVector< CMetab >::const_iterator end = it + mNumMetabolitesReactionIndependent;

  CCopasiObjectName CN;
  size_t j;

  for (j = 0; it != end; ++it, j++)
    {
      CN = (*it)->getCN();

      mpStoiAnnotation->setAnnotationCN(0, j, CN);
      mpLinkMatrixAnnotation->setAnnotationCN(0, j, CN);
      mpLinkMatrixAnnotation->setAnnotationCN(1, j, CN);
      mpRedStoiAnnotation->setAnnotationCN(0, j, CN);
    }

  end += MNumMetabolitesReactionDependent;

  for (; it != end; ++it, j++)
    {
      CN = (*it)->getCN();

      mpStoiAnnotation->setAnnotationCN(0, j, CN);
      mpLinkMatrixAnnotation->setAnnotationCN(0, j, CN);
    }
}

void CModel::updateMoietyValues()
{
  CCopasiVector< CMoiety >::iterator it = mMoieties.begin();
  CCopasiVector< CMoiety >::iterator end = mMoieties.end();

  for (; it != end; ++it)
    (*it)->refreshInitialValue();
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
      pMoiety = new CMoiety((*itDependent)->getObjectName());
      pMoiety->add(1.0, *itDependent);

      if (pFactor != NULL)
        {
          for (itIndependent = mMetabolitesX.begin() + mNumMetabolitesODE; itIndependent != endIndependent; ++itIndependent, ++pFactor)
            if (fabs(*pFactor) > std::numeric_limits< C_FLOAT64 >::epsilon())
              pMoiety->add(- *pFactor, *itIndependent);
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
  mMetabolites.clear();

  CCopasiVector< CCompartment >::iterator itCompartment = mCompartments.begin();
  CCopasiVector< CCompartment >::iterator endCompartment = mCompartments.end();
  CCopasiVector< CMetab >::iterator itMetab;
  CCopasiVector< CMetab >::iterator endMetab;

  for (; itCompartment != endCompartment; ++itCompartment)
    {
      itMetab = (*itCompartment)->getMetabolites().begin();
      endMetab = (*itCompartment)->getMetabolites().end();

      for (; itMetab != endMetab; ++itMetab)
        {
          // Reset all moieties
          (*itMetab)->setDependentOn(NULL);
          mMetabolites.add(*itMetab);
        }
    }

  // We sort the metabolites by type
  itMetab = mMetabolites.begin();
  endMetab = mMetabolites.end();

  std::vector< CMetab *> ODEMetabs;
  std::vector< CMetab *> ReactionMetabs;
  std::vector< CMetab *> AssignmentMetabs;
  std::vector< CMetab *> FixedMetabs;

  for (; itMetab != endMetab; ++itMetab)
    switch ((*itMetab)->getStatus())
      {
        case FIXED:
          FixedMetabs.push_back(*itMetab);
          (*itMetab)->setUsed(false);
          break;

        case ASSIGNMENT:
          AssignmentMetabs.push_back(*itMetab);
          (*itMetab)->setUsed(true);
          break;

        case ODE:
          ODEMetabs.push_back(*itMetab);
          (*itMetab)->setUsed(true);
          break;

        case REACTIONS:
          ReactionMetabs.push_back(*itMetab);
          (*itMetab)->setUsed(true);
          break;

        default:
          fatalError();
          break;
      }

  // Update mMetabolitesX to reflect the reordering.
  // We need to to this to allow the use of the full model for simulation.
  mMetabolitesX.resize(mMetabolites.size());

  mNumMetabolitesODE = ODEMetabs.size();
  itMetab = mMetabolitesX.begin();
  std::vector< CMetab *>::const_iterator itSorted = ODEMetabs.begin();
  std::vector< CMetab *>::const_iterator endSorted = ODEMetabs.end();

  for (; itSorted != endSorted; ++itSorted, ++itMetab)
    *itMetab = *itSorted;

  mNumMetabolitesReaction = ReactionMetabs.size();
  itSorted = ReactionMetabs.begin();
  endSorted = ReactionMetabs.end();

  for (; itSorted != endSorted; ++itSorted, ++itMetab)
    *itMetab = *itSorted;

  mNumMetabolitesAssignment = AssignmentMetabs.size();
  itSorted = AssignmentMetabs.begin();
  endSorted = AssignmentMetabs.end();

  for (; itSorted != endSorted; ++itSorted, ++itMetab)
    *itMetab = *itSorted;

  mNumMetabolitesUnused = FixedMetabs.size();
  itSorted = FixedMetabs.begin();
  endSorted = FixedMetabs.end();

  for (; itSorted != endSorted; ++itSorted, ++itMetab)
    *itMetab = *itSorted;
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
{CCHECK return mMetabolitesX;}

const CCopasiVector< CMetab > & CModel::getMetabolitesX() const
{CCHECK return mMetabolitesX;}

const CCopasiVectorN< CModelValue > & CModel::getModelValues() const
{return mValues;}

CCopasiVectorN< CModelValue > & CModel::getModelValues()
{return mValues;}

const CCopasiVectorN< CModelParameterSet > & CModel::getModelParameterSets() const
{return mParameterSets;}

CCopasiVectorN< CModelParameterSet > & CModel::getModelParameterSets()
{return mParameterSets;}

const CModelParameterSet & CModel::getModelParameterSet() const
{
  return mParameterSet;
}

CModelParameterSet & CModel::getModelParameterSet()
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
{return mMetabolites.size();}

size_t CModel::getNumVariableMetabs() const
{return mNumMetabolitesODE + mNumMetabolitesReaction + mNumMetabolitesAssignment;}

size_t CModel::getNumODEMetabs() const
{CCHECK return mNumMetabolitesODE;}

size_t CModel::getNumAssignmentMetabs() const
{CCHECK return mNumMetabolitesAssignment;}

size_t CModel::getNumIndependentReactionMetabs() const
{CCHECK return mNumMetabolitesReactionIndependent;}

size_t CModel::getNumDependentReactionMetabs() const
{CCHECK return mNumMetabolitesReaction - mNumMetabolitesReactionIndependent;}

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
{CCHECK return mRedStoi;}

/**
 *  Get the reordered stoichiometry matrix of this model
 */
const CMatrix < C_FLOAT64 >& CModel::getStoi() const
{CCHECK return mStoi;}

const CCopasiVector < CMoiety > & CModel::getMoieties() const
{return mMoieties;}

const CLinkMatrixView & CModel::getL() const
{CCHECK return mLView;}

const CMatrix< C_FLOAT64 > & CModel::getL0() const
{return mL;}

const CStateTemplate & CModel::getStateTemplate() const
{CCHECK return mStateTemplate;}

CStateTemplate & CModel::getStateTemplate()
{CCHECK return mStateTemplate;}

const std::set< const CCopasiObject * > & CModel::getUptoDateObjects() const
{return mSimulatedUpToDateObjects;}

void CModel::setInitialTime(const C_FLOAT64 & time)
{*mpIValue = time;}

const C_FLOAT64 & CModel::getInitialTime() const
{return *mpIValue;}

void CModel::setTime(const C_FLOAT64 & time)
{*mpValue = time;}

const C_FLOAT64 & CModel::getTime() const
{return *mpValue;}

//**********************************************************************

/**
 *        Returns the index of the metab
 */
size_t CModel::findMetabByName(const std::string & name) const
{
  size_t i, imax = mMetabolites.size();
  CCopasiVector< CMetab >::const_iterator Target = mMetabolites.begin();

  std::string Name = unQuote(name);

  for (i = 0; i < imax; i++, Target++)
    if (*Target &&
        ((*Target)->getObjectName() == name ||
         (*Target)->getObjectName() == Name)) return i;

  return C_INVALID_INDEX;
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
      name = mMoieties[i]->getObjectName();

      if (name == Target)
        return i;
    }

  return C_INVALID_INDEX;
}

//**********************************************************************

void CModel::applyInitialValues()
{
  // Copy the initial state to the current state,
  setState(mInitialState);

  // Since the initial state is in itself consistent we should not need to
  // do anything further. However, for species of type ODE and ASSIGNMENT
  // the effective state variable is the concentration, i.e., we need to update
  // their concentration here.
  std::vector< Refresh * >::const_iterator itRefresh = mApplyInitialValuesRefreshes.begin();
  std::vector< Refresh * >::const_iterator endRefresh = mApplyInitialValuesRefreshes.end();

  while (itRefresh != endRefresh)
    (**itRefresh++)();

  // Update all dependent objects needed for simulation.
  updateSimulatedValues(false);

  mpMathModel->applyInitialValues();
}

void CModel::clearMoieties()
{
  mMoieties.clear();
}

bool CModel::buildStateTemplate()
{
  CVector<CModelEntity *> Entities(mMetabolitesX.size() + mCompartments.size() + mValues.size());
  CModelEntity ** ppEntity = Entities.array();

  CCopasiVector< CModelValue >::iterator itValue = mValues.begin();
  CCopasiVector< CModelValue >::iterator endValue = mValues.end();

  for (; itValue != endValue; ++itValue)
    if ((*itValue)->getStatus() == ODE)
      {
        *ppEntity = *itValue;
        (*ppEntity++)->setUsed(true);
      }

  CCopasiVector< CCompartment >::iterator itCompartment = mCompartments.begin();
  CCopasiVector< CCompartment >::iterator endCompartment = mCompartments.end();

  for (; itCompartment != endCompartment; ++itCompartment)
    if ((*itCompartment)->getStatus() == ODE)
      {
        *ppEntity = *itCompartment;
        (*ppEntity++)->setUsed(true);
      }

  CCopasiVector< CMetab >::iterator itMetab = mMetabolitesX.begin();
  CCopasiVector< CMetab >::iterator endMetab = mMetabolitesX.end();

  for (; itMetab != endMetab; ++itMetab)
    {
      if (!(*itMetab)->isUsed()) break;

      *ppEntity++ = *itMetab;
    }

  itCompartment = mCompartments.begin();

  for (; itCompartment != endCompartment; ++itCompartment)
    if ((*itCompartment)->getStatus() == ASSIGNMENT)
      {
        *ppEntity = *itCompartment;
        (*ppEntity++)->setUsed(true);
      }

  itValue = mValues.begin();

  for (; itValue != endValue; ++itValue)
    if ((*itValue)->getStatus() == ASSIGNMENT)
      {
        *ppEntity = *itValue;
        (*ppEntity++)->setUsed(true);
      }

  for (; itMetab != endMetab; ++itMetab)
    *ppEntity++ = *itMetab;

  itCompartment = mCompartments.begin();

  for (; itCompartment != endCompartment; ++itCompartment)
    if ((*itCompartment)->isFixed())
      *ppEntity++ = *itCompartment;

  itValue = mValues.begin();

  for (; itValue != endValue; ++itValue)
    if ((*itValue)->isFixed())
      *ppEntity++ = *itValue;

  mStateTemplate.reorder(Entities);
  mReorderNeeded = false;

  // Now all entities and reactions can be compiled
  ppEntity = mStateTemplate.beginIndependent();
  CModelEntity ** ppEntityEnd = mStateTemplate.endFixed();

  for (; ppEntity != ppEntityEnd; ++ppEntity)
    (*ppEntity)->compile();

  CCopasiVector< CReaction >::iterator itReaction = mSteps.begin();
  CCopasiVector< CReaction >::iterator endReaction = mSteps.end();

  for (; itReaction != endReaction; ++itReaction)
    (*itReaction)->compile();

  return true;
}

bool CModel::buildUserOrder()
{
  CVector<CModelEntity *> Entities(mMetabolites.size() + mCompartments.size() + mValues.size());
  CModelEntity ** ppEntity = Entities.array();

  CCopasiVector< CMetab >::iterator itMetab = mMetabolites.begin();
  CCopasiVector< CMetab >::iterator endMetab = mMetabolites.end();

  for (; itMetab != endMetab; ++itMetab)
    *ppEntity++ = *itMetab;;

  CCopasiVector< CCompartment >::iterator itCompartment = mCompartments.begin();
  CCopasiVector< CCompartment >::iterator endCompartment = mCompartments.end();

  for (; itCompartment != endCompartment; ++itCompartment)
    *ppEntity++ = *itCompartment;

  CCopasiVector< CModelValue >::iterator itValue = mValues.begin();
  CCopasiVector< CModelValue >::iterator endValue = mValues.end();

  for (; itValue != endValue; ++itValue)
    *ppEntity++ = *itValue;

  mStateTemplate.setUserOrder(Entities);

  mJacobianPivot.resize(mStateTemplate.getNumIndependent() + MNumMetabolitesReactionDependent);
  //now sized to the number of entities with ODEs + all metabolites dependent on reactions

  const size_t * pUserOrder = mStateTemplate.getUserOrder().array();
  const size_t * pUserOrderEnd = pUserOrder + mStateTemplate.getUserOrder().size();
  ppEntity = mStateTemplate.getEntities();

  size_t i;

  for (i = 0; pUserOrder != pUserOrderEnd; ++pUserOrder)
    {
      const Status & Status = ppEntity[*pUserOrder]->getStatus();

      if (Status == ODE ||
          (Status == REACTIONS && ppEntity[*pUserOrder]->isUsed()))
        mJacobianPivot[i++] = *pUserOrder - 1;
    }

  return true;
}

bool CModel::buildInitialSequence()
{
  bool success = true;

  // The objects which are changed are all initial values of of all model entities including
  // fixed and unused once. Additionally, all kinetic parameters are possibly changed.
  // This is basically all the parameters in the parameter overview whose value is editable.

  // Issue 1170: We need to add elements of the stoichiometry, reduced stoichiometry,
  // and link matrix.

  CCopasiObject::DataObjectSet Objects;

  Objects.insert(static_cast< const CCopasiObject * >(getObject(CCopasiObjectName("Reference=Avogadro Constant"))));

  // The initial values of the model entities
  CModelEntity **ppEntity = mStateTemplate.beginIndependent() - 1; // Offset for time
  CModelEntity **ppEntityEnd = mStateTemplate.endFixed();

  for (; ppEntity != ppEntityEnd; ++ppEntity)
    {
      // Assignments have no initial values
      if ((*ppEntity)->getStatus() != ASSIGNMENT ||
          (*ppEntity)->getInitialValueReference()->getDirectDependencies().size() == 0)
        Objects.insert((*ppEntity)->getInitialValueReference());
    }

  // The reaction parameters
  CCopasiVector< CReaction >::const_iterator itReaction = mSteps.begin();
  CCopasiVector< CReaction >::const_iterator endReaction = mSteps.end();
  size_t i, imax;

  for (; itReaction != endReaction; ++itReaction)
    {
      const CCopasiParameterGroup & Group = (*itReaction)->getParameters();

      for (i = 0, imax = Group.size(); i < imax; i++)
        Objects.insert(Group.getParameter(i)->getValueReference());
    }

  // Fix for Issue 1170: We need to add elements of the stoichiometry, reduced stoichiometry,
  // and link matrices.
  if (mpStoiAnnotation != NULL)
    mpStoiAnnotation->appendElementReferences(Objects);

  if (mpRedStoiAnnotation != NULL)
    mpRedStoiAnnotation->appendElementReferences(Objects);

  if (mpLinkMatrixAnnotation != NULL)
    mpLinkMatrixAnnotation->appendElementReferences(Objects);

  try
    {
      mInitialRefreshes = buildInitialRefreshSequence(Objects);
    }
  catch (...)
    {
      mInitialRefreshes.clear();
      success = false;
    }

  mBuildInitialSequence = false;

  return success;
}

bool CModel::updateInitialValues()
{
  if (mCompileIsNecessary)
    {
      compileIfNecessary(NULL);
    }

  if (mBuildInitialSequence)
    {
      buildInitialSequence();
    }

  // Update all initial values.
  std::vector< Refresh * >::const_iterator itRefresh = mInitialRefreshes.begin();
  std::vector< Refresh * >::const_iterator endRefresh = mInitialRefreshes.end();

  while (itRefresh != endRefresh)
    (**itRefresh++)();

  return true;
}

bool CModel::buildSimulatedSequence()
{
  bool success = true;

  // We need to add each used model entity to the objects which need to be updated.
  mSimulatedUpToDateObjects.clear();

  // For CModelValues and CCompartment ODEs we need to add the Rate
  // For CMetab ODEs we need to add the Particle Rate
  CModelEntity **ppEntity = mStateTemplate.beginIndependent();
  CModelEntity **ppEntityEnd = mStateTemplate.endIndependent() - mNumMetabolitesReactionIndependent;

  for (; ppEntity != ppEntityEnd; ++ppEntity) //loop over all entities with ODEs
    mSimulatedUpToDateObjects.insert((*ppEntity)->getRateReference());

  // We do not add the rates for metabolites of type REACTION. These are automatically calculated
  // with dgemm in calculate derivatives based on the reaction fluxes added below.
  // In the case that other simulated values depend on such a rate this is taken care by
  // calculating all dependencies.
  // This mechanism may lead occasionally to multiple calculations of rates of metabolites when used
  // in assignments or ODEs. However this is acceptable and more than compensated by the performance
  // gains of dgemm.

  // Furthermore all reaction fluxes have to be calculated too (see CMetab REACTION above)
  CCopasiVector< CReaction >::iterator itReaction = mSteps.begin();
  CCopasiVector< CReaction >::iterator endReaction = mSteps.end();

  for (; itReaction != endReaction; ++itReaction)
    mSimulatedUpToDateObjects.insert((*itReaction)->getParticleFluxReference());

  // We now detect unused assignments, i.e., the result of an assignment is not
  // used during updateSimulatedValues except for itself or another unused assignment.
  bool UnusedFound = true;

  std::set<const CCopasiObject * > Candidate;
  std::set< const CCopasiObject * >::iterator it;
  std::set< const CCopasiObject * >::iterator end = mSimulatedUpToDateObjects.end();
  CCopasiObject * pObject;
  CMetab * pMetab;
  ppEntityEnd = mStateTemplate.endDependent();

  while (UnusedFound)
    {
      UnusedFound = false;
      ppEntity = mStateTemplate.beginDependent() + MNumMetabolitesReactionDependent;
      //now points to the first entity with assignment

      for (; ppEntity != ppEntityEnd; ++ppEntity) //over all entities with assignments
        if ((*ppEntity)->isUsed())
          {
            if ((*ppEntity)->getStatus() != ASSIGNMENT)
              pObject = *ppEntity;
            else if ((pMetab = dynamic_cast< CMetab *>(*ppEntity)) != NULL)
              pObject = pMetab->getConcentrationReference();
            else
              pObject = (*ppEntity)->getValueReference();

            Candidate.insert(pObject);

            for (it = mSimulatedUpToDateObjects.begin(), end = mSimulatedUpToDateObjects.end(); it != end; ++it)
              if (*it != pObject &&
                  (*it)->dependsOn(Candidate))
                break;

            if (it == end)
              {
                UnusedFound = true;
                mReorderNeeded = true;
                (*ppEntity)->setUsed(false);
              }

            Candidate.erase(pObject);
          }
    }

  if (mReorderNeeded)
    {
      CVector< CModelEntity * > Reorder(mStateTemplate.size() - 1);
      CModelEntity ** ppReorder = Reorder.array();

      ppEntity = mStateTemplate.beginIndependent();
      ppEntityEnd = mStateTemplate.beginDependent() + MNumMetabolitesReactionDependent;

      //range is for all entities with ODEs + all metabs dependent on Reactions
      for (; ppEntity != ppEntityEnd; ++ppEntity, ++ppReorder)
        *ppReorder = *ppEntity;

      // :TODO: This must be enhanced as the mMetaboliteX and the state template may get out of sync
      // when we use assignments for metabolites.

      // the entities with assignments are reordered according to the isUsed() flag
      ppEntityEnd = mStateTemplate.endDependent();

      for (; ppEntity != ppEntityEnd; ++ppEntity) //over all entities with assignments
        if ((*ppEntity)->isUsed())
          *ppReorder++ = *ppEntity;

      ppEntity = mStateTemplate.beginDependent() + MNumMetabolitesReactionDependent;

      for (; ppEntity != ppEntityEnd; ++ppEntity) //again over all entities with assignments
        if (!(*ppEntity)->isUsed())
          *ppReorder++ = *ppEntity;

      ppEntityEnd = mStateTemplate.endFixed();

      for (; ppEntity != ppEntityEnd; ++ppEntity, ++ppReorder) //over all fixed entities
        *ppReorder = *ppEntity;

      mStateTemplate.reorder(Reorder);
      mReorderNeeded = false;

      // We need to recompile as pointers to values may have changed
      ppEntity = mStateTemplate.beginIndependent();
      ppEntityEnd = mStateTemplate.endFixed();

      for (; ppEntity != ppEntityEnd; ++ppEntity)
        (*ppEntity)->compile();

      itReaction = mSteps.begin();
      endReaction = mSteps.end();

      for (; itReaction != endReaction; ++itReaction)
        (*itReaction)->compile();

      // The compile might have broken some refresh pointers we need to rebuild the constant sequence
      buildInitialSequence();
      buildApplyInitialValuesSequence();
    }

  std::set< const CCopasiObject * > UpToDate;

  try
    {
      mSimulatedRefreshes = CCopasiObject::buildUpdateSequence(mSimulatedUpToDateObjects, UpToDate);
    }
  catch (...)
    {
      mSimulatedRefreshes.clear();
      success = false;
    }

  return success;
}

bool CModel::buildApplyInitialValuesSequence()
{
  bool success = true;

  mApplyInitialValuesRefreshes.clear();

  std::set< const CCopasiObject * > Objects;

  const CMetab * pMetab;

  CModelEntity ** ppEntity =  mStateTemplate.beginIndependent();
  CModelEntity ** ppEntityEnd = mStateTemplate.endFixed();

  for (; ppEntity != ppEntityEnd; ++ppEntity)
    {
      if ((*ppEntity)->getStatus() == ODE)
        {
          // TODO We need only to calculate rates which are constant since the other will
          // be updated by the simulation request.
          Objects.insert((*ppEntity)->getRateReference());
        }

      // Species of type assignment have a second pseudo state value the concentration,
      // which always can be directly calculated.
      if ((*ppEntity)->getStatus() == ASSIGNMENT &&
          (pMetab = dynamic_cast< const CMetab * >(*ppEntity)) != NULL)
        {
          mApplyInitialValuesRefreshes.push_back(pMetab->getConcentrationReference()->getApplyInitialValueRefresh());
        }
    }

  std::set< const CCopasiObject * > UpToDate;

  try
    {
      std::vector< Refresh * > RateRefreshes =
        CCopasiObject::buildUpdateSequence(Objects, UpToDate);

      mApplyInitialValuesRefreshes.insert(mApplyInitialValuesRefreshes.end(),
                                          RateRefreshes.begin(),
                                          RateRefreshes.end());
    }
  catch (...)
    {
      mApplyInitialValuesRefreshes.clear();
      success = false;
    }

  return success;
}

bool CModel::buildNonSimulatedSequence()
{
  bool success = true;

  CCopasiObject::DataObjectSet Objects;

  // Compartments
  CCopasiVector< CCompartment >::iterator itComp = mCompartments.begin();
  CCopasiVector< CCompartment >::iterator endComp = mCompartments.end();

  for (; itComp != endComp; ++itComp)
    {
      Objects.insert((*itComp)->getValueReference());

      switch ((*itComp)->getStatus())
        {
          case ODE:
            Objects.insert((*itComp)->getRateReference());
            break;

          default:
            break;
        }
    }

  // Metabolites
  CCopasiVector< CMetab >::iterator itMetab = mMetabolites.begin();
  CCopasiVector< CMetab >::iterator endMetab = mMetabolites.end();

  for (; itMetab != endMetab; ++itMetab)
    {
      Objects.insert((*itMetab)->getConcentrationReference());
      Objects.insert((*itMetab)->getValueReference());

      switch ((*itMetab)->getStatus())
        {
          case REACTIONS:
          case ODE:
            Objects.insert(static_cast< const CCopasiObject *>((*itMetab)->getObject(CCopasiObjectName("Reference=TransitionTime"))));
            Objects.insert((*itMetab)->getConcentrationRateReference());
            Objects.insert((*itMetab)->getRateReference());
            break;

          default:
            break;
        }
    }

  // Reactions
  CCopasiVector< CReaction >::iterator itStep = mSteps.begin();
  CCopasiVector< CReaction >::iterator endStep = mSteps.end();

  for (; itStep != endStep; ++itStep)
    {
      Objects.insert(static_cast< const CCopasiObject * >((*itStep)->getObject(CCopasiObjectName("Reference=Flux"))));
      Objects.insert((*itStep)->getParticleFluxReference());
    }

  // Model Values
  CCopasiVector< CModelValue >::iterator itValue = mValues.begin();
  CCopasiVector< CModelValue >::iterator endValue = mValues.end();

  for (; itValue != endValue; ++itValue)
    {
      Objects.insert((*itValue)->getValueReference());

      switch ((*itValue)->getStatus())
        {
          case ODE:
            Objects.insert((*itValue)->getRateReference());
            break;

          default:
            break;
        }
    }

  try
    {
      mNonSimulatedRefreshes = CCopasiObject::buildUpdateSequence(Objects, mSimulatedUpToDateObjects);
    }
  catch (...)
    {
      mNonSimulatedRefreshes.clear();
      success = false;
    }

  return success;
}

const CState & CModel::getInitialState() const
{return mInitialState;}

const CState & CModel::getState() const
{return mCurrentState;}

void CModel::setInitialState(const CState & state)
{
  mInitialState = state;

  if (mIsAutonomous &&
      !mCompileIsNecessary)
    mInitialState.setTime(0.0);

  return;
}

void CModel::setState(const CState & state)
{
  mCurrentState = state;

  return;
}

bool CModel::getInitialUpdateSequence(const CMath::SimulationContextFlag & context,
                                      const CCopasiObject::DataObjectSet & changedObjects,
                                      const CCopasiObject::DataObjectSet & requestedObjects,
                                      CCopasiObject::DataUpdateSequence & updateSequence) const
{
  return getUpdateSequence(mInitialDependencies,
                           context,
                           changedObjects,
                           requestedObjects,
                           updateSequence);
}

bool CModel::getTransientUpdateSequence(const CMath::SimulationContextFlag & context,
                                        const CCopasiObject::DataObjectSet & changedObjects,
                                        const CCopasiObject::DataObjectSet & requestedObjects,
                                        CCopasiObject::DataUpdateSequence & updateSequence) const
{
  return getUpdateSequence(mTransientDependencies,
                           context,
                           changedObjects,
                           requestedObjects,
                           updateSequence);
}

bool CModel::getUpdateSequence(CMathDependencyGraph & dependencyGraph,
                               const CMath::SimulationContextFlag & context,
                               const CCopasiObject::DataObjectSet & changedObjects,
                               const CCopasiObject::DataObjectSet & requestedObjects,
                               CCopasiObject::DataUpdateSequence & updateSequence) const
{
  updateSequence.clear();

  CObjectInterface::UpdateSequence UpdateSequence;

  if (!dependencyGraph.getUpdateSequence(context,
                                         *reinterpret_cast< const CObjectInterface::ObjectSet *>(&changedObjects),
                                         *reinterpret_cast< const CObjectInterface::ObjectSet *>(&requestedObjects),
                                         UpdateSequence))
    {
      return false;
    }

  CObjectInterface::UpdateSequence::iterator it = UpdateSequence.begin();
  CObjectInterface::UpdateSequence::iterator end = UpdateSequence.end();
  Refresh * pRefresh = NULL;

  for (; it != end; ++it)
    {
      pRefresh = static_cast< CCopasiObject * >(*it)->getRefresh();

      if (pRefresh != NULL)
        {
          updateSequence.push_back(pRefresh);
        }
    }

  return true;
}

void CModel::updateSimulatedValues(const bool & updateMoieties)
{
  // Depending on which model we are using we need to update
  // the particle numbers for the dependent metabolites.
  if (updateMoieties)
    {
      C_FLOAT64 * pDependent = mCurrentState.beginDependent();
      CCopasiVector< CMoiety >::iterator itMoiety = mMoieties.begin();
      CCopasiVector< CMoiety >::iterator endMoiety = mMoieties.end();

      for (; itMoiety != endMoiety; ++itMoiety, ++pDependent)
        *pDependent = (*itMoiety)->dependentNumber();
    }

  std::vector< Refresh * >::const_iterator itRefresh = mSimulatedRefreshes.begin();
  std::vector< Refresh * >::const_iterator endRefresh = mSimulatedRefreshes.end();

  while (itRefresh != endRefresh)
    (**itRefresh++)();

  // Store the particle fluxes for further calculations
  CCopasiVector< CReaction >::iterator it = mSteps.begin();
  CCopasiVector< CReaction >::iterator end = mSteps.end();

  C_FLOAT64 * pFlux = mParticleFluxes.array();

  for (; it != end; ++it, ++pFlux)
    {
      *pFlux = (*it)->getParticleFlux();

#ifdef COPASI_DEBUG

      if (isnan(*pFlux))
        {
          std::cout << "Reaction Flux[" <<   it -  mSteps.begin() << "] is NaN" << std::endl;
        }

#endif // COPASI_DEBUG
    }
}

void CModel::updateNonSimulatedValues(void)
{
  std::vector< Refresh * >::const_iterator itRefresh = mNonSimulatedRefreshes.begin();
  std::vector< Refresh * >::const_iterator endRefresh = mNonSimulatedRefreshes.end();

  while (itRefresh != endRefresh)
    (**itRefresh++)();

  return;
}

void CModel::calculateDerivatives(C_FLOAT64 * derivatives)
{
  C_FLOAT64 * pTmp = derivatives;

  // First retrieve derivatives of quantities determined by ODE
  // The offset 1 is for the model time which is always the first
  // state variable.
  CModelEntity ** ppIt = mStateTemplate.getEntities() + 1;
  CModelEntity ** ppEnd =
    ppIt + mStateTemplate.getNumIndependent() - mNumMetabolitesReactionIndependent;

  for (; ppIt != ppEnd; ++ppIt, ++pTmp)
    {
      *pTmp = (*ppIt)->getRate();

#ifdef COPASI_DEBUG

      if (isnan(*pTmp))
        {
          std::cout << "Entity[" <<   ppIt - (mStateTemplate.getEntities() + 1) << "] is NaN" << std::endl;
        }

#endif // COPASI_DEBUG
    }

  // Now calculate derivatives of all metabolites determined by reactions
  char T = 'N';
  C_INT M = 1;
  C_INT N = (C_INT) mNumMetabolitesReaction;
  C_INT K = (C_INT) mSteps.size();
  C_FLOAT64 Alpha = 1.0;
  C_FLOAT64 Beta = 0.0;

  if (K != 0)
    dgemm_(&T, &T, &M, &N, &K, &Alpha, mParticleFluxes.array(), &M,
           mStoi.array(), &K, &Beta, pTmp, &M);
}

void CModel::calculateDerivativesX(C_FLOAT64 * derivativesX)
{
  C_FLOAT64 * pTmp = derivativesX;

  // First retrieve derivatives of quantities determined by ODE
  // The offset 1 is for the model time which is always the first
  // state variable.
  CModelEntity ** ppIt = mStateTemplate.getEntities() + 1;
  CModelEntity ** ppEnd =
    ppIt + mStateTemplate.getNumIndependent() - mNumMetabolitesReactionIndependent;

  for (; ppIt != ppEnd; ++ppIt, ++pTmp)
    *pTmp = (*ppIt)->getRate();

  // Now calculate derivatives of the independent metabolites determined by reactions
  char T = 'N';
  C_INT M = 1;
  C_INT N = (C_INT) mNumMetabolitesReactionIndependent;
  C_INT K = (C_INT) mSteps.size();
  C_FLOAT64 Alpha = 1.0;
  C_FLOAT64 Beta = 0.0;

  if (K != 0)
    dgemm_(&T, &T, &M, &N, &K, &Alpha, mParticleFluxes.array(), &M,
           mRedStoi.array(), &K, &Beta, pTmp, &M);
}

void CModel::calculateElasticityMatrix(const C_FLOAT64 & factor,
                                       const C_FLOAT64 & resolution)
{
  size_t Col;
  size_t nCol = mElasticities.numCols();

  C_FLOAT64 * itE;
  C_FLOAT64 * beginE = mElasticities.array();

  CCopasiVector< CReaction >::const_iterator itReaction;
  CCopasiVector< CReaction >::const_iterator beginReaction = mSteps.begin();
  CCopasiVector< CReaction >::const_iterator endReaction = mSteps.end();

  CModelEntity ** itEntity;
  CModelEntity ** beginEntity = mStateTemplate.beginIndependent();
  CModelEntity ** endEntity = mStateTemplate.endDependent();

  for (itEntity = beginEntity, Col = 0; itEntity != endEntity; ++itEntity, ++Col)
    {
      // :TODO: This only works for entities of type metabolites.
      //        The scaling factor for other entities should be 1.
      const C_FLOAT64 invVolume =
        1.0 / static_cast<CMetab *>(*itEntity)->getCompartment()->getValue();
      C_FLOAT64 * pX =
        const_cast<C_FLOAT64 *>(&static_cast<CMetab *>(*itEntity)->getConcentration());

      for (itReaction = beginReaction, itE = beginE + Col;
           itReaction != endReaction;
           ++itReaction, itE += nCol)
        * itE = invVolume * (*itReaction)->calculatePartialDerivative(pX, factor, resolution);
    }

  // DebugFile << "CModel::calculateElasticityMatrix()" << std::endl;
  // DebugFile << mElasticities << std::endl;

  return;
}

void CModel::calculateJacobian(CMatrix< C_FLOAT64 > & jacobian,
                               const C_FLOAT64 & derivationFactor,
                               const C_FLOAT64 & /* resolution */)
{
  C_FLOAT64 DerivationFactor = std::max(derivationFactor, 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon());

  size_t Dim =
    mCurrentState.getNumIndependent() + MNumMetabolitesReactionDependent;
  //Dim now contains the number of entities with ODEs + number of metabs depending on reactions.

  size_t Col;

  jacobian.resize(Dim, Dim);

  C_FLOAT64 Store;
  C_FLOAT64 X1;
  C_FLOAT64 X2;
  C_FLOAT64 InvDelta;

  CVector< C_FLOAT64 > Y1(Dim);
  CVector< C_FLOAT64 > Y2(Dim);

  C_FLOAT64 * pY1;
  C_FLOAT64 * pY2;

  C_FLOAT64 * pX = mCurrentState.beginIndependent();
  C_FLOAT64 * pXEnd = pX + Dim;

  C_FLOAT64 * pJacobian;
  C_FLOAT64 * pJacobianEnd = jacobian.array() + Dim * Dim;

  for (Col = 0; pX != pXEnd; ++pX, ++Col)
    {
      Store = *pX;

      // We only need to make sure that we do not have an underflow problem
      if (fabs(Store) < DerivationFactor)
        {
          X1 = 0.0;

          if (Store < 0.0)
            X2 = -2.0 * DerivationFactor;
          else
            X2 = 2.0 * DerivationFactor;
        }
      else
        {
          X1 = Store * (1.0 + DerivationFactor);
          X2 = Store * (1.0 - DerivationFactor);
        }

      InvDelta = 1.0 / (X2 - X1);

      *pX = X1;
      updateSimulatedValues(false);
      calculateDerivatives(Y1.array());

      *pX = X2;
      updateSimulatedValues(false);
      calculateDerivatives(Y2.array());

      *pX = Store;

      pJacobian = jacobian.array() + Col;
      pY1 = Y1.array();
      pY2 = Y2.array();

      for (; pJacobian < pJacobianEnd; pJacobian += Dim, ++pY1, ++pY2)
        * pJacobian = (*pY2 - *pY1) * InvDelta;
    }

  updateSimulatedValues(false);

  return;
}

void CModel::calculateJacobianX(CMatrix< C_FLOAT64 > & jacobianX,
                                const C_FLOAT64 & derivationFactor,
                                const C_FLOAT64 & /* resolution */)
{
  C_FLOAT64 DerivationFactor = std::max(derivationFactor, 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon());

  size_t Dim = mCurrentState.getNumIndependent();
  size_t Col;

  jacobianX.resize(Dim, Dim);

  C_FLOAT64 Store;
  C_FLOAT64 X1;
  C_FLOAT64 X2;
  C_FLOAT64 InvDelta;

  CVector< C_FLOAT64 > Y1(Dim);
  CVector< C_FLOAT64 > Y2(Dim);

  C_FLOAT64 * pY1;
  C_FLOAT64 * pY2;

  C_FLOAT64 * pX = mCurrentState.beginIndependent();
  C_FLOAT64 * pXEnd = pX + Dim;

  C_FLOAT64 * pJacobian;
  C_FLOAT64 * pJacobianEnd = jacobianX.array() + Dim * Dim;

  for (Col = 0; pX != pXEnd; ++pX, ++Col)
    {
      Store = *pX;

      // We only need to make sure that we do not have an underflow problem
      if (fabs(Store) < DerivationFactor)
        {
          X1 = 0.0;

          if (Store < 0.0)
            X2 = -2.0 * DerivationFactor;
          else
            X2 = 2.0 * DerivationFactor;;
        }
      else
        {
          X1 = Store * (1.0 + DerivationFactor);
          X2 = Store * (1.0 - DerivationFactor);
        }

      InvDelta = 1.0 / (X2 - X1);

      *pX = X1;
      updateSimulatedValues(true);
      calculateDerivativesX(Y1.array());

      *pX = X2;
      updateSimulatedValues(true);
      calculateDerivativesX(Y2.array());

      *pX = Store;

      pJacobian = jacobianX.array() + Col;
      pY1 = Y1.array();
      pY2 = Y2.array();

      for (; pJacobian < pJacobianEnd; pJacobian += Dim, ++pY1, ++pY2)
        * pJacobian = (*pY2 - *pY1) * InvDelta;
    }

  updateSimulatedValues(true);
}

C_FLOAT64 CModel::calculateDivergence() const
{
  fatalError(); //not yet implemented
  return 0.0;
}

bool CModel::setVolumeUnit(const std::string & name)
{
  return setVolumeUnit(toEnum(name.c_str(), CUnit::VolumeUnitNames, CUnit::ml));
}

bool CModel::setVolumeUnit(const CUnit::VolumeUnit & unitEnum)
{
  mpVolumeUnit->setSymbol(CUnit::VolumeUnitNames[unitEnum]);
  return true;
}

const CUnit * CModel::getVolumeUnit() const
{
  return mpVolumeUnit;
}

std::string CModel::getVolumeUnitName() const
{
  return mpVolumeUnit->getSymbol();
}

CUnit::VolumeUnit CModel::getVolumeUnitEnum() const
{
  return toEnum(mpVolumeUnit->getSymbol().c_str(), CUnit::VolumeUnitNames, CUnit::ml);
}

//****

bool CModel::setAreaUnit(const std::string & name)
{
  return setAreaUnit(toEnum(name.c_str(), CUnit::AreaUnitNames, CUnit::m2));
}

bool CModel::setAreaUnit(const CUnit::AreaUnit & unitEnum)
{
  mpAreaUnit->setSymbol(CUnit::AreaUnitNames[unitEnum]);
  return true;
}

const CUnit * CModel::getAreaUnit() const
{
  return mpAreaUnit;
}

std::string CModel::getAreaUnitName() const
{
  return mpAreaUnit->getSymbol();
}

CUnit::AreaUnit CModel::getAreaUnitEnum() const
{
  return toEnum(mpAreaUnit->getSymbol().c_str(), CUnit::AreaUnitNames, CUnit::m2);
}

//****
bool CModel::setLengthUnit(const std::string & name)
{
  return setLengthUnit(toEnum(name.c_str(), CUnit::LengthUnitNames, CUnit::m));
}

bool CModel::setLengthUnit(const CUnit::LengthUnit & unitEnum)
{
  mpLengthUnit->setSymbol(CUnit::LengthUnitNames[unitEnum]);
  return true;
}

const CUnit * CModel::getLengthUnit() const
{
  return mpLengthUnit;
}

std::string CModel::getLengthUnitName() const
{
  return mpLengthUnit->getSymbol();
}

CUnit::LengthUnit CModel::getLengthUnitEnum() const
{
  return toEnum(mpLengthUnit->getSymbol().c_str(), CUnit::LengthUnitNames, CUnit::m);
}

//****

bool CModel::setTimeUnit(const std::string & name)
{
  return setTimeUnit(toEnum(name.c_str(), CUnit::TimeUnitNames, CUnit::s));
}

bool CModel::setTimeUnit(const CUnit::TimeUnit & unitEnum)
{
  mpTimeUnit->setSymbol(CUnit::TimeUnitNames[unitEnum]);
  return true;
}

const CUnit * CModel::getTimeUnit() const
{
  return mpTimeUnit;
}

std::string CModel::getTimeUnitName() const
{
  return mpTimeUnit->getSymbol();
}

CUnit::TimeUnit CModel::getTimeUnitEnum() const
{
  return toEnum(mpTimeUnit->getSymbol().c_str(), CUnit::TimeUnitNames, CUnit::s);
}

//****

bool CModel::setQuantityUnit(const std::string & name)
{
  CUnit::QuantityUnit unit = toEnum(name.c_str(), CUnit::QuantityUnitNames, CUnit::OldXML);

  if (unit == CUnit::OldXML)
    unit = toEnum(name.c_str(), CUnit::QuantityUnitOldXMLNames, CUnit::mMol);

  return setQuantityUnit(unit);
}

bool CModel::setQuantityUnit(const CUnit::QuantityUnit & unitEnum)
{
  // TODO: Commented out the code below, to allow the quantity unit to be set again
  //       but this needs to be solved correctly.
  //
  //   // if it is already there and set properly . . .
  //   if (mpQuantityUnit != NULL) // &&
  // //      *mpQuantityUnit == unitEnum) //create appropriate comparison operator
  //     return true;

  mpQuantityUnit->fromEnum(unitEnum);

  if (mListOfUnits.getIndex(mpQuantityUnit->getObjectName()) == C_INVALID_INDEX)   // if one has already been added to the list of units, use that one
    mListOfUnits.add(mpQuantityUnit, true);

  bool success = true;

  switch (unitEnum)
    {
      case CUnit::Mol:
        mQuantity2NumberFactor = mAvogadro;
        break;

      case CUnit::mMol:
        mQuantity2NumberFactor = mAvogadro * 1E-3;
        break;

      case CUnit::microMol:
        mQuantity2NumberFactor = mAvogadro * 1E-6;
        break;

      case CUnit::nMol:
        mQuantity2NumberFactor = mAvogadro * 1E-9;
        break;

      case CUnit::pMol:
        mQuantity2NumberFactor = mAvogadro * 1E-12;
        break;

      case CUnit::fMol:
        mQuantity2NumberFactor = mAvogadro * 1E-15;
        break;

      case CUnit::number:
        mQuantity2NumberFactor = 1.0;
        break;

      case CUnit::dimensionlessQuantity:
        mQuantity2NumberFactor = 1.0;
        break;

      default:
        mpQuantityUnit->setSymbol("number");
        mQuantity2NumberFactor = 1.0;
        success = false;
        break;
    }

  mNumber2QuantityFactor = 1.0 / mQuantity2NumberFactor;

  //adapt particle numbers
  size_t i, imax = mMetabolites.size();

  for (i = 0; i < imax; ++i)
    {
      //update particle numbers
      mMetabolites[i]->setInitialConcentration(mMetabolites[i]->getInitialConcentration());
      mMetabolites[i]->setConcentration(mMetabolites[i]->getConcentration());
    }

  return success;
}

const CUnit * CModel::getQuantityUnit() const
{
  return mpQuantityUnit;
}

std::string CModel::getQuantityUnitName() const
{
  return mpQuantityUnit->getSymbol();
}

std::string CModel::getQuantityUnitOldXMLName() const
{
  return mpQuantityUnit->getSymbol();
}

CUnit::QuantityUnit CModel::getQuantityUnitEnum() const
{
  return toEnum(mpQuantityUnit->getSymbol().c_str(), CUnit::QuantityUnitNames, CUnit::mMol);
}

void CModel::setModelType(const CModel::ModelType & modelType)
{mType = modelType;}

const CModel::ModelType & CModel::getModelType() const
{return mType;}

void CModel::setAvogadro(const C_FLOAT64 & avogadro)
{
  mAvogadro = avogadro;

  setQuantityUnit(mpQuantityUnit->getSymbol());
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
    if (candidates.find(*it) == candidates.end())
      {
        // Check whether the reaction is already in the list of deleted objects
        if (candidates.find(*it) == candidates.end())
          {
            if ((*it)->mustBeDeleted(candidates))
              {
                dependents.insert(*it);
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
      it = (*itComp)->getMetabolites().begin();
      end = (*itComp)->getMetabolites().end();

      for (; it != end; ++it)
        {
          // Check whether the species is already in the list of deleted objects
          if (candidates.find(*it) == candidates.end())
            {
              if ((*it)->mustBeDeleted(candidates))
                {
                  dependents.insert(*it);
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
      if (candidates.find(*it) == candidates.end())
        {
          if ((*it)->mustBeDeleted(candidates))
            {
              dependents.insert(*it);
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
    if (candidates.find(*it) == candidates.end())
      {
        if ((*it)->mustBeDeleted(candidates))
          {
            dependents.insert(*it);
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
    if (candidates.find(*it) == candidates.end())
      {
        if ((*it)->mustBeDeleted(candidates))
          {
            dependents.insert(*it);
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

  if (mCompartments[Index]->getMetabolites().getIndex(name) != C_INVALID_INDEX)
    return NULL;

  CMetab * pMetab = new CMetab(name);

  if (!mCompartments[Index]->addMetabolite(pMetab))
    {
      delete pMetab;
      return NULL;
    }

  pMetab->setStatus(status);
  pMetab->setInitialConcentration(iconc);
  pMetab->refreshInitialValue();

  if (!mMetabolites.add(pMetab))
    return NULL;

  mCompileIsNecessary = true;

  return pMetab;
}

bool CModel::removeMetabolite(const size_t index,
                              const bool & recursive)
{
  const CMetab* pMetabolite = getMetabolites()[index];
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
      removeDependentModelObjects(pMetabolite->getDeletedObjects());
    }

  /* Assure that all references are removed */
  mMetabolites.remove((CMetab *)pMetabolite);
  mMetabolitesX.remove((CMetab *)pMetabolite);

  pdelete(pMetabolite);

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
  const CCompartment * pCompartment = getCompartments()[index];
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
  const CReaction * pReaction = getReactions()[index];
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
  const CModelValue * pMV = getModelValues()[index];
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
  const CEvent * pEvent = mEvents[index];

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

#if WITH_PE_EVENT_CREATION

#include <copasi/parameterFitting/CExperiment.h>
#include <copasi/parameterFitting/CExperimentSet.h>
#include <copasi/parameterFitting/CExperimentObjectMap.h>
#include <copasi/parameterFitting/CFitTask.h>
#include <copasi/parameterFitting/CFitProblem.h>

#include <copasi/commandline/CLocaleString.h>

std::string getNextId(const std::string& base, int count)
{
  std::stringstream str;
  str << base << count;
  return str.str();
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
      const CFitTask* task = dynamic_cast<const CFitTask*>((*dataModel->getTaskList())["Parameter Estimation"]);

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

          if (exp->getExperimentType() == CCopasiTask::timeCourse)
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

  if (experiment->getExperimentType() != CCopasiTask::timeCourse)
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

  if (!experiment->compile())
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

  size_t numCols = experiment->getNumColumns();
  const CVector< CCopasiObject * > &objects = experiment->getObjectMap().getMappedObjects();

  // then go through each time point
  for (size_t i = 0; i < numRows - 1; ++i)
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
          const CCopasiObject* currentObject = objects[j + 1];

          if (currentObject == NULL || currentObject->getObjectParent() == NULL) continue;

          double value = data(i, j);

          CEventAssignment * pNewAssignment =
            new CEventAssignment(currentObject->getObjectParent()->getKey());
          std::stringstream assignmentStr; assignmentStr << value;
          pNewAssignment->setExpression(assignmentStr.str());
          pNewAssignment->getExpressionPtr()->compile();
          pEvent->getAssignments().add(pNewAssignment, true);
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
  CReactionInterface ri1(this), ri2(this);
  std::string fn, rn1, rn2;

  //CModel* model = dynamic_cast< CModel * >(CCopasiRootContainer::getKeyFactory()->get(objKey));
  //if (!model) return false;

  CCopasiVectorN< CReaction > & steps = this->getReactions();

  size_t i, imax = steps.size();

  for (i = 0; i < imax; ++i)
    if (steps[i]->isReversible())
      {
        reac0 = steps[i];
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
          reac1->addSubstrate(reac0->getChemEq().getSubstrates()[i]->getMetaboliteKey(),
                              reac0->getChemEq().getSubstrates()[i]->getMultiplicity());

        //products
        imax = reac0->getChemEq().getProducts().size();

        for (i = 0; i < imax; ++i)
          reac1->addProduct(reac0->getChemEq().getProducts()[i]->getMetaboliteKey(),
                            reac0->getChemEq().getProducts()[i]->getMultiplicity());

        //function
        reac1->setFunction(tmp.first);

        //**** create 2nd reaction.
        reac2 = createReaction(rn2);
        reac2->setReversible(false);
        //substrates -> products
        imax = reac0->getChemEq().getSubstrates().size();

        for (i = 0; i < imax; ++i)
          reac2->addProduct(reac0->getChemEq().getSubstrates()[i]->getMetaboliteKey(),
                            reac0->getChemEq().getSubstrates()[i]->getMultiplicity());

        //products -> substrates
        imax = reac0->getChemEq().getProducts().size();

        for (i = 0; i < imax; ++i)
          reac2->addSubstrate(reac0->getChemEq().getProducts()[i]->getMetaboliteKey(),
                              reac0->getChemEq().getProducts()[i]->getMultiplicity());

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

        // TODO CRITICAL BUG 1848. We need to replace all references to the flux and particle flux
        // with the difference of the forward and backward reaction fluxes and particle fluxes, i.e,
        // flux = forward.flux - backward.flux

        std::string Old = "<" + reac0->getFluxReference()->getCN() + ">";
        std::string New = "(<" + reac1->getFluxReference()->getCN() + "> - <" + reac2->getFluxReference()->getCN() + ">)";

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
            std::string Infix = pEntity->getExpression();

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
            std::string Infix = pEvent->getTriggerExpression();

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
                Infix = (*itAssignment)->getExpression();

                if (stringReplace(Infix, Old, New))
                  {
                    (*itAssignment)->setExpression(Infix);
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
            std::string Infix = pEntity->getExpression();

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
            std::string Infix = pEvent->getTriggerExpression();

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
                Infix = (*itAssignment)->getExpression();

                if (stringReplace(Infix, Old, New))
                  {
                    (*itAssignment)->setExpression(Infix);
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
  mKey = CCopasiRootContainer::getKeyFactory()->add("Model", this);

  // The regular CModelEntity mechanism does not work since
  // CModel is created before mStateTemplate :(
  C_FLOAT64 InitialValue = *mpIValue;
  C_FLOAT64 Value = *mpValue;
  pdelete(mpIValue);
  pdelete(mpValue);
  mStateTemplate.add(this);
  *mpIValue = InitialValue;
  *mpValue = Value;

  // units

  mpVolumeUnit = new CUnit("ml");
  mListOfUnits.add(mpVolumeUnit, true);
  mpVolumeUnit->fromEnum(CUnit::ml);

  mpAreaUnit = new CUnit("m2");
  mListOfUnits.add(mpAreaUnit, true);
  mpAreaUnit->fromEnum(CUnit::m2);

  mpLengthUnit = new CUnit("m");
  mListOfUnits.add(mpLengthUnit, true);
  mpLengthUnit->fromEnum(CUnit::m);

  mpTimeUnit = new CUnit("s");
  mListOfUnits.add(mpTimeUnit, true);
  mpTimeUnit->fromEnum(CUnit::s);

  mpQuantityUnit = new CUnit("mMol");
  mListOfUnits.add(mpQuantityUnit, true);
  mpQuantityUnit->fromEnum(CUnit::mMol);

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
  addObjectReference("Quantity Unit", mpQuantityUnit);
  addObjectReference("Quantity Conversion Factor", mQuantity2NumberFactor, CCopasiObject::ValueDbl);
  addObjectReference("Avogadro Constant", mAvogadro, CCopasiObject::ValueDbl);

  mpStoiAnnotation = new CArrayAnnotation("Stoichiometry(ann)", this, new CCopasiMatrixInterface<CMatrix<C_FLOAT64> >(&mStoi), true);
  mpStoiAnnotation->setDescription("Stoichiometry Matrix");
  mpStoiAnnotation->setMode(0, CArrayAnnotation::OBJECTS);
  mpStoiAnnotation->setDimensionDescription(0, "Species that are controlled by reactions");
  mpStoiAnnotation->setMode(1, CArrayAnnotation::VECTOR_ON_THE_FLY);
  mpStoiAnnotation->setDimensionDescription(1, "Reactions");
  mpStoiAnnotation->setCopasiVector(1, &mSteps);

  mpRedStoiAnnotation = new CArrayAnnotation("Reduced stoichiometry(ann)", this, new CCopasiMatrixInterface<CMatrix<C_FLOAT64> >(&mRedStoi), true);
  mpRedStoiAnnotation->setDescription("Reduced stoichiometry Matrix");
  mpRedStoiAnnotation->setMode(0, CArrayAnnotation::OBJECTS);
  mpRedStoiAnnotation->setDimensionDescription(0, "Species (reduced system)");
  mpRedStoiAnnotation->setMode(1, CArrayAnnotation::VECTOR_ON_THE_FLY);
  mpRedStoiAnnotation->setDimensionDescription(1, "Reactions");
  mpRedStoiAnnotation->setCopasiVector(1, &mSteps);

  mpLinkMatrixAnnotation = new CArrayAnnotation("Link matrix(ann)", this, new CCopasiMatrixInterface<CLinkMatrixView>(&mLView), true);
  mpLinkMatrixAnnotation->setDescription("Link matrix");
  mpLinkMatrixAnnotation->setMode(0, CArrayAnnotation::OBJECTS);
  mpLinkMatrixAnnotation->setDimensionDescription(0, "Species that are controlled by reactions (full system)");
  mpLinkMatrixAnnotation->setMode(1, CArrayAnnotation::OBJECTS);
  mpLinkMatrixAnnotation->setDimensionDescription(1, "Species (reduced system)");

  mpMathModel = new CMathModel(this);
}

bool CModel::hasReversibleReaction() const
{
  size_t i, imax = mSteps.size();

  for (i = 0; i < imax; ++i) if (mSteps[i]->isReversible()) return true;

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
      //if (mSteps[i]->getCompartmentNumber() != 1) return - 1;

      // TEST isReversible() == 0
      if (mSteps[i]->isReversible() != 0)
        return "At least one reaction is reversible. That means stochastic simulation is not possible. \nYou can use \"Tools|Convert to irreversible\" which will split the reversible reactions \n into two irreversible reactions. However you should check the kinetics afterwards.";

      // TEST integer stoichiometry
      // Iterate through each the metabolites
      // Juergen: the number of rows of mStoiInternal equals the number of non-fixed metabs!
      //  for (j=0; i<metabSize; j++)
      for (j = 0; j < mStoiInternal.numRows(); j++)
        {
          multFloat = mStoiInternal(j, i);
          multInt = static_cast<C_INT32>(floor(multFloat + 0.5)); // +0.5 to get a rounding out of the static_cast to int!

          if ((multFloat - multInt) > 0.01)
            return "Not all stoichiometries are integer numbers. \nThat means that discrete simulation is not possible.";
        }
    }

  for (i = 0; i < mMetabolites.size(); ++i)
    {
      if (mMetabolites[i]->getInitialValue() > std::numeric_limits< C_INT64 >::max())
        return "At least one particle number in the initial state is too big.";
    }

  return ""; // Model is appropriate for hybrid simulation
}

#ifdef COPASI_DEBUG
void CModel::check() const
{}
#endif

void CModel::buildLinkZero()
{
  mL.build(mStoiInternal);
  mNumMetabolitesReactionIndependent = mL.getNumIndependent();
  mStoi = mStoiInternal;
  mL.doRowPivot(mStoi);

  return;
}

const bool & CModel::isAutonomous() const
{return mIsAutonomous;}

void CModel::determineIsAutonomous()
{
  mIsAutonomous = true;

  // If the model is not empty we check whether anything depends on time
  if (mCompartments.size() != 0 ||
      mValues.size() != 0)
    {
      std::set< const CCopasiObject * > TimeDependent;

      appendDependentReactions(getDeletedObjects(), TimeDependent);
      appendDependentMetabolites(getDeletedObjects(), TimeDependent);
      appendDependentCompartments(getDeletedObjects(), TimeDependent);
      appendDependentModelValues(getDeletedObjects(), TimeDependent);
      appendDependentEvents(getDeletedObjects(), TimeDependent);

      mIsAutonomous = (TimeDependent.begin() == TimeDependent.end());
    }

  // An autonomous models always start simulation at T = 0
  if (mIsAutonomous)
    setInitialValue(0.0);
}

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

  CModelEntity * const* it = mStateTemplate.beginIndependent();
  CModelEntity * const* end = mStateTemplate.endDependent();

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
  CModelEntity *const* ppEntity = mStateTemplate.getEntities();
  CModelEntity *const* ppEntityEnd = ppEntity + mStateTemplate.size();

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
      if ((*itReaction)->getFunction() &&
          (*itReaction)->getFunction()->hasDiscontinuity())
        {
          TreesWithDiscontinuities.push_back((*itReaction)->getFunction());
        }
    }

  // Check all event triggers
  CCopasiVector< CEvent >::const_iterator itEvent = mEvents.begin();
  CCopasiVector< CEvent >::const_iterator endEvent = mEvents.end();

  for (; itEvent != endEvent; ++itEvent)
    {
      if ((*itEvent)->getTriggerExpressionPtr() &&
          (*itEvent)->getTriggerExpressionPtr()->hasDiscontinuity())
        {
          TreesWithDiscontinuities.push_back((*itEvent)->getTriggerExpressionPtr());
        }
    }

  return TreesWithDiscontinuities;
}

bool CModel::compileEvents()
{
  bool success = true;

  std::vector< CCopasiContainer * > ListOfContainer;

  CCopasiVectorN< CEvent >::iterator it = mEvents.begin();
  CCopasiVectorN< CEvent >::iterator end = mEvents.end();

  for (; it != end; ++ it)
    {
      success &= (*it)->compile(ListOfContainer);
    }

  return success;
}

const std::vector< Refresh * > & CModel::getListOfInitialRefreshes() const
{return mInitialRefreshes;}

const std::vector< Refresh * > & CModel::getListOfSimulatedRefreshes() const
{return mSimulatedRefreshes;}

const std::vector< Refresh * > & CModel::getListOfConstantRefreshes() const
{return mApplyInitialValuesRefreshes;}

const std::vector< Refresh * > & CModel::getListOfNonSimulatedRefreshes() const
{return mNonSimulatedRefreshes;}

void
CModel::updateInitialValues(std::set< const CCopasiObject * > & changedObjects)
{
  std::vector< Refresh * > refreshes = buildInitialRefreshSequence(changedObjects);
  std::vector< Refresh * >::iterator it = refreshes.begin(), endIt = refreshes.end();

  while (it != endIt)
    (**it++)();
}

void
CModel::updateInitialValues(const CCopasiObject* changedObject)
{
  std::set<const CCopasiObject*> changedObjects;
  changedObjects.insert(changedObject);
  updateInitialValues(changedObjects);
}

std::vector< Refresh * >
CModel::buildInitialRefreshSequence(std::set< const CCopasiObject * > & changedObjects)
{
  // First we remove all objects which are of type assignment from the changed objects
  // since this may not be changed as they are under control of the assignment.
  std::set< const CCopasiObject * >::iterator itSet;
  std::set< const CCopasiObject * >::iterator endSet;
  std::set< const CCopasiObject * > Objects;

  CModelEntity **ppEntity;
  CModelEntity **ppEntityEnd = mStateTemplate.endFixed();

  const CModelEntity * pEntity;
  CMetab * pMetab;

  // If the changed objects are empty we assume that all changeable objects have been changed
  if (changedObjects.size() == 0)
    {
      // The objects which are changed are all initial values of of all model entities including
      // fixed and unused once. Additionally, all kinetic parameters are possibly changed.
      // This is basically all the parameters in the parameter overview whose value is editable.

      // :TODO: Theoretically, it is possible that also task parameters influence the initial
      // state of a model but that is currently not handled.

      // The initial values of the model entities
      ppEntity = mStateTemplate.beginIndependent() - 1; // Offset for time

      for (; ppEntity != ppEntityEnd; ++ppEntity)
        {
          // If we have an initial expression we have no initial values
          if (((*ppEntity)->getInitialExpression() != "" ||
               (*ppEntity)->getStatus() == ASSIGNMENT) &&
              (*ppEntity)->getInitialValueReference()->getDirectDependencies().size() > 0)
            continue;

          // Metabolites have two initial values
          if ((pMetab = dynamic_cast< CMetab * >(*ppEntity)) != NULL)
            {
              // The concentration is assumed to be fix accept when this would lead to circular dependencies,
              // for the parent's compartment's initial volume.
              if (pMetab->isInitialConcentrationChangeAllowed())
                changedObjects.insert(pMetab->getInitialConcentrationReference());
              else
                changedObjects.insert(pMetab->getInitialValueReference());
            }
          else
            changedObjects.insert((*ppEntity)->getInitialValueReference());
        }

      // The reaction parameters
      CCopasiVector< CReaction >::const_iterator itReaction = mSteps.begin();
      CCopasiVector< CReaction >::const_iterator endReaction = mSteps.end();
      size_t i, imax;

      for (; itReaction != endReaction; ++itReaction)
        {
          const CCopasiParameterGroup & Group = (*itReaction)->getParameters();

          for (i = 0, imax = Group.size(); i < imax; i++)
            changedObjects.insert(Group.getParameter(i));
        }

      // Fix for Issue 1170: We need to add elements of the stoichiometry, reduced stoichiometry,
      // and link matrices.
      if (mpStoiAnnotation != NULL)
        mpStoiAnnotation->appendElementReferences(changedObjects);

      if (mpRedStoiAnnotation != NULL)
        mpRedStoiAnnotation->appendElementReferences(changedObjects);

      if (mpLinkMatrixAnnotation != NULL)
        mpLinkMatrixAnnotation->appendElementReferences(changedObjects);
    }
  else
    {
      // Remove all objects with initial assignments
      itSet = changedObjects.begin();
      endSet = changedObjects.end();

      for (; itSet != endSet; ++itSet)
        {
          if ((pEntity = dynamic_cast< const CModelEntity * >((*itSet)->getObjectParent())) != NULL &&
              (pEntity->getInitialExpression() != "" ||
               pEntity->getStatus() == ASSIGNMENT) &&
              pEntity->getInitialValueReference()->getDirectDependencies().size() > 0)
            Objects.insert(*itSet);
        }

      for (itSet = Objects.begin(), endSet = Objects.end(); itSet != endSet; ++itSet)
        changedObjects.erase(*itSet);
    }

  // We need to add all initial values which are dynamically calculated.
  // These are initial assignments and either a metabolite's initial particle number
  // or concentration.
  ppEntity = mStateTemplate.beginIndependent() - 1; // Offset for time
  Objects.clear();

  for (; ppEntity != ppEntityEnd; ++ppEntity)
    {
      if (((*ppEntity)->getInitialExpression() != "" ||
           (*ppEntity)->getStatus() == ASSIGNMENT))
        {
          Objects.insert((*ppEntity)->getInitialValueReference());
          continue;
        }

      // For metabolites we need to add the initial concentration or the initial
      // particle number..
      if ((pMetab = dynamic_cast< CMetab * >(*ppEntity)) != NULL)
        {
          if (changedObjects.count(pMetab->getInitialConcentrationReference()) != 0)
            {
              Objects.insert(pMetab->getInitialValueReference());
            }
          else
            {
              Objects.insert(pMetab->getInitialConcentrationReference());
            }
        }
    }

  // We need to add the total particle number of moieties.
  CCopasiVector< CMoiety >::iterator itMoiety = mMoieties.begin();
  CCopasiVector< CMoiety >::iterator endMoiety = mMoieties.end();

  for (; itMoiety != endMoiety; ++itMoiety)
    Objects.insert((*itMoiety)->getInitialValueReference());

  std::set< const CCopasiObject * > DependencySet;
  std::set< const CCopasiObject * > VerifiedSet;
  std::pair<std::set< const CCopasiObject * >::iterator, bool> InsertedObject;

  assert(Objects.count(NULL) == 0);

  // Check whether we have any circular dependencies
  for (itSet = Objects.begin(), endSet = Objects.end(); itSet != endSet; ++itSet)
    if ((*itSet)->hasCircularDependencies(DependencySet, VerifiedSet, changedObjects))
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCObject + 1, (*itSet)->getCN().c_str());

  // Build the complete set of dependencies
  for (itSet = Objects.begin(); itSet != endSet; ++itSet)
    {
      // At least the object itself needs to be up to date.
      InsertedObject = DependencySet.insert(*itSet);

      // Add all its dependencies
      if (InsertedObject.second)
        (*itSet)->getAllDependencies(DependencySet, changedObjects);
    }

  // Remove all objects which do not depend on the changed objects, or do not have a
  // refresh method.
  Objects.clear();

  // We now check which objects we need to refresh
  for (itSet = DependencySet.begin(), endSet = DependencySet.end(); itSet != endSet; ++itSet)
    {
      // No refresh method
      if ((*itSet)->getRefresh() == NULL)
        Objects.insert(*itSet);
      // Is a changed object
      else if (changedObjects.count(*itSet) != 0)
        Objects.insert(*itSet);
      // Not dependent on the changed objects.
      else if (!(*itSet)->dependsOn(changedObjects, changedObjects))
        Objects.insert(*itSet);
    }

  for (itSet = Objects.begin(), endSet = Objects.end(); itSet != endSet; ++itSet)
    DependencySet.erase(*itSet);

  // Create a properly sorted list.
  std::list< const CCopasiObject * > SortedList =
    sortObjectsByDependency(DependencySet.begin(), DependencySet.end(), changedObjects);

  std::list< const CCopasiObject * >::iterator itList;
  std::list< const CCopasiObject * >::iterator endList;

  // Build the vector of pointers to refresh methods
  Refresh * pRefresh;

  std::vector< Refresh * > UpdateVector;
  std::vector< Refresh * >::const_iterator itUpdate;
  std::vector< Refresh * >::const_iterator endUpdate;

  itList = SortedList.begin();
  endList = SortedList.end();

  for (; itList != endList; ++itList)
    {
      pRefresh = (*itList)->getRefresh();
      itUpdate = UpdateVector.begin();
      endUpdate = UpdateVector.end();

      while (itUpdate != endUpdate && !(*itUpdate)->isEqual(pRefresh)) ++itUpdate;

      if (itUpdate == endUpdate)
        UpdateVector.push_back(pRefresh);
    }

  return UpdateVector;
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

  CModelEntity *const* ppEntity = getStateTemplate().beginIndependent();
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

#include "utilities/CDimension.h"

std::string CModel::printParameterOverview()
{
  std::ostringstream oss;
  CModel* model = this;

  oss << "Initial time: " << model->getInitialTime() << " " << model->getTimeUnitName() << std::endl;

  oss << std::endl;

  size_t i, imax, j, jmax;

  //Compartments
  const CCopasiVector< CCompartment > & comps = model->getCompartments();
  imax = comps.size();

  if (imax)
    {
      oss << "Initial volumes:\n\n";

      for (i = 0; i < imax; ++i)
        oss << comps[i]->getObjectName() << " \t" << comps[i]->getInitialValue()
            << " " << model->getVolumeUnitsDisplayString() << "\n";

      oss << "\n";
    }

  //Species
  const CCopasiVector< CMetab > & metabs = model->getMetabolites();
  imax = metabs.size();

  if (imax)
    {
      oss << "Initial concentrations:\n\n";

      for (i = 0; i < imax; ++i)
        oss << CMetabNameInterface::getDisplayName(model, *metabs[i], false) << " \t"
            << metabs[i]->getInitialConcentration() << " "
            << model->getConcentrationUnitsDisplayString() << "\n";

      oss << "\n";
    }

  //global Parameters
  const CCopasiVector< CModelValue > & params = model->getModelValues();
  imax = params.size();

  if (imax)
    {
      oss << "Initial values of global quantities:\n\n";

      for (i = 0; i < imax; ++i)
        oss << params[i]->getObjectName() << " \t"
            << params[i]->getInitialValue() << "\n";

      oss << "\n";
    }

  //Reactions
  const CCopasiVector< CReaction > & reacs = model->getReactions();
  imax = reacs.size();

  if (imax)
    {
      oss << "Reaction parameters:\n\n";
      CReaction* reac;

      for (i = 0; i < imax; ++i)
        {
          reac = reacs[i];
          oss << reac->getObjectName() << "\n";

          //calculate units
          CFindDimensions units(reac->getFunction(), getQuantityUnit()->isDimensionless(),
                                getVolumeUnit()->isDimensionless(),
                                getTimeUnit()->isDimensionless(),
                                getAreaUnit()->isDimensionless(),
                                getLengthUnit()->isDimensionless());
          units.setUseHeuristics(true);
          units.setChemicalEquation(&reac->getChemEq());
          units.findDimensions(reac->getCompartmentNumber() > 1);

          const CFunctionParameters & params = reac->getFunctionParameters();
          jmax = params.size();

          for (j = 0; j < jmax; ++j)
            if (params[j]->getUsage() == CFunctionParameter::PARAMETER)
              {
                CCopasiObject * obj = CCopasiRootContainer::getKeyFactory()->get(reac->getParameterMappings()[j][0]);

                if (!obj) continue;

                if (reac->isLocalParameter(j))
                  {
                    CCopasiParameter * par = dynamic_cast<CCopasiParameter*>(obj); //must be a CCopasiParameter

                    if (!par) continue; //or rather fatal error?

                    oss << "    " << params[j]->getObjectName() << " \t"
                        << *par->getValue().pDOUBLE << " "
                        << units.getDimensions()[j].getDisplayString(this) << "\n";
                  }
                else
                  {
                    CModelValue * par = dynamic_cast<CModelValue*>(obj); //must be a CModelValue

                    if (!par) continue; //or rather fatal error?

                    oss << "    " << params[j]->getObjectName() << " \t"
                        << "-> " + par->getObjectName()
                        << " (" << units.getDimensions()[j].getDisplayString(this) << ")\n";
                  }
              }

          oss << "\n";
        }
    }

  return oss.str();
}

std::string CModel::getTimeUnitsDisplayString() const
{
  if (mpTimeUnit->isDimensionless())
    return "";

  return mpTimeUnit->getSymbol();
}

std::string CModel::getFrequencyUnitsDisplayString() const
{
  if (mpTimeUnit->isDimensionless())
    return "";

  return std::string("1/") + mpTimeUnit->getSymbol();
}

std::string CModel::getVolumeUnitsDisplayString() const
{
  if (getVolumeUnit()->isDimensionless())
    return "";

  return mpVolumeUnit->getSymbol();
}

std::string CModel::getAreaUnitsDisplayString() const
{
  if (mpAreaUnit->isDimensionless())
    return "";

  return mpAreaUnit->getSymbol();
}

std::string CModel::getLengthUnitsDisplayString() const
{
  if (mpLengthUnit->isDimensionless())
    return "";

  return mpLengthUnit->getSymbol();
}

std::string CModel::getVolumeRateUnitsDisplayString() const
{
  if (getVolumeUnitEnum() == CUnit::dimensionlessVolume)
    {
      if (mpTimeUnit->isDimensionless())
        return "";

      return std::string("1/") + mpTimeUnit->getSymbol();
    }

  if (mpTimeUnit->isDimensionless())
    return mpVolumeUnit->getSymbol();

  return mpVolumeUnit->getSymbol() + "/" + mpTimeUnit->getSymbol();
}

std::string CModel::getConcentrationUnitsDisplayString() const
{
  std::string Units;

  if (mpQuantityUnit->isDimensionless())
    {
      if (getVolumeUnitEnum() == CUnit::dimensionlessVolume)
        return "";

      return std::string("1/") + mpVolumeUnit->getSymbol();
    }

  Units = mpQuantityUnit->getSymbol();

  if (getVolumeUnitEnum() == CUnit::dimensionlessVolume)
    return Units;

  return Units + "/" + mpVolumeUnit->getSymbol();
}

std::string CModel::getConcentrationRateUnitsDisplayString() const
{
  std::string Units;

  if (mpQuantityUnit->isDimensionless())
    {
      Units = "1";

      if (getVolumeUnitEnum() == CUnit::dimensionlessVolume)
        {
          if (mpTimeUnit->isDimensionless())
            return "";

          return Units + "/" + mpTimeUnit->getSymbol();
        }
      else
        {
          if (mpTimeUnit->isDimensionless())
            return Units + "/" + mpVolumeUnit->getSymbol();

          return Units + "/(" + mpVolumeUnit->getSymbol() + "*" + mpTimeUnit->getSymbol() + ")";
        }
    }

  Units = mpQuantityUnit->getSymbol();

  if (getVolumeUnitEnum() == CUnit::dimensionlessVolume)
    {
      if (mpTimeUnit->isDimensionless())
        return Units;

      return Units + "/" + mpTimeUnit->getSymbol();
    }

  if (mpTimeUnit->isDimensionless())
    return Units + "/" + mpVolumeUnit->getSymbol();

  return Units + "/(" + mpVolumeUnit->getSymbol() + "*" + mpTimeUnit->getSymbol() + ")";
}

std::string CModel::getQuantityUnitsDisplayString() const
{
  if (mpQuantityUnit->isDimensionless())
    {
      return "";
    }

  return mpQuantityUnit->getSymbol();
}

std::string CModel::getQuantityRateUnitsDisplayString() const
{
  std::string Units;

  if (mpQuantityUnit->isDimensionless())
    {
      if (mpTimeUnit->isDimensionless())
        return "";

      return std::string("1/") + mpTimeUnit->getSymbol();
    }

  Units = mpQuantityUnit->getSymbol();

  if (mpTimeUnit->isDimensionless())
    return Units;

  return Units + "/" + mpTimeUnit->getSymbol();
}

/****** Below will be removed when the math model completed ******/

void CModel::evaluateRoots(CVectorCore< C_FLOAT64 > & rootValues,
                           const bool & ignoreDiscrete)
{
  return mpMathModel->evaluateRoots(rootValues, ignoreDiscrete);
}

bool CModel::processQueue(const C_FLOAT64 & time,
                          const bool & equality,
                          CProcessQueue::resolveSimultaneousAssignments pResolveSimultaneousAssignments)
{
  return mpMathModel->processQueue(time, equality, pResolveSimultaneousAssignments);
}

void CModel::processRoots(const C_FLOAT64 & time,
                          const bool & equality,
                          const bool & correct,
                          const CVector< C_INT > & roots)
{
  mpMathModel->processRoots(time, equality, correct, roots);

  return;
}

const C_FLOAT64 & CModel::getProcessQueueExecutionTime() const
{
  return mpMathModel->getProcessQueueExecutionTime();
}

size_t CModel::getNumRoots() const
{
  return mpMathModel->getNumRoots();
}

void CModel::calculateRootDerivatives(CVector< C_FLOAT64 > & rootDerivatives)
{
  return mpMathModel->calculateRootDerivatives(rootDerivatives);
}

const CVector< CMathTrigger::CRootFinder * > & CModel::getRootFinders() const
{
  return mpMathModel->getRootFinders();
}

const CMathModel* CModel::getMathModel() const
{return mpMathModel;}

CMathModel* CModel::getMathModel()
{return mpMathModel;}

#ifdef USE_MATH_CONTAINER
const CMathContainer* CModel::getMathContainer() const
{return mpMathContainer;}

CMathContainer* CModel::getMathContainer()
{return mpMathContainer;}
#endif // USE_MATH_CONTAINER
