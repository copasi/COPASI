// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CQPlayerControlWidget.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/09/09 03:39:31 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQPlayerControlWidget.h"

#include <qtoolbutton.h>
#include <qpixmap.h>
#include <qiconset.h>
#include <qlayout.h>

#include "play.xpm"
#include "stop.xpm"
#include "pause.xpm"
#include "forward.xpm"
#include "backward.xpm"
#include "forward_single.xpm"
#include "backward_single.xpm"

CQPlayerControlWidget::CQPlayerControlWidget(QWidget* pParent, const char* name): QWidget(pParent, name), mNumSteps(0), mCurrentStep(0), mPlaying(false)
{
  QGridLayout* pLayout = new QGridLayout(this, 2, 3);
  this->mpStepBackwardButton = new QToolButton(this);
  this->mpStepBackwardButton->setIconSet(QPixmap(backward_single_xpm));
  pLayout->addWidget(this->mpStepBackwardButton, 0, 0);
  this->mpPlayButton = new QToolButton(this);
  this->mpPlayButton->setIconSet(QPixmap(play_xpm));
  pLayout->addWidget(this->mpPlayButton, 0, 1);
  this->mpStepForwardButton = new QToolButton(this);
  pLayout->addWidget(this->mpStepForwardButton, 0, 2);
  this->mpStepForwardButton->setIconSet(QPixmap(forward_single_xpm));
  this->mpBackwardButton = new QToolButton(this);
  this->mpBackwardButton->setIconSet(QPixmap(backward_xpm));
  pLayout->addWidget(this->mpBackwardButton, 1, 0);
  this->mpStopButton = new QToolButton(this);
  this->mpStopButton->setIconSet(QPixmap(stop_xpm));
  pLayout->addWidget(this->mpStopButton, 1, 1);
  this->mpForwardButton = new QToolButton(this);
  this->mpForwardButton->setIconSet(QPixmap(forward_xpm));
  pLayout->addWidget(this->mpForwardButton, 1, 2);
  this->updateButtons();
  connect(this->mpPlayButton, SIGNAL(clicked()), this, SLOT(slot_play_clicked()));
  connect(this->mpStopButton, SIGNAL(clicked()), this, SLOT(slot_stop_clicked()));
  connect(this->mpForwardButton, SIGNAL(clicked()), this, SLOT(slot_forward_clicked()));
  connect(this->mpBackwardButton, SIGNAL(clicked()), this, SLOT(slot_backward_clicked()));
  connect(this->mpStepForwardButton, SIGNAL(clicked()), this, SLOT(slot_step_forward_clicked()));
  connect(this->mpStepBackwardButton, SIGNAL(clicked()), this, SLOT(slot_step_backward_clicked()));
}

void CQPlayerControlWidget::setNumSteps(unsigned int numSteps)
{
  this->mNumSteps = numSteps;
  this->updateButtons();
}

void CQPlayerControlWidget::setCurrentStep(unsigned int currentStep)
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
}

void CQPlayerControlWidget::slot_play_clicked()
{
  if (this->mPlaying)
    {
      this->mpPlayButton->setIconSet(QPixmap(play_xpm));
      this->mPlaying = !this->mPlaying;
      emit pause();
    }
  else
    {
      this->mpPlayButton->setIconSet(QPixmap(pause_xpm));
      this->mPlaying = !this->mPlaying;
      emit play();
    }
}

void CQPlayerControlWidget::slot_stop_clicked()
{
  this->mCurrentStep = 0;
  this->mPlaying = false;
  this->updateButtons();
  emit stop();
}

void CQPlayerControlWidget::slot_forward_clicked()
{
  this->mCurrentStep = this->mNumSteps - 1;
  this->updateButtons();
  emit forward();
}

void CQPlayerControlWidget::updateButtons()
{
  if (this->mNumSteps < 2)
    {
      // disable all buttons
      if (this->mpPlayButton->isEnabled())
        {
          this->mpPlayButton->setEnabled(FALSE);
          if (this->mPlaying)
            {
              // reset the icon
              this->mpPlayButton->setIconSet(QPixmap(play_xpm));
            }
        }
      if (this->mpStopButton->isEnabled())
        {
          this->mpStopButton->setEnabled(FALSE);
        }
      if (this->mpForwardButton->isEnabled())
        {
          this->mpForwardButton->setEnabled(FALSE);
        }
      if (this->mpStepForwardButton->isEnabled())
        {
          this->mpStepForwardButton->setEnabled(FALSE);
        }
      if (this->mpBackwardButton->isEnabled())
        {
          this->mpBackwardButton->setEnabled(FALSE);
        }
      if (this->mpStepBackwardButton->isEnabled())
        {
          this->mpStepBackwardButton->setEnabled(FALSE);
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
              this->mpPlayButton->setIconSet(QPixmap(play_xpm));
            }
          if (this->mpBackwardButton->isEnabled())
            {
              this->mpBackwardButton->setEnabled(FALSE);
            }
          if (this->mpStepBackwardButton->isEnabled())
            {
              this->mpStepBackwardButton->setEnabled(FALSE);
            }
          if (this->mpPlayButton->isEnabled() == FALSE)
            {
              this->mpPlayButton->setEnabled(TRUE);
            }
          if (this->mpStopButton->isEnabled() == FALSE)
            {
              this->mpStopButton->setEnabled(TRUE);
            }
          if (this->mpForwardButton->isEnabled() == FALSE)
            {
              this->mpForwardButton->setEnabled(TRUE);
            }
          if (this->mpStepForwardButton->isEnabled() == FALSE)
            {
              this->mpStepForwardButton->setEnabled(TRUE);
            }
        }
      else if (this->mCurrentStep == this->mNumSteps - 1)
        {
          // make sure play, forward and step_forward are disabled and all other
          // buttons are enabled
          // reset the icon on the play button
          if (this->mpForwardButton->isEnabled())
            {
              this->mpForwardButton->setEnabled(FALSE);
            }
          if (this->mpStepForwardButton->isEnabled())
            {
              this->mpStepForwardButton->setEnabled(FALSE);
            }
          if (this->mpPlayButton->isEnabled())
            {
              this->mpPlayButton->setIconSet(QPixmap(play_xpm));
              this->mpPlayButton->setEnabled(FALSE);
            }
          if (this->mpBackwardButton->isEnabled() == FALSE)
            {
              this->mpBackwardButton->setEnabled(TRUE);
            }
          if (this->mpStepBackwardButton->isEnabled() == FALSE)
            {
              this->mpStepBackwardButton->setEnabled(TRUE);
            }
          if (this->mpStopButton->isEnabled() == FALSE)
            {
              this->mpStopButton->setEnabled(TRUE);
            }
        }
      else
        {
          // make sure all buttons are enabled
          if (this->mpPlayButton->isEnabled() == FALSE)
            {
              this->mpPlayButton->setEnabled(TRUE);
            }
          if (this->mpStopButton->isEnabled() == FALSE)
            {
              this->mpStopButton->setEnabled(TRUE);
            }
          if (this->mpForwardButton->isEnabled() == FALSE)
            {
              this->mpForwardButton->setEnabled(TRUE);
            }
          if (this->mpBackwardButton->isEnabled() == FALSE)
            {
              this->mpBackwardButton->setEnabled(TRUE);
            }
          if (this->mpStepBackwardButton->isEnabled() == FALSE)
            {
              this->mpStepBackwardButton->setEnabled(TRUE);
            }
          if (this->mpStepForwardButton->isEnabled() == FALSE)
            {
              this->mpStepForwardButton->setEnabled(TRUE);
            }
        }
    }
}

void CQPlayerControlWidget::slot_backward_clicked()
{
  this->mCurrentStep = 0;
  this->updateButtons();
  emit backward();
}

void CQPlayerControlWidget::slot_step_forward_clicked()
{
  if (this->mCurrentStep != this->mNumSteps - 1)
    {
      ++this->mCurrentStep;
    }
  this->updateButtons();
  emit step_forward();
}

void CQPlayerControlWidget::slot_step_backward_clicked()
{
  if (this->mCurrentStep != 0)
    {
      --this->mCurrentStep;
    }
  this->updateButtons();
  emit step_backward();
}

bool CQPlayerControlWidget::isPlaying() const
  {
    return this->mPlaying;
  }
