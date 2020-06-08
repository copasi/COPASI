// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
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

#include "CQPlayerControlWidget.h"

#include <QAction>
#include <QGridLayout>
#include <QIcon>
#include <QLayout>
#include <QPixmap>
#include <QPushButton>

#include <copasi/resourcesUI/CQIconResource.h>

QPushButton *createControl(const CQIconResource::IconID &iconId, int size = 32)
{
  QPushButton *button = new QPushButton;
  button->setFlat(true);
  button->setMinimumSize(size, size);
  button->setMaximumSize(size, size);
  button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  QIcon icon(CQIconResource::icon(iconId));
  button->setIcon(icon);
  button->setIconSize(QSize(size, size));
  return button;
}

CQPlayerControlWidget::CQPlayerControlWidget(QWidget *pParent):
  QWidget(pParent),
  mNumSteps(0),
  mCurrentStep(0),
  mPlaying(false),
  mpPlayButton(NULL),
  mpStopButton(NULL),
  mpForwardButton(NULL),
  mpBackwardButton(NULL),
  mpStepForwardButton(NULL),
  mpStepBackwardButton(NULL),
  mpPlayAction(NULL),
  mpPauseAction(NULL),
  mpStopAction(NULL),
  mpForwardAction(NULL),
  mpBackwardAction(NULL),
  mpStepForwardAction(NULL),
  mpStepBackwardAction(NULL)
{
  QGridLayout *pLayout = new QGridLayout;
  this->mpStepBackwardButton = createControl(CQIconResource::backward);
  pLayout->addWidget(this->mpStepBackwardButton, 0, 0, 1, 1);
  this->mpPlayButton = createControl(CQIconResource::play);
  pLayout->addWidget(this->mpPlayButton, 0, 1, 1, 1);
  this->mpStepForwardButton = createControl(CQIconResource::forward);
  pLayout->addWidget(this->mpStepForwardButton, 0, 2, 1, 1);
  this->mpBackwardButton = createControl(CQIconResource::skipBackward);
  pLayout->addWidget(this->mpBackwardButton, 1, 0, 1, 1);
  this->mpStopButton = createControl(CQIconResource::stop);
  pLayout->addWidget(this->mpStopButton, 1, 1, 1, 1);
  this->mpForwardButton = createControl(CQIconResource::skipForward);
  pLayout->addWidget(this->mpForwardButton, 1, 2, 1, 1);
  this->setLayout(pLayout);
  pLayout->setSizeConstraint(QLayout::SetFixedSize);
  this->createActions();
  this->updateButtons();
  this->updateActions();
  this->setTabOrder(this->mpPlayButton, this->mpStopButton);
  this->setTabOrder(this->mpStopButton, this->mpStepForwardButton);
  this->setTabOrder(this->mpStepForwardButton, this->mpStepBackwardButton);
  this->setTabOrder(this->mpStepBackwardButton, this->mpForwardButton);
  this->setTabOrder(this->mpForwardButton, this->mpBackwardButton);
  connect(this->mpPlayButton, SIGNAL(clicked()), this, SLOT(slot_play_clicked()));
  connect(this->mpStopButton, SIGNAL(clicked()), this, SLOT(slot_stop_clicked()));
  connect(this->mpForwardButton, SIGNAL(clicked()), this, SLOT(slot_forward_clicked()));
  connect(this->mpBackwardButton, SIGNAL(clicked()), this, SLOT(slot_backward_clicked()));
  connect(this->mpStepForwardButton, SIGNAL(clicked()), this, SLOT(slot_step_forward_clicked()));
  connect(this->mpStepBackwardButton, SIGNAL(clicked()), this, SLOT(slot_step_backward_clicked()));
}

void CQPlayerControlWidget::createActions()
{
  this->mpPlayAction = new QAction(CQIconResource::icon(CQIconResource::play), "Play", this);
  connect(this->mpPlayAction, SIGNAL(triggered()), this, SLOT(slot_play_clicked()));
  this->mpPauseAction = new QAction(CQIconResource::icon(CQIconResource::pause), "Pause", this);
  connect(this->mpPauseAction, SIGNAL(triggered()), this, SLOT(slot_pause_clicked()));
  this->mpStopAction = new QAction(CQIconResource::icon(CQIconResource::stop), "Stop", this);
  connect(this->mpStopAction, SIGNAL(triggered()), this, SLOT(slot_stop_clicked()));
  this->mpForwardAction = new QAction(CQIconResource::icon(CQIconResource::skipForward), "Forward", this);
  connect(this->mpForwardAction, SIGNAL(triggered()), this, SLOT(slot_forward_clicked()));
  this->mpBackwardAction = new QAction(CQIconResource::icon(CQIconResource::skipBackward), "Backward", this);
  connect(this->mpBackwardAction, SIGNAL(triggered()), this, SLOT(slot_backward_clicked()));
  this->mpStepForwardAction = new QAction(CQIconResource::icon(CQIconResource::forward), "Step Forward", this);
  connect(this->mpStepForwardAction, SIGNAL(triggered()), this, SLOT(slot_step_forward_clicked()));
  this->mpStepBackwardAction = new QAction(CQIconResource::icon(CQIconResource::backward), "Step Backward", this);
  connect(this->mpStepBackwardAction, SIGNAL(triggered()), this, SLOT(slot_step_backward_clicked()));
}

void CQPlayerControlWidget::setNumSteps(size_t numSteps)
{
  this->mNumSteps = numSteps;
  this->updateButtons();
  this->updateActions();
}

void CQPlayerControlWidget::setCurrentStep(size_t currentStep)
{
  if (currentStep < this->mNumSteps)
    {
      this->mCurrentStep = currentStep;
    }
  else
    {
      this->mCurrentStep = this->mNumSteps - 1;
    }

  this->updateButtons();
  this->updateActions();
}

void CQPlayerControlWidget::slot_pause_clicked()
{
  this->mpPlayButton->setIcon(CQIconResource::icon(CQIconResource::play));
  this->mPlaying = !this->mPlaying;
  this->mpPauseAction->setEnabled(false);
  emit pause();
}

void CQPlayerControlWidget::slot_play_clicked()
{
  if (this->mPlaying)
    {
      this->slot_pause_clicked();
    }
  else
    {
      this->mpPlayButton->setIcon(CQIconResource::icon(CQIconResource::pause));
      this->mPlaying = !this->mPlaying;
      this->mpPauseAction->setEnabled(true);
      emit play();
    }
}

void CQPlayerControlWidget::slot_stop_clicked()
{
  this->mCurrentStep = 0;
  this->mPlaying = false;
  this->updateButtons();
  this->updateActions();
  emit stop();
}

void CQPlayerControlWidget::slot_forward_clicked()
{
  this->mCurrentStep = this->mNumSteps - 1;
  this->updateButtons();
  this->updateActions();
  emit forward();
}

void CQPlayerControlWidget::updateActions()
{
  if (this->mNumSteps < 2)
    {
      // disable all actionsw
      if (this->mpPlayAction->isEnabled())
        {
          this->mpPlayAction->setEnabled(false);
        }

      if (this->mpPauseAction->isEnabled())
        {
          this->mpPauseAction->setEnabled(false);
        }

      if (this->mpStopAction->isEnabled())
        {
          this->mpStopAction->setEnabled(false);
        }

      if (this->mpForwardAction->isEnabled())
        {
          this->mpForwardAction->setEnabled(false);
        }

      if (this->mpStepForwardAction->isEnabled())
        {
          this->mpStepForwardAction->setEnabled(false);
        }

      if (this->mpBackwardAction->isEnabled())
        {
          this->mpBackwardAction->setEnabled(false);
        }

      if (this->mpStepBackwardAction->isEnabled())
        {
          this->mpStepBackwardAction->setEnabled(false);
        }
    }
  else
    {
      if (this->mCurrentStep == 0)
        {
          // make sure backward and step_backward are disabled and all other
          // actions are enabled
          if (!this->mPlaying)
            {
              this->mpPauseAction->setEnabled(false);
            }
          else
            {
              this->mpPauseAction->setEnabled(true);
            }

          if (this->mpBackwardAction->isEnabled())
            {
              this->mpBackwardAction->setEnabled(false);
            }

          if (this->mpStepBackwardAction->isEnabled())
            {
              this->mpStepBackwardAction->setEnabled(false);
            }

          if (this->mpPlayAction->isEnabled() == false)
            {
              this->mpPlayAction->setEnabled(true);
            }

          if (this->mpStopAction->isEnabled() == false)
            {
              this->mpStopAction->setEnabled(true);
            }

          if (this->mpForwardAction->isEnabled() == false)
            {
              this->mpForwardAction->setEnabled(true);
            }

          if (this->mpStepForwardAction->isEnabled() == false)
            {
              this->mpStepForwardAction->setEnabled(true);
            }
        }
      else if (this->mCurrentStep == this->mNumSteps - 1)
        {
          // make sure play, forward and step_forward are disabled and all other
          // actions are enabled
          // reset the icon on the play button
          if (this->mpForwardAction->isEnabled())
            {
              this->mpForwardAction->setEnabled(false);
            }

          if (this->mpStepForwardAction->isEnabled())
            {
              this->mpStepForwardAction->setEnabled(false);
            }

          if (this->mpPlayAction->isEnabled())
            {
              this->mpPlayAction->setEnabled(false);
            }

          if (this->mpPauseAction->isEnabled())
            {
              this->mpPauseAction->setEnabled(false);
            }

          if (this->mpBackwardAction->isEnabled() == false)
            {
              this->mpBackwardAction->setEnabled(true);
            }

          if (this->mpStepBackwardAction->isEnabled() == false)
            {
              this->mpStepBackwardAction->setEnabled(true);
            }

          if (this->mpStopAction->isEnabled() == false)
            {
              this->mpStopAction->setEnabled(true);
            }
        }
      else
        {
          // make sure all buttons are enabled
          if (this->mpPlayAction->isEnabled() == false)
            {
              this->mpPlayAction->setEnabled(true);
            }

          if (this->mpStopAction->isEnabled() == false)
            {
              this->mpStopAction->setEnabled(true);
            }

          if (this->mpForwardAction->isEnabled() == false)
            {
              this->mpForwardAction->setEnabled(true);
            }

          if (this->mpBackwardAction->isEnabled() == false)
            {
              this->mpBackwardAction->setEnabled(true);
            }

          if (this->mpStepBackwardAction->isEnabled() == false)
            {
              this->mpStepBackwardAction->setEnabled(true);
            }

          if (this->mpStepForwardAction->isEnabled() == false)
            {
              this->mpStepForwardAction->setEnabled(true);
            }
        }
    }
}

void CQPlayerControlWidget::updateButtons()
{
  if (this->mNumSteps < 2)
    {
      // disable all buttons
      if (this->mpPlayButton->isEnabled())
        {
          this->mpPlayButton->setEnabled(false);

          if (this->mPlaying)
            {
              // reset the icon
              this->mpPlayButton->setIcon(CQIconResource::icon(CQIconResource::play));
            }
        }

      if (this->mpStopButton->isEnabled())
        {
          this->mpStopButton->setEnabled(false);
        }

      if (this->mpForwardButton->isEnabled())
        {
          this->mpForwardButton->setEnabled(false);
        }

      if (this->mpStepForwardButton->isEnabled())
        {
          this->mpStepForwardButton->setEnabled(false);
        }

      if (this->mpBackwardButton->isEnabled())
        {
          this->mpBackwardButton->setEnabled(false);
        }

      if (this->mpStepBackwardButton->isEnabled())
        {
          this->mpStepBackwardButton->setEnabled(false);
        }
    }
  else
    {
      if (this->mCurrentStep == 0)
        {
          // make sure backward and step_backward are disabled and all other
          // buttons are enabled
          if (!this->mPlaying)
            {
              this->mpPlayButton->setIcon(CQIconResource::icon(CQIconResource::play));
            }
          else
            {
              this->mpPlayButton->setIcon(CQIconResource::icon(CQIconResource::pause));
            }

          if (this->mpBackwardButton->isEnabled())
            {
              this->mpBackwardButton->setEnabled(false);
            }

          if (this->mpStepBackwardButton->isEnabled())
            {
              this->mpStepBackwardButton->setEnabled(false);
            }

          if (this->mpPlayButton->isEnabled() == false)
            {
              this->mpPlayButton->setEnabled(true);
            }

          if (this->mpStopButton->isEnabled() == false)
            {
              this->mpStopButton->setEnabled(true);
            }

          if (this->mpForwardButton->isEnabled() == false)
            {
              this->mpForwardButton->setEnabled(true);
            }

          if (this->mpStepForwardButton->isEnabled() == false)
            {
              this->mpStepForwardButton->setEnabled(true);
            }
        }
      else if (this->mCurrentStep == this->mNumSteps - 1)
        {
          // make sure play, forward and step_forward are disabled and all other
          // buttons are enabled
          // reset the icon on the play button
          if (this->mpForwardButton->isEnabled())
            {
              this->mpForwardButton->setEnabled(false);
            }

          if (this->mpStepForwardButton->isEnabled())
            {
              this->mpStepForwardButton->setEnabled(false);
            }

          if (this->mpPlayButton->isEnabled())
            {
              this->mpPlayButton->setIcon(CQIconResource::icon(CQIconResource::play));
              this->mpPlayButton->setEnabled(false);
            }

          if (this->mpBackwardButton->isEnabled() == false)
            {
              this->mpBackwardButton->setEnabled(true);
            }

          if (this->mpStepBackwardButton->isEnabled() == false)
            {
              this->mpStepBackwardButton->setEnabled(true);
            }

          if (this->mpStopButton->isEnabled() == false)
            {
              this->mpStopButton->setEnabled(true);
            }
        }
      else
        {
          // make sure all buttons are enabled
          if (this->mpPlayButton->isEnabled() == false)
            {
              this->mpPlayButton->setEnabled(true);
            }

          if (this->mpStopButton->isEnabled() == false)
            {
              this->mpStopButton->setEnabled(true);
            }

          if (this->mpForwardButton->isEnabled() == false)
            {
              this->mpForwardButton->setEnabled(true);
            }

          if (this->mpBackwardButton->isEnabled() == false)
            {
              this->mpBackwardButton->setEnabled(true);
            }

          if (this->mpStepBackwardButton->isEnabled() == false)
            {
              this->mpStepBackwardButton->setEnabled(true);
            }

          if (this->mpStepForwardButton->isEnabled() == false)
            {
              this->mpStepForwardButton->setEnabled(true);
            }
        }
    }
}

void CQPlayerControlWidget::slot_backward_clicked()
{
  this->mCurrentStep = 0;
  this->updateButtons();
  this->updateActions();
  emit backward();
}

void CQPlayerControlWidget::slot_step_forward_clicked()
{
  if (this->mCurrentStep != this->mNumSteps - 1)
    {
      ++this->mCurrentStep;
    }

  this->updateButtons();
  this->updateActions();
  emit step_forward();
}

void CQPlayerControlWidget::slot_step_backward_clicked()
{
  if (this->mCurrentStep != 0)
    {
      --this->mCurrentStep;
    }

  this->updateButtons();
  this->updateActions();
  emit step_backward();
}

bool CQPlayerControlWidget::isPlaying() const
{
  return this->mPlaying;
}

QAction *CQPlayerControlWidget::getPlayAction()
{
  return this->mpPlayAction;
}

QAction *CQPlayerControlWidget::getPauseAction()
{
  return this->mpPauseAction;
}

QAction *CQPlayerControlWidget::getStopAction()
{
  return this->mpStopAction;
}

QAction *CQPlayerControlWidget::getForwardAction()
{
  return this->mpForwardAction;
}

QAction *CQPlayerControlWidget::getBackwardAction()
{
  return this->mpBackwardAction;
}

QAction *CQPlayerControlWidget::getStepForwardAction()
{
  return this->mpStepForwardAction;
}

QAction *CQPlayerControlWidget::getStepBackwardAction()
{
  return this->mpStepBackwardAction;
}
