/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQFittingResult.ui.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/03/22 16:52:55 $
   End CVS Header */

/****************************************************************************
 ** ui.h extension file, included from the uic-generated form implementation.
 **
 ** If you want to add, delete, or rename functions or slots, use
 ** Qt Designer to update this file, preserving your code.
 **
 ** You should not define a constructor or destructor in this file.
 ** Instead, write your code in functions called init() and destroy().
 ** These will automatically be called by the form's constructor and
 ** destructor.
 *****************************************************************************/

#include "copasi.h"

#include "qheader.h"

#include "copasiDataModel/CCopasiDataModel.h"
 #include "parameterFitting/CFitTask.h"
 #include "parameterFitting/CFitProblem.h"
 #include "parameterFitting/CFitItem.h"
 #include "parameterFitting/CExperimentSet.h"
 #include "parameterFitting/CExperiment.h"

#include "qtUtilities.h"

void CQFittingResult::init()
{
  unsigned C_INT32 i, imax;

  // Set up the parameters table
  mpParameters->setNumCols(mpParameters->numCols() + 1);
  mpParameters->horizontalHeader()->setLabel(mpParameters->numCols() - 1, tr("Parameter"));
  mpParameters->setNumCols(mpParameters->numCols() + 1);
  mpParameters->horizontalHeader()->setLabel(mpParameters->numCols() - 1, tr("Value"));
  mpParameters->setNumCols(mpParameters->numCols() + 1);
  mpParameters->horizontalHeader()->setLabel(mpParameters->numCols() - 1, tr("Relative Error [%]"));
  mpParameters->setNumCols(mpParameters->numCols() + 1);
  mpParameters->horizontalHeader()->setLabel(mpParameters->numCols() - 1, tr("Std. Deviation"));
  mpParameters->setNumCols(mpParameters->numCols() + 1);
  mpParameters->horizontalHeader()->setLabel(mpParameters->numCols() - 1, tr("Gradient"));
  mpParameters->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)7, (QSizePolicy::SizeType)5, 0, 0, mpParameters->sizePolicy().hasHeightForWidth()));
  mpParameters->setNumRows(0);
  mpParameters->setNumCols(5);
  mpParameters->setReadOnly(TRUE);

  for (i = 0, imax = mpParameters->numCols(); i != imax; i++)
    mpParameters->adjustColumn(i);

  // Set up the experiments table
  mpExperiments->setNumCols(mpExperiments->numCols() + 1);
  mpExperiments->horizontalHeader()->setLabel(mpExperiments->numCols() - 1, tr("Experiment"));
  mpExperiments->setNumCols(mpExperiments->numCols() + 1);
  mpExperiments->horizontalHeader()->setLabel(mpExperiments->numCols() - 1, tr("Objective Value"));
  mpExperiments->setNumCols(mpExperiments->numCols() + 1);
  mpExperiments->horizontalHeader()->setLabel(mpExperiments->numCols() - 1, tr("Root Mean Square"));
  mpExperiments->setNumCols(mpExperiments->numCols() + 1);
  mpExperiments->horizontalHeader()->setLabel(mpExperiments->numCols() - 1, tr("Error Mean"));
  mpExperiments->setNumCols(mpExperiments->numCols() + 1);
  mpExperiments->horizontalHeader()->setLabel(mpExperiments->numCols() - 1, tr("Error Mean Std. Deviation"));
  mpExperiments->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)7, (QSizePolicy::SizeType)5, 0, 0, mpExperiments->sizePolicy().hasHeightForWidth()));
  mpExperiments->setNumRows(0);
  mpExperiments->setNumCols(5);
  mpExperiments->setReadOnly(TRUE);

  for (i = 0, imax = mpExperiments->numCols(); i != imax; i++)
    mpExperiments->adjustColumn(i);

  // Set up the experiments table
  mpValues->setNumCols(mpValues->numCols() + 1);
  mpValues->horizontalHeader()->setLabel(mpValues->numCols() - 1, tr("Fitted Value"));
  mpValues->setNumCols(mpValues->numCols() + 1);
  mpValues->horizontalHeader()->setLabel(mpValues->numCols() - 1, tr("Objective Value"));
  mpValues->setNumCols(mpValues->numCols() + 1);
  mpValues->horizontalHeader()->setLabel(mpValues->numCols() - 1, tr("Root Mean Square"));
  mpValues->setNumCols(mpValues->numCols() + 1);
  mpValues->horizontalHeader()->setLabel(mpValues->numCols() - 1, tr("Error Mean"));
  mpValues->setNumCols(mpValues->numCols() + 1);
  mpValues->horizontalHeader()->setLabel(mpValues->numCols() - 1, tr("Error Mean Std. Deviation"));
  mpValues->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)7, (QSizePolicy::SizeType)5, 0, 0, mpValues->sizePolicy().hasHeightForWidth()));
  mpValues->setNumRows(0);
  mpValues->setNumCols(5);
  mpValues->setReadOnly(TRUE);

  for (i = 0, imax = mpValues->numCols(); i != imax; i++)
    mpValues->adjustColumn(i);
}

bool CQFittingResult::update(ListViews::ObjectType /* objectType */,
                             ListViews::Action /* action */,
                             const std::string & /* key */)
{
  // :TODO:
  return true;
}

bool CQFittingResult::leave()
{
  // :TODO:
  return true;
}

bool CQFittingResult::enter(const std::string & /* key */)
{
  mpTask =
    dynamic_cast<CFitTask *>((*CCopasiDataModel::Global->getTaskList())["Parameter Estimation"]);
  if (!mpTask) return false;

  mpProblem = dynamic_cast<const CFitProblem *>(mpTask->getProblem());
  if (!mpProblem) return false;

  mpMain->load(mpProblem);

  unsigned C_INT32 i, imax;

  // Loop over the optimization items
  const std::vector< COptItem * > & Items = mpProblem->getOptItemList();
  const CVector< C_FLOAT64 > & Solutions = mpProblem->getSolutionVariables();
  const CVector< C_FLOAT64 > & StdDeviations = mpProblem->getVariableStdDeviations();
  const CVector< C_FLOAT64 > & Gradients = mpProblem->getVariableGradients();

  imax = Items.size();
  if (mpProblem->getFunctionEvaluations() == 0)
    imax = 0;

  mpParameters->setNumRows(imax);
  for (i = 0; i != imax; i++)
    {
      const CCopasiObject *pObject =
        RootContainer.getObject(Items[i]->getObjectCN());
      if (pObject)
        {
          std::string Experiments =
            static_cast<CFitItem *>(Items[i])->getExperiments();

          if (Experiments != "")
            Experiments = "; {" + Experiments + "}";

          mpParameters->setText(i, 0, FROM_UTF8(pObject->getObjectDisplayName() + Experiments));
        }
      else
        mpParameters->setText(i, 0, "Not Found");

      const C_FLOAT64 & Solution = Solutions[i];
      mpParameters->setText(i, 1, QString::number(Solution));
      const C_FLOAT64 & StdDeviation = StdDeviations[i];
      mpParameters->setText(i, 2, QString::number(fabs(100.0 * StdDeviation / Solution)));
      mpParameters->setText(i, 3, QString::number(StdDeviation));
      mpParameters->setText(i, 4, QString::number(Gradients[i]));
    }

  for (i = 0, imax = mpParameters->numCols(); i != imax; i++)
    mpParameters->adjustColumn(i);

  // Loop over the experiments
  const CExperimentSet & Experiments = mpProblem->getExperiementSet();

  imax = Experiments.size();
  if (mpProblem->getFunctionEvaluations() == 0)
    imax = 0;

  mpExperiments->setNumRows(imax);
  for (i = 0; i != imax; i++)
    {
      const CExperiment & Experiment = * Experiments.getExperiment(i);
      mpExperiments->setText(i, 0, FROM_UTF8(Experiment.getObjectName()));
      mpExperiments->setText(i, 1, QString::number(Experiment.getObjectiveValue()));
      mpExperiments->setText(i, 2, QString::number(Experiment.getRMS()));

      mpExperiments->setText(i, 3, QString::number(Experiment.getErrorMean()));
      mpExperiments->setText(i, 4, QString::number(Experiment.getErrorMeanSD()));
    }

  for (i = 0, imax = mpExperiments->numCols(); i != imax; i++)
    mpExperiments->adjustColumn(i);

  // Loop over the dependent objects
  imax = Experiments.getDependentObjects().size();
  if (mpProblem->getFunctionEvaluations() == 0)
    imax = 0;

  mpValues->setNumRows(imax);
  for (i = 0; i != imax; i++)
    {
      const CCopasiObject * pObject = Experiments.getDependentObjects()[i];
      if (pObject)
        mpValues->setText(i, 0, FROM_UTF8(pObject->getObjectDisplayName()));
      else
        mpValues->setText(i, 0, "Not Found");

      mpValues->setText(i, 1, QString::number(Experiments.getDependentObjectiveValues()[i]));
      mpValues->setText(i, 2, QString::number(Experiments.getDependentRMS()[i]));

      mpValues->setText(i, 3, QString::number(Experiments.getDependentErrorMean()[i]));
      mpValues->setText(i, 4, QString::number(Experiments.getDependentErrorMeanSD()[i]));
    }

  for (i = 0, imax = mpValues->numCols(); i != imax; i++)
    mpValues->adjustColumn(i);

  // Fill correlation matrix
  imax = Items.size();
  if (mpProblem->getFunctionEvaluations() == 0)
    imax = 0;

  mpCorrelations->setNumRows(imax);
  mpCorrelations->setNumCols(imax);

  // Update the table headers
  for (i = 0; i != imax; i++)
    {
      const CCopasiObject *pObject =
        RootContainer.getObject(Items[i]->getObjectCN());

      QHeader * pVerticalHeader = mpCorrelations->verticalHeader();
      QHeader * pHorizontalHeader = mpCorrelations->horizontalHeader();

      if (pObject)
        {
          std::string Experiments =
            static_cast<CFitItem *>(Items[i])->getExperiments();

          if (Experiments != "")
            {
              Experiments = "{" + Experiments + "}";
              pVerticalHeader->setLabel(i, FROM_UTF8(pObject->getObjectDisplayName() + "; " + Experiments));
              pHorizontalHeader->setLabel(i, FROM_UTF8(pObject->getObjectDisplayName() + "\n" + Experiments));
            }
          else
            {
              pVerticalHeader->setLabel(i, FROM_UTF8(pObject->getObjectDisplayName()));
              pHorizontalHeader->setLabel(i, FROM_UTF8(pObject->getObjectDisplayName()));
            }
        }
      else
        {
          pVerticalHeader->setLabel(i, "Not Found");
          pHorizontalHeader->setLabel(i, "Not Found");
        }
    }

  // Fill the table
  const C_FLOAT64 * pCorrelation = mpProblem->getVariableCorrelations().array();
  unsigned C_INT32 j;
  for (i = 0; i != imax; i++)
    for (j = 0; j != imax; j++)
      mpCorrelations->setText(i, j, QString::number(*pCorrelation++));

  for (i = 0; i != imax; i++)
    mpCorrelations->adjustColumn(i);

  return true;
}

void CQFittingResult::slotSave(void)
{}
