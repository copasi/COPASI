// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef QANIMATION_WINDOW_H
#define QANIMATION_WINDOW_H

#include <QMainWindow>

#include <UI/CWindowInterface.h>
#include <qlayout/ui_qanimationwindow.h>

class QLayoutScene;
class QCopasiAnimation;
class CCopasiDataModel;
class QCloseEvent;
class QMenu;
class CLayout;
class CQSpringLayoutParameterWindow;
class QAnimationWindow : public CWindowInterface, public Ui::QAnimationWindow
{
  Q_OBJECT
public:
  QAnimationWindow(CLayout* layout, CCopasiDataModel* dataModel = NULL);
  QAnimationWindow();
  virtual ~QAnimationWindow();
  void setScene(QLayoutScene* scene, CCopasiDataModel* dataModel);
  void setAnimation(QCopasiAnimation* animation, CCopasiDataModel* dataModel);
  virtual QMenu *getWindowMenu() const;
public slots:
  void slotShowStep(int);
  void slotExportImage();
  void slotEditSettings();
  void slotSwitchAnimation();
  void slotRandomizeLayout();
  void slotAutoLayout();
  void slotStopLayout();
private:
  void init();
  void toggleUI(bool isPlaying);
protected:
  virtual void closeEvent(QCloseEvent *closeEvent);

  QLayoutScene* mpScene;
  CCopasiDataModel* mpModel;
  QMenu* mpWindowMenu;
  QCopasiAnimation* mAnimation;
  bool mStopLayout;
  bool mIsRunning;
  CQSpringLayoutParameterWindow* mpParameterWindow;
};

#endif // QANIMATION_WINDOW_H
