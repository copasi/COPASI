// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CQPlayerControlWidget.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/09/09 03:39:31 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQPlayerControlWidget_H__
#define CQPlayerControlWidget_H__

#include <qwidget.h>

class QToolButton;

class CQPlayerControlWidget : public QWidget
  {

    Q_OBJECT

  signals:
    void play();
    void pause();
    void stop();
    void forward();
    void backward();
    void step_forward();
    void step_backward();

  private slots:
    void slot_play_clicked();
    void slot_stop_clicked();
    void slot_forward_clicked();
    void slot_backward_clicked();
    void slot_step_forward_clicked();
    void slot_step_backward_clicked();

  protected:
    unsigned int mNumSteps;
    unsigned int mCurrentStep;
    bool mPlaying;

    QToolButton* mpPlayButton;
    QToolButton* mpStopButton;
    QToolButton* mpForwardButton;
    QToolButton* mpBackwardButton;
    QToolButton* mpStepForwardButton;
    QToolButton* mpStepBackwardButton;

  public:
    CQPlayerControlWidget(QWidget* pParent = NULL, const char* name = "");

    void setNumSteps(unsigned int numSteps);
    void setCurrentStep(unsigned int currentStep);
    bool isPlaying() const;

  protected:
    void updateButtons();
  };

#endif // CQPlayerControlWidget_H__
