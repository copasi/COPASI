// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
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

#ifndef QANIMATION_WINDOW_H
#define QANIMATION_WINDOW_H

#include <QMainWindow>
#include <QtCore/QSharedPointer>

#include <copasi/UI/CWindowInterface.h>

#include <copasi/layout/CLayoutState.h>
#include <copasi/qlayout/ui_CQAnimationWindow.h>

class CQLayoutScene;
class CQCopasiAnimation;
class CDataModel;
class QCloseEvent;
class QDockWidget;
class QMenu;
class CLayout;
class CQLayoutThread;
class CQElementProperties;

class CQAnimationWindow : public CWindowInterface, public Ui::CQAnimationWindow
{
  Q_OBJECT
public:
  CQAnimationWindow(CLayout* layout, CDataModel* dataModel = NULL);
  CQAnimationWindow();
  virtual ~CQAnimationWindow();
  void setScene(CQLayoutScene* scene, CDataModel* dataModel);
  void setAnimation(CQCopasiAnimation* animation, CDataModel* dataModel);
  virtual QMenu *getWindowMenu() const;
public slots:
  void slotShowStep(int);
  void slotExportImage();
  void slotEditSettings();
  void slotSwitchAnimation();
  void slotRandomizeLayout();
  void slotAutoLayout();
  void slotStopLayout();
  void slotLayoutStateChanged(QSharedPointer<CLayoutState> state);
private:
  void init();
  void toggleUI(bool isPlaying);
  QDockWidget * createPropertiesWidget();

protected:
  virtual void closeEvent(QCloseEvent *closeEvent);

  CQLayoutScene* mpScene;
  CDataModel* mpModel;
  QMenu* mpWindowMenu;
  CQCopasiAnimation* mAnimation;
  CQLayoutThread* mpLayoutThread;
  CLayout* mpCopy;
  CQElementProperties* mpProperties;
};

#endif // QANIMATION_WINDOW_H
