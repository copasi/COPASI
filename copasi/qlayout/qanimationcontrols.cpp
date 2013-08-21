// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <QTimer>

#include <qlayout/qanimationcontrols.h>
#include <resourcesUI/CQIconResource.h>

QAnimationControls::QAnimationControls(QWidget* parent)
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

void QAnimationControls::slotChangeInterval(int interval)
{
  mpTimer->setInterval(interval);
}

void QAnimationControls::setNumSteps(size_t numSteps)
{
  if (mNumSteps == numSteps) return;

  mNumSteps = numSteps;
  sldPosition->setMaximum(numSteps - 1);
  lblCurrent->setText(QString::number(sldPosition->minimum() + 1));
  lblDuration->setText(QString::number(numSteps));
}

void QAnimationControls::setCurrentStep(size_t currentStep)
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

bool QAnimationControls::isPlaying() const
{
  return mpTimer->isActive();
}

QAnimationControls::~QAnimationControls()
{
}

void QAnimationControls::slotBack()
{
  emit backward();
  sldPosition->setValue(0);
}

void QAnimationControls::slotForward()
{
  emit forward();
  sldPosition->setValue(mNumSteps - 1);
}

void QAnimationControls::slotTogglePlayPause()
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

void QAnimationControls::slotStepBack()
{
  emit step_backward();
  sldPosition->setValue(mCurrentStep < 2 ? 0 : --mCurrentStep);
}

void QAnimationControls::slotStepForward()
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

void QAnimationControls::slotStop()
{
  mpTimer->stop();
  cmdPlayPause->setIcon(CQIconResource::icon(CQIconResource::play));
  emit stop();
  sldPosition->setValue(0);
}

void QAnimationControls::slotShowStep(int step)
{
  mCurrentStep = step;
  lblCurrent->setText(QString::number(step + 1));
  updateButtons();
  updateActions();
  emit showStep(step);
}

void QAnimationControls::updateButtons()
{
}
void QAnimationControls::updateActions()
{
}
