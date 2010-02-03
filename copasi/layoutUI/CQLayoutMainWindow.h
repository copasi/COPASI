// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CQLayoutMainWindow.h,v $
//   $Revision: 1.51 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2010/02/03 13:53:00 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef SIMGUI_H_
#define SIMGUI_H_
#include <QMainWindow>
#include <QString>
#include <QIcon>

#include <string>

#include "CDataEntity.h"
#include "CVisParameters.h"
#include "copasi.h"

class CLayout;
class CQCurrentValueTable;
class CQGLViewport;
class CQParaPanel;
class CQPlayerControlWidget;
class CVisParameters;
class QAction;
class QActionGroup;
class QCloseEvent;
class QComboBox;
class QFrame;
class QMenu;
class QSplitter;
class QToolBar;
class QwtSlider;

class CQLayoutMainWindow : public QMainWindow
{

  Q_OBJECT      // must include this if you use Qt signals/slots

signals:
  void signal_close(const CQLayoutMainWindow* pWindow);

public:
  CQLayoutMainWindow(CLayout* pLayout = NULL);
  void setIndividualScaling();
  void setGlobalScaling();
  void setSizeMode();
  void setColorMode();
  void setValueOnSlider(C_INT32);
  void insertValueTable(CDataEntity dataSet);
  void updateValueTable(CDataEntity dataSet);
  void setMinValue(C_INT32 minNdSize); // set minimum possible node size
  void setMaxValue(C_INT32 maxNdSize); // set maximum possible node size
  void setMinAndMaxValue(C_INT32 minNdSize, C_INT32 maxNdSize);
  void setFontSizeForLabels(C_INT32 size);
  bool getAnimationRunning();
  void setAnimationRunning(bool animationRunningP);
  void setMinNodeSize(C_FLOAT64 minNdSize);
  void setMaxNodeSize(C_FLOAT64 minNdSize);
  C_FLOAT64 getMinNodeSize();
  C_FLOAT64 getMaxNodeSize();
  C_INT32 getStepsPerSecond();
  void setStepsPerSecond(C_INT16 val);
  CVisParameters::SCALING_MODE getScalingMode();
  CVisParameters::MAPPING_MODE getMappingMode();
  C_INT16 getFontSize();
  C_INT32 getCurrentStep();
  void addItemInAnimation(std::string s);
  void removeItemInAnimation(std::string s);

protected:
  void closeEvent(QCloseEvent *event);
  void setZoomFactor(QString s);

private slots:
  void loadSBMLFile();
  void loadData();
  void showAnimation();
  void saveImage();
  void closeApplication();
  void mapLabelsToCircles();
  void mapLabelsToRectangles();
  void changeMinMaxNodeSizes();
  void changeFontSize();
  void showStep(double i);
  void startAnimation();
  void pauseAnimation();
  void stopAnimation();
  void forwardAnimation();
  void backwardAnimation();
  void stepForwardAnimation();
  void stepBackwardAnimation();
  void slotResetView();
  void slotZoomItemActivated(QAction* pAction);
  void slotActivated(int);
  void slotZoomIn();
  void slotZoomOut();
  void slotValueTableToggled(bool checked);
  void slotParameterTableToggled(bool checked);
  void slotPlayerControlToggled(bool checked);
  void slotToolbarToggled(bool checked);
  void slotLoopActivated(bool checked);
  void parameterTableValueChanged(int row);

public slots:
  void changeStepValue(C_INT32 i);
  void endOfAnimationReached();

private:
  void createActions();
  void createMenus();
  bool maybeSave();
  QIcon createStartIcon();
  QIcon createStopIcon();

  CVisParameters *mpVisParameters;
  QMenu *mpFileMenu;
  QMenu *mpOptionsMenu;
  QMenu *mpLabelShapeMenu;
  QMenu *mpViewMenu;
  QMenu *mpZoomMenu;
  QMenu *mpPlayMenu;

  QAction *mpCreatePicture;
  QAction *mpOpenSBMLFile;
  QAction *mpCloseAction;
  QAction *mpRectangularShape;
  QAction *mpCircularShape;
  QAction *mpMimaNodeSizes;
  QAction *mpSFontSize;
  QAction *mpLoadDataAction;

  CQParaPanel *mpParaPanel;
  CQCurrentValueTable *mpValTable;
  QSplitter* mpSplitter;
  CQGLViewport *mpGLViewport;
  QwtSlider *mpTimeSlider;

  QFrame *mpFrame;
  QFrame *mpMainBox;

  QFrame *mpInfoBox;

  CQPlayerControlWidget* mpControlWidget;

  bool mDataPresent; // shows whether time series data already load
  QString mCurrentPlace;
  QToolBar* mpToolbar;
  QComboBox* mpZoomComboBox;
  bool mLooping;
  QAction* mpLoopItemAction;
  QAction* mpValueTableAction;
  QAction* mpParameterTableAction;
  QActionGroup* mpZoomActionGroup;
  CLayout* mpLayout;
};

#endif /*SIMGUI_H_*/
