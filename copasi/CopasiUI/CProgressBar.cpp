/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CProgressBar.cpp,v $
   $Revision: 1.7 $
   $Name:  $
   $Author: stupe $ 
   $Date: 2004/11/17 17:26:42 $
   End CVS Header */

#include <qprogressdialog.h>
#include <qapplication.h>

#include "copasi.h"
#include "qtUtilities.h"
#include "CProgressBar.h"
#include "DataModelGUI.h"

CProgressBar::CProgressBar(DataModelGUI* dm)
    : mpWidget(NULL),
    mProgress(0),
    mDataModel(dm)
{}

bool CProgressBar::init(C_INT32 maxSteps, const std::string & text, bool cancelButton)
{
  if (!mpWidget)
    {
      if (cancelButton)
        mpWidget = new QProgressDialog(FROM_UTF8(text), "Stop", maxSteps,
                                       NULL, "progress_bar", FALSE);
      else
        mpWidget = new QProgressDialog(FROM_UTF8(text), 0, maxSteps,
                                       NULL, "progress_bar", FALSE);
    }
  else
    {
      mpWidget->reset();
      mpWidget->setLabelText(FROM_UTF8(text));
      mpWidget->setTotalSteps(maxSteps);

      if (cancelButton)
        mpWidget->setCancelButtonText("Stop");
      else
        mpWidget->setCancelButtonText(0);
    }

  mpWidget->setMinimumDuration(0); //
  mpWidget->setProgress(0);
  mProgress = 0;
  mDataModel->getQApp()->processEvents();

  //std::cout << "ProgressBar: init" << std::endl;
  return true;
}

bool CProgressBar::reInit(C_INT32 maxSteps, const std::string & text)
{
  mpWidget->setLabelText(FROM_UTF8(text));
  if (maxSteps) mpWidget->setTotalSteps(maxSteps);
  mDataModel->getQApp()->processEvents();

  //std::cout << "ProgressBar: reInit" << std::endl;
  return mpWidget->wasCanceled();
}

bool CProgressBar::progress(C_INT32 steps)
{
  if (steps == -1)
    {
      mpWidget->setProgress(++mProgress);
    }
  else
    {
      mpWidget->setProgress(steps);
      mProgress = steps;
    }

  mDataModel->getQApp()->processEvents();
  //std::cout << "ProgressBar: progress... " << steps << std::endl;
  return mpWidget->wasCanceled();
}

bool CProgressBar::finish()
{
  mpWidget->setProgress(mpWidget->totalSteps());
  mpWidget->reset();
  //std::cout << "ProgressBar: finish" << std::endl;
  return true;
}
