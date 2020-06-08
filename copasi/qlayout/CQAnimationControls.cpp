// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2013 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <QtCore/QTimer>

#include <copasi/qlayout/CQAnimationControls.h>
#include <copasi/resourcesUI/CQIconResource.h>

CQAnimationControls::CQAnimationControls(QWidget* parent)
  : QWidget(parent)
  , mNumSteps(100)
  , mCurrentStep(0)
  , mShouldLoop(true)
  , mpTimer(new QTimer(this))
{

  setupUi(this);

  cmdBack->setIcon(CQIconResource::icon(CQIconResource::skipBackward));
  cmdForward->setIcon(CQIconResource::icon(CQIconResource::skipForward));
  cmdStepBack->setIcon(CQIconResource::icon(CQIconResource::backward));
  cmdStepForward->setIcon(CQIconResource::icon(CQIconResource::forward));
  cmdPlayPause->setIcon(CQIconResource::icon(CQIconResource::play));
  cmdStop->setIcon(CQIconResource::icon(CQIconResource::stop));

  mpTimer->setInterval(1000 / 10); // 10fps default
  lblDuration->setText(QString::number(mNumSteps));
  connect(mpTimer, SIGNAL(timeout()), this, SLOT(slotStepForward()));
}

void CQAnimationControls::slotChangeInterval(int interval)
{
  mpTimer->setInterval(interval);
}

void CQAnimationControls::setNumSteps(size_t numSteps)
{
  if (mNumSteps == numSteps) return;

  mNumSteps = numSteps;
  sldPosition->setMaximum(numSteps - 1);
  lblCurrent->setText(QString::number(sldPosition->minimum() + 1));
  lblDuration->setText(QString::number(numSteps));
}

void CQAnimationControls::setCurrentStep(size_t currentStep)
{
  if (currentStep < mNumSteps)
    {
      mCurrentStep = currentStep;
    }
  else if (mNumSteps > 0)
    {
      mCurrentStep = mNumSteps - 1;
    }
  else
    {
      mCurrentStep = 0;
    }

  updateButtons();
  updateActions();
}

bool CQAnimationControls::isPlaying() const
{
  return mpTimer->isActive();
}

CQAnimationControls::~CQAnimationControls()
{
}

void CQAnimationControls::slotBack()
{
  emit backward();
  sldPosition->setValue(0);
}

void CQAnimationControls::slotForward()
{
  emit forward();
  sldPosition->setValue(mNumSteps - 1);
}

void CQAnimationControls::slotTogglePlayPause()
{
  bool playing = isPlaying();

  if (playing)
    {
      mpTimer->stop();
      emit pause();
      cmdPlayPause->setIcon(CQIconResource::icon(CQIconResource::play));
    }
  else
    {
      mpTimer->start();
      emit play();
      cmdPlayPause->setIcon(CQIconResource::icon(CQIconResource::pause));
    }
}

void CQAnimationControls::slotStepBack()
{
  emit step_backward();
  sldPosition->setValue(mCurrentStep < 2 ? 0 : --mCurrentStep);
}

void CQAnimationControls::slotStepForward()
{
  emit step_forward();

  int next;

  if (mCurrentStep >= mNumSteps - 1)
    {
      if (mShouldLoop)
        {
          next = 0;
        }
      else
        {
          slotStop();
          return;
        }
    }
  else
    {
      next = ++mCurrentStep;
    }

  sldPosition->setValue(next);
}

void CQAnimationControls::slotStop()
{
  mpTimer->stop();
  cmdPlayPause->setIcon(CQIconResource::icon(CQIconResource::play));
  emit stop();
  sldPosition->setValue(0);
}

void CQAnimationControls::slotShowStep(int step)
{
  mCurrentStep = step;
  lblCurrent->setText(QString::number(step + 1));
  updateButtons();
  updateActions();
  emit showStep(step);
}

void CQAnimationControls::updateButtons()
{
}
void CQAnimationControls::updateActions()
{
}
