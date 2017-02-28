// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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

#ifndef CQPlayerControlWidget_H__
#define CQPlayerControlWidget_H__

#include <QWidget>

class QAction;
class QPushButton;

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
  void slot_pause_clicked();
  void slot_stop_clicked();
  void slot_forward_clicked();
  void slot_backward_clicked();
  void slot_step_forward_clicked();
  void slot_step_backward_clicked();

protected:
  size_t mNumSteps;
  size_t mCurrentStep;
  bool mPlaying;

  QPushButton* mpPlayButton;
  QPushButton* mpStopButton;
  QPushButton* mpForwardButton;
  QPushButton* mpBackwardButton;
  QPushButton* mpStepForwardButton;
  QPushButton* mpStepBackwardButton;

  QAction* mpPlayAction;
  QAction* mpPauseAction;
  QAction* mpStopAction;
  QAction* mpForwardAction;
  QAction* mpBackwardAction;
  QAction* mpStepForwardAction;
  QAction* mpStepBackwardAction;

public:
  CQPlayerControlWidget(QWidget* pParent = NULL);

  void setNumSteps(size_t numSteps);
  void setCurrentStep(size_t currentStep);
  bool isPlaying() const;

  QAction* getPlayAction();
  QAction* getPauseAction();
  QAction* getStopAction();
  QAction* getForwardAction();
  QAction* getBackwardAction();
  QAction* getStepForwardAction();
  QAction* getStepBackwardAction();

protected:
  void updateButtons();
  void updateActions();
  void createActions();
};

#endif // CQPlayerControlWidget_H__
